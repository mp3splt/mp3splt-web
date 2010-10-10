#!/bin/bash

. ./utils.sh || exit 1

function test_time_vbr
{
  local tags_version=$1

  remove_output_dir

  test_name="vbr time"
  M_FILE="La_Verue__Today"

  if [[ $tags_version -eq -1 ]];then
    tags_option="-n"
      test_name="vbr no tags"
  else
    test_name="vbr id3v$tags_version"
    tags_option="-T $tags_version"
  fi

  expected=" Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3\" created
 Processed 9402 frames - Sync errors: 0
 time split ok"
  mp3splt_args="$tags_option -d $OUTPUT_DIR $MP3_FILE -t 1.0" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing

  if [[ $tags_version -eq -1 ]];then
    check_current_mp3_no_tags
    check_current_file_size "1325582"
  else
    check_all_mp3_tags_with_version $tags_version "La Verue" "Riez Noir" "Today"\
    "2007" "Rock" "17" "1" "http://www.jamendo.com/"

    if [[ $tags_version -eq 2 ]];then
      check_current_file_size "1325798"
    else
      check_current_file_size "1325710"
    fi
  fi

  current_file="$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing

  if [[ $tags_version -eq -1 ]];then
    check_current_mp3_no_tags
    check_current_file_size "1361325"
  else
    check_all_mp3_tags_with_version $tags_version "La Verue" "Riez Noir" "Today"\
    "2007" "Rock" "17" "2" "http://www.jamendo.com/"

    if [[ $tags_version -eq 2 ]];then
      check_current_file_size "1361541"
    else
      check_current_file_size "1361453"
    fi
  fi

  current_file="$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing

  if [[ $tags_version -eq -1 ]];then
    check_current_mp3_no_tags
    check_current_file_size "1392837"
  else
    check_all_mp3_tags_with_version $tags_version "La Verue" "Riez Noir" "Today"\
    "2007" "Rock" "17" "3" "http://www.jamendo.com/"

    if [[ $tags_version -eq 2 ]];then
      check_current_file_size "1393053"
    else
      check_current_file_size "1392965"
    fi
  fi

  current_file="$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing

  if [[ $tags_version -eq -1 ]];then
    check_current_mp3_no_tags
    check_current_file_size "1433903"
  else
    check_all_mp3_tags_with_version $tags_version "La Verue" "Riez Noir" "Today"\
    "2007" "Rock" "17" "4" "http://www.jamendo.com/"

    if [[ $tags_version -eq 2 ]];then
      check_current_file_size "1434119"
    else
      check_current_file_size "1434031"
    fi
  fi

  current_file="$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing

  if [[ $tags_version -eq -1 ]];then
    check_current_mp3_no_tags
    check_current_file_size "1433903"
  else
    check_all_mp3_tags_with_version $tags_version "La Verue" "Riez Noir" "Today"\
    "2007" "Rock" "17" "4" "http://www.jamendo.com/"

    if [[ $tags_version -eq 2 ]];then
      check_current_file_size "1434119"
    else
      check_current_file_size "1434031"
    fi
  fi

  current_file="$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3" 
  check_current_mp3_length "00.05"
  check_current_file_has_xing

  if [[ $tags_version -eq -1 ]];then
    check_current_mp3_no_tags
    check_current_file_size "98561"
  else
    check_all_mp3_tags_with_version $tags_version "La Verue" "Riez Noir" "Today"\
    "2007" "Rock" "17" "5" "http://www.jamendo.com/"

    if [[ $tags_version -eq 2 ]];then
      check_current_file_size "98777"
    else
      check_current_file_size "98689"
    fi
  fi

  p_green "OK"
  echo
}

function test_time_vbr_no_tags { test_time_vbr -1; }
function test_time_vbr_id3v1 { test_time_vbr 1; }
function test_time_vbr_id3v2 { test_time_vbr 2; }

function test_time_vbr_pretend
{
  remove_output_dir

  test_name="vbr time & pretend"
  M_FILE="La_Verue__Today"

  expected=" Pretending to split file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3\" created
 Processed 9402 frames - Sync errors: 0
 time split ok"
  mp3splt_args="-P -d $OUTPUT_DIR $MP3_FILE -t 1.0"
  run_check_output "$mp3splt_args" "$expected"

  check_output_directory_is_empty

  p_green "OK"
  echo
}

