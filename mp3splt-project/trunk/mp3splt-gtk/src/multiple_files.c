/**********************************************************
 *
 * mp3splt-gtk -- utility based on mp3splt,
 *                for mp3/ogg splitting without decoding
 *
 * Copyright: (C) 2005-2012 Alexandru Munteanu
 * Contact: io_fx@yahoo.fr
 *
 * http://mp3splt.sourceforge.net/
 *
 *********************************************************/

/**********************************************************
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 *
 *********************************************************/

/*!********************************************************
 * \file 
 * Batch processing internals
 *
 * this file is for management for the the multiple files
 * mode that currently allows only for batch processing.
 *********************************************************/

#include "multiple_files.h"

#define MY_GTK_RESPONSE 200

//!Create the model for the batch processing file list
static GtkTreeModel *create_multiple_files_model()
{
  GtkListStore *model =
    gtk_list_store_new(MULTIPLE_FILES_COLUMNS, G_TYPE_STRING, G_TYPE_STRING);
  return GTK_TREE_MODEL(model);
}

static GtkTreeView *create_multiple_files_tree()
{
  return GTK_TREE_VIEW(gtk_tree_view_new_with_model(create_multiple_files_model()));
}

static void create_multiple_files_columns(GtkTreeView *multiple_files_tree)
{
  GtkCellRendererText *renderer = GTK_CELL_RENDERER_TEXT(gtk_cell_renderer_text_new());
  GtkTreeViewColumn *filename_column = gtk_tree_view_column_new_with_attributes 
    (_("Complete filename"), GTK_CELL_RENDERER(renderer), "text", MULTIPLE_COL_FILENAME, NULL);
  gtk_tree_view_insert_column(multiple_files_tree,
      GTK_TREE_VIEW_COLUMN(filename_column), MULTIPLE_COL_FILENAME);

  gtk_tree_view_column_set_alignment(GTK_TREE_VIEW_COLUMN(filename_column), 0.5);
  gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(filename_column),
      GTK_TREE_VIEW_COLUMN_AUTOSIZE);
  gtk_tree_view_column_set_sort_column_id(filename_column, MULTIPLE_COL_FILENAME);
}

static void multiple_files_open_button_event(GtkWidget *widget, gpointer data)
{
  gtk_dialog_response(GTK_DIALOG(data), MY_GTK_RESPONSE);
}

