/*
 * Mp3Splt -- Utility for mp3/ogg splitting without decoding
 *
 * Copyright (c) 2002-2005 M. Trotta - <mtrotta@users.sourceforge.net>
 * Copyright (c) 2005-2006 Munteanu Alexandru - <io_alex_2002@yahoo.fr>
 *
 * http://mp3splt.sourceforge.net
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA.
 */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <sys/stat.h>
#include <ctype.h>

#include <libmp3splt/mp3splt.h>

#include "getopt.h"

//constants
//we include the "config.h" file from the config options
#ifdef HAVE_CONFIG_H
#include "config.h"
#else
#define VERSION "2.2_rc1"
#define PACKAGE_NAME "mp3splt-gtk"
#endif
#define MP3SPLT_DATE "21/12/06"
#define MP3SPLT_AUTHOR1 "Matteo Trotta"
#define MP3SPLT_AUTHOR2 "Munteanu Alexandru Ionut"
#define MP3SPLT_EMAIL1 "<mtrotta AT users.sourceforge.net>"
#define MP3SPLT_EMAIL2 "<io_alex_2002 AT yahoo.fr>"
#define MP3SPLT_CDDBFILE "query.cddb"

//command line options
typedef struct {
  //wrap split, list wrap options, error split
  short w_option; short l_option; short e_option;
  //frame mode, cddb/cue option, time split
  short f_option; short c_option; short t_option;
  //silence split, adjust option, parameters
  short s_option; short a_option; short p_option;
  //output filename, output directory, seekable
  short o_option; short d_option; short k_option;
  //custom tags, no tags, quiet option
  short g_option; short n_option; short q_option;
  //info -i option, m3u file option
  short i_option; short m_option;
  //cddb argument, output dir argument, parameters arguments with -p
  char *cddb_arg; char *dir_arg; char *param_args;
  //the m3u filename
  char *m3u_arg;
  //custom tags with -g
  char *custom_tags;
  //output format (-o)
  char *output_format;
  //the parsed freedb_search_type
  //the parsed freedb_search_server
  //the parsed freedb_search_port
  int freedb_search_type;
  char freedb_search_server[256];
  int freedb_search_port;
  //the parsed freedb_get_type
  //the parsed freedb_get_server
  //the parsed freedb_get_port
  int freedb_get_type;
  char freedb_get_server[256];
  int freedb_get_port;
} Options;

//we make a global variable, we use it in
//sigint_handler
splt_state *state;

//prints a message
void print_message(char *m)
{
  fprintf(stdout,"%s\n",m);
  fflush(stdout);
}

//prints a warning
void print_warning(char *w)
{
  fprintf(stderr,"Warning, %s\n",w);
  fflush(stderr);
}

//puts an error message and exists the program with error 1
void put_error_message_exit(char *message, Options *opt,
    splt_state *state)
{
  fprintf(stderr,"%s\n",message);
  fflush(stderr);
  //we free options
  free(opt);
  int err = SPLT_OK;
  //we free left variables in the state
  mp3splt_free_state(state,&err);
  exit(1);
}

//shows a small mp3splt help and exits with error 1
void show_small_help_exit(Options *opt,splt_state *state)
{
  //we free options
  free(opt);
  int err = SPLT_OK;
  //we free left variables in the state
  mp3splt_free_state(state,&err);

  fprintf(stdout,
      "\n"
      "USAGE (Please read man page for complete documentation)\n"
      "      mp3splt [SPLIT_MODE] [OPTIONS] FILE [BEGIN_TIME1] [TIME2] ... [END_TIME]\n"
      "      TIME FORMAT: min.sec[.0-99], even if minutes are over 59. \n"
      "\nSPLIT_MODE\n"
      "\tIf you have a ogg stream, split from 0 to a big number to fix it; \n\t example : mp3splt stream_song.ogg 0.0 7000.0\n"
      " -t + TIME: to split files every fixed time len. (TIME format same as above). \n"
      " -c + file.cddb, file.cue or \"query\". Get splitpoints and filenames from a\n"
      "      .cddb or .cue file or from Internet (\"query\"). Use -a to auto-adjust.\n"
      " -s   Silence detection: automatically find splitpoint. (Use -p for arguments)\n"
      " -w   Splits wrapped files created with Mp3Wrap or AlbumWrap.\n"
      " -l   Lists the tracks from file without extraction. (Only for wrapped mp3)\n"
      " -e   Error mode: split mp3 with sync error detection. (For concatenated mp3)\n"
      " -i   Count how many silence splitpoints we have with silence detection\n"
      "      (Use -p for arguments)\n"
      "\nOPTIONS\n"
      " -m + M3U_FILE: Creates a m3u file with the newly splitted files\n"
      " -f   Frame mode (mp3 only): process all frames. For higher precision and VBR.\n"
      " -a   Auto-Adjust splitpoints with silence detection. (Use -p for arguments)\n"
      " -p + PARAMETERS (th, nt, off, min, rm, gap): user arguments for -s and -a.\n"
                                                     " -o + FORMAT: output filename pattern. Can contain those variables:\n"
                                                     "      @a: artist tag, @p: performer tag (might not exists), @b: album tag\n"
                                                     "      @t: title tag, @n: track number tag, @f: original filename\n"
                                                     " -g + TAGS_FORMAT: allows you to put custom tags "
                                                     "to your splitted files.\n"
                                                     "      Example, tags for the first splitted file and all the others like the second one : \n"
                                                     "       @o means that we put the original tags, before replacing artist with \"artist2\"\n\t"
                                                     "[@a=artist1,@t=title1]%%[@o,@a=artist2]\n"
                                                     " -d + DIRNAME: to put all output files in the directory DIRNAME.\n"
                                                     " -k   Consider input not seekable (slower). Default when input is STDIN (-).\n"
                                                     " -n   No Tag: does not write ID3v1 or vorbis comment. If you need clean files.\n"
                                                     " -q   Quiet mode: do not prompt for anything and print less messages.\n"
                                                     " -D   Debug mode: used to debug the program (by developers).\n");
  fflush(stdout);
  exit(0);
}

//removes options until offset
char **rmopt (char **argv, int offset, int tot)
{
  char **first = &argv[1];
  while (offset < tot)
  {
    *first = argv[offset];
    first++;
    offset++;
  }

  return argv;
}

//removes the element index from the argv
char **rmopt2 (char **argv,int index, int tot)
{
  char **first = &argv[1];
  int i = 1;
  while (i < tot)
  {
    if (i != index)
    {
      *first = argv[i];
      first++;
    }
    i++;
  }

  return argv;
}

