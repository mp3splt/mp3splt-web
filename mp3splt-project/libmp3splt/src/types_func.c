/**********************************************************
 *
 * libmp3splt -- library based on mp3splt,
 *               for mp3/ogg splitting without decoding
 *
 * Copyright (c) 2002-2005 M. Trotta - <mtrotta@users.sourceforge.net>
 * Copyright (c) 2005-2006 Munteanu Alexandru - io_alex_2002@yahoo.fr
 *
 * http://mp3splt.sourceforge.net
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
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307,
 * USA.
 *
 *********************************************************/

#include <string.h>
#include <math.h>

#include "splt.h"

extern short global_debug;

/********************************/
/* types: prototypes */

static void splt_t_free_oformat(splt_state *state);
static void splt_t_state_put_default_options(splt_state *state);
static void splt_t_free_files(char **files, int number);

/********************************/
/* types: state access */

//create new state aux, allocationg memory
//error is the possible error
splt_state *splt_t_new_state(splt_state *state, int *error)
{
  if ((state =malloc(sizeof(splt_state))) ==NULL)
    {
      *error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
      return NULL;
    }
  else
    {
      memset(state, 0x0, sizeof(splt_state));
      if ((state->wrap = malloc(sizeof(splt_wrap))) == NULL)
        {
          *error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
          free(state);
          return NULL;
        }
      memset(state->wrap,0x0,sizeof(state->wrap));
      if ((state->serrors = malloc(sizeof(splt_syncerrors))) == NULL)
        {
          free(state->wrap);
          free(state);
          *error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
          return NULL;
        }
      memset(state->serrors,0x0,sizeof(state->serrors));
      if ((state->split.p_bar = malloc(sizeof(splt_progress))) == NULL)
        {
          free(state->wrap);
          free(state->serrors);
          free(state);
          *error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
          return NULL;
        }
      //put default options
      splt_t_state_put_default_options(state);
    }
  
  return state;
}

//free the state
//frees only the state, not the structures in the state
//call after freeing all the structures in the state
static void splt_t_free_state_struct(splt_state *state)
{
  if (state)
    {
      if (state->fname_to_split)
        {
          free(state->fname_to_split);
          state->fname_to_split = NULL;
        }
      if (state->path_of_split)
        {
          free(state->path_of_split);
          state->path_of_split = NULL;
        }
      if (state->m3u_filename)
        {
          free(state->m3u_filename);
          state->m3u_filename = NULL;
        }
      if (state->wrap)
        {
          free(state->wrap);
          state->wrap = NULL;
        }
      if (state->serrors)
        {
          free(state->serrors);
          state->serrors = NULL;
        }
      free(state);
      state = NULL;
    }
}

//we free internal options
void splt_t_iopts_free(splt_state *state)
{
  if (state->iopts.new_filename_path)
    {
      free(state->iopts.new_filename_path);
      state->iopts.new_filename_path = NULL;
    }
}

//this function frees all the memory from the state
void splt_t_free_state(splt_state *state)
{
  if (state)
    {
      //free mp3state
      if (state->mstate)
        {
          splt_mp3_state_free(state);
        }
      //free oggstate
      if (state->ostate)
        {
          splt_ogg_state_free(state);
        }
      //free original tags
      splt_t_clean_original_tags(state);
      //we free output format
      splt_t_free_oformat(state);
      //free the wrapped files
      splt_t_wrap_free(state);
      //we free syncerrors
      splt_t_serrors_free(state);
      //we free the search results
      splt_t_freedb_free_search(state);
      //we free the splitpoints and tags
      splt_t_free_splitpoints_tags(state);
      //free internal options
      splt_t_iopts_free(state);
      //we free the progress bar
      if (state->split.p_bar)
        {
          free(state->split.p_bar);
        }
      //free our state
      splt_t_free_state_struct(state);
    }
}

/********************************/
/* types: total time access */

//sets the total time of the file
void splt_t_set_total_time(splt_state *state, long value)
{
  splt_u_print_debug("We set total time to",value,NULL);
  
  if (value >= 0)
    {
      state->split.total_time = value;
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT,__func__, value, NULL);
    }
}

//returns total time of the file
long splt_t_get_total_time(splt_state *state)
{
  return state->split.total_time;
}

/**********************************/
/* types: filename and path access */

//sets the new filename path
void splt_t_set_new_filename_path(splt_state *state, 
                                  char *new_filename_path,
                                  int *error)
{
  //free previous path
  if (state->iopts.new_filename_path)
    {
      free(state->iopts.new_filename_path);
      state->iopts.new_filename_path = NULL;
    }
  
  //put the new path
  if (new_filename_path == NULL)
    {
      state->iopts.new_filename_path = NULL;
    }
  else
    {
      state->iopts.new_filename_path = strdup(new_filename_path);
      
      if (state->iopts.new_filename_path == NULL)
        {
          *error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
        }
    }
}

//returns the new filename path
char *splt_t_get_new_filename_path(splt_state *state)
{
  return state->iopts.new_filename_path;
}

//sets the path of the split
//returns possible error
int splt_t_set_path_of_split(splt_state *state, char *path)
{
  int error = SPLT_OK;
  
  //free previous memory
  if (splt_t_get_path_of_split(state))
    {
      free(state->path_of_split);
      state->path_of_split = NULL;
    }
  
  splt_u_print_debug("Setting path of split...",0,path);
  
  if (path != NULL)
    {
      if((state->path_of_split = malloc(sizeof(char)*(strlen(path)+1)))
         != NULL)
        {
          snprintf(state->path_of_split,(strlen(path)+1), 
                   "%s", path);
        }
      else
        {
          error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
        }
    }
  else
    {
      state->path_of_split = NULL;
    }
  
  return error;
}

//sets the m3u filename
//returns possible error
int splt_t_set_m3u_filename(splt_state *state, char *filename)
{
  int error = SPLT_OK;
  
  //free previous memory
  if (splt_t_get_m3u_filename(state))
    {
      free(state->m3u_filename);
      state->m3u_filename = NULL;
    }
  
  splt_u_print_debug("Setting m3u filename...",0,filename);
  
  if (filename != NULL)
    {
      if((state->m3u_filename = malloc(sizeof(char)*(strlen(filename)+1)))
         != NULL)
        {
          snprintf(state->m3u_filename,(strlen(filename)+1), 
                   "%s", filename);
        }
      else
        {
          error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
        }
    }
  else
    {
      state->m3u_filename = NULL;
    }
  
  return error;
}

//sets the filename to split
int splt_t_set_filename_to_split(splt_state *state, char *filename)
{
  int error = SPLT_OK;
  
  //free previous memory
  if (splt_t_get_filename_to_split(state))
    {
      free(state->fname_to_split);
      state->fname_to_split = NULL;
    }
  
  splt_u_print_debug("Setting filename to split...",0,filename);
  
  if (filename != NULL)
    {
      if ((state->fname_to_split = malloc(sizeof(char)*(strlen(filename)+1))) 
          != NULL)
        {
          snprintf(state->fname_to_split,strlen(filename)+1,
                   filename);
        }
      else
        {
          error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
        }
    }
  else
    {
      state->fname_to_split = NULL;
    }
  
  return error;
}

//returns the filename to split
char *splt_t_get_filename_to_split(splt_state *state)
{
  return state->fname_to_split;
}

//returns path of split
char *splt_t_get_path_of_split(splt_state *state)
{
  return state->path_of_split;
}

//returns path of split
char *splt_t_get_m3u_filename(splt_state *state)
{
  return state->m3u_filename;
}

/********************************/
/* types: file format access */

//sets the file format
void splt_t_set_file_format(splt_state *state, int file_format)
{
  if ((file_format == SPLT_MP3_FORMAT)
      ||(file_format == SPLT_OGG_FORMAT)
      ||(file_format == SPLT_INVALID_FORMAT))
    {
      state->file_format = file_format;
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT,__func__, file_format, NULL);
    }
}

//returns the file format
int splt_t_get_file_format(splt_state *state)
{
  return state->file_format;
}

/********************************/
/* types: current split access */

//sets the current split
void splt_t_set_current_split(splt_state *state, int index)
{
  //if ((index < state->split.real_splitnumber) &&
  //(index >= 0))
  if (index >= 0)
    {
      state->split.current_split = index;
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT, __func__,index, NULL);
    }
}

