/**********************************************************
 *
 * mp3splt-gtk -- utility based on mp3splt,
 *                for mp3/ogg splitting without decoding
 *
 * Copyright: (C) 2005-2012 Alexandru Munteanu
 * Contact: m@ioalex.net
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
 * USA.
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 *
 *********************************************************/

/*!********************************************************
 * \file 
 * Save and read preferences
 *
 * This file contains the functions to save the preferences
 * on the hard disk and to read them again at the next 
 * start of the program.
 ********************************************************/

#include "preferences_manager.h"

#include "all_includes.h"

static void check_pref_file_and_write_default(ui_state *ui);
static void pm_free_spinner_int_preferences(GArray *spinner_int_preferences);
static void pm_free_range_preferences(GArray *range_preferences);
static void pm_load_spinner_int_preferences(GKeyFile *key_file, preferences_state *pm);
static void pm_save_spinner_int_preferences(GKeyFile *key_file, preferences_state *pm);
static void pm_write_default_spinner_int_preferences(GKeyFile *key_file, preferences_state *pm);
static void pm_load_range_preferences(GKeyFile *key_file, preferences_state *pm);
static void pm_save_range_preferences(GKeyFile *key_file, preferences_state *pm);
static void pm_write_default_range_preferences(GKeyFile *key_file, preferences_state *pm);

void pm_register_spinner_int_preference(gchar *main_key, gchar *second_key,
    gint default_value, GtkWidget *spinner,
    void (*update_spinner_value_cb)(GtkWidget *spinner, gpointer data),
    gpointer user_data_for_cb, preferences_state *pm)
{
  spinner_int_preference preference;

  preference.main_key = strdup(main_key);
  preference.second_key = strdup(second_key);
  preference.default_value = default_value;
  preference.spinner = spinner;
  preference.update_spinner_value_cb = update_spinner_value_cb;
  preference.user_data_for_cb = user_data_for_cb;

  g_array_append_val(pm->spinner_int_preferences, preference);
}

void pm_register_range_preference(gchar *main_key, gchar *second_key,
    gint default_value, GtkWidget *range,
    void (*update_adjustment_value)(GtkAdjustment *adjustment, gpointer data),
    gpointer user_data_for_cb, preferences_state *pm)
{
  range_preference preference;

  preference.main_key = strdup(main_key);
  preference.second_key = strdup(second_key);
  preference.default_value = default_value;
  preference.range = range;
  preference.update_adjustment_value = update_adjustment_value;
  preference.user_data_for_cb = user_data_for_cb;

  g_array_append_val(pm->range_preferences, preference);
}

preferences_state *pm_state_new()
{
  preferences_state *pm = g_malloc0(sizeof(preferences_state));

  pm->spinner_int_preferences = g_array_new(TRUE, TRUE, sizeof(spinner_int_preference));
  pm->range_preferences = g_array_new(TRUE, TRUE, sizeof(range_preference));

  return pm;
}

void pm_free(preferences_state **pm)
{
  if (!pm || !*pm)
  {
    return;
  }

  pm_free_spinner_int_preferences((*pm)->spinner_int_preferences);
  pm_free_range_preferences((*pm)->range_preferences);

  g_free(*pm);
  *pm = NULL;
}

static void pm_load(GKeyFile *key_file, preferences_state *pm)
{
  pm_load_spinner_int_preferences(key_file, pm);
  pm_load_range_preferences(key_file, pm);
}

static void pm_save(GKeyFile *key_file, preferences_state *pm)
{
  pm_save_spinner_int_preferences(key_file, pm);
  pm_save_range_preferences(key_file, pm);
}

static void pm_write_default(GKeyFile *key_file, preferences_state *pm)
{
  pm_write_default_spinner_int_preferences(key_file, pm);
  pm_write_default_range_preferences(key_file, pm);
}