//parse the -p option
int parse_arg(char *arg, float *th, int *gap, int *nt,
    float *off, int *rm, float *min)
{
  char *ptr;
  int found=0;

  if ((gap!=NULL) && ((ptr=strstr(arg, "gap"))!=NULL))
  {
    if ((ptr=strchr(ptr, '='))!=NULL)
    {
      if (sscanf(ptr+1, "%d", gap)==1)
      {
        found++;
      }
      else 
      {
        print_warning("bad gap argument. It will be ignored!");
      }
    }
  }
  if ((th!=NULL) && ((ptr=strstr(arg, "th"))!=NULL))
  {
    if ((ptr=strchr(ptr, '='))!=NULL)
    {
      if (sscanf(ptr+1, "%f", th)==1)
      {
        found++;
      }
      else 
      {
        print_warning("bad threshold argument. It will be ignored!");
      }
    }
  }
  if ((nt!=NULL) && ((ptr=strstr(arg, "nt"))!=NULL))
  {
    if ((ptr=strchr(ptr, '='))!=NULL)
    {
      if (sscanf(ptr+1, "%d", nt)==1)
      {
        found++;
      }
      else 
      {
        print_warning("bad tracknumber argument. It will be ignored!");
      }
    }
  }
  if (rm!=NULL)
  {
    if ((ptr=strstr(arg, "rm"))!=NULL) {
      found++;
      *rm = 1;
    }
  }
  if ((off!=NULL) && ((ptr=strstr(arg, "off"))!=NULL))
  {
    if ((ptr=strchr(ptr, '='))!=NULL)
    {
      if (sscanf(ptr+1, "%f", off)==1)
      {
        found++;
      }
      else 
      {
        print_warning("bad offset argument. It will be ignored!");
      }
    }
  }
  if ((min!=NULL) && ((ptr=strstr(arg, "min"))!=NULL))
  {
    if ((ptr=strchr(ptr, '='))!=NULL)
    {
      if (sscanf(ptr+1, "%f", min)==1)
      {
        found++;
      }
      else 
      {
        print_warning("bad minimum silence length argument. It will be ignored!");
      }
    }
  }
  return found;
}

//check if we have the correct arguments
void check_args(int argc, Options *opt, splt_state *state)
{
  if (argc < 2)
  {
    show_small_help_exit(opt,state);
  }
  else
  {
    //TODO
    //-i option

    //if we want input not seekable (-k)
    if (opt->k_option)
    {
      if (opt->s_option || opt->a_option ||
          opt->e_option || opt->w_option)
      {
        put_error_message_exit("Error: can't use -k option with\
            -s -a -e -w -l (input must be seekable)",opt,state);
      }
    }

    //if we dewrap (-w)
    if (opt->w_option)
    {
      if (opt->l_option || opt->e_option ||
          opt->f_option || opt->c_option ||
          opt->t_option || opt->s_option ||
          opt->a_option || opt->p_option ||
          opt->o_option || opt->n_option ||
          opt->g_option)
      {
        put_error_message_exit("Error: usage is 'mp3splt -w FILE...'",opt,state);
      }
    }

    //if we list wrapped files (-l)
    if (opt->l_option)
    {
      if (opt->t_option || opt->s_option ||
          opt->e_option || opt->f_option ||
          opt->d_option || opt->p_option ||
          opt->o_option || opt->c_option ||
          opt->a_option || opt->g_option ||
          opt->n_option)
      {
        put_error_message_exit("Error: usage is 'mp3splt -l FILE...'",opt,state);
      }
    }

    //error mode (-e)
    if (opt->e_option)
    {
      if (opt->c_option || opt->t_option || 
          opt->s_option || opt->a_option || 
          opt->p_option || opt->f_option ||
          opt->n_option)
      {
        put_error_message_exit("Error: usage is 'mp3splt -e FILE...'",opt,state);
      }
    }

    //frame mode (-f)
    if (opt->f_option)
    {
    }

    //cddb/cue/freedb (-c)
    if (opt->c_option)
    {
      if (opt->t_option || opt->s_option || 
          opt->g_option)
      {
        put_error_message_exit("Error: usage is 'mp3splt -c \
            SOURCE FILE...''",opt,state);
      }
    }

    //time split (-t)
    if (opt->t_option)
    {
      if (opt->s_option || opt->e_option ||
          opt->p_option)
      {
        put_error_message_exit("Error: usage is 'mp3splt -t TIME FILE...'",opt,state);
      }
    }

    //silence split (-s)
    if (opt->s_option)
    {
      if (opt->e_option || opt->a_option)
      {
        put_error_message_exit("Error: usage is 'mp3splt \
            -s [-p th=THRESHOLD,nt=NUMBER,off=OFFSET,rm] FILE...'",opt,state);
      }
    }

    //auto adjust option (-a)
    if (opt->a_option)
    {
    }

    //parameters (-p)
    if (opt->p_option)
    {
      if (!opt->a_option && !opt->s_option
          && !opt->i_option)
      {
        put_error_message_exit("Error : cannot use '-p' without \
            '-a' or '-s'",opt,state);
      }
    }

    //output format (-o)
    if (opt->o_option)
    {
    }

    //custom tags (-g)
    if (opt->g_option)
    {
      if (opt->n_option)
      {
        put_error_message_exit("Error: cannot use '-g' with '-n'",opt,state);
      }
    }

    //directory (-d)
    if (opt->d_option)
    {
    }

    //input not seekable (-k)
    if (opt->k_option)
    {
    }

    //no tags (-n)
    if (opt->n_option)
    {
    }

    //quiet mode (-q)
    if (opt->n_option)
    {
    }
  }
}