function test_time_vbr_cue_export
{
  remove_output_dir

  test_name="vbr time & cue export"
  M_FILE="La_Verue__Today"

  expected=" Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3\" created
 Processed 9402 frames - Sync errors: 0
 time split ok
 CUE file 'output/output_out.cue' created."
  mp3splt_args="-T 2 -E output/out.cue -d $OUTPUT_DIR $MP3_FILE -t 1.0" 
  run_check_output "$mp3splt_args" "$expected"

  check_file_content "output/output_out.cue" 'TITLE "Riez Noir"
PERFORMER "La Verue"
FILE "songs/La_Verue__Today.mp3" MP3
  TRACK 01 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 00:00:00
  TRACK 02 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 01:00:00
  TRACK 03 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 02:00:00
  TRACK 04 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 03:00:00
  TRACK 05 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 04:00:00'

  current_file="$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "1" "http://www.jamendo.com/"
  check_current_file_size "1325798"

  current_file="$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "2" "http://www.jamendo.com/"
  check_current_file_size "1361541"

  current_file="$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "3" "http://www.jamendo.com/"
  check_current_file_size "1393053"

  current_file="$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "4" "http://www.jamendo.com/"
  check_current_file_size "1434119"

  current_file="$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "4" "http://www.jamendo.com/"
  check_current_file_size "1434119"

  current_file="$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3" 
  check_current_mp3_length "00.05"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "5" "http://www.jamendo.com/"
  check_current_file_size "98777"

  p_green "OK"
  echo
}

function test_time_vbr_pretend_cue_export
{
  remove_output_dir

  test_name="vbr time & pretend & cue export"
  M_FILE="La_Verue__Today"

  expected=" Pretending to split file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3\" created
 Processed 9402 frames - Sync errors: 0
 time split ok
 CUE file 'output/output_out.cue' created."
  mp3splt_args="-P -E output/out.cue -d $OUTPUT_DIR $MP3_FILE -t 1.0"
  run_check_output "$mp3splt_args" "$expected"

  check_output_directory_number_of_files 1

  check_file_content 'output/output_out.cue' 'TITLE "Riez Noir"
PERFORMER "La Verue"
FILE "songs/La_Verue__Today.mp3" MP3
  TRACK 01 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 00:00:00
  TRACK 02 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 01:00:00
  TRACK 03 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 02:00:00
  TRACK 04 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 03:00:00
  TRACK 05 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 04:00:00'

  p_green "OK"
  echo
}

function test_time_vbr_overlap_split
{
  remove_output_dir

  test_name="vbr time overlap splitpoints"
  M_FILE="La_Verue__Today"

  expected=" Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
 info: overlapping split files with 0.30.0
   File \"$OUTPUT_DIR/${M_FILE}_00m_00s__02m_30s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_02m_00s__04m_05s_58h.mp3\" created
 time split ok"
  mp3splt_args="-T 2 -O 0.30 -d $OUTPUT_DIR $MP3_FILE -t 2.0"
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/${M_FILE}_00m_00s__02m_30s.mp3"
  check_current_mp3_length "02.30"
  check_current_file_size "3328252"

  current_file="$OUTPUT_DIR/${M_FILE}_02m_00s__04m_05s_58h.mp3"
  check_current_mp3_length "02.05"
  check_current_file_size "2925727"

  p_green "OK"
  echo
}

function test_time_vbr_overlap_split_and_cue_export
{
  remove_output_dir

  test_name="vbr time overlap & cue export"
  M_FILE="La_Verue__Today"

  expected=" Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
 info: overlapping split files with 0.30.0
   File \"$OUTPUT_DIR/${M_FILE}_00m_00s__02m_30s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_02m_00s__04m_05s_58h.mp3\" created
 time split ok
 CUE file 'output/output_out.cue' created."
  mp3splt_args="-T 2 -O 0.30 -E output/out.cue -d $OUTPUT_DIR $MP3_FILE -t 2.0"
  run_check_output "$mp3splt_args" "$expected"

  check_file_content 'output/output_out.cue' 'TITLE "Riez Noir"
PERFORMER "La Verue"
FILE "songs/La_Verue__Today.mp3" MP3
  TRACK 01 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 00:00:00
  TRACK 02 AUDIO
    TITLE "Today"
    PERFORMER "La Verue"
    INDEX 01 02:00:00'

  current_file="$OUTPUT_DIR/${M_FILE}_00m_00s__02m_30s.mp3"
  check_current_mp3_length "02.30"
  check_current_file_size "3328252"

  current_file="$OUTPUT_DIR/${M_FILE}_02m_00s__04m_05s_58h.mp3"
  check_current_mp3_length "02.05"
  check_current_file_size "2925727"

  p_green "OK"
  echo
}