gchar *get_configuration_directory()
{
  gchar mp3splt_dir[14] = ".mp3splt-gtk";

  gchar *home_dir = g_strdup(g_get_home_dir());

#ifdef __WIN32__
  //manage c:\ because the gtk dir returns us "c:\"
  //and the normal directories without the "\"
  if (home_dir[strlen(home_dir)-1] == '\\')
  {
    home_dir[strlen(home_dir)-1] = '\0';
  }
#endif

  gint malloc_number = strlen(home_dir) + strlen(mp3splt_dir) + 2;
  gchar *mp3splt_dir_with_path = malloc(malloc_number * sizeof(gchar));
  g_snprintf(mp3splt_dir_with_path, malloc_number,
      "%s%s%s", home_dir, G_DIR_SEPARATOR_S, mp3splt_dir);

  if (home_dir)
  {
    g_free(home_dir);
    home_dir = NULL;
  }

  struct stat buffer;
  gint status = g_stat(mp3splt_dir_with_path, &buffer);
  if ((status != 0) || (S_ISDIR(buffer.st_mode) == 0))
  {
    if ((status == 0) && (S_ISREG(buffer.st_mode) != 0))
    {
      gint malloc_number = strlen(mp3splt_dir_with_path) + 5;
      gchar *backup_file = malloc(malloc_number * sizeof(gchar));
      snprintf(backup_file, malloc_number, "%s%s", mp3splt_dir_with_path,".bak");
      g_rename(mp3splt_dir_with_path, backup_file);
      g_free(backup_file);
    }

    //if it is not a directory and not a file, we suppose we can
    //create the directory
#ifdef __WIN32__      
    g_mkdir(mp3splt_dir_with_path, 0775);
#else
    g_mkdir(mp3splt_dir_with_path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
  }

  return mp3splt_dir_with_path;
}

/*! Get the name of the preferences file.

\attention filename returned must be freed after
that functions also checks if we have a directory .mp3splt-gtk and
if not it creates it. if we have a file .mp3splt-gtk, it makes a
backup and then creates the directory
result must be freed!!!!
*/
gchar *get_preferences_filename()
{
  gchar *mp3splt_dir_with_path = get_configuration_directory();

  gint fname_malloc_number = strlen(mp3splt_dir_with_path) + 30;
  gchar *filename = malloc(fname_malloc_number * sizeof(gchar));

  g_snprintf(filename, fname_malloc_number, "%s%smp3splt-gtk_prefs",
      mp3splt_dir_with_path, G_DIR_SEPARATOR_S);

  if (mp3splt_dir_with_path)
  {
    g_free(mp3splt_dir_with_path);
    mp3splt_dir_with_path = NULL;
  }

  return filename;
}

/*! \brief Read the preferences from the preferences file.
 */
void load_preferences(ui_state *ui)
{
  check_pref_file_and_write_default(ui);

  GKeyFile *key_file = g_key_file_new();

  gchar *filename = get_preferences_filename();
  g_key_file_load_from_file(key_file, filename, G_KEY_FILE_KEEP_COMMENTS, NULL);
  if (filename)
  {
    g_free(filename);
  }

#ifdef __WIN32__
  //language
  gchar *file_string = g_key_file_get_string(key_file, "general", "language", NULL);
  GString *lang = g_string_new(file_string);

  //0 = german, 1 = french, 2 = english
  gint list_number = 2;
  if (g_string_equal(lang,g_string_new("de")) || g_string_equal(lang,g_string_new("de_DE")))
  {
    list_number = 0;
  }
  else if (g_string_equal(lang, g_string_new("fr")) || g_string_equal(lang, g_string_new("fr_FR")))
  {
    list_number = 1;
  }

  GSList *radio_button_list = gtk_radio_button_get_group(GTK_RADIO_BUTTON(ui->gui->radio_button));
  GtkWidget *our_button = GTK_WIDGET(g_slist_nth_data(radio_button_list, list_number));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(our_button), TRUE);

  g_free(file_string);
  g_string_free(lang, TRUE);
  file_string = NULL;
  lang = NULL;
#endif

  // If get_output_directory()!=NULL the path where to output the split file
  // to has been set from command line
  if (get_output_directory(ui) == NULL)
  {
    // No output_path from command-line => get the path from the preferences
    gchar *save_path = g_key_file_get_string(key_file, "split", "save_path", NULL);
    if (save_path != NULL)
    {
      set_output_directory_and_update_ui(save_path, ui);
    }
    g_free(save_path);
    save_path = NULL;
  }

  //player
  gint item = g_key_file_get_integer(key_file, "player", "default_player",NULL);
  ch_set_active_value(GTK_COMBO_BOX(ui->gui->player_combo_box), item);

  item = g_key_file_get_boolean(key_file, "player", "amplitude_wave_ticked", NULL);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ui->gui->silence_wave_check_button), item);
  ui->status->show_silence_wave = item;

  pm_load(key_file, ui->preferences);

  //frame mode
  item = g_key_file_get_boolean(key_file, "split", "frame_mode", NULL);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ui->gui->frame_mode), item);

  //adjust mode
  item = g_key_file_get_boolean(key_file, "split", "adjust_mode", NULL);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ui->gui->adjust_mode), item);

  item = g_key_file_get_boolean(key_file, "output", "splitpoint_names_from_filename", NULL);
  if (item)
  {
    gtk_toggle_button_set_active(ui->gui->names_from_filename, TRUE);
  }
  else
  {
    gtk_toggle_button_set_active(ui->gui->names_from_filename, FALSE);
  }

  //adjust threshold
  gfloat item2;
  item = g_key_file_get_integer(key_file, "split", "adjust_threshold", NULL);  
  item2 = item/100 + (item%100)/100.;
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(ui->gui->spinner_adjust_threshold), item2);
  //adjust offset
  item = g_key_file_get_integer(key_file, "split", "adjust_offset", NULL);
  item2 = item/100 + (item%100)/100.;
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(ui->gui->spinner_adjust_offset), item2);
  //adjust gap
  item = g_key_file_get_integer(key_file, "split", "adjust_gap", NULL);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(ui->gui->spinner_adjust_gap), item);
  //adjust min
  item = g_key_file_get_integer(key_file, "split", "adjust_min", NULL);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(ui->gui->spinner_adjust_min), item);

  //tags options
  gint tag_pref_file = g_key_file_get_integer(key_file, "split", "tags", NULL);
  rh_set_radio_value(ui->gui->tags_radio, tag_pref_file, TRUE);

  //replace underscores by spaces
  item = g_key_file_get_boolean(key_file, "split", "replace_underscore_by_space", NULL);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ui->gui->replace_underscore_by_space_check_box), 
      item);

  //artist text properties
  item = g_key_file_get_integer(key_file, "split", "artist_text_properties",NULL);
  if (item)
  {
    ch_set_active_value(ui->gui->artist_text_properties_combo, item);
  }
  else
  {
    ch_set_active_value(ui->gui->artist_text_properties_combo, SPLT_NO_CONVERSION);
  }
  //album text properties
  item = g_key_file_get_integer(key_file, "split", "album_text_properties",NULL);
  if (item)
  {
    ch_set_active_value(ui->gui->album_text_properties_combo, item);
  }
  else
  {
    ch_set_active_value(ui->gui->album_text_properties_combo, SPLT_NO_CONVERSION);
  }
  //title text properties
  item = g_key_file_get_integer(key_file, "split", "title_text_properties",NULL);
  if (item)
  {
    ch_set_active_value(ui->gui->title_text_properties_combo, item);
  }
  else
  {
    ch_set_active_value(ui->gui->title_text_properties_combo, SPLT_NO_CONVERSION);
  }
  //comment text properties
  item = g_key_file_get_integer(key_file, "split", "comment_text_properties",NULL);
  if (item)
  {
    ch_set_active_value(ui->gui->comment_text_properties_combo, item);
  }
  else
  {
    ch_set_active_value(ui->gui->comment_text_properties_combo, SPLT_NO_CONVERSION);
  }

  //genre
  gchar *default_genre = g_key_file_get_string(key_file, "split", "genre", NULL);
  if (default_genre)
  {
    ch_set_active_str_value(ui->gui->genre_combo, default_genre);
    g_free(default_genre);
    default_genre = NULL;
  }
  else
  {
    ch_set_active_str_value(ui->gui->genre_combo, SPLT_UNDEFINED_GENRE);
  }

  //default comment tag
  gchar *default_comment_tag = g_key_file_get_string(key_file, "split", "default_comment_tag", NULL);
  if (default_comment_tag)
  {
    gtk_entry_set_text(GTK_ENTRY(ui->gui->comment_tag_entry), default_comment_tag);
    g_free(default_comment_tag);
    default_comment_tag = NULL;
  }

  //regexp to parse filename into tags
  gchar *tags_from_fname_regex =
    g_key_file_get_string(key_file, "split", "tags_from_filename_regex", NULL);
  if (tags_from_fname_regex)
  {
    gtk_entry_set_text(GTK_ENTRY(ui->gui->regex_entry), tags_from_fname_regex);
    g_free(tags_from_fname_regex);
    tags_from_fname_regex = NULL;
  }

  gchar *test_regex_fname = 
    g_key_file_get_string(key_file, "split", "test_regex_fname", NULL);
  if (test_regex_fname)
  {
    gtk_entry_set_text(GTK_ENTRY(ui->gui->test_regex_fname_entry), test_regex_fname);
    g_free(test_regex_fname);
    test_regex_fname = NULL;
  }

  //tags version
  tag_pref_file = g_key_file_get_integer(key_file, "split", "tags_version", NULL);

  GSList *tags_version_radio_button_list = 
    gtk_radio_button_get_group(GTK_RADIO_BUTTON(ui->gui->tags_version_radio));
  GtkWidget *the_selection =
    GTK_WIDGET(g_slist_nth_data(tags_version_radio_button_list, tag_pref_file));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(the_selection), TRUE);

  //default output format or not
  gint default_output_format = 
    g_key_file_get_boolean(key_file, "output", "default_output_format", NULL);
  GSList *output_radio_button_list = 
    gtk_radio_button_get_group(GTK_RADIO_BUTTON(ui->gui->radio_output));
  GtkWidget *our_selection =
    GTK_WIDGET(g_slist_nth_data(output_radio_button_list, default_output_format));
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(our_selection), TRUE);
  if (default_output_format)
  {
    gtk_widget_set_sensitive(ui->gui->output_entry, FALSE);
    gtk_widget_set_sensitive(ui->gui->output_label, FALSE);
  }
  else
  {
    gtk_widget_set_sensitive(ui->gui->output_default_label, FALSE);
  }

  //output format
  gchar *output_format = g_key_file_get_string(key_file, "output", "output_format", NULL);
  if (output_format)
  {
    gtk_entry_set_text(GTK_ENTRY(ui->gui->output_entry), output_format);
    g_free(output_format);
    output_format = NULL;
  }

  //create directories if needed
  item = g_key_file_get_boolean(key_file, "output", "create_dirs_if_needed", NULL);
  gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(ui->gui->create_dirs_from_output_files), item);

  //type of split: split mode
  gint split_mode = g_key_file_get_integer(key_file, "split", "split_mode", NULL);
  select_split_mode(split_mode, ui);

  //time value
  gint time_value = g_key_file_get_integer(key_file, "split", "split_mode_time_value", NULL);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(ui->gui->spinner_time), time_value);

  //equal time tracks value
  gint equal_tracks = g_key_file_get_integer(key_file, "split",
      "split_mode_equal_time_tracks", NULL);
  gtk_spin_button_set_value(GTK_SPIN_BUTTON(ui->gui->spinner_equal_tracks), equal_tracks);

  gint root_x = g_key_file_get_integer(key_file, "gui", "root_x_position", NULL);
  gint root_y = g_key_file_get_integer(key_file, "gui", "root_y_position", NULL);
  if (root_x && root_y)
  {
    ui_set_main_win_position(ui, root_x, root_y);
  }

  gint width = g_key_file_get_integer(key_file, "gui", "width", NULL);
  gint height = g_key_file_get_integer(key_file, "gui", "height", NULL);
  if (width && height)
  {
    ui_set_main_win_size(ui, width, height);
  }

  gchar *browser_directory = g_key_file_get_string(key_file, "gui", "browser_directory", NULL);
  if (browser_directory)
  {
    ui_set_browser_directory(ui, browser_directory);
    g_free(browser_directory);
  }

  g_key_file_free(key_file);
  key_file = NULL;
}