//prints a confirmation error that comes from the library
void print_confirmation_error(int conf, Options *opt, 
    splt_state *state)
{
  switch (conf)
  {
    case SPLT_SPLITPOINT_BIGGER_THAN_LENGTH :
      print_message(" file splitted, splitpoints bigger than length");
      break;
    case SPLT_OK_SPLITTED :
      print_message(" file splitted");
      break;
    case SPLT_OK_SPLITTED_EOF :
      print_message(" file splitted");
      break;
    case SPLT_OK :
      //fprintf(stderr," bug in the program, please report it");
      break;
    case SPLT_ERROR_SPLITPOINTS :
      put_error_message_exit(" error: not enough splitpoints (<2)",opt,state);
      break;
    case SPLT_ERROR_CANNOT_OPEN_FILE :
      put_error_message_exit(" error: cannot open file",opt,state);
      break;
    case SPLT_ERROR_INVALID :
      put_error_message_exit(" error: invalid file",opt,state);
      break;
    case SPLT_ERROR_EQUAL_SPLITPOINTS :
      put_error_message_exit(" error: equal splitpoints",opt,state);
      break;
    case SPLT_ERROR_SPLITPOINTS_NOT_IN_ORDER :
      put_error_message_exit(" error: splitpoints not in order",opt,state);
      break;
    case SPLT_ERROR_NEGATIVE_SPLITPOINT :
      put_error_message_exit(" error: negative splitpoint",opt,state);
      break;
    case SPLT_ERROR_INCORRECT_PATH :
      put_error_message_exit(" error: incorrect destination folder",opt,state);
      break;
    case SPLT_ERROR_INVALID_FORMAT :
      put_error_message_exit(" error: invalid format",opt,state);
      break;
    case SPLT_FREEDB_OK :
      print_message(" freedb search processed ok");
      break;
    case SPLT_FREEDB_FILE_OK :
      print_message(" freedb processed ok");
      break;
    case SPLT_FREEDB_CDDB_OK :
      print_message(" cddb file processed ok");
      break;
    case SPLT_FREEDB_CUE_OK :
      print_message(" cue file processed ok");
      break;
    case SPLT_FREEDB_ERROR_INITIALISE_SOCKET :
      put_error_message_exit(" error: cannot initialise socket",opt,state);
      break;
    case SPLT_FREEDB_ERROR_CANNOT_GET_HOST :
      put_error_message_exit(" error: cannot get host by name",opt,state);
      break;
    case SPLT_FREEDB_ERROR_CANNOT_OPEN_SOCKET :
      put_error_message_exit(" error: cannot open socket",opt,state);
      break;
    case SPLT_FREEDB_ERROR_CANNOT_CONNECT :
      put_error_message_exit(" error: cannot connect to host",opt,state);
      break;
    case SPLT_FREEDB_ERROR_CANNOT_SEND_MESSAGE :
      put_error_message_exit(" error: cannot send message to host",opt,state);
      break;
    case SPLT_FREEDB_ERROR_INVALID_SERVER_ANSWER :
      put_error_message_exit(" error: invalid server answer",opt,state);
      break;
    case SPLT_FREEDB_ERROR_SITE_201 :
      put_error_message_exit(" error: error 201 while connecting"
          " to site",opt,state);
      break;
    case SPLT_FREEDB_ERROR_SITE_200 :
      put_error_message_exit(" error: error 200 while connecting"
          " to site",opt,state);
      break;
    case SPLT_FREEDB_ERROR_SITE :
      put_error_message_exit(" freedb error: unknown error from the website",opt,state);
      break;
    case SPLT_FREEDB_NO_SUCH_CD_IN_DATABASE :
      put_error_message_exit(" freedb error: No such CD entry in database",opt,state);
      break;
    case SPLT_FREEDB_ERROR_BAD_COMMUNICATION :
      put_error_message_exit(" error: bad communication with site",opt,state);
      break;
    case SPLT_FREEDB_ERROR_GETTING_INFOS :
      put_error_message_exit(" error: could not get infos from site",opt,state);
      break;
    case SPLT_FREEDB_NO_CD_FOUND :
      print_message(" no cd found for this search");
      break;
    case SPLT_FREEDB_MAX_CD_REACHED :
      print_message(" maximum number of found"
          " CD reached");
      break;
    case SPLT_CUE_ERROR_CANNOT_OPEN_FILE_READING:
      put_error_message_exit(" cue error: cannot read file",opt,state);
      break;
    case SPLT_CDDB_ERROR_CANNOT_OPEN_FILE_READING:
      put_error_message_exit(" cddb error: cannot read file",opt,state);
      break;
    case SPLT_INVALID_CUE_FILE:
      put_error_message_exit(" cue error: invalid cue file",opt,state);
      break;
    case SPLT_INVALID_CDDB_FILE:
      put_error_message_exit(" cddb error: invalid cddb file",opt,state);
      break;
    case SPLT_SILENCE_OK:
      print_message(" silence split ok");
      break;
    case SPLT_ERROR_CANNOT_SYNC:
      put_error_message_exit(" sync error: cannot sync files",opt,state);
      break;
    case SPLT_ERROR_INCOMPATIBLE_OPTIONS:
      put_error_message_exit(" error: incompatible options",opt,state);
      break;
    case SPLT_ERROR_SILENCE:
      put_error_message_exit(" error for the silence split",opt,state);
      break;
    case SPLT_SYNC_OK:
      print_message(" error mode ok");
      break;
    case SPLT_ERR_SYNC:
      put_error_message_exit(" error: sync",opt,state);
      break;
    case SPLT_ERR_NO_SYNC_FOUND:
      print_message(" no sync errors found                ");
      break;
    case SPLT_ERR_TOO_MANY_SYNC_ERR:
      put_error_message_exit(" sync error: too many sync errors",opt,state);
      break;
    case SPLT_DEWRAP_OK:
      print_message(" wrap split ok");
      break;
    case SPLT_DEWRAP_ERR_FILE_LENGTH:
      put_error_message_exit(" wrap error: file length",opt,state);
      break;
    case SPLT_DEWRAP_ERR_VERSION_OLD:
      put_error_message_exit(" wrap error: version too old",opt,state);
      break;
    case SPLT_DEWRAP_ERR_NO_FILE_OR_BAD_INDEX:
      put_error_message_exit(" wrap error: no file or bad index",opt,state);
      break;
    case SPLT_DEWRAP_ERR_FILE_DAMAGED_INCOMPLETE:
      put_error_message_exit(" wrap error: file damaged or incomplete",opt,state);
      break;
    case SPLT_DEWRAP_ERR_FILE_NOT_WRAPED_DAMAGED:
      put_error_message_exit(" wrap error: maybe not a wrapped"
          " file or wrap file damaged",opt,state); 
      break;
    case SPLT_TIME_SPLIT_OK:
      print_message(" time split ok");
      break;
    case SPLT_ERROR_INPUT_OUTPUT_SAME_FILE:
      put_error_message_exit(" error: input and output are the same file",opt,state); 
      break;
    case SPLT_NO_SILENCE_SPLITPOINTS_FOUND:
      print_message(" no silence splitpoints found    ");
      break;
    case SPLT_ERROR_CANNOT_ALLOCATE_MEMORY:
      put_error_message_exit(" error: unable to allocate"
          " memory",opt,state);
      break;
    case SPLT_MIGHT_BE_VBR:
      print_message(" warning: might be VBR,"
          " use frame mode");
      break;
    case SPLT_ERROR_CANNOT_OPEN_DEST_FILE:
      put_error_message_exit(" error: cannot open"
          " destination file",opt,state);
      break;
    case SPLT_ERROR_CANT_WRITE_TO_OUTPUT_FILE:
      put_error_message_exit(" error: cannot write"
          " to output file",opt,state);
      break;
    case SPLT_ERROR_WHILE_READING_FILE:
      put_error_message_exit(" error: cannot read file",opt,state);
      break;
    case SPLT_ERROR_SEEKING_FILE:
      put_error_message_exit(" error: cannot seek file",opt,state);
      break;
    case SPLT_ERROR_BEGIN_OUT_OF_FILE:
      put_error_message_exit(" error: begin point out of file",opt,state);
      break;
    case SPLT_ERROR_INEXISTENT_FILE:
      put_error_message_exit(" error: inexistent file",opt,state);
      break;
    case SPLT_SPLIT_CANCELLED:
      print_message(" split process cancelled");
      break;
    case SPLT_ERROR_WRAP_NOT_IMPLEMENTED:
      put_error_message_exit(" wrap error: wrap not implemented for this format",opt,state);
      break;
    case SPLT_OUTPUT_FORMAT_OK:

      break;
    case SPLT_OUTPUT_FORMAT_ERROR:
      print_message(" warning: output format error");
      break;
    case SPLT_OUTPUT_FORMAT_AMBIGUOUS:
      print_message(" warning: output format ambiguous");
      break;
    default:
      break;
  }
}