function test_time_vbr_original_tags
{
  remove_output_dir

  test_name="vbr time"
  M_FILE="La_Verue__Today"

  expected=" Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3\" created
 Processed 9402 frames - Sync errors: 0
 time split ok"
  mp3splt_args="-d $OUTPUT_DIR $MP3_FILE -t 1.0" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 1 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "1" "http://www.jamendo.com/"
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "1" "http://www.jamendo.com/"
  check_current_file_size "1325926"

  current_file="$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 1 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "2" "http://www.jamendo.com/"
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "2" "http://www.jamendo.com/"
  check_current_file_size "1361669"

  current_file="$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 1 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "3" "http://www.jamendo.com/"
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "3" "http://www.jamendo.com/"
  check_current_file_size "1393181"

  current_file="$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 1 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "4" "http://www.jamendo.com/"
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "4" "http://www.jamendo.com/"
  check_current_file_size "1434247"

  current_file="$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3" 
  check_current_mp3_length "01.00"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 1 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "4" "http://www.jamendo.com/"
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "4" "http://www.jamendo.com/"
  check_current_file_size "1434247"

  current_file="$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3" 
  check_current_mp3_length "00.05"
  check_current_file_has_xing
  check_all_mp3_tags_with_version 1 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "5" "http://www.jamendo.com/"
  check_all_mp3_tags_with_version 2 "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "5" "http://www.jamendo.com/"
  check_current_file_size "98905"

  p_green "OK"
  echo
}

function test_time_vbr_no_xing
{
  remove_output_dir

  test_name="vbr time no xing"
  M_FILE="La_Verue__Today"

  mp3splt_args="-T 2 -x -d $OUTPUT_DIR $MP3_FILE -t 2.0" 
  run_check_output "$mp3splt_args" ""

  current_file="$OUTPUT_DIR/${M_FILE}_00m_00s__02m_00s.mp3" 
  check_current_mp3_length "02.48"
  check_current_file_has_no_xing
  check_current_file_size "2686289"

  current_file="$OUTPUT_DIR/${M_FILE}_02m_00s__04m_00s.mp3" 
  check_current_mp3_length "02.57"
  check_current_file_has_no_xing
  check_current_file_size "2826122"

  current_file="$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3" 
  check_current_mp3_length "00.04"
  check_current_file_has_no_xing
  check_current_file_size "98360"

  p_green "OK"
  echo
}

function test_time_vbr_m3u
{
  remove_output_dir

  test_name="vbr time m3u"
  M_FILE="La_Verue__Today"

  expected=" Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 M3U file '$OUTPUT_DIR/m3u/playlist.m3u' will be created.
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/m3u/${M_FILE}_00m_00s__01m_50s.mp3\" created
   File \"$OUTPUT_DIR/m3u/${M_FILE}_01m_50s__03m_40s.mp3\" created
   File \"$OUTPUT_DIR/m3u/${M_FILE}_03m_40s__04m_05s_58h.mp3\" created
 Processed 9402 frames - Sync errors: 0
 time split ok"
  mp3splt_args="-m playlist.m3u -d $OUTPUT_DIR/m3u $MP3_FILE -t 1.50" 
  run_check_output "$mp3splt_args" "$expected"

  expected="La_Verue__Today_00m_00s__01m_50s.mp3
La_Verue__Today_01m_50s__03m_40s.mp3
La_Verue__Today_03m_40s__04m_05s_58h.mp3"
  check_file_content "$OUTPUT_DIR/m3u/playlist.m3u" "$expected"

  p_green "OK"
  echo
}