void save_preferences(ui_state *ui)
{
  gchar *filename = get_preferences_filename();

  GKeyFile *my_key_file = g_key_file_new();
  g_key_file_load_from_file(my_key_file, filename, G_KEY_FILE_KEEP_COMMENTS, NULL);

  //save_path
  g_key_file_set_string(my_key_file, "split", "save_path", get_output_directory(ui));

  //player
  g_key_file_set_integer(my_key_file, "player", "default_player", ui->infos->selected_player);

  g_key_file_set_boolean(my_key_file, "player", "amplitude_wave_ticked",
  gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ui->gui->silence_wave_check_button)));

  pm_save(my_key_file, ui->preferences);
 
#ifdef __WIN32__
  GString *selected_lang = get_checked_language(ui);
  g_key_file_set_string(my_key_file, "general", "language", selected_lang->str);
  g_string_free(selected_lang, TRUE);
  selected_lang = NULL;
#endif

  //frame mode
  g_key_file_set_boolean(my_key_file, "split", "frame_mode",
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ui->gui->frame_mode)));

  //adjust mode
  g_key_file_set_boolean(my_key_file, "split", "adjust_mode",
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ui->gui->adjust_mode)));

  //adjust threshold
  g_key_file_set_integer(my_key_file, "split", "adjust_threshold",
      gtk_spin_button_get_value(GTK_SPIN_BUTTON(ui->gui->spinner_adjust_threshold)) * 100);
  //adjust offset
  g_key_file_set_integer(my_key_file, "split", "adjust_offset",
      gtk_spin_button_get_value(GTK_SPIN_BUTTON(ui->gui->spinner_adjust_offset)) * 100);
  //adjust gap
  g_key_file_set_integer(my_key_file, "split", "adjust_gap",
      gtk_spin_button_get_value(GTK_SPIN_BUTTON(ui->gui->spinner_adjust_gap)));
  //adjust min
  g_key_file_set_integer(my_key_file, "split", "adjust_min",
      gtk_spin_button_get_value(GTK_SPIN_BUTTON(ui->gui->spinner_adjust_min)));

  g_key_file_set_boolean(my_key_file, "output", "splitpoint_names_from_filename",
      gtk_toggle_button_get_active(ui->gui->names_from_filename));

  //output format
  g_key_file_set_string(my_key_file, "output", "output_format",
      gtk_entry_get_text(GTK_ENTRY(ui->gui->output_entry)));
  //default output format
  g_key_file_set_boolean(my_key_file, "output", "default_output_format",
      get_checked_output_radio_box(ui));
  g_key_file_set_boolean(my_key_file, "output", "create_dirs_if_needed",
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ui->gui->create_dirs_from_output_files)));

  //tags
  g_key_file_set_integer(my_key_file, "split", "tags", rh_get_active_value(ui->gui->tags_radio));

  //replace underscores by space
  g_key_file_set_boolean(my_key_file, "split", "replace_underscore_by_space",
  gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(ui->gui->replace_underscore_by_space_check_box)));

  //artist text properties
  g_key_file_set_integer(my_key_file, "split", "artist_text_properties",
      ch_get_active_value(ui->gui->artist_text_properties_combo));
  //album text properties
  g_key_file_set_integer(my_key_file, "split", "album_text_properties",
      ch_get_active_value(ui->gui->album_text_properties_combo));
  //title text properties
  g_key_file_set_integer(my_key_file, "split", "title_text_properties",
      ch_get_active_value(ui->gui->title_text_properties_combo));
  //comment text properties
  g_key_file_set_integer(my_key_file, "split", "comment_text_properties",
      ch_get_active_value(ui->gui->comment_text_properties_combo));

  //genre
  gchar *genre_value = ch_get_active_str_value(ui->gui->genre_combo);
  if (genre_value != NULL)
  {
    g_key_file_set_string(my_key_file, "split", "genre", genre_value);
    g_free(genre_value);
  }

  const gchar *comment = gtk_entry_get_text(GTK_ENTRY(ui->gui->comment_tag_entry));
  if (comment != NULL)
  {
    g_key_file_set_string(my_key_file, "split", "default_comment_tag", comment);
  }

  const gchar *regex_text = gtk_entry_get_text(GTK_ENTRY(ui->gui->regex_entry));
  if (regex_text != NULL)
  {
    g_key_file_set_string(my_key_file, "split", "tags_from_filename_regex", regex_text);
  }

  const gchar *test_regex_fname = gtk_entry_get_text(GTK_ENTRY(ui->gui->test_regex_fname_entry));
  if (test_regex_fname != NULL)
  {
    g_key_file_set_string(my_key_file, "split", "test_regex_fname", test_regex_fname);
  }

  //tags version
  g_key_file_set_integer(my_key_file, "split", "tags_version",
      get_checked_tags_version_radio_box(ui->gui));

  //type of split: split mode
  g_key_file_set_integer(my_key_file, "split", "split_mode", get_selected_split_mode_safe(ui));
  //time value
  g_key_file_set_integer(my_key_file, "split", "split_mode_time_value",
      gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ui->gui->spinner_time)));
  //equal time tracks value
  g_key_file_set_integer(my_key_file, "split", "split_mode_equal_time_tracks",
      gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(ui->gui->spinner_equal_tracks)));

  const ui_main_window *main_win = ui_get_main_window_infos(ui);
  g_key_file_set_integer(my_key_file, "gui", "root_x_position", main_win->root_x_pos);
  g_key_file_set_integer(my_key_file, "gui", "root_y_position", main_win->root_y_pos);
  g_key_file_set_integer(my_key_file, "gui", "width", main_win->width);
  g_key_file_set_integer(my_key_file, "gui", "height", main_win->height);

  const char *browser_directory = ui_get_browser_directory(ui);
  if (browser_directory != NULL)
  {
    g_key_file_set_string(my_key_file, "gui", "browser_directory", browser_directory);
  }

  gchar *key_data = g_key_file_to_data(my_key_file, NULL, NULL);

  //we write to the preference file
  FILE *preferences_file;
  preferences_file = (FILE *)g_fopen(filename,"w");
  g_fprintf(preferences_file,"%s", key_data);
  fclose(preferences_file);
  preferences_file = NULL;

  //we free memory
  g_free(key_data);
  g_key_file_free(my_key_file);

  if (filename)
  {
    g_free(filename);
    filename = NULL;
  }
}