//converts string s in hundredth
//and returns seconds
//returns -1 if it cannot convert (usually we hope it can :)
long c_hundreths (char *s)
{
  long minutes=0, seconds=0, hundredths=0, i;
  long hun = -1;

  for(i=0; i<strlen(s); i++) // Some checking
  {
    if ((s[i]<0x30 || s[i] > 0x39) && (s[i]!='.'))
    {
      return -1;
    }
  }

  if (sscanf(s, "%ld.%ld.%ld", &minutes, &seconds, &hundredths)<2)
  {
    return -1;
  }

  if ((minutes < 0) || (seconds < 0) || (hundredths < 0))
  {
    return -1;
  }

  if ((seconds > 59) || (hundredths > 99))
  {
    return -1;
  }

  if (s[strlen(s)-2]=='.')
  {
    hundredths *= 10;
  }

  hun = hundredths;
  hun += (minutes*60 + seconds) * 100;

  return hun;
}

//interaction with the user when he was choosing the
//freedb.org search to detect if the entered string was a number
int checkstring (char *s)
{
  int i;
  for (i=0; i<strlen(s); i++)
  {
    if ((isalnum(s[i])==0)&&(s[i]!=0x20))
    {
      fprintf (stderr, " Error: '%c' is not allowed!\n", s[i]);
      fflush(stderr);
      return -1;
    }
  }

  return 0;
}

//for the moment 3 ways of getting the file and one way to search it
//freedb get type can be : cddb_cgi or cddb_protocol
//freedb search type can be : cddb_cgi or web_search
//query[get=cddb_cgi://freedb2.org/~cddb/cddb.cgi:80,search=cddb_cgi://freedb2.org/~cddb/cddb.cgi:80]
//query[get=cddb_protocol://freedb.org:8880,search=cddb_cgi://freedb2.org/~cddb/cddb.cgi:80]
//query[get=cddb_cgi://freedb.org/~cddb/cddb.cgi:80,search=cddb_cgi://freedb2.org/~cddb/cddb.cgi:80]
//we parse the query arguments
int parse_query_arg(Options *opt, char *query)
{
  char *cur_pos = NULL;
  char *end_pos = NULL;
  char *test_pos = NULL;
  cur_pos = query;

  short ambigous = SPLT_FALSE;

  //if we have query[
  if (strstr(query ,"query[") == query)
  {
    cur_pos = strchr(query,'[');

    //if we don't have ], ambigous
    if (!(test_pos = strchr(cur_pos,']')))
    {
      ambigous = SPLT_TRUE;
    }
    else
    {
      //if we have something after ], ambigous
      if (*(test_pos+1) != '\0')
      {
        ambigous = SPLT_TRUE;
      }
    }

    int search_found = SPLT_FALSE;
    int get_found = SPLT_FALSE;
    int paranthesis_has_content = SPLT_FALSE;
    //we find "get" or "search"
    while((test_pos = strstr(cur_pos,"get="))||
        (test_pos = strstr(cur_pos,"search=")))
    {
      paranthesis_has_content = SPLT_TRUE;

      //we find out which one is first
      end_pos = strstr(cur_pos,"get=");
      test_pos = strstr(cur_pos,"search=");
      if (end_pos == NULL)
      {
        cur_pos = test_pos;
      }
      else
      {
        if (test_pos == NULL)
        {
          cur_pos = end_pos;
        }
        else
        {
          if (end_pos < test_pos)
          {
            cur_pos = end_pos;
          }
          else
          {
            cur_pos = test_pos;
          }
        }
      }

      //we determine the type (get or search)
      if (strstr(cur_pos,"get=") == cur_pos)
      {
        get_found = SPLT_TRUE;
        search_found = SPLT_FALSE;
        cur_pos += 4;
      }
      else
      {
        search_found = SPLT_TRUE;
        get_found = SPLT_FALSE;
        cur_pos += 7;
      }

      //we get out the type of the search
      char freedb_type[256] = "\0";
      if ((end_pos=strstr(cur_pos,"://"))||
          (end_pos=strchr(cur_pos,',')) ||
          (end_pos=strchr(cur_pos,']')))
      {
        if (end_pos-cur_pos < 255)
        {
          snprintf(freedb_type,end_pos-cur_pos+1,"%s",cur_pos);
          freedb_type[end_pos-cur_pos+1] = '\0';
          if ((strchr(cur_pos,',')==end_pos) ||
              (strchr(cur_pos,']')==end_pos))
          {
            cur_pos = end_pos;
          }
          else
          {
            cur_pos = end_pos+3;
          }
          end_pos = cur_pos;
        }
      }
      else
      {
        end_pos = cur_pos;
      }

      //we get out the server
      char freedb_server[256] = "\0";
      while ((*end_pos != ':') && (*end_pos != ',') &&
          (*end_pos != ']') && (*end_pos != '\0'))
      {
        end_pos++;
      }
      if ((end_pos != cur_pos) && (end_pos-cur_pos < 255)
          && (*end_pos != '\0'))
      {
        snprintf(freedb_server,end_pos-cur_pos+1,"%s",cur_pos);
        freedb_server[end_pos-cur_pos+1] = '\0';
        if (*(end_pos+1) == ']' || *(end_pos+1) == ',')
        {
          cur_pos = end_pos+1;
        }
        else
        {
          cur_pos = end_pos;
        }
        end_pos = cur_pos;
      }
      else
      {
        cur_pos = end_pos;
      }

      //we get out the port
      char freedb_port[10] = "\0";
      int is_only_digits = SPLT_TRUE;
      int freedb_int_port = -1;
      //if we have the port
      if (*end_pos == ':')
      {
        cur_pos++;
        end_pos++;
        while((*end_pos != ']') &&
            (*end_pos != '\0') &&
            (*end_pos != ','))
        {
          //we have to have only digits for the port
          if (!isdigit(*end_pos))
          {
            ambigous = SPLT_TRUE;
            is_only_digits = SPLT_FALSE;
          }
          end_pos++;
        }
        if ((end_pos != cur_pos) && (end_pos-cur_pos < 10))
        {
          snprintf(freedb_port,end_pos-cur_pos+1,"%s",cur_pos);
          freedb_port[end_pos-cur_pos+1] = '\0';
          cur_pos = end_pos;
        }

        //we get the port as integer
        if (*freedb_port != '\0')
        {
          if (is_only_digits)
          {
            freedb_int_port = atoi(freedb_port);
          }
          else
          {
            freedb_int_port = SPLT_FREEDB_CDDB_CGI_PORT;
            print_warning("found non digits in port ! (switched to default)");
          }
        }
      }

      //we put the search type as integer
      int freedb_int_type = -1;
      if (*freedb_type != '\0')
      {
        //get type
        if (get_found)
        {
          if (strcmp(freedb_type,"cddb_protocol") == 0)
          {
            freedb_int_type = SPLT_FREEDB_GET_FILE_TYPE_CDDB;
          }
          else
          {
            if (strcmp(freedb_type,"cddb_cgi") == 0)
            {
              freedb_int_type = SPLT_FREEDB_GET_FILE_TYPE_CDDB_CGI;
            }
            else
            {
              print_warning("unknown search type ! (switched to default)");
            }
          }
        }
        else
        {
          //search type
          if (strcmp(freedb_type,"cddb_cgi") == 0)
          {
            freedb_int_type = SPLT_FREEDB_SEARCH_TYPE_CDDB_CGI;
          }
          else
          {
            if (strcmp(freedb_type,"web_search") == 0)
            {
              freedb_int_type = SPLT_FREEDB_SEARCH_TYPE_CDDB_CGI;
              print_warning("freedb web search not implemented yet ! (switched to default)");
            }
            else
            {
              print_warning("unknown get type ! (switched to default)");
            }
          }
        }
      }
      else
      {
        ambigous = SPLT_TRUE;
      }

      //if we have found search
      if (search_found)
      {
        if (freedb_int_type != -1)
        {
          opt->freedb_search_type = freedb_int_type;
        }
        if (*freedb_server != '\0')
        {
          snprintf(opt->freedb_search_server,255, freedb_server);
        }
        else
        {
          snprintf(opt->freedb_search_server,255, SPLT_FREEDB2_CGI_SITE);
        }
        if (freedb_int_port != -1)
        {
          opt->freedb_search_port = freedb_int_port;
        }
      }
      else
      {
        //if we have found get
        if (get_found)
        {
          if (freedb_int_type != -1)
          {
            opt->freedb_get_type = freedb_int_type;
          }
          if (*freedb_server != '\0')
          {
            snprintf(opt->freedb_get_server,255, freedb_server);
          }
          else
          {
            snprintf(opt->freedb_get_server,255, SPLT_FREEDB2_CGI_SITE);
          }
          if (freedb_int_port != -1)
          {
            opt->freedb_get_port = freedb_int_port;
          }
        }
      }

      //if at the and something else than , or ], ambigous
      if ((*cur_pos != ',') &&
          (*cur_pos != ']') &&
          (*cur_pos != '\0'))
      {
        ambigous = SPLT_TRUE;
      }
    }
    //if we don't have anything inside the paranthesis,
    //ambigous
    if (!paranthesis_has_content)
    {
      ambigous = SPLT_TRUE;
    }
  }

  return ambigous;
}