//returns the current split
int splt_t_get_current_split(splt_state *state)
{
  return state->split.current_split;
}

//adds 1 to the current split
void splt_t_current_split_next(splt_state *state)
{
  splt_t_set_current_split(state, splt_t_get_current_split(state)+1);
}

/********************************/
/* types: output format access */

//free the format_string
static void splt_t_free_oformat(splt_state *state)
{
  if (state->oformat.format_string)
    {
      free(state->oformat.format_string);
      state->oformat.format_string = NULL;
    }
}

//set the output format string
int splt_t_new_oformat(splt_state *state, char *format_string)
{
  int error = SPLT_OK;
  splt_t_free_oformat(state);
  
  if (format_string != NULL)
    {
      if ((state->oformat.format_string =
           malloc(sizeof(char)*(strlen(format_string)+1)))
          == NULL)
        {
          error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
        }
      else
        {
          snprintf(state->oformat.format_string,
                   strlen(format_string)+1,"%s",format_string);
        }
    }
  else
    {
      state->oformat.format_string = NULL;
    }
  
  return error;
}

//puts the output format
void splt_t_set_oformat(splt_state *state, char *format_string,
                        int *error)
{
  int j = 0;
  
  //we clean out the output
  while (j <= SPLT_OUTNUM)
    {
      memset(state->oformat.format[j],'\0',SPLT_MAXOLEN);
      j++;
    }
  
  splt_t_new_oformat(state, format_string);
  char *new_str = strdup(format_string);
  *error = splt_u_parse_outformat(new_str,state);
  free(new_str);
  
  //if no error
  if (*error == SPLT_OUTPUT_FORMAT_OK)
    {
      splt_t_set_oformat_digits(state); 
    }
}

//puts the number of digits for the output format
void splt_t_set_oformat_digits(splt_state *state)
{
  int i = 0;
  i = (int) (log10((double) (splt_t_get_splitnumber(state))));
  state->oformat.output_format_digits = (char) ((i+1) | 0x30);
}

//returns the output format string
char *splt_t_get_oformat(splt_state *state)
{
  return state->oformat.format_string;
}

/********************************/
/* types: splitnumber access */

//sets how many splitpoints we want to split
void splt_t_set_splitnumber(splt_state *state, int number)
{
  //if (number >= 0) &&
  //(number <= state->split.real_splitnumber))
  
  if (number >= 0)
    {
      state->split.splitnumber = number;
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT,__func__, number, NULL);
    }
}

//returns how many splitpoints we want to split
int splt_t_get_splitnumber(splt_state *state)
{
  return state->split.splitnumber;
}

/********************************/
/* types: splitpoints access */

//puts a splitpoint in the state with an eventual file name
//split_value is which splitpoint hundreths of seconds
//if split_value is LONG_MAX, we put the end of the song (EOF)
//TODO, we need to have the filename in the state here
//in order to treat LONG_MAX value
int splt_t_append_splitpoint(splt_state *state, long split_value,
                             char *name)
{
  int error = SPLT_OK;
  
  splt_u_print_debug("Appending splitpoint...",0,NULL);
  
  //if we put the EOF
  if (split_value == LONG_MAX)
    {
      //we check if mp3 or ogg
      splt_check_if_mp3_or_ogg(state, &error);
      //we put the total time
      splt_s_put_total_time(state, &error);
      if (error != SPLT_OK)
        {
          return error;
        }
      else
        {
          //we take the total time and assign it to split_value
          split_value = splt_t_get_total_time(state);
        }
    }
  
  if (split_value >= 0)
    {
      state->split.real_splitnumber++;
      
      //we allocate memory for this splitpoint
      if (!state->split.points)
        {
          if ((state->split.points = malloc(sizeof(splt_point)))
              == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
              return error;
            }
        }
      else
        {
          if ((state->split.points = 
               realloc(state->split.points,
                       state->split.real_splitnumber * sizeof(splt_point)))
              == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
              return error;
            }
        }
      
      //put name NULL
      state->split.points[state->split.real_splitnumber-1].name = NULL;
      
      //we change the splitpoint value
      int value_error = SPLT_OK;
      value_error = splt_t_set_splitpoint_value(state,
                                                state->split.real_splitnumber-1,
                                                split_value);
      if (value_error != SPLT_OK)
        {
          error = value_error;
          return error;
        }
      
      //we change the splitpoint name
      int name_error = SPLT_OK;
      name_error = splt_t_set_splitpoint_name(state,
                                              state->split.real_splitnumber-1,
                                              name);
      if (name_error != SPLT_OK)
        {
          error = name_error;
          return error;
        }
    }
  else
    {
      splt_u_print_debug("Negative splitpoint.. ",(double)split_value,NULL);
      error = SPLT_ERROR_NEGATIVE_SPLITPOINT;
      return error;
    }
  
  return error;
}

//this function clears all the splitpoints, the filename to split,
//the path of splitpoints
void splt_t_free_splitpoints(splt_state *state)
{
  if (state->split.points)
    {
      int i = 0;
      for (i = 0; i < state->split.real_splitnumber; i++)
        {
          if (state->split.points[i].name)
            {
              free(state->split.points[i].name);
              state->split.points[i].name = NULL;
            }
        }
      free(state->split.points);
      state->split.points = NULL;
    }
  
  state->split.splitnumber = 0;
  state->split.real_splitnumber = 0;
}

//returns if the splitpoint at index position exists
int splt_t_splitpoint_exists(splt_state *state,
                             int index)
{
  if ((index >= 0) &&
      (index < state->split.real_splitnumber))
    {
      return SPLT_TRUE;
    }
  else
    {
      return SPLT_FALSE;
    }
}

//change the splitpoint value
int splt_t_set_splitpoint_value(splt_state *state,
                                int index, long split_value)
{
  char temp[100];
  snprintf(temp,100,"%d",index);
  splt_u_print_debug("Splitpoint value is.. at ",split_value,temp);
  
  int error = SPLT_OK;
  
  if ((index >= 0) &&
      (index < state->split.real_splitnumber))
    {
      state->split.points[index].value = split_value;
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
    }
  
  return error;
}

//change the splitpoint name
int splt_t_set_splitpoint_name(splt_state *state,
                               int index, char *name)
{
  splt_u_print_debug("Splitpoint name at ",index,name);
  
  int error = SPLT_OK;
  
  if ((index >= 0) &&
      (index < state->split.real_splitnumber))
    {
      if (state->split.points[index].name)
        {
          free(state->split.points[index].name);
          state->split.points[index].name = NULL;
        }
      
      if (name != NULL)
        {
          //allocate memory for this split name
          if((state->split.points[index].name =
              malloc((strlen(name)+1)*sizeof(char)))
             == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
              return error;
            }
          
          snprintf(state->split.points[index].name,
                   strlen(name)+1, "%s",name);
        }
      else
        {
          state->split.points[index].name = NULL;
        }
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
    }
  
  return error;
}

//returns the splitpoints from the state
splt_point *splt_t_get_splitpoints(splt_state *state,
                                   int *splitpoints_number)
{
  *splitpoints_number = state->split.real_splitnumber;
  return state->split.points;
}

//get the splitpoint value
long splt_t_get_splitpoint_value(splt_state *state,
                                 int index, int *error)
{
  if ((index >= 0) &&
      (index < state->split.real_splitnumber))
    {
      return state->split.points[index].value;
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
      return -1;
    }
}

//get the splitpoint name
char *splt_t_get_splitpoint_name(splt_state *state,
                                 int index, int *error)
{
  if ((index >= 0) &&
      (index < state->split.real_splitnumber))
    {
      return state->split.points[index].name;
    }
  else
    {
      //splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
      return NULL;
    }
}

/********************************/
/* types: tags access */

//sets the original tags to the state
void splt_t_get_original_tags(splt_state *state, int *err)
{
  //we clean the original tags
  splt_t_clean_original_tags(state);
  
  char *filename = splt_t_get_filename_to_split(state);
  if (splt_t_get_file_format(state) == SPLT_MP3_FORMAT)
    {
      splt_u_print_debug("Putting mp3 original tags...\n",0,NULL);
#ifndef NO_ID3TAG
      splt_mp3_get_original_tags(filename, state, err);
#else
      splt_u_error(SPLT_IERROR_SET_ORIGINAL_TAGS,__func__, 0, NULL);
#endif
    }
  else
    {
#ifndef NO_OGG
      if (splt_t_get_file_format(state) == SPLT_OGG_FORMAT)
	{
	  splt_u_print_debug("Putting ogg original tags...\n",0,NULL);
	  splt_ogg_get_original_tags(filename, state, err);
	}
#endif
      //TODO if no mp3 or ogg
    }
}