/* \brief writes a default configuration file

Also is used to write good values on a bad existing configuration file
*/
static void write_default_preferences_file(ui_state *ui)
{
  gchar *filename = get_preferences_filename();

  GKeyFile *my_key_file = g_key_file_new();
  g_key_file_load_from_file(my_key_file, filename, G_KEY_FILE_KEEP_COMMENTS, NULL);

#ifdef __WIN32__
  //default language
  if (!g_key_file_has_key(my_key_file, "general", "language",NULL))
  {
    g_key_file_set_string(my_key_file, "general", "language", "en");
    g_key_file_set_comment(my_key_file, "general", "language",
        "\n language of the gui: en = english, fr = french, de = german", NULL);
  }
  //if we have the key, but we have ugly values
  else
  {
    gchar *file_string = g_key_file_get_string(my_key_file, "general", "language", NULL);
    GString * lang_char = g_string_new(file_string);

    if((!g_string_equal(lang_char,g_string_new("en")))
        &&(!g_string_equal(lang_char, g_string_new("fr")))
        &&(!g_string_equal(lang_char, g_string_new("fr_FR")))
        &&(!g_string_equal(lang_char, g_string_new("de")))
        &&(!g_string_equal(lang_char, g_string_new("de_DE")))
        )
    {
      g_key_file_set_string(my_key_file, "general", "language", "en");
      g_key_file_set_comment(my_key_file, "general", "language",
          "\n language of the gui: en = english, fr_FR = french, de_DE = german", NULL);
    }

    g_free(file_string);
    g_string_free(lang_char, TRUE);
    file_string = NULL;
    lang_char = NULL;
  }
#endif

  //frame mode
  if (!g_key_file_has_key(my_key_file, "split", "frame_mode",NULL))
  {
    g_key_file_set_boolean(my_key_file, "split", "frame_mode", FALSE);
  }

  //adjust mode
  if (!g_key_file_has_key(my_key_file, "split", "adjust_mode",NULL))
  {
    g_key_file_set_boolean(my_key_file, "split", "adjust_mode", FALSE);
  }

  gint item;
  gfloat item2;
  //adjust threshold
  if (!g_key_file_has_key(my_key_file, "split", "adjust_threshold",NULL))
  {
    g_key_file_set_integer(my_key_file, "split", "adjust_threshold",
        (int)(SPLT_DEFAULT_PARAM_THRESHOLD * 100));
  }
  //if we have the key but we have ugly values
  else
  {
    item = g_key_file_get_integer(my_key_file, "split", "adjust_threshold", NULL);
    //convert to float
    item2 = item/100 + (item%100)/100.;

    if ((item2 < -96) || (item2 > 0))
    {
      g_key_file_set_integer(my_key_file, "split", "adjust_threshold",
          (int)(SPLT_DEFAULT_PARAM_THRESHOLD * 100));
    }
  }

  //adjust offset
  if (!g_key_file_has_key(my_key_file, "split", "adjust_offset",NULL))
  {
    g_key_file_set_integer(my_key_file, "split", "adjust_offset",
        (int)(SPLT_DEFAULT_PARAM_OFFSET * 100));
  }
  //if we have the key but we have ugly values
  else
  {
    item = g_key_file_get_integer(my_key_file, "split", "adjust_offset", NULL);
    //convert to float
    item2 = item/100 + (item%100)/100.;

    //if ugly values
    if ((item2 < -2) || (item2 > 2))
    {
      g_key_file_set_integer(my_key_file, "split", "adjust_offset",
          (int)(SPLT_DEFAULT_PARAM_OFFSET * 100));
    }
  }

  //adjust gap
  if (!g_key_file_has_key(my_key_file, "split", "adjust_gap",NULL))
  {
    g_key_file_set_integer(my_key_file, "split", "adjust_gap", SPLT_DEFAULT_PARAM_GAP);
  }
  //if we have the key but we have ugly values
  else
  {
    item = g_key_file_get_integer(my_key_file, "split", "adjust_gap", NULL);
    if ((item < 0) || (item > 2000))
    {
      g_key_file_set_integer(my_key_file, "split", "adjust_gap", SPLT_DEFAULT_PARAM_GAP);
    }
  }

  //tags options
  if (!g_key_file_has_key(my_key_file, "split", "tags",NULL))
  {
    g_key_file_set_integer(my_key_file, "split", "tags", 1);
    g_key_file_set_comment(my_key_file, "split", "tags",
        "\n 0 - No tags, 1 - Default tags, 2 - Original tags, 3 - Tags from filename", NULL);
  }

  //tags version
  if (!g_key_file_has_key(my_key_file, "split", "tags_version",NULL))
  {
    g_key_file_set_integer(my_key_file, "split", "tags_version", 0);
    g_key_file_set_comment(my_key_file, "split", "tags_version",
        "\n 0 - same tags version as the input file, 1 - ID3v1 tags,"
        " 2 - ID3v2 tags, 3 - ID3v1 & ID3v2 tags",
        NULL);
  }

  //default player
  if (!g_key_file_has_key(my_key_file, "player", "default_player",NULL))
  {
    g_key_file_set_integer(my_key_file, "player", "default_player",
        PLAYER_GSTREAMER);
    g_key_file_set_comment (my_key_file, "player", "default_player",
        "\n 1 = PLAYER_AUDACIOUS, 2 = PLAYER_SNACKAMP, 3 = PLAYER_GSTREAMER",
        NULL);
  }
  else
  {
    //check if we support selected player
    gint the_player = 
      g_key_file_get_integer(my_key_file, "player", "default_player", NULL);
    if (the_player == PLAYER_AUDACIOUS)
    {
#ifdef NO_AUDACIOUS
      g_key_file_set_integer(my_key_file, "player", "default_player", PLAYER_SNACKAMP);
#endif
    }
    //if the value do not make sense
    else if ((the_player > PLAYER_GSTREAMER) || (the_player < 0))
    {
      g_key_file_set_integer(my_key_file, "player", "default_player",
          PLAYER_GSTREAMER);
    }
  }

  pm_write_default(my_key_file, ui->preferences);

  //output format
  if (!g_key_file_has_key(my_key_file, "output", "output_format",NULL))
  {
    g_key_file_set_string(my_key_file, "output", "output_format", SPLT_DEFAULT_OUTPUT);
    g_key_file_set_comment (my_key_file, "output", "output_format",
        "\n the output format, contains @a,"
        "@b, @g, @p, @t and @n, see the program for"
        " more details", NULL);
  }

  //default output path boolean
  if (!g_key_file_has_key(my_key_file, "output", "default_output_format",NULL))
  {
    g_key_file_set_boolean(my_key_file, "output", "default_output_format", TRUE);
    g_key_file_set_comment(my_key_file, "output", "default_output_format",
        "\n can be true or false"
        " - if we use the default output or"
        " not for cddb, cue and freedb search", NULL);
  }

  //frame mode
  if (!g_key_file_has_key(my_key_file, "output", "create_dirs_if_needed", NULL))
  {
    g_key_file_set_boolean(my_key_file, "output", "create_dirs_if_needed", TRUE);
  }

  //split save path (output dir)
  if (!g_key_file_has_key(my_key_file, "split", "save_path",NULL))
  {
#ifdef __WIN32__
    const gchar *home_dir = g_get_home_dir();
    gint dir_malloc_number = strlen(home_dir)+ 10;
    gchar *default_dir = malloc(dir_malloc_number*sizeof(gchar *));
    g_snprintf(default_dir, dir_malloc_number, "%s\\Desktop",home_dir);

    //see if the directory exists
    struct stat buffer;
    gint status = g_stat(default_dir, &buffer);
    if ((status == 0) && (S_ISDIR(buffer.st_mode) == 0))
    {
      g_snprintf(default_dir, dir_malloc_number, "%s",home_dir);
    }
#else
    const gchar *default_dir = g_get_home_dir();
#endif

    g_key_file_set_string(my_key_file, "split", "save_path", default_dir);
    g_key_file_set_comment(my_key_file, "split", "save_path",
        "\n this is the path where you will find your split files ",
        NULL);

#ifdef __WIN32__
    g_free(default_dir);
#endif
  }

  //type of split: split mode
  if (!g_key_file_has_key(my_key_file, "split", "split_mode",NULL))
  {
    g_key_file_set_integer(my_key_file, "split", "split_mode", 3);
    g_key_file_set_comment(my_key_file, "split", "split_mode",
        "\n 0 - error mode, 1 - wrap mode, 2 - time mode, 3 - normal mode, 4 - equal time tracks",
        NULL);
  }

  //type of split: time value
  if (!g_key_file_has_key(my_key_file, "split", "split_mode_time_value",NULL))
  {
    g_key_file_set_integer(my_key_file, "split", "split_mode_time_value", 60);
    g_key_file_set_comment(my_key_file, "split", "split_mode_time_value",
        "\n value in seconds to split every X seconds (for the time split)", NULL);
  }

  //equal time tracks
  if (!g_key_file_has_key(my_key_file, "split", "split_mode_equal_time_tracks",NULL))
  {
    g_key_file_set_integer(my_key_file, "split", "split_mode_equal_time_tracks", 10);
    g_key_file_set_comment(my_key_file, "split", "split_mode_equal_time_tracks",
        "\n number of tracks when to split in X tracks (for the equal time tracks split)", NULL);
  }

  gchar *key_data = g_key_file_to_data(my_key_file, NULL, NULL);

  FILE *preferences_file = (FILE *)fopen(filename,"w");
  g_fprintf(preferences_file,"%s", key_data);
  fclose(preferences_file);

  if (filename)
  {
    g_free(filename);
  }

  g_free(key_data);
  g_key_file_free(my_key_file);
}