//makes the freedb search
void do_freedb_search(Options *opt, splt_state *state,int *err)
{
  //we find out what search and get type we have
  char search_type[30] = "";
  char get_type[30] = "";
  if (opt->freedb_search_type == SPLT_FREEDB_SEARCH_TYPE_CDDB_CGI)
  {
    snprintf(search_type,30,"%s","cddb.cgi");
  }
  else
  {
    snprintf(search_type,30,"%s","web_search");
  }
  if (opt->freedb_get_type == SPLT_FREEDB_GET_FILE_TYPE_CDDB_CGI)
  {
    snprintf(get_type,30,"%s","cddb.cgi");
  }
  else
  {
    snprintf(get_type,30,"%s","cddb_protocol");
  }

  //print out infos about the servers
  fprintf(stdout," Freedb_search_type : %s , Url: %s , Port: %d\n",
      search_type,opt->freedb_search_server,opt->freedb_search_port);
  fflush(stdout);
  fprintf(stdout," Freedb_get_type : %s , Url: %s , Port: %d\n",
      get_type,opt->freedb_get_server,opt->freedb_get_port);
  fflush(stdout);

  //freedb search
  print_message("CDDB QUERY. Insert album and artist informations to find cd.");

  char freedb_input[1024];
  short first_time = SPLT_TRUE;
  //here we search freedb
  do {
    if (!first_time)
    {
      print_message("\nPlease search something ...");
    }

    fprintf (stdout, "\n\t____________________________________________________________]");
    fprintf (stdout, "\r Search: [");
    fgets(freedb_input, 800, stdin);

    first_time = SPLT_FALSE;

    freedb_input[strlen(freedb_input)-1]='\0';
  } while ((strlen(freedb_input)==0)||
      (checkstring(freedb_input)!=0));

  fprintf(stdout, "\nSearching from %s on port %d using %s ...\n",
      opt->freedb_search_server,opt->freedb_search_port,
      search_type);
  fflush(stdout);

  //the freedb results
  splt_freedb_results *f_results;
  //we search the freedb
  f_results = mp3splt_get_freedb_search(state,freedb_input,
      err, opt->freedb_search_type,
      opt->freedb_search_server,
      opt->freedb_search_port);
  print_confirmation_error(*err,opt,state);

  if (*err >= 0)
  {
    //print the searched informations
    print_message("List of found cd:");

    int cd_number = 0;
    short end = SPLT_FALSE;
    do {
      fprintf (stdout,"%3d) %s\n",
          f_results->results[cd_number].id,
          f_results->results[cd_number].name);

      int i;
      for(i = 0; i < f_results->results[cd_number].revision_number; i++)
      {
        fprintf (stdout, "  |\\=>");
        fprintf (stdout, "%3d) ",
            f_results->results[cd_number].id+i+1);
        fprintf (stdout, "Revision: %d\n", i+2);

        //break at 22
        if (((f_results->results[cd_number].id+i+2)%22)==0)
        {
          //duplicate, see below
          char junk[18];
          fprintf (stdout, "-- 'q' to select cd, Enter for more:");
          fflush(stdout);

          fgets(junk, 16, stdin);
          if (junk[0]=='q')
          {
            end = SPLT_TRUE;
            goto end;
          }
        }
      }

      //we read result from the char, q tu select cd or
      //enter to show more results
      if (((f_results->results[cd_number].id+1)%22)==0)
      {
        //duplicate, see ^^
        char junk[18];
        fprintf (stdout, "-- 'q' to select cd, Enter for more: ");
        fflush(stdout);

        fgets(junk, 16, stdin);
        if (junk[0]=='q')
        {
          end = SPLT_TRUE;
          goto end;
        }
      }

end:
      if (end)
      {
        end = SPLT_FALSE;
        break;
      }

      cd_number++;
    } while (cd_number < f_results->number);

    //select the CD
    //input of the selected cd
    char sel_cd_input[1024];
    //selected_cd = the selected cd
    int selected_cd = 0,tot = 0;
    do {
      selected_cd = 0;
      fprintf (stdout, "Select cd #: ");
      fflush(stdout);
      fgets(sel_cd_input, 254, stdin);
      sel_cd_input[strlen(sel_cd_input)-1]='\0';
      tot = 0;

      if (sel_cd_input[tot] == '\0') 
      {
        selected_cd = -1;
      }

      while(sel_cd_input[tot] != '\0')
      {
        if (isdigit(sel_cd_input[tot++])==0)
        {
          fprintf (stdout, "Please ");
          fflush(stdout);

          selected_cd = -1;
          break;
        }
      }

      if (selected_cd != -1) 
      {
        selected_cd = atoi (sel_cd_input);
      }

    } while ((selected_cd >= f_results->number) 
        || (selected_cd < 0));

    fprintf(stdout, "\nGetting file from %s on port %d using %s ...\n",
        opt->freedb_get_server,opt->freedb_get_port,
        get_type);
    fflush(stdout);

    //here we have the selected cd in selected_cd
    mp3splt_write_freedb_file_result(state, selected_cd,
        MP3SPLT_CDDBFILE, err,
        opt->freedb_get_type,
        opt->freedb_get_server,
        opt->freedb_get_port);
    print_confirmation_error(*err,opt,state);

    //if no error
    if (*err >= 0)
    {
      //we get the splitpoints from the file
      mp3splt_put_cddb_splitpoints_from_file(state, MP3SPLT_CDDBFILE,
          err);
      print_confirmation_error(*err,opt,state);
    }
  }
}