//append original tags
void splt_t_append_original_tags(splt_state *state)
{
  splt_t_append_tags(state,
                     state->original_tags.title,
                     state->original_tags.artist,
                     state->original_tags.album,
                     state->original_tags.artist,
                     state->original_tags.year,
                     state->original_tags.comment,
                     state->original_tags.track,
                     state->original_tags.genre);
}

//append tags
int splt_t_append_tags(splt_state *state, 
                       char *title, char *artist,
                       char *album, char *performer,
                       char *year, char *comment,
                       int track, unsigned char genre)
{
  int error = SPLT_OK;
  int old_tagsnumber = state->split.real_tagsnumber;
  
  error = splt_t_set_tags_char_field(state,
                                     old_tagsnumber,
                                     SPLT_TAGS_TITLE, title);
  if (error != SPLT_OK)
    return error;
  error = splt_t_set_tags_char_field(state,
                                     old_tagsnumber,
                                     SPLT_TAGS_ARTIST, artist);
  if (error != SPLT_OK)
    return error;
  error = splt_t_set_tags_char_field(state,
                                     old_tagsnumber,
                                     SPLT_TAGS_ALBUM, album);
  if (error != SPLT_OK)
    return error;
  error = splt_t_set_tags_char_field(state,
                                     old_tagsnumber,
                                     SPLT_TAGS_PERFORMER, performer);
  if (error != SPLT_OK)
    return error;
  error = splt_t_set_tags_char_field(state,
                                     old_tagsnumber,
                                     SPLT_TAGS_YEAR, year);
  if (error != SPLT_OK)
    return error;
  error = splt_t_set_tags_char_field(state,
                                     old_tagsnumber,
                                     SPLT_TAGS_COMMENT, comment);
  if (error != SPLT_OK)
    return error;
  error = splt_t_set_tags_int_field(state,
                                    old_tagsnumber,
                                    SPLT_TAGS_TRACK, track);
  if (error != SPLT_OK)
    return error;
  error = splt_t_set_tags_uchar_field(state,
                                      old_tagsnumber,
                                      SPLT_TAGS_GENRE, genre);
  
  return error;
}

//append tags on the previous song
//only if char non null and track != -1 and genre != 12
int splt_t_append_only_non_null_previous_tags(splt_state *state, 
                                              char *title, char *artist,
                                              char *album, char *performer,
                                              char *year, char *comment,
                                              int track, unsigned char genre)
{
  int error = SPLT_OK;
  int old_tagsnumber = state->split.real_tagsnumber-1;
  
  if (old_tagsnumber >= 0)
    {
      if (title != NULL)
        {
          error = splt_t_set_tags_char_field(state,
                                             old_tagsnumber,
                                             SPLT_TAGS_TITLE, title);
        }
      if (error != SPLT_OK)
        return error;
      if (artist != NULL)
        {
          error = splt_t_set_tags_char_field(state,
                                             old_tagsnumber,
                                             SPLT_TAGS_ARTIST, artist);
        }
      if (error != SPLT_OK)
        return error;
      if (album != NULL)
        {
          error = splt_t_set_tags_char_field(state,
                                             old_tagsnumber,
                                             SPLT_TAGS_ALBUM, album);
        }
      if (error != SPLT_OK)
        return error;
      if (performer != NULL)
        {
          error = splt_t_set_tags_char_field(state,
                                             old_tagsnumber,
                                             SPLT_TAGS_PERFORMER, performer);
        }
      if (error != SPLT_OK)
        return error;
      if (year != NULL)
        {
          error = splt_t_set_tags_char_field(state,
                                             old_tagsnumber,
                                             SPLT_TAGS_YEAR, year);
        }
      if (error != SPLT_OK)
        return error;
      if (comment != NULL)
        {
          error = splt_t_set_tags_char_field(state,
                                             old_tagsnumber,
                                             SPLT_TAGS_COMMENT, comment);
        }
      if (error != SPLT_OK)
        return error;
      if (track != -1)
        {
          error = splt_t_set_tags_int_field(state,
                                            old_tagsnumber,
                                            SPLT_TAGS_TRACK, track);
        }
      if (error != SPLT_OK)
        return error;
      if (genre != 12)
        {
          error = splt_t_set_tags_uchar_field(state,
                                              old_tagsnumber,
                                              SPLT_TAGS_GENRE, genre);
        }
    }
  
  return error;
}

//only used for splt_t_new_tags_if_necessary
static void splt_t_set_empty_tags(splt_state *state, int index)
{
  state->split.tags[index].title = NULL;
  state->split.tags[index].artist = NULL;
  state->split.tags[index].album = NULL;
  state->split.tags[index].performer = NULL;
  state->split.tags[index].year = NULL;
  state->split.tags[index].comment = NULL;
  state->split.tags[index].track = 0;
  state->split.tags[index].genre = 0x0;
}

//allocate new tags if necessary
static int splt_t_new_tags_if_necessary(splt_state *state, int index)
{
  int error = SPLT_OK;
  
  if (!state->split.tags)
    {
      if ((index > state->split.real_tagsnumber)
          || (index < 0))
        {
          splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
        }
      else
        {
          if ((state->split.tags = malloc(sizeof(splt_tags)))
              == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
              return error;
            }
          else
            {
              splt_t_set_empty_tags(state,index);
              state->split.real_tagsnumber++;
            }
        }
    }
  else
    {
      if ((index > state->split.real_tagsnumber)
          || (index < 0))
        {
          splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
        }
      else
        {
          if (index == state->split.real_tagsnumber)
            {
              if ((state->split.tags = realloc(state->split.tags,
                                               sizeof(splt_tags) *
                                               (index+1)))
                  == NULL)
                {
                  error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
                  return error;
                }
              else
                {
                  splt_t_set_empty_tags(state,index);
                  state->split.real_tagsnumber++;
                }
            }
        }
    }
  
  return error;
}

//returns if the tags at index position exists
int splt_t_tags_exists(splt_state *state, int index)
{
  if ((index >= 0) &&
      (index < state->split.real_tagsnumber))
    {
      return SPLT_TRUE;
    }
  else
    {
      return SPLT_FALSE;
    }
}