static void multiple_files_add_button_event(GtkWidget *widget, ui_state *ui)
{
  GtkWidget *file_chooser = gtk_file_chooser_dialog_new(_("Choose file or directory"),
      NULL,
      GTK_FILE_CHOOSER_ACTION_OPEN,
      GTK_STOCK_CANCEL,
      GTK_RESPONSE_CANCEL,
      NULL);

  wh_set_browser_directory_handler(ui, file_chooser);

  GtkWidget *button = gtk_dialog_add_button(GTK_DIALOG(file_chooser),
      GTK_STOCK_ADD, MY_GTK_RESPONSE);
  gtk_button_set_use_stock(GTK_BUTTON(button), TRUE);
  g_signal_connect(G_OBJECT(button), "clicked",
      G_CALLBACK(multiple_files_open_button_event), file_chooser);
  g_signal_connect(G_OBJECT(file_chooser), "file-activated",
      G_CALLBACK(multiple_files_open_button_event), file_chooser);

  gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(file_chooser), TRUE);

  //mp3 & ogg filter
  GtkFileFilter *our_filter = gtk_file_filter_new();
  gtk_file_filter_set_name(our_filter, _("mp3 and ogg files (*.mp3 *.ogg)"));
  gtk_file_filter_add_pattern(our_filter, "*.mp3");
  gtk_file_filter_add_pattern(our_filter, "*.MP3");
  gtk_file_filter_add_pattern(our_filter, "*.ogg");
  gtk_file_filter_add_pattern(our_filter, "*.OGG");
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), our_filter);
  //mp3 filter
  our_filter = gtk_file_filter_new();
  gtk_file_filter_set_name(our_filter, _("mp3 files (*.mp3)"));
  gtk_file_filter_add_pattern(our_filter, "*.mp3");
  gtk_file_filter_add_pattern(our_filter, "*.MP3");
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), our_filter);
  //ogg filter
  our_filter = gtk_file_filter_new();
  gtk_file_filter_set_name(our_filter, _("ogg files (*.ogg)"));
  gtk_file_filter_add_pattern(our_filter, "*.ogg");
  gtk_file_filter_add_pattern(our_filter, "*.OGG");
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), our_filter);

  //all files filter
  our_filter = gtk_file_filter_new();
  gtk_file_filter_set_name(our_filter, _("All Files"));
  gtk_file_filter_add_pattern(our_filter, "*");
  gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), our_filter);

  if (gtk_dialog_run(GTK_DIALOG(file_chooser)) == MY_GTK_RESPONSE)
  {
    GSList *files = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(file_chooser));
    if (!files)
    {
      gtk_widget_destroy(file_chooser);
      return;
    }

    GtkTreeModel *model = gtk_tree_view_get_model(ui->gui->multiple_files_tree);
    while (files)
    {
      gchar *filename = files->data;

      int err = SPLT_OK;
      int num_of_files_found = 0;
      char **splt_filenames =
        mp3splt_find_filenames(ui->mp3splt_state, filename, &num_of_files_found, &err);

      if (splt_filenames)
      {
        int i = 0;
        for (i = 0;i < num_of_files_found;i++)
        {
          GtkTreeIter iter;
          gtk_list_store_append(GTK_LIST_STORE(model), &iter);

          gtk_list_store_set(GTK_LIST_STORE(model), &iter,
              MULTIPLE_COL_FILENAME, splt_filenames[i], -1);
          ui->infos->multiple_files_tree_number++;

          if (splt_filenames[i])
          {
            free(splt_filenames[i]);
            splt_filenames[i] = NULL;
          }
        }

        free(splt_filenames);
        splt_filenames = NULL;
      }

      g_free(filename);
      filename = NULL;

      files = g_slist_next(files);
    }
    g_slist_free(files);

    if (ui->infos->multiple_files_tree_number > 0)
    {
      gtk_widget_set_sensitive(ui->gui->multiple_files_remove_all_files_button, TRUE);
    }
  }

  gtk_widget_destroy(file_chooser);
}

static void multiple_files_remove_button_event(GtkWidget *widget, ui_state *ui)
{
  GtkTreeModel *model = gtk_tree_view_get_model(ui->gui->multiple_files_tree);
  GtkTreeSelection *selection = gtk_tree_view_get_selection(ui->gui->multiple_files_tree);
  GList *selected_list = gtk_tree_selection_get_selected_rows(selection, &model);

  while (g_list_length(selected_list) > 0)
  {
    GList *current_element = g_list_last(selected_list);
    GtkTreePath *path = current_element->data;
    GtkTreeIter iter;
    gtk_tree_model_get_iter(model, &iter, path);

    gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
    selected_list = g_list_remove(selected_list, path);
    ui->infos->multiple_files_tree_number--;

    gtk_tree_path_free(path);
  }

  if (ui->infos->multiple_files_tree_number == 0)
  {
    gtk_widget_set_sensitive(ui->gui->multiple_files_remove_all_files_button, FALSE);
  }

  gtk_widget_set_sensitive(ui->gui->multiple_files_remove_file_button,FALSE);

  g_list_foreach(selected_list, (GFunc)gtk_tree_path_free, NULL);
  g_list_free(selected_list);  
}

static void multiple_files_remove_all_button_event(GtkWidget *widget, ui_state *ui)
{
  GtkTreeModel *model = gtk_tree_view_get_model(ui->gui->multiple_files_tree);
  while (ui->infos->multiple_files_tree_number > 0)
  {
    GtkTreeIter iter;
    gtk_tree_model_get_iter_first(model, &iter);
    gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
    ui->infos->multiple_files_tree_number--;
  }
  
  gtk_widget_set_sensitive(ui->gui->multiple_files_remove_all_files_button, FALSE);
  gtk_widget_set_sensitive(ui->gui->multiple_files_remove_file_button, FALSE);
}