function test_time_vbr_create_directories
{
  remove_output_dir

  test_name="vbr time create directories"
  M_FILE="La_Verue__Today"

  expected=" Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/a/b/c/${M_FILE}_00m_00s__02m_00s.mp3\" created
   File \"$OUTPUT_DIR/a/b/c/${M_FILE}_02m_00s__04m_00s.mp3\" created
   File \"$OUTPUT_DIR/a/b/c/${M_FILE}_04m_00s__04m_05s_58h.mp3\" created
 Processed 9402 frames - Sync errors: 0
 time split ok"
  mp3splt_args=" -d $OUTPUT_DIR/a/b/c $MP3_FILE -t 2.0"
  run_check_output "$mp3splt_args" "$expected"

  check_if_directory_exist "$OUTPUT_DIR/a/b/c"
  check_if_file_exist "$OUTPUT_DIR/a/b/c/${M_FILE}_00m_00s__02m_00s.mp3"
  check_if_file_exist "$OUTPUT_DIR/a/b/c/${M_FILE}_02m_00s__04m_00s.mp3"
  check_if_file_exist "$OUTPUT_DIR/a/b/c/${M_FILE}_04m_00s__04m_05s_58h.mp3"

  p_green "OK"
  echo
}

function test_time_vbr_custom_tags
{
  remove_output_dir

  test_name="vbr time custom tags"
  M_FILE="La_Verue__Today"

  expected=" Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3\" created
 Processed 9402 frames - Sync errors: 0
 time split ok"
  tags_option="[@a=a1,@b=b1,@t=t1,@y=2000,@c=my_comment,@n=10][]%[@o,@b=album,@N=7][@a=custom_artist][@o,@n=20]"
  mp3splt_args="-d $OUTPUT_DIR -g \"$tags_option\" $MP3_FILE -t 1.0"
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3"
  check_all_mp3_tags_with_version "2" "a1" "b1" "t1"\
  "2000" "Other" "12" "10" "my_comment"

  current_file="$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3"
  check_all_mp3_tags_with_version "2" "" "" "" ""\
  "Other" "12" "2" ""

  current_file="$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3"
  check_all_mp3_tags_with_version "2" "La Verue" "album" "Today"\
  "2007" "Rock" "17" "7" "http://www.jamendo.com/"

  current_file="$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3"
  check_all_mp3_tags_with_version "2" "custom_artist" "album" "Today"\
  "2007" "Rock" "17" "8" "http://www.jamendo.com/"

  current_file="$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3"
  check_all_mp3_tags_with_version "2" "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "20" "http://www.jamendo.com/"

  p_green "OK"
  echo
}

function test_time_vbr_custom_tags_multiple_percent
{
  remove_output_dir

  test_name="vbr time custom tags multiple percent"
  M_FILE="La_Verue__Today"

  expected=" Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3\" created
   File \"$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3\" created
 Processed 9402 frames - Sync errors: 0
 time split ok"
  tags_option="%[@a=a1,@b=b1,@n=10][]%[@o,@b=album,@N=7][@a=custom_artist][@o,@n=20]"
  mp3splt_args="-d $OUTPUT_DIR -g \"$tags_option\" $MP3_FILE -t 1.0"
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/${M_FILE}_00m_00s__01m_00s.mp3"
  check_all_mp3_tags_with_version "2" "a1" "b1" "" ""\
  "Other" "12" "10" ""

  current_file="$OUTPUT_DIR/${M_FILE}_01m_00s__02m_00s.mp3"
  check_all_mp3_tags_with_version "2" "a1" "b1" "" ""\
  "Other" "12" "2" ""

  current_file="$OUTPUT_DIR/${M_FILE}_02m_00s__03m_00s.mp3"
  check_all_mp3_tags_with_version "2" "La Verue" "album" "Today"\
  "2007" "Rock" "17" "7" "http://www.jamendo.com/"

  current_file="$OUTPUT_DIR/${M_FILE}_03m_00s__04m_00s.mp3"
  check_all_mp3_tags_with_version "2" "custom_artist" "album" "Today"\
  "2007" "Rock" "17" "8" "http://www.jamendo.com/"

  current_file="$OUTPUT_DIR/${M_FILE}_04m_00s__04m_05s_58h.mp3"
  check_all_mp3_tags_with_version "2" "La Verue" "Riez Noir" "Today"\
  "2007" "Rock" "17" "20" "http://www.jamendo.com/"

  p_green "OK"
  echo
}