//set title, artist, album, year or comment
int splt_t_set_tags_char_field(splt_state *state, int index,
                               int tags_field, char *data)
{
  int error = SPLT_OK;
  
  error = splt_t_new_tags_if_necessary(state,index);
  
  if (error != SPLT_OK)
    {
      return error;
    }
  
  if ((index >= state->split.real_tagsnumber)
      || (index < 0))
    {
      error = SPLT_ERROR_INEXISTENT_SPLITPOINT;
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
      return error;
    }
  else
    {
      switch(tags_field)
        {
        case SPLT_TAGS_TITLE:
          splt_u_print_debug("Setting title tags at ",index,data);
          if (state->split.tags[index].title)
            {
              free(state->split.tags[index].title);
              state->split.tags[index].title = NULL;
            }
          if (data == NULL)
            {
              state->split.tags[index].title = NULL;
            }
          else
            {
              if ((state->split.tags[index].title = malloc((strlen(data)+1) * 
                                                           sizeof(char)))
                  == NULL)
                {
                  error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
                }
              else
                {
                  snprintf(state->split.tags[index].title,(strlen(data)+1),"%s", data);
                }
            }
          break;
        case SPLT_TAGS_ARTIST:
          splt_u_print_debug("Setting artist tags at ",index,data);
          if (state->split.tags[index].artist)
            {
              free(state->split.tags[index].artist);
              state->split.tags[index].artist = NULL;
            }
          if (data == NULL)
            {
              state->split.tags[index].artist = NULL;
            }
          else
            {
              if ((state->split.tags[index].artist = malloc((strlen(data)+1) * 
                                                            sizeof(char)))
                  == NULL)
                {
                  error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
                }
              else
                {
                  snprintf(state->split.tags[index].artist,(strlen(data)+1),"%s", data);
                }
            }
          break;
        case SPLT_TAGS_ALBUM:
          splt_u_print_debug("Setting album tags at ",index,data);
          if (state->split.tags[index].album)
            {
              free(state->split.tags[index].album);
              state->split.tags[index].album = NULL;
            }
          if (data == NULL)
            {
              state->split.tags[index].album = NULL;
            }
          else
            {
              if ((state->split.tags[index].album = malloc((strlen(data)+1) * 
                                                           sizeof(char)))
                  == NULL)
                {
                  error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
                }
              else
                {
                  snprintf(state->split.tags[index].album,(strlen(data)+1),"%s", data);
                }
            }
          break;
        case SPLT_TAGS_YEAR:
          splt_u_print_debug("Setting year tags at ",index,data);
          if (state->split.tags[index].year)
            {
              free(state->split.tags[index].year);
              state->split.tags[index].year = NULL;
            }
          if (data == NULL)
            {
              state->split.tags[index].year = NULL;
            }
          else
            {
              if ((state->split.tags[index].year = malloc((strlen(data)+1) * 
                                                          sizeof(char)))
                  == NULL)
                {
                  error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
                }
              else
                {
                  snprintf(state->split.tags[index].year,(strlen(data)+1),"%s", data);
                }
            }
          break;
        case SPLT_TAGS_COMMENT:
          if (state->split.tags[index].comment)
            {
              free(state->split.tags[index].comment);
              state->split.tags[index].comment = NULL;
            }
          if (data == NULL)
            {
              state->split.tags[index].comment = NULL;
            }
          else
            {
              if ((state->split.tags[index].comment = malloc((strlen(data)+1) * 
                                                             sizeof(char)))
                  == NULL)
                {
                  error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
                }
              else
                {
                  snprintf(state->split.tags[index].comment,(strlen(data)+1),"%s", data);
                }
            }
          break;
        case SPLT_TAGS_PERFORMER:
          splt_u_print_debug("Setting performer tags at ",index,data);
          if (state->split.tags[index].performer)
            {
              free(state->split.tags[index].performer);
              state->split.tags[index].performer = NULL;
            }
          if (data == NULL)
            {
              state->split.tags[index].performer = NULL;
            }
          else
            {
              if ((state->split.tags[index].performer = malloc((strlen(data)+1) * 
                                                               sizeof(char)))
                  == NULL)
                {
                  error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
                }
              else
                {
                  snprintf(state->split.tags[index].performer,(strlen(data)+1),"%s", data);
                }
            }
          break;
        default:
          break;
        }
    }
  
  if (error != SPLT_OK)
    {
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
    }
  
  return error;
}

//cleans original tags
void splt_t_clean_original_tags(splt_state *state)
{
  if (state->original_tags.year)
    {
      free(state->original_tags.year);
      state->original_tags.year = NULL;
    }
  if (state->original_tags.artist)
    {
      free(state->original_tags.artist);
      state->original_tags.artist = NULL;
    }
  if (state->original_tags.album)
    {
      free(state->original_tags.album);
      state->original_tags.album = NULL;
    }
  if (state->original_tags.title)
    {
      free(state->original_tags.title);
      state->original_tags.title = NULL;
    }
  if (state->original_tags.comment)
    {
      free(state->original_tags.comment);
      state->original_tags.comment = NULL;
    }
  state->original_tags.track = -1;
  //12 means "other"
  state->original_tags.genre = 12;
}

//returns error
//length is the length of the string
int splt_t_set_original_tags_field(splt_state *state,
                                   int tags_field, int int_data,
                                   char *char_data, unsigned char uchar_data,
                                   int length)
{
  int error = SPLT_OK;
  
  switch (tags_field)
    {
    case SPLT_TAGS_TITLE:
      if (state->original_tags.title)
        {
          free(state->original_tags.title);
          state->original_tags.title = NULL;
        }
      if (char_data == NULL)
        {
          state->original_tags.title = NULL;
        }
      else
        {
          if ((state->original_tags.title = malloc(sizeof(char)*(length+1)))
              == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
            }
          else
            {
              snprintf(state->original_tags.title,
                       length+1,"%s", char_data);
            }
        }      
      break;
    case SPLT_TAGS_ARTIST:
      if (state->original_tags.artist)
        {
          free(state->original_tags.artist);
          state->original_tags.artist = NULL;
        }
      if (char_data == NULL)
        {
          state->original_tags.artist = NULL;
        }
      else
        {
          if ((state->original_tags.artist = malloc(sizeof(char)*(length+1)))
              == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
            }
          else
            {
              snprintf(state->original_tags.artist,
                       length+1,"%s", char_data);
            }
        }
      break;
    case SPLT_TAGS_ALBUM:
      if (state->original_tags.album)
        {
          free(state->original_tags.album);
          state->original_tags.album = NULL;
        }
      if (char_data == NULL)
        {
          state->original_tags.album = NULL;
        }
      else
        {
          if ((state->original_tags.album = malloc(sizeof(char)*(length+1)))
              == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
            }
          else
            {
              snprintf(state->original_tags.album,
                       length+1,"%s", char_data);
            }
        }      
      break;
    case SPLT_TAGS_YEAR:
      if (state->original_tags.year)
        {
          free(state->original_tags.year);
          state->original_tags.year = NULL;
        }
      if (char_data == NULL)
        {
          state->original_tags.year = NULL;
        }
      else
        {
          if ((state->original_tags.year = malloc(sizeof(char)*(length+1)))
              == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
            }
          else
            {
              snprintf(state->original_tags.year,
                       length+1,"%s", char_data);
            }
        }      
      break;
    case SPLT_TAGS_COMMENT:
      if (state->original_tags.comment)
        {
          free(state->original_tags.comment);
          state->original_tags.comment = NULL;
        }
      if (char_data == NULL)
        {
          state->original_tags.comment = NULL;
        }
      else
        {
          if ((state->original_tags.comment = malloc(sizeof(char)*(length+1)))
              == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
            }
          else
            {
              snprintf(state->original_tags.comment,
                       length+1,"%s", char_data);
            }
        }      
      break;
    case SPLT_TAGS_PERFORMER:
      if (state->original_tags.performer)
        {
          free(state->original_tags.performer);
          state->original_tags.performer = NULL;
        }
      if (char_data == NULL)
        {
          state->original_tags.performer = NULL;
        }
      else
        {
          if ((state->original_tags.performer = malloc(sizeof(char)*(length+1)))
              == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
            }
          else
            {
              snprintf(state->original_tags.performer,
                       length+1,"%s", char_data);
            }
        }      
      break;
    case SPLT_TAGS_TRACK:
      state->original_tags.track = int_data;
      break;
    case SPLT_TAGS_GENRE:
      state->original_tags.genre = uchar_data;
      break;
    default:
      splt_u_error(SPLT_IERROR_INT,__func__, -500, NULL);
      break;
    }
  
  if (error != SPLT_OK)
    {
      splt_u_error(SPLT_IERROR_INT,__func__, -500, NULL);
    }
  
  return error;
}

//set track number
int splt_t_set_tags_int_field(splt_state *state, int index,
                              int tags_field, int data)
{
  int error = SPLT_OK;
  
  error = splt_t_new_tags_if_necessary(state,index);
  
  if (error != SPLT_OK)
    {
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
      return error;
    }
  
  if ((index >= state->split.real_tagsnumber)
      || (index < 0))
    {
      error = SPLT_ERROR_INEXISTENT_SPLITPOINT;
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
      return error;
    }
  else
    {
      char temp[100];
      switch (tags_field)
        {
        case SPLT_TAGS_TRACK:
          //debug
          snprintf(temp,100,"%d",data);
          splt_u_print_debug("Setting track tags at",index,temp);
          state->split.tags[index].track = data;
          break;
        default:
          break;
        }
    }
  
  return error;
}

//set genre
int splt_t_set_tags_uchar_field(splt_state *state, int index,
                                int tags_field, unsigned char data)
{
  int error = SPLT_OK;
  
  error = splt_t_new_tags_if_necessary(state,index);
  
  if (error != SPLT_OK)
    {
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
      return error;
    }
  
  if ((index >= state->split.real_tagsnumber)
      || (index < 0))
    {
      error = SPLT_ERROR_INEXISTENT_SPLITPOINT;
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
      return error;
    }
  else
    {
      char temp[100];
      switch (tags_field)
        {
        case SPLT_TAGS_GENRE:
          //debug
          snprintf(temp,100,"%uc",data);
          splt_u_print_debug("Setting genre tags at",index,temp);
          state->split.tags[index].genre = data;
          break;
        default:
          break;
        }
    }
  
  return error;
}

