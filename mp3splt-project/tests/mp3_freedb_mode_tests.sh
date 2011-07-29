#!/bin/bash

. ./utils.sh || exit 1

function _test_freedb_search_get_cgi_tracktype
{
  get_type=$1
  get_url=$2
  get_port=$3

  rm -f query.cddb
  remove_output_dir

  M_FILE="La_Verue__Today"

  expected=" Processing file 'songs/La_Verue__Today.mp3' ...
 Freedb search type: cddb_cgi , Site: tracktype.org/~cddb/cddb.cgi , Port: 80
 Freedb get type: $get_type , Site: $get_url , Port: $get_port

  Search string: hacking the future

Searching from tracktype.org/~cddb/cddb.cgi on port 80 using cddb_cgi ...
 freedb search processed

Getting file from $get_url on port $get_port using $get_type ...
 freedb file downloaded
 reading informations from CDDB file query.cddb ...

  Artist: Various
  Album: Hacking The Future
  Tracks: 37

 cddb file processed
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting normal split
   File \"$OUTPUT_DIR/Various - 01 - The Body Electronic Spews.mp3\" created
   File \"$OUTPUT_DIR/Various - 02 - I will tell U 3 things.mp3\" created
   File \"$OUTPUT_DIR/Various - 03 - Spew Culture.mp3\" created
 Processed 9402 frames - Sync errors: 0
 file split (EOF)"
  freedb_album_search="hacking the future"
  freedb_search="search=cddb_cgi://tracktype.org/~cddb/cddb.cgi:80"
  freedb_get="get=$get_type://$get_url:$get_port"
  freedb_options="query[$freedb_search,$freedb_get]{$freedb_album_search}(0)"
  mp3splt_args="-d $OUTPUT_DIR -q -c \"$freedb_options\" $MP3_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/Various - 01 - The Body Electronic Spews.mp3"
  check_current_mp3_length "00.37"

  current_file="$OUTPUT_DIR/Various - 02 - I will tell U 3 things.mp3"
  check_current_mp3_length "03.15"

  current_file="$OUTPUT_DIR/Various - 03 - Spew Culture.mp3"
  check_current_mp3_length "00.12"

  print_ok
  echo
}

function test_freedb_search_get_cgi_tracktype
{ 
  test_name="freedb mode - search & get cgi tracktype"

  _test_freedb_search_get_cgi_tracktype "cddb_cgi" "tracktype.org/~cddb/cddb.cgi" "80"
}

function test_freedb_search_tracktype_get_cgi_freedb
{
  test_name="freedb mode - search tracktype & get cgi freedb"

  _test_freedb_search_get_cgi_tracktype "cddb_cgi" "freedb.org/~cddb/cddb.cgi" "80"
}

function test_freedb_search_tracktype_get_cddb_protocol_freedb
{
  test_name="freedb mode - search tracktype & get cddb protocol freedb"

  _test_freedb_search_get_cgi_tracktype "cddb_protocol" "freedb.org" "8880"
}

function run_freedb_mode_tests
{
  p_blue " FREEDB tests ..."
  echo

  freedb_mode_test_functions=$(declare -F | grep " test_freedb" | awk '{ print $3 }')

  for test_func in $freedb_mode_test_functions;do
    eval $test_func
  done

  p_blue " FREEDB tests DONE."
  echo
}

#main
export LC_ALL="C"
start_date=$(date +%s)

run_freedb_mode_tests

p_failed_tests

end_date=$(date +%s)

p_time_diff_cyan $start_date $end_date "\t"
echo -e '\n'

exit 0