function test_time_vbr_stdin
{
  remove_output_dir

  test_name="vbr time stdin"
  M_FILE="La_Verue__Today"

  expected=" Processing file '-' ...
 info: file matches the plugin 'mp3 (libmad)'
 warning: stdin '-' is supposed to be mp3 stream.
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE NS - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/-_00m_00s__02m_00s.mp3\" created
   File \"$OUTPUT_DIR/-_02m_00s__04m_00s.mp3\" created
   File \"$OUTPUT_DIR/-_04m_00s__04m_05s_58h.mp3\" created
 Processed 9400 frames - Sync errors: 1
 time split ok"
  mp3splt_args="-d $OUTPUT_DIR - -t 2.0"
  run_custom_check_output "cat songs/${M_FILE}.mp3 | $MP3SPLT" "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/-_00m_00s__02m_00s.mp3"
  check_current_mp3_length "02.00"
  check_current_mp3_no_tags
  check_current_file_size "2687012"

  current_file="$OUTPUT_DIR/-_02m_00s__04m_00s.mp3"
  check_current_mp3_length "02.00"
  check_current_mp3_no_tags
  check_current_file_size "2826636"

  current_file="$OUTPUT_DIR/-_04m_00s__04m_05s_58h.mp3"
  check_current_mp3_length "00.05"
  check_current_mp3_no_tags
  check_current_file_size "97309"

  p_green "OK"
  echo
}

function _test_time_vbr_stdin_and_tags
{
  local tags_version=$1

  remove_output_dir

  test_name="vbr time stdin and tags v$tags_version"
  M_FILE="La_Verue__Today"

  expected=" Processing file '-' ...
 info: file matches the plugin 'mp3 (libmad)'
 warning: stdin '-' is supposed to be mp3 stream.
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE NS - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/-_00m_00s__02m_00s.mp3\" created
   File \"$OUTPUT_DIR/-_02m_00s__04m_00s.mp3\" created
   File \"$OUTPUT_DIR/-_04m_00s__04m_05s_58h.mp3\" created
 Processed 9400 frames - Sync errors: 1
 time split ok"
  mp3splt_args="-g %[@a=a1,@b=b1,@y=1070,@N=1] -T $tags_version -d $OUTPUT_DIR - -t 2.0"
  run_custom_check_output "cat songs/${M_FILE}.mp3 | $MP3SPLT" "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/-_00m_00s__02m_00s.mp3"
  check_all_mp3_tags_with_version $tags_version "a1" "b1" "" "1070"\
  "Other" "12" "1" ""
  check_current_mp3_length "02.00"
  check_current_file_has_xing
  if [[ $tags_version -eq 2 ]];then
    check_current_file_size "2687115"
  else
    check_current_file_size "2687140"
  fi

  current_file="$OUTPUT_DIR/-_02m_00s__04m_00s.mp3"
  check_all_mp3_tags_with_version $tags_version "a1" "b1" "" "1070"\
  "Other" "12" "2" ""
  check_current_mp3_length "02.00"
  check_current_file_has_xing
  if [[ $tags_version -eq 2 ]];then
    check_current_file_size "2826739"
  else
    check_current_file_size "2826764"
  fi

  current_file="$OUTPUT_DIR/-_04m_00s__04m_05s_58h.mp3"
  check_all_mp3_tags_with_version $tags_version "a1" "b1" "" "1070"\
  "Other" "12" "3" ""
  check_current_mp3_length "00.05"
  check_current_file_has_xing
  if [[ $tags_version -eq 2 ]];then
    check_current_file_size "97412"
  else
    check_current_file_size "97437"
  fi

  p_green "OK"
  echo
}

function test_time_vbr_stdin_and_tags_v1 { _test_time_vbr_stdin_and_tags 1; }
function test_time_vbr_stdin_and_tags_v2 { _test_time_vbr_stdin_and_tags 2; }