//returns the tags structure from the state
splt_tags *splt_t_get_tags(splt_state *state,int *tags_number)
{
  *tags_number = state->split.real_tagsnumber;
  return state->split.tags;
}

//get title, artist, album, year or comment
char *splt_t_get_tags_char_field(splt_state *state, int index,
                                 int tags_field)
{
  if ((index >= state->split.real_tagsnumber)
      || (index < 0))
    {
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
      return NULL;
    }
  else
    {
      switch(tags_field)
        {
        case SPLT_TAGS_TITLE:
          return state->split.tags[index].title;
          break;
        case SPLT_TAGS_ARTIST:
          return state->split.tags[index].artist;
          break;
        case SPLT_TAGS_ALBUM:
          return state->split.tags[index].album;
          break;
        case SPLT_TAGS_YEAR:
          return state->split.tags[index].year;
          break;
        case SPLT_TAGS_COMMENT:
          return state->split.tags[index].comment;
          break;
        case SPLT_TAGS_PERFORMER:
          return state->split.tags[index].performer;
          break;
        default:
          splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
          return NULL;
          break;
        }
    }
  
  return NULL;
}

//get track number
int splt_t_get_tags_int_field(splt_state *state, int index, int tags_field)
{
  if ((index >= state->split.real_tagsnumber)
      || (index < 0))
    {
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
      return 0;
    }
  else
    {
      switch (tags_field)
        {
        case SPLT_TAGS_TRACK:
          return state->split.tags[index].track;
          break;
        default:
          splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
          break;
        }
    }
  
  return 0;
}

//get genre
unsigned char splt_t_get_tags_uchar_field(splt_state *state, int index,
                                          int tags_field)
{
  if ((index >= state->split.real_tagsnumber)
      || (index < 0))
    {
      splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
      return 0x0;
    }
  else
    {
      switch (tags_field)
        {
        case SPLT_TAGS_GENRE:
          return state->split.tags[index].genre;
          break;
        default:
          splt_u_error(SPLT_IERROR_INT,__func__, index, NULL);
          break;
        }
    }
  
  return 0x0;
}

//this function clears all the tags
void splt_t_free_tags(splt_state *state)
{
  if (state->split.tags)
    {
      int i = 0;
      for (i = 0; i < state->split.real_tagsnumber; i++)
        {
          if (state->split.tags[i].title)
            {
              free(state->split.tags[i].title);
              state->split.tags[i].title = NULL;
            }
          if (state->split.tags[i].artist)
            {
              free(state->split.tags[i].artist);
              state->split.tags[i].artist = NULL;
            }
          if (state->split.tags[i].album)
            {
              free(state->split.tags[i].album);
              state->split.tags[i].album = NULL;
            }
          if (state->split.tags[i].performer)
            {
              free(state->split.tags[i].performer);
              state->split.tags[i].performer = NULL;
            }
          if (state->split.tags[i].year)
            {
              free(state->split.tags[i].year);
              state->split.tags[i].year = NULL;
            }
          if (state->split.tags[i].comment)
            {
              free(state->split.tags[i].comment);
              state->split.tags[i].comment = NULL;
            }
        }
      free(state->split.tags);
      state->split.tags = NULL;
    }
  
  state->split.real_tagsnumber = 0;
}

/********************************/
/* types: options access */

//returns if the library is locked or not
int splt_t_library_locked(splt_state *state)
{
  return state->iopts.library_locked;
}

//locks the library
void splt_t_lock_library(splt_state *state)
{
  state->iopts.library_locked = SPLT_TRUE;
}

//unlocks the library
void splt_t_unlock_library(splt_state *state)
{
  state->iopts.library_locked = SPLT_FALSE;
}

//returns if the messages are locked or not
int splt_t_messages_locked(splt_state *state)
{
  return state->iopts.messages_locked;
}

//lock messages send to client
void splt_t_lock_messages(splt_state *state)
{
  state->iopts.messages_locked = SPLT_TRUE;
}

//unlock messages send to client
void splt_t_unlock_messages(splt_state *state)
{
  state->iopts.messages_locked = SPLT_FALSE;
}

//sets the begin point as double float
//i = internal
void splt_t_set_i_begin_point(splt_state *state, double value)
{
  state->iopts.split_begin = value;
}

//sets the end point as double float
//i = internal
void splt_t_set_i_end_point(splt_state *state, double value)
{
  state->iopts.split_end = value;
}

//returns the begin point as double float
//i = internal
double splt_t_get_i_begin_point(splt_state *state)
{
  return state->iopts.split_begin;
}

//returns the end point as double float
//i = internal
double splt_t_get_i_end_point(splt_state *state)
{
  return state->iopts.split_end;
}

//sets an internal option
void splt_t_set_iopt(splt_state *state, int type, int value)
{
  switch (type)
    {
    case SPLT_MESS_FRAME_MODE_ENABLED:
      state->iopts.frame_mode_enabled = value;
      break;
    case SPLT_INTERNAL_PROGRESS_RATE:
      state->iopts.current_refresh_rate = value;
      break;
    default:
      break;
    }
}

//returns internal option
int splt_t_get_iopt(splt_state *state, int type) 
{
  switch (type)
    {
    case SPLT_MESS_FRAME_MODE_ENABLED:
      return state->iopts.frame_mode_enabled;
      break;
    case SPLT_INTERNAL_PROGRESS_RATE:
      return state->iopts.current_refresh_rate;
      break;
    default:
      break;
    }
  
  return 0;
}

//set default internal options
void splt_t_set_default_iopts(splt_state *state)
{
  splt_t_set_iopt(state, SPLT_MESS_FRAME_MODE_ENABLED,SPLT_FALSE);
  splt_t_set_iopt(state, SPLT_INTERNAL_PROGRESS_RATE,0);
  int error = SPLT_OK;
  splt_t_set_new_filename_path(state,NULL,&error);
}

//puts the default options for a normal split
static void splt_t_state_put_default_options(splt_state *state)
{
  //split
  state->split.tags = NULL;
  state->split.points = NULL;
  state->fname_to_split = NULL;
  state->path_of_split = NULL;
  state->m3u_filename = NULL;
  state->split.real_tagsnumber = 0;
  state->split.real_splitnumber = 0;
  state->split.splitnumber = 0;
  //syncerrors
  state->serrors->serrors_points = NULL;
  state->serrors->serrors_points_num = 0;
  //freedb
  state->fdb.search_results = NULL;
  state->fdb.cdstate = NULL;
  //wrap
  state->wrap->wrap_files = NULL;
  state->wrap->wrap_files_num = 0;
  //output format
  state->oformat.format_string = NULL;
  splt_t_new_oformat(state,SPLT_DEFAULT_OUTPUT);
  //client connection
  state->split.put_message = NULL;
  state->split.file_splitted = NULL;
  state->split.p_bar->progress_text_max_char = 40;
  snprintf(state->split.p_bar->filename_shorted,512, "%s","");
  state->split.p_bar->percent_progress = 0;
  state->split.p_bar->current_split = 0;
  state->split.p_bar->max_splits = 0;
  state->split.p_bar->progress_type = SPLT_PROGRESS_PREPARE;
  state->split.p_bar->user_data = 0;
  state->split.p_bar->progress = NULL;
  //other
  state->file_format = SPLT_MP3_FORMAT;
  state->cancel_split = SPLT_FALSE;
  //internal
  state->iopts.library_locked = SPLT_FALSE;
  state->iopts.messages_locked = SPLT_FALSE;
  state->iopts.current_refresh_rate = SPLT_DEFAULT_PROGRESS_RATE;
  state->iopts.frame_mode_enabled = SPLT_FALSE;
  state->iopts.new_filename_path = NULL;
  state->iopts.split_begin = 0;
  state->iopts.split_end = 0;
  //options
  state->options.output_filenames = SPLT_OUTPUT_DEFAULT;
  state->options.split_mode = SPLT_OPTION_NORMAL_MODE;
  state->options.tags = SPLT_CURRENT_TAGS;
  state->options.option_mp3_frame_mode = SPLT_TRUE;
  state->options.option_auto_adjust = SPLT_FALSE;
  state->options.option_input_not_seekable = SPLT_FALSE;
  state->options.parameter_number_tracks = SPLT_DEFAULT_PARAM_TRACKS;
  state->options.parameter_remove_silence = SPLT_FALSE;
  state->options.parameter_gap = SPLT_DEFAULT_PARAM_GAP;
  state->options.parameter_threshold = SPLT_DEFAULT_PARAM_THRESHOLD;
  state->options.parameter_offset = SPLT_DEFAULT_PARAM_OFFSET;
  state->options.parameter_minimum_length = SPLT_DEFAULT_PARAM_MINIMUM_LENGTH;
  state->options.split_time = 6000;
  
  state->options.tags_after_x_like_x_one = -1;
}

