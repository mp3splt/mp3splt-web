/**********************************************************
 *
 * mp3splt-gtk -- utility based on mp3splt,
 *                for mp3/ogg splitting without decoding
 *
 * Copyright: (C) 2005-2013 Alexandru Munteanu
 * Contact: m@ioalex.net
 *
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
 * USA.
 *
 *********************************************************/

#ifndef OPTIONS_MANAGER_H

#define OPTIONS_MANAGER_H

#include "all_includes.h"

void update_output_options(ui_state *ui, gboolean is_checked_output_radio_box, gchar *output_format);
void put_options_from_preferences(ui_for_split *ui_fs);
void put_tags_from_filename_regex_options(ui_for_split *ui_fs);

ui_for_split *build_ui_for_split(ui_state *ui);
void free_ui_for_split(ui_for_split *ui_fs);

#endif