function test_time_vbr_output_fnames_and_dirs
{
  remove_output_dir

  test_name="vbr time output fnames & directories"
  M_FILE="La_Verue__Today"

  expected=" Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/La Verue/Riez Noir/La Verue-Today 1.mp3\" created
   File \"$OUTPUT_DIR/La Verue/Riez Noir/La Verue-Today 2.mp3\" created
   File \"$OUTPUT_DIR/La Verue/Riez Noir/La Verue-Today 3.mp3\" created
 Processed 9402 frames - Sync errors: 0
 time split ok"
  output_option="@a/@b/@a-@t @n"
  mp3splt_args="-o '$output_option' -d $OUTPUT_DIR $MP3_FILE -t 2.0" 
  run_check_output "$mp3splt_args" "$expected"

  check_if_directory_exist "$OUTPUT_DIR/La Verue"
  check_if_directory_exist "$OUTPUT_DIR/La Verue/Riez Noir"
  check_if_file_exist "$OUTPUT_DIR/La Verue/Riez Noir/La Verue-Today 1.mp3"
  check_if_file_exist "$OUTPUT_DIR/La Verue/Riez Noir/La Verue-Today 2.mp3"
  check_if_file_exist "$OUTPUT_DIR/La Verue/Riez Noir/La Verue-Today 3.mp3"

  p_green "OK"
  echo
}

function test_time_vbr_output_fnames_and_custom_tags_dirs
{
  remove_output_dir

  test_name="vbr time output fnames & custom tags & directories"
  M_FILE="La_Verue__Today"

  expected=" Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"$OUTPUT_DIR/La Verue/album1/La Verue-Today 1.mp3\" created
   File \"$OUTPUT_DIR/La Verue/album2/La Verue-Today 2.mp3\" created
   File \"$OUTPUT_DIR/La Verue/album3/La Verue-Today 3.mp3\" created
 Processed 9402 frames - Sync errors: 0
 time split ok"
  output_option="@a/@b/@a-@t @n"
  tags_option="%[@o,@b=album1][@b=album2][@b=album3]"
  mp3splt_args="-o '$output_option' -g \"$tags_option\" -d $OUTPUT_DIR $MP3_FILE -t 2.0" 
  run_check_output "$mp3splt_args" "$expected"

  check_if_directory_exist "$OUTPUT_DIR/La Verue"
  check_if_directory_exist "$OUTPUT_DIR/La Verue/album1"
  check_if_directory_exist "$OUTPUT_DIR/La Verue/album2"
  check_if_directory_exist "$OUTPUT_DIR/La Verue/album3"
  check_if_file_exist "$OUTPUT_DIR/La Verue/album1/La Verue-Today 1.mp3"
  check_if_file_exist "$OUTPUT_DIR/La Verue/album2/La Verue-Today 2.mp3"
  check_if_file_exist "$OUTPUT_DIR/La Verue/album3/La Verue-Today 3.mp3"

  p_green "OK"
  echo
}

function test_time_vbr_stdout_multiple_splitpoints
{
  remove_output_dir

  test_name="vbr time stdout & splitpoints > 2"
  M_FILE="La_Verue__Today"

expected=" Warning: using time mode with stdout !
 Processing file 'songs/${M_FILE}.mp3' ...
 info: file matches the plugin 'mp3 (libmad)'
 info: found Xing or Info header. Switching to frame mode... 
 info: MPEG 1 Layer 3 - 44100 Hz - Joint Stereo - FRAME MODE - Total time: 4m.05s
 info: starting time mode split
   File \"-\" created
   File \"-\" created
   File \"-\" created
 Processed 9402 frames - Sync errors: 0
 time split ok"
  mp3splt_args="-T 2 -o - $MP3_FILE -t 2.0"
  run_custom_check_output "$MP3SPLT $mp3splt_args > $OUTPUT_DIR/stdout.mp3" "" "$expected"

  current_file="$OUTPUT_DIR/stdout.mp3"
  check_current_mp3_length "02.00"
  check_current_file_size "5612022"

  p_green "OK"
  echo
}

function run_time_vbr_tests
{
  p_blue " TIME VBR mp3 tests ..."
  echo

  time_test_functions=$(declare -F | grep " test_time_vbr_" | awk '{ print $3 }')

  for test_func in $time_test_functions;do
    eval $test_func
  done

  p_blue " TIME VBR tests DONE."
  echo
}

#main
export LC_ALL="C"
start_date=$(date +%s)

run_time_vbr_tests

end_date=$(date +%s)

p_time_diff_cyan $start_date $end_date "\t"
echo -e '\n'

exit 0