//set an int option
void splt_t_set_int_option(splt_state *state, int option_name,
                           int value)
{
  switch (option_name)
    {
    case SPLT_OPT_DEBUG_MODE:
      if (value)
        {
          global_debug = SPLT_TRUE;
        }
      else
        {
          global_debug = SPLT_FALSE;
        }
      break;
    case SPLT_OPT_OUTPUT_FILENAMES:
      state->options.output_filenames = value;
      break;
    case SPLT_OPT_SPLIT_MODE:
      state->options.split_mode = value;
      break;
    case SPLT_OPT_TAGS:
      state->options.tags = value;
      break;
    case SPLT_OPT_MP3_FRAME_MODE:
      state->options.option_mp3_frame_mode = value;
      break;
    case SPLT_OPT_AUTO_ADJUST:
      state->options.option_auto_adjust = value;
      break;
    case SPLT_OPT_INPUT_NOT_SEEKABLE:
      state->options.option_input_not_seekable = value;
      break;
    case SPLT_OPT_PARAM_NUMBER_TRACKS:
      state->options.parameter_number_tracks = value;
      break;
    case SPLT_OPT_PARAM_REMOVE_SILENCE:
      state->options.parameter_remove_silence = value;
      break;
    case SPLT_OPT_PARAM_GAP:
      state->options.parameter_gap = value;
      break;
    case SPLT_OPT_ALL_TAGS_LIKE_X_AFTER_X:
      state->options.tags_after_x_like_x_one = value;
      break;
    default:
      splt_u_error(SPLT_IERROR_INT,__func__, option_name, NULL);
      break;
    }
}

//sets a float option
void splt_t_set_float_option(splt_state *state, int option_name,
                             float value)
{
  switch (option_name)
    {
    case SPLT_OPT_SPLIT_TIME:
      state->options.split_time = value;
      break;
    case SPLT_OPT_PARAM_THRESHOLD:
      state->options.parameter_threshold = value;
      break;
    case SPLT_OPT_PARAM_OFFSET:
      state->options.parameter_offset = value;
      break;
    case SPLT_OPT_PARAM_MIN_LENGTH:
      state->options.parameter_minimum_length = value;
      break;
    default:
      splt_u_error(SPLT_IERROR_INT,__func__, option_name, NULL);
      break;
    }
}

//returns a int option (see mp3splt_types.h for int options)
int splt_t_get_int_option(splt_state *state, int option_name)
{
  int returned = 0;
  switch (option_name)
    {
    case SPLT_OPT_OUTPUT_FILENAMES:
      returned = state->options.output_filenames;
      break;
    case SPLT_OPT_SPLIT_MODE:
      returned = state->options.split_mode;
      break;
    case SPLT_OPT_TAGS:
      returned = state->options.tags;
      break;
    case SPLT_OPT_MP3_FRAME_MODE:
      returned = state->options.option_mp3_frame_mode;
      break;
    case SPLT_OPT_AUTO_ADJUST:
      returned = state->options.option_auto_adjust;
      break;
    case SPLT_OPT_INPUT_NOT_SEEKABLE:
      returned = state->options.option_input_not_seekable;
      break;
    case SPLT_OPT_PARAM_NUMBER_TRACKS:
      returned = state->options.parameter_number_tracks;
      break;
    case SPLT_OPT_PARAM_REMOVE_SILENCE:
      returned = state->options.parameter_remove_silence;
      break;
    case SPLT_OPT_PARAM_GAP:
      returned = state->options.parameter_gap;
      break;
    case SPLT_OPT_ALL_TAGS_LIKE_X_AFTER_X:
      returned = state->options.tags_after_x_like_x_one;
      break;
    default:
      splt_u_error(SPLT_IERROR_INT,__func__, option_name, NULL);
      break;
    }
  
  return returned;
}

//returns a float option (see mp3splt_types.h for int options)
float splt_t_get_float_option(splt_state *state, int option_name)
{
  float returned = 0;
  switch (option_name)
    {
    case SPLT_OPT_SPLIT_TIME:
      returned = state->options.split_time;
      break;
    case SPLT_OPT_PARAM_THRESHOLD:
      returned = state->options.parameter_threshold;
      break;
    case SPLT_OPT_PARAM_OFFSET:
      returned = state->options.parameter_offset;
      break;
    case SPLT_OPT_PARAM_MIN_LENGTH:
      returned = state->options.parameter_minimum_length;
      break;
    default:
      splt_u_error(SPLT_IERROR_INT,__func__, option_name, NULL);
      break;
    }
  
  return returned;
}

/********************************/
/* types: freedb access */

/* structures initialisation and frees */
static void splt_t_free_freedb_search(splt_state *state)
{
  splt_freedb_results *search_results = state->fdb.search_results;
  
  if (state->fdb.search_results)
    {
      int i;
      for(i = 0; i < search_results->number;i++)
      {
        if (search_results->results[i].revisions)
        {
          free(search_results->results[i].revisions);
          search_results->results[i].revisions = NULL;
        }
        if (search_results->results[i].name)
        {
          free(search_results->results[i].name);
          search_results->results[i].name = NULL;
        }
      }
      if (search_results->results)
        {
          free(search_results->results);
          search_results->results = NULL;
        }
      
      state->fdb.search_results->number = 0;
      free(state->fdb.search_results);
      state->fdb.search_results = NULL;
    }
}

//free the search results from the state
void splt_t_freedb_free_search(splt_state *state)
{
  splt_cd_state *cdstate = state->fdb.cdstate;
  
  splt_t_free_freedb_search(state);
  //freeing the cdstate
  if (cdstate != NULL)
    { 
      free(cdstate);
      cdstate = NULL;
    }
}

//sets a freedb result
//if revision != -1, then not a revision
int splt_t_freedb_append_result(splt_state *state,char *album_name,
                                int revision)
{
  int error = SPLT_OK;
  
  //if we had not initialised the 
  //search_results variable, do it now
  if (state->fdb.search_results->number == 0)
    {
      state->fdb.search_results->results =
        malloc(sizeof(splt_freedb_one_result));
      state->fdb.search_results->results[0].revisions = NULL;
      if (state->fdb.search_results->results == NULL)
        {
          error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
        }
      else
        {
          state->fdb.search_results->results[0].name = strdup(album_name);
          //if strdup fails
          if (state->fdb.search_results->results[0].name == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
            }
          else
            {
              state->fdb.search_results->results[state->fdb.search_results->number]
                .revision_number = 0;
              //unique identifier       
              state->fdb.search_results->results[state->fdb.search_results->number]
                .id = 0;
              state->fdb.search_results->number++;
            }
        }
    }
  else
    {
      //if its not a revision
      if (revision != -1)
        {
          state->fdb.search_results->results = 
            realloc(state->fdb.search_results->results,
                    (state->fdb.search_results->number + 1)
                    * sizeof(splt_freedb_one_result));
          state->fdb.search_results->results[state->fdb.search_results->number].revisions = NULL;
          if (state->fdb.search_results->results == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
            }
          else
            {
              state->fdb.search_results->results[state->fdb.search_results->number]
                .name = strdup(album_name);
              //if strdup fails
              if (state->fdb.search_results->results[state->fdb.search_results->number]
                  .name == NULL)
                {
                  error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
                }
              else
                {
                  state->fdb.search_results->results[state->fdb.search_results->number]
                    .revision_number = 0;
                  state->fdb.search_results->results[state->fdb.search_results->number]
                    .id = (state->fdb.search_results->results[state->fdb.search_results->number - 1]
                           .id + state->fdb.search_results->results[state->fdb.search_results->number - 1]
                           .revision_number + 1);
                  state->fdb.search_results->number++;
                }
            }
        }
      else
        //if it's a revision
        {
          //if it's the first revision
          if (state->fdb.search_results->results[state->fdb.search_results->number-1]
              .revision_number == 0)
            {
              state->fdb.search_results->results[state->fdb.search_results->number-1].revisions =
                malloc(sizeof(int));
              if (state->fdb.search_results->results[state->fdb.search_results->number-1].revisions
                  == NULL)
                {
                  error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;              
                }
              else
                {
                  state->fdb.search_results->results[state->fdb.search_results->number-1].revisions[0]
                    = atoi(album_name);
                  state->fdb.search_results->results[state->fdb.search_results->number-1].revision_number++;
                }
            }
          else
            //if it's not the first revision
            {
              state->fdb.search_results->results[state->fdb.search_results->number-1].revisions =
                realloc(state->fdb.search_results->results
                        [state->fdb.search_results->number-1].revisions,
                        (state->fdb.search_results->results[state->fdb.search_results->number-1]
                         .revision_number + 1)
                        * sizeof(int));
              if (state->fdb.search_results->results[state->fdb.search_results->number-1].revisions
                  == NULL)
                {
                  error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;              
                }
              else
                {
                  state->fdb.search_results->results[state->fdb.search_results->number-1].
                    revisions[state->fdb.search_results->results[state->fdb.search_results->number-1].revision_number]
                    = atoi(album_name);
                  state->fdb.search_results->results[state->fdb.search_results->number-1].revision_number++;
                }
            }
        }
    }
  
  return error;
}