//prints a library message
void put_library_message(int message)
{
  switch (message)
  {
    case SPLT_MESS_FRAME_MODE_ENABLED:
      print_message(" info: frame mode enabled");
      break;
    case SPLT_MESS_START_WRAP_SPLIT:
      print_message(" info: starting wrap mode split");
      break;
    case SPLT_MESS_START_SILENCE_SPLIT:
      print_message(" info: starting silence mode split");
      break;
    case SPLT_MESS_START_ERROR_SPLIT:
      print_message(" info: starting error mode split");
      break;
    case SPLT_MESS_START_NORMAL_SPLIT:
      print_message(" info: starting normal split");
      break;
    case SPLT_MESS_START_TIME_SPLIT:
      print_message(" info: starting time mode split");
      break;
    case SPLT_MESS_DETECTED_INVALID:
      fprintf(stderr," info error: invalid format detected");
      fflush(stderr);
      break;
    case SPLT_MESS_STOP_SPLIT:
      print_message("\n info: stopping split...");
      break;
    default:
      break;
  }
}

//prints the splitted file
void put_splitted_file(char *file, int progress_data)
{
  //we put necessary spaces
  char temp[1024] = "";
  int this_spaces = strlen(file)+16;
  int counter = strlen(file)+16;
  while (counter <= progress_data)
  {
    temp[counter-this_spaces] = ' ';
    counter++;
  }
  temp[counter] = '\0';

  fprintf(stdout,"   File \"%s\" created%s\n",file,temp);
  fflush(stdout);
}

//prints the progress bar
void put_progress_bar(splt_progress *p_bar)
{
  char progress_text[1024] = " ";

  switch (p_bar->progress_type)
  {
    case SPLT_PROGRESS_PREPARE :
      snprintf(progress_text,1023,
          " preparing \"%s\" (%d of %d)",
          p_bar->filename_shorted,
          p_bar->current_split,
          p_bar->max_splits);
      break;
    case SPLT_PROGRESS_CREATE :
      snprintf(progress_text,1023,
          " creating \"%s\" (%d of %d)",
          p_bar->filename_shorted,
          p_bar->current_split,
          p_bar->max_splits);
      break;
    case SPLT_PROGRESS_SEARCH_SYNC :
      snprintf(progress_text,1023,
          " searching for sync errors...");
      break;
    case SPLT_PROGRESS_SCAN_SILENCE :
      snprintf(progress_text,1023,
          " scanning for silence...");
      break;
    default:
      snprintf(progress_text,1023, " ");
      break;
  }

  char printed_value[1024] = "";
  //we update the progress
  snprintf(printed_value,1023,"%6.2f %% %s",
      p_bar->percent_progress * 100,
      progress_text);

  //we put necessary spaces
  char temp[1024] = "";
  int this_spaces = strlen(printed_value);
  int counter = strlen(printed_value);
  while (counter <= p_bar->user_data)
  {
    temp[counter-this_spaces] = ' ';
    counter++;
  }
  temp[counter] = '\0';

  fprintf(stdout,"%s%s\r",printed_value,temp);
  fflush(stdout);

  p_bar->user_data = strlen(printed_value)+1;
}

//handler for the SIGINT signal
void sigint_handler(int sig)
{
  int err = SPLT_OK;
  mp3splt_stop_split(state,&err);
  exit(0);
}

//returns the options
Options *new_options()
{
  Options *opt = malloc(sizeof(Options));

  opt->w_option = SPLT_FALSE; opt->l_option = SPLT_FALSE;
  opt->e_option = SPLT_FALSE; opt->f_option = SPLT_FALSE;
  opt->c_option = SPLT_FALSE; opt->t_option = SPLT_FALSE;
  opt->s_option = SPLT_FALSE; opt->a_option = SPLT_FALSE;
  opt->p_option = SPLT_FALSE; opt->o_option = SPLT_FALSE;
  opt->d_option = SPLT_FALSE; opt->k_option = SPLT_FALSE;
  opt->g_option = SPLT_FALSE; opt->n_option = SPLT_FALSE;
  opt->q_option = SPLT_FALSE; opt->i_option = SPLT_FALSE;
  opt->m_option = SPLT_FALSE;
  opt->cddb_arg = NULL; opt->dir_arg = NULL;
  opt->param_args = NULL; opt->custom_tags = NULL;
  opt->m3u_arg = NULL;

  //we put the default values for freedb search
  //by default, CDDB_CGI (cddb.cgi) port 80 on freedb2.org
  opt->freedb_search_type = SPLT_FREEDB_SEARCH_TYPE_CDDB_CGI;
  snprintf(opt->freedb_search_server,255, SPLT_FREEDB2_CGI_SITE);
  opt->freedb_search_port = SPLT_FREEDB_CDDB_CGI_PORT;
  //we put the default values for the freedb cddb file get
  //by default, CDDB_CGI (cddb.cgi) port 80 on freedb2.org
  opt->freedb_get_type = SPLT_FREEDB_GET_FILE_TYPE_CDDB_CGI;
  snprintf(opt->freedb_get_server,255, SPLT_FREEDB2_CGI_SITE);
  opt->freedb_get_port = SPLT_FREEDB_CDDB_CGI_PORT;

  return opt;
}