/*!\brief Create a preferences file --- if needed.

checks if preferences file exists and if it does not, create it
*/
static void check_pref_file_and_write_default(ui_state *ui)
{
  gchar *pref_file = get_preferences_filename();

  struct stat buffer;
  gint status = stat(pref_file, &buffer);
  if ((status == 0) &&
      (S_ISREG(buffer.st_mode) == 0) && 
      (S_ISDIR(buffer.st_mode) != 0))
  {
    gint malloc_number = strlen(pref_file)+5;
    gchar *backup_dir = malloc(malloc_number * sizeof(gchar *));
    snprintf(backup_dir,malloc_number, "%s%s", pref_file, ".bak");
    g_rename(pref_file, backup_dir);
    g_free(backup_dir);
    backup_dir = NULL;
  }

  if (pref_file)
  {
    g_free(pref_file);
    pref_file = NULL;
  }

  write_default_preferences_file(ui);
}

static void pm_free_spinner_int_preferences(GArray *spinner_int_preferences)
{
  gint i = 0;
  for (i = 0; i < spinner_int_preferences->len; i++)
  {
    spinner_int_preference preference =
      g_array_index(spinner_int_preferences, spinner_int_preference, i);

    g_free(preference.main_key);
    preference.main_key = NULL;

    g_free(preference.second_key);
    preference.second_key = NULL;
  }

  g_array_free(spinner_int_preferences, TRUE);
}