//initialises a freedb search
//returns possible error
int splt_t_freedb_init_search(splt_state *state)
{
  int error = SPLT_OK;
  
  if ((state->fdb.cdstate = 
       malloc(sizeof(splt_cd_state))) == NULL)
    {
      error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
    }
  else
    {
      state->fdb.cdstate->foundcd = 0;
      //initialise the search results
      if ((state->fdb.search_results =
           malloc (sizeof(splt_freedb_results))) == NULL)
        {
          free(state->fdb.cdstate);
          state->fdb.cdstate = NULL;
          error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
        }
      else
        {
          state->fdb.search_results->number = 0;
          state->fdb.search_results->results = NULL;
        }
    }
  
  return error;
}

//returns the number of found cds
int splt_t_freedb_get_found_cds(splt_state *state)
{
  return state->fdb.cdstate->foundcd;
}

//sets the number of found cds
static void splt_t_freedb_set_found_cds(splt_state *state, int number)
{
  state->fdb.cdstate->foundcd = number;
}

//adds 1 to the number of freedb search found cds
void splt_t_freedb_found_cds_next(splt_state *state)
{
  splt_t_freedb_set_found_cds(state, splt_t_freedb_get_found_cds(state)+1);
}

//set a disc
void splt_t_freedb_set_disc(splt_state *state, int index,
                            char *discid, char *category,
			    int category_size)
{
  splt_cd_state *cdstate = state->fdb.cdstate;
  
  if ((index >= 0) && (index < SPLT_MAXCD))
    {
      memset(cdstate->discs[index].category, '\0', 20);
      snprintf(cdstate->discs[index].category, category_size,"%s",category);
			//snprintf seems buggy
#ifdef __WIN32__
			cdstate->discs[index].category[category_size-1] = '\0';
#endif
      splt_u_print_debug("Setting disc category ",0,cdstate->discs[index].category);
      
      memset(cdstate->discs[index].discid, '\0', SPLT_DISCIDLEN+1);
      snprintf(cdstate->discs[index].discid,SPLT_DISCIDLEN+1,"%s",discid);
			//snprintf seems buggy
#ifdef __WIN32__
			cdstate->discs[index].discid[SPLT_DISCIDLEN] = '\0';
#endif
      splt_u_print_debug("Setting disc id ",SPLT_DISCIDLEN+1,cdstate->discs[index].discid);
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT, __func__, index, NULL);
    }
}

//get disc category
char *splt_t_freedb_get_disc_category(splt_state *state, 
                                      int index)
{
  splt_cd_state *cdstate = state->fdb.cdstate;
  
  if ((index >= 0) && (index < cdstate->foundcd))
    {
      return cdstate->discs[index].category;
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT, __func__, index, NULL);
      return NULL;
    }
}

//get freedb discid
char *splt_t_freedb_get_disc_id(splt_state *state,
                                int index)
{
  splt_cd_state *cdstate = state->fdb.cdstate;
  
  if ((index >= 0) && (index < cdstate->foundcd))
    {
      return cdstate->discs[index].discid;
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT, __func__, index, NULL);
      return NULL;
    }
}

/********************************/
/* types: silence access */

//creates a new ssplit structure
int splt_t_ssplit_new(struct splt_ssplit **silence_list, 
                      float begin_position, float end_position, int len)
{
  struct splt_ssplit *temp;
  struct splt_ssplit *s_new;
  
  if ((s_new = malloc(sizeof(struct splt_ssplit)))==NULL)
    return -1;
  s_new->len = len;
  s_new->begin_position = begin_position;
  s_new->end_position = end_position;
  s_new->next = NULL;
  
  temp = *silence_list;
  if (temp == NULL)
    {
      *silence_list = s_new; // No elements
    }
  else 
    {
      if (temp->len < len)
        {
          s_new->next = temp;
          *silence_list = s_new;
        }
      else  
        {
          if (temp->next == NULL)
            temp->next = s_new;
          else 
            {
              while (temp != NULL) 
                {
                  if (temp->next != NULL) 
                    {
                      if (temp->next->len < len) 
                        {
                          // We build an ordered list by len to keep most probable silence points
                          s_new->next = temp->next;
                          temp->next = s_new;
                          break;
                        }
                    }
                  else 
                    {
                      temp->next = s_new;
                      break;
                    }
                  temp = temp->next;
                }
            }
        }
    }

  return 0;
}

//free the ssplit structure
void splt_t_ssplit_free (struct splt_ssplit **silence_list)
{
  struct splt_ssplit *temp, *saved;
  
  if (silence_list)
    {
      temp = *silence_list;
      
      while (temp != NULL)
        {
          saved = temp->next;
          free(temp);
          temp = saved;
        }
      
      *silence_list = NULL;
    }
}
/********************************/
/* types: syncerrors access */

//appends a syncerror splitpoint
int splt_t_serrors_append_point(splt_state *state, off_t point)
{
  int error = SPLT_OK;
  
  state->mstate->syncerrors++;
  state->serrors->serrors_points_num++;
  
  if (point > 0)
    {
      //allocate memory for the splitpoints
      if (state->serrors->serrors_points == NULL)
        {
          if((state->serrors->serrors_points = 
              malloc(sizeof(off_t)*(state->mstate->syncerrors+2)))
             == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
            }
          else
            {
              state->serrors->serrors_points[0] = 0;
            }
        }
      else
        {
          if((state->serrors->serrors_points = 
              realloc(state->serrors->serrors_points,
                      sizeof(off_t)*(state->mstate->syncerrors+2)))
             == NULL)
            {
              error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
            }
        }
  
      if (error == SPLT_OK)
        {
          state->serrors->serrors_points[state->mstate->syncerrors] = 
            point;
          
          if (state->serrors->serrors_points[state->mstate->syncerrors] == -1)
            {
              error = SPLT_MP3_ERR_SYNC;
            }
        }
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT, __func__, point, NULL);
    }
  
  return error;
}

//sets a syncerror point
void splt_t_serrors_set_point(splt_state *state, int index,
                              off_t point)
{
  if ((index <= state->serrors->serrors_points_num+1)
      && (index >= 0))
    {
      state->serrors->serrors_points[index] = point;
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT, __func__, index, NULL);
    }
}

//returns a syncerror point
off_t splt_t_serrors_get_point(splt_state *state, int index)
{
  if ((index <= state->serrors->serrors_points_num)
      && (index >= 0))
    {
      return state->serrors->serrors_points[index];
    }
  else
    {
      splt_u_error(SPLT_IERROR_INT, __func__, index, NULL);
      return -1;
    }
}