static GtkWidget *create_multiple_files_buttons_hbox(ui_state *ui)
{
  GtkWidget *hbox = wh_hbox_new();

  //button for adding file(s)
  GtkWidget *multiple_files_add_button =
    wh_create_cool_button(GTK_STOCK_ADD, _("_Add files"), FALSE);
  gtk_box_pack_start(GTK_BOX(hbox), multiple_files_add_button, FALSE, FALSE, 5);
  gtk_widget_set_sensitive(multiple_files_add_button, TRUE);
  g_signal_connect(G_OBJECT(multiple_files_add_button), "clicked",
                   G_CALLBACK(multiple_files_add_button_event), ui);

  //button for removing a file
  GtkWidget *multiple_files_remove_file_button =
    wh_create_cool_button(GTK_STOCK_DELETE, _("_Remove selected entries"),FALSE);
  ui->gui->multiple_files_remove_file_button = multiple_files_remove_file_button;
  gtk_box_pack_start(GTK_BOX(hbox),
      multiple_files_remove_file_button, FALSE, FALSE, 5);
  gtk_widget_set_sensitive(multiple_files_remove_file_button,FALSE);
  g_signal_connect(G_OBJECT(multiple_files_remove_file_button), "clicked",
                   G_CALLBACK(multiple_files_remove_button_event), ui);
  
  //button for removing a file
  GtkWidget *multiple_files_remove_all_files_button =
    wh_create_cool_button(GTK_STOCK_DELETE, _("R_emove all entries"),FALSE);
  ui->gui->multiple_files_remove_all_files_button = multiple_files_remove_all_files_button;
  gtk_box_pack_start(GTK_BOX(hbox), multiple_files_remove_all_files_button,
      FALSE, FALSE, 5);
  gtk_widget_set_sensitive(multiple_files_remove_all_files_button,FALSE);
  g_signal_connect(G_OBJECT(multiple_files_remove_all_files_button), "clicked",
                   G_CALLBACK(multiple_files_remove_all_button_event), NULL);

  return hbox;
}

static void multiple_files_selection_changed(GtkTreeSelection *selec, ui_state *ui)
{
  GtkTreeModel *model = gtk_tree_view_get_model(ui->gui->multiple_files_tree);
  GtkTreeSelection *selection = gtk_tree_view_get_selection(ui->gui->multiple_files_tree);
  GList *selected_list = gtk_tree_selection_get_selected_rows(selection, &model);

  if (g_list_length(selected_list) > 0)
  {
    gtk_widget_set_sensitive(ui->gui->multiple_files_remove_file_button, TRUE);
  }
  else
  {
    gtk_widget_set_sensitive(ui->gui->multiple_files_remove_file_button, FALSE);
  }
}

GtkWidget *create_multiple_files_component(ui_state *ui)
{
  GtkWidget *vbox = wh_vbox_new();

  GtkTreeView *multiple_files_tree = create_multiple_files_tree();
  ui->gui->multiple_files_tree = multiple_files_tree;

  GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolled_window), GTK_SHADOW_NONE);
  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (scrolled_window),
      GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
  gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

  //create columns
  create_multiple_files_columns(multiple_files_tree);

  //add the tree to the scrolled window
  gtk_container_add(GTK_CONTAINER(scrolled_window), GTK_WIDGET(multiple_files_tree));

  //selection for the tree
  GtkTreeSelection *multiple_files_tree_selection = gtk_tree_view_get_selection(multiple_files_tree);
  g_signal_connect(G_OBJECT(multiple_files_tree_selection), "changed",
      G_CALLBACK(multiple_files_selection_changed), ui);
  gtk_tree_selection_set_mode(GTK_TREE_SELECTION(multiple_files_tree_selection),
      GTK_SELECTION_MULTIPLE);

  GtkWidget *buttons_hbox = create_multiple_files_buttons_hbox(ui);
  gtk_box_pack_start(GTK_BOX(vbox), buttons_hbox, FALSE, FALSE, 2);

  return vbox;
}