static void pm_free_range_preferences(GArray *range_preferences)
{
  gint i = 0;
  for (i = 0; i < range_preferences->len; i++)
  {
    spinner_int_preference preference =
      g_array_index(range_preferences, spinner_int_preference, i);

    g_free(preference.main_key);
    preference.main_key = NULL;

    g_free(preference.second_key);
    preference.second_key = NULL;
  }

  g_array_free(range_preferences, TRUE);
}

static void pm_load_spinner_int_preferences(GKeyFile *key_file, preferences_state *pm)
{
  GArray *spinner_int_preferences = pm->spinner_int_preferences;

  gint i = 0;
  for (i = 0; i < spinner_int_preferences->len; i++)
  {
    spinner_int_preference preference =
      g_array_index(spinner_int_preferences, spinner_int_preference, i);

    gint value =
      g_key_file_get_integer(key_file, preference.main_key, preference.second_key, NULL);  
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(preference.spinner), value);
    preference.update_spinner_value_cb(preference.spinner, preference.user_data_for_cb);
  }
}

static void pm_save_spinner_int_preferences(GKeyFile *key_file, preferences_state *pm)
{
  GArray *spinner_int_preferences = pm->spinner_int_preferences;

  gint i = 0;
  for (i = 0; i < spinner_int_preferences->len; i++)
  {
    spinner_int_preference preference =
      g_array_index(spinner_int_preferences, spinner_int_preference, i);

    g_key_file_set_integer(key_file, preference.main_key, preference.second_key,
        gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(preference.spinner)));
  }
}