//free the syncerrors
void splt_t_serrors_free(splt_state *state)
{
  if (state->serrors->serrors_points)
    {
      free(state->serrors->serrors_points);
      state->serrors->serrors_points = NULL;
    }
}

/********************************/
/* types: wrap access */

//appends a file from to the wrap files
int splt_t_wrap_put_file(splt_state *state,
                         //how many files
                         int wrapfiles,
                         int index, char *filename)
{
  int error = SPLT_OK;
  
  //we allocate memory the first time for all files
  if (index == 0)
    {
      if ((state->wrap->wrap_files = 
           malloc(wrapfiles * sizeof(char*)))
          == NULL)
        {
          error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
        }
      else
        {
          state->wrap->wrap_files_num = 0;
        }
    }
  
  if (error == SPLT_OK)
    {
      //if strdup fails
      if ((state->wrap->wrap_files[index] = strdup(filename))
          == NULL)
        {
          error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
        }
      else
        {
          state->wrap->wrap_files_num++;
        }
    }
  
  return error;
}

//free the wrap files
void splt_t_wrap_free(splt_state *state)
{
  splt_t_free_files(state->wrap->wrap_files,
                    state->wrap->wrap_files_num);
  state->wrap->wrap_files_num = 0;
}

/******************************/
/* types: client communication */

//says to the program using the library the splitted file
void splt_t_put_splitted_file(splt_state *state, char *filename)
{
  //put splitted file 
  if (state->split.file_splitted != NULL)
    {
      state->split.file_splitted(filename,state->split.p_bar->user_data);
      //if we create a m3u file
      char *m3u_file = splt_t_get_m3u_filename(state);
      if (m3u_file != NULL)
      {
        //we don't care about the path; we clean the string
        char *real_name_m3u_file = splt_u_cleanstring(m3u_file);
        char *path_of_split = splt_t_get_path_of_split(state);
        char *new_m3u_file = NULL;
        int malloc_number = strlen(real_name_m3u_file)+strlen(path_of_split)+2;
        if ((new_m3u_file = malloc(malloc_number)) != NULL)
          {
            snprintf(new_m3u_file,malloc_number,"%s%c%s",
                     path_of_split, SPLT_DIRCHAR,real_name_m3u_file);
            //we open the m3u file
            FILE *file_input = NULL;
            if((file_input = fopen(new_m3u_file, "a+")))
              {
                //we don't care about the path of the splitted filename
                fprintf(file_input,"%s\n",splt_u_get_real_name(filename));
                fclose(file_input);
              }
            free(new_m3u_file);
          }
      }
    }
  else
    {
      //splt_u_error(SPLT_IERROR_INT,__func__, -500, NULL);
    }
}

//puts in the state->progress_text the real text 
//of the progress
//type = 0 we put " preparing... "
//type = 1, we put " creating ... ",
//type = 2 we put " searching for sync errors ..."
//type = 3 we put " scanning for silence ..."
//we write the filename that we are currently splitting
void splt_t_put_progress_text(splt_state *state,int type)
{
  //filename_shorted_length = sp_state->progress_text_max_char;
  //if we have a too long filename, display it shortly
  char filename_shorted[512] = "";
  
  int err = SPLT_OK;
  
  //if we have a progress function
  if (state->split.p_bar->progress != NULL)
    {
      char *point_name = NULL;
      int curr_split =
        splt_t_get_current_split(state);
      point_name = 
        splt_t_get_splitpoint_name(state, curr_split-1,&err);
      
      if (point_name != NULL)
        {
          //we put the extension of the song
          char extension[10] = SPLT_MP3EXT;
          if (splt_t_get_file_format(state) == SPLT_OGG_FORMAT)
            {
              snprintf(extension, 9, SPLT_OGGEXT);
            }
          
          snprintf(filename_shorted,
                   state->split.p_bar->progress_text_max_char,"%s%s",
                   point_name,extension);
          
          if (strlen(point_name)
              > state->split.p_bar->progress_text_max_char)
            {
              filename_shorted[strlen(filename_shorted)-1] = '.';
              filename_shorted[strlen(filename_shorted)-2] = '.';
              filename_shorted[strlen(filename_shorted)-3] = '.';
            }
        }
      
      snprintf(state->split.p_bar->filename_shorted, 512,"%s",
               filename_shorted);
      
      state->split.p_bar->current_split = splt_t_get_current_split(state);
      state->split.p_bar->max_splits = state->split.splitnumber-1;
      state->split.p_bar->progress_type = type;
    }
}

//puts a message to the client
void splt_t_put_message_to_client(splt_state *state, int message)
{
  if (!splt_t_messages_locked(state))
    {
      if (state->split.put_message != NULL)
        {
          state->split.put_message(message);
        }
      else
        {
          //splt_u_error(SPLT_IERROR_INT,__func__, -500, NULL);
        }
    }
}

//update the progress,
//current_point = the current progress point
//total_points = total progress points
//split_stage = 1 means we put on the whole progress bar,
//if split_stage = 2,
//progress_start = from where to start the progress (fraction)
//refresh_rate = the refresh rate of the display
void splt_t_update_progress(splt_state *state, float current_point,
                            float total_points, int progress_stage,
                            float progress_start, int refresh_rate)
{
  //if we have a progress callback function
  if (state->split.p_bar->progress != NULL)
    {
      if (splt_t_get_iopt(state, SPLT_INTERNAL_PROGRESS_RATE)
          > refresh_rate)
        {
          //shows the progress
          state->split.p_bar->percent_progress = 
            (current_point / total_points);
      
          state->split.p_bar->percent_progress = 
            state->split.p_bar->percent_progress / progress_stage +
            progress_start;
          
          //security check
          if (state->split.p_bar->percent_progress < 0)
            {
              state->split.p_bar->percent_progress = 0;
            }
          if (state->split.p_bar->percent_progress > 1)
            {
              state->split.p_bar->percent_progress = 1;
            }
          
          //call
          state->split.p_bar->progress(state->split.p_bar);
          splt_t_set_iopt(state, SPLT_INTERNAL_PROGRESS_RATE, 0);
        }
      else
        {
          splt_t_set_iopt(state, SPLT_INTERNAL_PROGRESS_RATE,
                          splt_t_get_iopt(state, SPLT_INTERNAL_PROGRESS_RATE)+1);
        }
    }
}

/********************************/
/* types: miscelanneous */

//frees the splitpoints and the tags
void splt_t_free_splitpoints_tags(splt_state *state)
{
  splt_t_free_splitpoints(state);
  splt_t_free_tags(state);
}

//cleans one split char data
void splt_t_clean_one_split_data(splt_state *state, int num)
{
  if (splt_t_tags_exists(state,num))
    {
      splt_t_set_tags_char_field(state,num, SPLT_TAGS_YEAR,NULL);
      splt_t_set_tags_char_field(state,num, SPLT_TAGS_ARTIST,NULL);
      splt_t_set_tags_char_field(state,num, SPLT_TAGS_ALBUM, NULL);
      splt_t_set_tags_char_field(state,num, SPLT_TAGS_TITLE,NULL);
      splt_t_set_tags_char_field(state,num, SPLT_TAGS_COMMENT,NULL);
      splt_t_set_tags_char_field(state,num, SPLT_TAGS_PERFORMER,NULL);
    }
  
  if (splt_t_splitpoint_exists(state, num))
    {
      splt_t_set_splitpoint_name(state, num, NULL);
    }
}

//frees an array of strings
static void splt_t_free_files(char **files, int number)
{
  int i = 0;
  if (files != NULL)
    {
      if (number != 0)
        {
          for (i = 0; i < number; i++)
            {
              free(files[i]);
              files[i] = NULL;
            }
          free(files);
          files = NULL;
        }
    }
}

//sets the stop split value
void splt_t_set_stop_split(splt_state *state, int bool_value)
{
  //splt_t_put_message_to_client(state,SPLT_MESS_STOP_SPLIT);
  state->cancel_split = bool_value;
}

//if we cancel split or not
int splt_t_split_is_canceled(splt_state *state)
{
  return state->cancel_split;
}

//cleans data for the strings in *state
void splt_t_clean_split_data(splt_state *state,int tracks)
{
  splt_t_set_current_split(state,0);
  do {
    splt_t_clean_one_split_data(state,state->split.current_split);
    splt_t_current_split_next(state);
  } while (splt_t_get_current_split(state)<tracks);
}