//output package, version and authors
void print_package_version_authors()
{
  fprintf (stdout, PACKAGE_NAME" version "VERSION", released on "MP3SPLT_DATE", by \n");
  fprintf (stdout, MP3SPLT_AUTHOR1" "MP3SPLT_EMAIL1"\n"MP3SPLT_AUTHOR2" "MP3SPLT_EMAIL2"\n");
  fprintf (stdout, "THIS SOFTWARE COMES WITH ABSOLUTELY NO WARRANTY! USE AT YOUR OWN RISK!\n");
  fflush(stdout);
}

//main program starts here
int main (int argc, char *argv[])
{
  //possible error
  int err = SPLT_OK;

  //command line options
  Options *opt = new_options();

  //we create our state
  state = mp3splt_new_state(&err);

  //close nicely on Ctrl+C
  signal (SIGINT, sigint_handler);

  //callback for the library messages
  mp3splt_set_message_function(state,put_library_message);
  //callback for the splitted files
  mp3splt_set_splitted_filename_function(state,put_splitted_file);
  //callback for the progress bar
  mp3splt_set_progress_function(state,put_progress_bar);

  //default we write mins_secs_hundr for normal split
  mp3splt_set_int_option(state, SPLT_OPT_OUTPUT_FILENAMES,
      SPLT_OUTPUT_DEFAULT);
  mp3splt_set_int_option(state, SPLT_OPT_TAGS,
      SPLT_TAGS_ORIGINAL_FILE);

  //the index of the file that we are splitting in argv
  int file_arg_position = 0;

  //parse command line options
  int option;
  //I have erased the "-i" option
  while ((option=getopt(argc, argv, "m:SDVifkwleqnasc:d:o:t:p:g:h"))!=-1)
  {
    switch (option)
    {
      case 'h':
        show_small_help_exit(opt, state);
        break;
      case 'D':
        mp3splt_set_int_option(state, SPLT_OPT_DEBUG_MODE,
            SPLT_TRUE);
        break;
      case 'V':
        //output package, version and authors
        print_package_version_authors();
        //free variables
        free(opt);
        mp3splt_free_state(state,&err);
        exit(0);
        break;
      case 'f':
        mp3splt_set_int_option(state, SPLT_OPT_FRAME_MODE,
            SPLT_TRUE);
        opt->f_option = SPLT_TRUE;
        break;
      case 'k':
        mp3splt_set_int_option(state, SPLT_OPT_INPUT_NOT_SEEKABLE,
            SPLT_TRUE);
        opt->k_option = SPLT_TRUE;
        break;
      case 'w':
        mp3splt_set_int_option(state, SPLT_OPT_SPLIT_MODE,
            SPLT_OPTION_WRAP_MODE);
        opt->w_option = SPLT_TRUE;
        break;
      case 'l':
        opt->l_option = SPLT_TRUE;
        break;
      case 'e':
        mp3splt_set_int_option(state, SPLT_OPT_SPLIT_MODE,
            SPLT_OPTION_ERROR_MODE);
        opt->e_option = SPLT_TRUE;
        break;
      case 'q':
        opt->q_option = SPLT_TRUE;
        break;
      case 'n':
        mp3splt_set_int_option(state, SPLT_OPT_TAGS,
            SPLT_NO_TAGS);
        opt->n_option = SPLT_TRUE;
        break;
      case 'a':
        mp3splt_set_int_option(state, SPLT_OPT_AUTO_ADJUST,
            SPLT_TRUE);
        opt->a_option = SPLT_TRUE;
        break;
      case 's':
        mp3splt_set_int_option(state, SPLT_OPT_SPLIT_MODE,
            SPLT_OPTION_SILENCE_MODE);
        opt->s_option = SPLT_TRUE;
        break;
      case 'i':
        mp3splt_set_int_option(state, SPLT_OPT_SPLIT_MODE,
            SPLT_OPTION_SILENCE_MODE);
        opt->i_option = SPLT_TRUE;
        break;
      case 'c':
        //default tags
        mp3splt_set_int_option(state, SPLT_OPT_TAGS,
            SPLT_CURRENT_TAGS);
        opt->c_option = SPLT_TRUE;
        opt->cddb_arg = optarg;
        break;
      case 'm':
        opt->m_option = SPLT_TRUE;
        opt->m3u_arg = optarg;
        mp3splt_set_m3u_filename(state,opt->m3u_arg);
        break;
      case 'd':
        opt->dir_arg = optarg;
        opt->d_option = SPLT_TRUE;
        break;
      case 'o':
        //default output is false now
        mp3splt_set_int_option(state, SPLT_OPT_OUTPUT_FILENAMES,
            SPLT_OUTPUT_FORMAT);
        opt->output_format = optarg;
        opt->o_option = SPLT_TRUE;
        break;
      case 't':
        mp3splt_set_int_option(state, SPLT_OPT_SPLIT_MODE,
            SPLT_OPTION_TIME_MODE);
        float converted_time = c_hundreths(optarg);

        if (converted_time != -1)
        {
          float split_time = converted_time / 100.0;
          mp3splt_set_float_option(state, SPLT_OPT_SPLIT_TIME,
              split_time);
        }
        else
        {
          put_error_message_exit("Error: bad time expression for the time split.\n"
              "Must be min.sec, read man page for details.",opt,state);
        }
        opt->t_option = SPLT_TRUE;
        break;
      case 'p':
        opt->p_option = SPLT_TRUE;
        opt->param_args = optarg;
        break;
      case 'g':
        mp3splt_set_int_option(state, SPLT_OPT_TAGS,
            SPLT_CURRENT_TAGS);
        opt->custom_tags = optarg;
        opt->g_option = SPLT_TRUE;
        break;
      default:
        put_error_message_exit("Read man page for complete documentation",opt,state);
        break;
    }
  }

  err = SPLT_OK;
  //after getting the options (especially the debug option), find plugins
  err = mp3splt_find_plugins(state);
  print_confirmation_error(err,opt,state);

  //if we have parameter options
  if (opt->p_option)
  {
    float th = -200,off = -200,min = -200;
    int gap = -200,nt = -200,rm = -200;
    if (parse_arg(opt->param_args,&th,&gap,&nt,&off,&rm,&min) < -1)
    {
      print_warning("bad argument for -p option");
    }

    //threshold
    if (th != -200)
    {
      mp3splt_set_float_option(state, SPLT_OPT_PARAM_THRESHOLD,
          th);
    }
    //offset
    if (off != -200)
    {
      mp3splt_set_float_option(state, SPLT_OPT_PARAM_OFFSET,
          off);
    }
    //min
    if (min != -200)
    {
      mp3splt_set_float_option(state, SPLT_OPT_PARAM_MIN_LENGTH,
          min);
    }
    //gap
    if (gap != -200)
    {
      mp3splt_set_int_option(state, SPLT_OPT_PARAM_GAP,
          gap);
    }
    //number of tracks
    if (nt != -200)
    {
      mp3splt_set_int_option(state, SPLT_OPT_PARAM_NUMBER_TRACKS,
          nt);
    }
    //remove silence (rm)
    if (rm != -200)
    {
      mp3splt_set_int_option(state, SPLT_OPT_PARAM_REMOVE_SILENCE,
          rm);
    }
  }

  //if quiet, does not write authors and other
  if (!opt->q_option)
  {
    print_package_version_authors();
  }

  if (opt->o_option)
  {
    //we set our output format
    mp3splt_set_oformat(state, opt->output_format,&err);
    print_confirmation_error(err,opt,state);
  }

  if (optind > 1)
  {
    argv = rmopt(argv, optind, argc);
    argc -= optind-1;
  }

  //check arguments
  check_args(argc, opt, state);

  int i = 0;
  //we get out the filename from the arguments
  for (i=1; i < argc; i++)
  {
    if ((c_hundreths(argv[i]) == -1) &&
        (strcmp(argv[i],"EOF") != 0))
    {
      break;
    }
  }
  file_arg_position = i;

  FILE *file_to_split_test;
  //we check that we can open the file
  if ((file_to_split_test = fopen(argv[file_arg_position],"r"))
      == NULL)
  {
    fprintf(stdout,"Error: cannot open file \"%s\"\n",
        argv[file_arg_position]);
    //just exit
    put_error_message_exit("",opt,state);
  }
  else
  {
    fclose(file_to_split_test);
  }

  err = SPLT_OK;
  //we put the filename
  err = mp3splt_set_filename_to_split(state,argv[file_arg_position]);
  print_confirmation_error(err,opt,state);

  //if error
  if (err != SPLT_OK)
  {
    //just exit
    put_error_message_exit("",opt,state);
  }

  //we remove the filename from the arguments
  argv = rmopt2(argv, file_arg_position, argc);
  argc--;

  //here we have all the trash or the splitpoints from
  //argv[1] to argv[argc-1] and argv[0] = program_command

  //just don't put incompatible options!, rtfm
  if (opt->l_option || opt->i_option || opt->c_option ||
      opt->e_option || opt->t_option || opt->w_option ||
      opt->s_option)
  {
    if (argc > 1)
    {
      fprintf(stdout," error: \"%s\" - unrecognized argument for\
          this type of split\n", argv[1]);
      //just exit
      put_error_message_exit("",opt,state);
    }
  }

  //if we list wrap files
  if (opt->l_option)
  {
    //if no error when putting the filename to split
    if (err >= 0)
    {
      splt_wrap *wrap_files;
      wrap_files = mp3splt_get_wrap_files(state,&err);

      //if no error when getting the wrap files
      if (err >= 0)
      {
        int wrap_files_number = wrap_files->wrap_files_num;
        int i = 0;
        fprintf(stdout,"\n");
        for (i = 0;i < wrap_files_number;i++)
        {
          fprintf(stdout,"%s\n",wrap_files->wrap_files[i]);
        }
        fprintf(stdout,"\n");
        fflush(stdout);
      }
      else
      {
        print_confirmation_error(err,opt,state);
      }
    }
  }
  else
    //count how many silence splitpoints we have
    //if we count how many silence splitpoints
    if (opt->i_option)
    {
      err = SPLT_OK;

      int silence_number =
        mp3splt_count_silence_points(state, &err);
      print_confirmation_error(err,opt,state);

      if (err >= 0)
      {
        fprintf(stdout,"%d silence splitpoints detected"
            "            \n",
            silence_number);
        fflush(stdout);
      }
    }
    else
      //if we don't list wrapped files and we don't count silence files
    {
      //if we have cddb option
      if (opt->c_option)
      {
        //we get the filename
        if ((strstr(opt->cddb_arg, ".cue")!=NULL)||
            (strstr(opt->cddb_arg, ".CUE")!=NULL))
        {
          //we have the cue filename in cddb_arg
          //here we get cue splitpoints
          mp3splt_put_cue_splitpoints_from_file(state, opt->cddb_arg,
              &err);
          print_confirmation_error(err,opt,state);
        }
        else
        {
          //if we have a freedb search
          if ((strcmp(opt->cddb_arg, "query")==0)
              ||(strstr(opt->cddb_arg,"query[") == opt->cddb_arg))
          {
            int ambigous = parse_query_arg(opt,opt->cddb_arg);
            if (ambigous)
            {
              print_warning("freedb server format ambigous !");
            }
            do_freedb_search(opt,state,&err);
          }
          else
            //here we have cddb file
          {
            mp3splt_put_cddb_splitpoints_from_file(state,
                opt->cddb_arg,
                &err);
            print_confirmation_error(err,opt,state);
          }
        }
      }
      else
        //if we have a normal split (includes time split,
        //error mode split, silence split)
      {
        for (i=1;i<argc; i++)
        {
          //we manage the EOF keyword
          if (strcmp(argv[i],"EOF") == 0)
          {
            //we put the splitpoints
            err = mp3splt_append_splitpoint(state,
                LONG_MAX, NULL);
            print_confirmation_error(err,opt,state);
          }
          else
          {
            long hundr_of_seconds = c_hundreths(argv[i]);

            //we put the splitpoints
            err = mp3splt_append_splitpoint(state,
                hundr_of_seconds, 
                NULL);
            print_confirmation_error(err,opt,state);
          }
        }
      }

      //if no error
      if (err >= 0)
      {
        //we set the path of split
        err = mp3splt_set_path_of_split(state, opt->dir_arg);
        print_confirmation_error(err,opt,state);

        if (err >= 0)
        {
          //if custom tags, we put the tags
          if(mp3splt_put_tags_from_string(state,opt->custom_tags))
          {
            print_warning("tags format ambigous !");
          }

          //we do the effective split
          err = mp3splt_split(state);
          print_confirmation_error(err,opt,state);
        }
      }
    }

  //we free left variables in the state
  mp3splt_free_state(state,&err);
  //we free the options
  free(opt);

  return 0;
}