static void pm_write_default_spinner_int_preferences(GKeyFile *key_file, preferences_state *pm)
{
  GArray *spinner_int_preferences = pm->spinner_int_preferences;

  gint i = 0;
  for (i = 0; i < spinner_int_preferences->len; i++)
  {
    spinner_int_preference preference =
      g_array_index(spinner_int_preferences, spinner_int_preference, i);

    if (!g_key_file_has_key(key_file, preference.main_key, preference.second_key, NULL))
    {
      g_key_file_set_integer(key_file, preference.main_key, preference.second_key,
          preference.default_value);
    }
  }
}

static void pm_load_range_preferences(GKeyFile *key_file, preferences_state *pm)
{
  GArray *range_preferences = pm->range_preferences;

  gint i = 0;
  for (i = 0; i < range_preferences->len; i++)
  {
    range_preference preference = g_array_index(range_preferences, range_preference, i);

    gint value =
      g_key_file_get_integer(key_file, preference.main_key, preference.second_key, NULL);  

    gtk_range_set_value(GTK_RANGE(preference.range), value);
    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(preference.range));
    preference.update_adjustment_value(adj, preference.user_data_for_cb);
  }
}

static void pm_save_range_preferences(GKeyFile *key_file, preferences_state *pm)
{
  GArray *range_preferences = pm->range_preferences;

  gint i = 0;
  for (i = 0; i < range_preferences->len; i++)
  {
    range_preference preference = g_array_index(range_preferences, range_preference, i);

    GtkAdjustment *adj = gtk_range_get_adjustment(GTK_RANGE(preference.range));
    g_key_file_set_integer(key_file, preference.main_key, preference.second_key,
        (gint)gtk_adjustment_get_value(adj));
  }
}

static void pm_write_default_range_preferences(GKeyFile *key_file, preferences_state *pm)
{
  GArray *range_preferences = pm->range_preferences;

  gint i = 0;
  for (i = 0; i < range_preferences->len; i++)
  {
    range_preference preference = g_array_index(range_preferences, range_preference, i);

    if (!g_key_file_has_key(key_file, preference.main_key, preference.second_key, NULL))
    {
      g_key_file_set_integer(key_file, preference.main_key, preference.second_key,
          preference.default_value);
    }
  }
}

