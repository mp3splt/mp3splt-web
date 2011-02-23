#!/bin/bash

. ./utils.sh || exit 1

#0.50 -> 1.00 (silence)
#1.37 -> 1.47 (silence)
#2.12 -> 2.22 (lower volume)

function _check_silence_output_files
{
  current_file="$OUTPUT_DIR/${O_FILE}_silence_1.ogg"
  check_current_ogg_length "0m:58.609s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "1"\
                     "http://www.jamendo.com"
  check_current_file_size "951612"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_2.ogg" 
  check_current_ogg_length "0m:45.780s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "2"\
                     "http://www.jamendo.com"
  check_current_file_size "698519"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_3.ogg" 
  check_current_ogg_length "1m:20.463s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "3"\
                     "http://www.jamendo.com"
  check_current_file_size "1371624"
}

function test_silence
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode - check creating mp3splt.log"

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.80, Min: 0.00, Remove: NO)

 Total silence points found: 2. (Selected 3 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/${O_FILE}_silence_1.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_2.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_3.ogg\" created
 silence split ok
 Average silence level: -20.26 dB"
  mp3splt_args="-d $OUTPUT_DIR -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  _check_silence_output_files

  expected="songs/${O_FILE}.ogg
-48.00\t0.00
50.649979\t60.609886\t433
98.005623\t105.996193\t353"
  check_file_content "mp3splt.log" "$expected"

  p_green "OK"
  echo

  test_name="silence mode - check reading from mp3splt.log"

  remove_output_dir

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.80, Min: 0.00, Remove: NO)
 Found silence log file 'mp3splt.log' ! Reading silence points from file to save time ;)
 Total silence points found: 2. (Selected 3 tracks)
   File \"$OUTPUT_DIR/${O_FILE}_silence_1.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_2.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_3.ogg\" created
 silence split ok"
  mp3splt_args="-d $OUTPUT_DIR -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  _check_silence_output_files

  p_green "OK"
  echo
}

function test_silence_and_pretend
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & pretend"

  expected=" Pretending to split file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.80, Min: 0.00, Remove: NO)

 Total silence points found: 2. (Selected 3 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/${O_FILE}_silence_1.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_2.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_3.ogg\" created
 silence split ok
 Average silence level: -20.26 dB"
  mp3splt_args="-P -d $OUTPUT_DIR -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  check_output_directory_is_empty
  check_if_file_does_not_exist "mp3splt.log"

  p_green "OK"
  echo
}

function test_silence_and_cue_export
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & cue export"

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.80, Min: 0.00, Remove: NO)

 Total silence points found: 2. (Selected 3 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/${O_FILE}_silence_1.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_2.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_3.ogg\" created
 silence split ok
 Average silence level: -20.26 dB
 CUE file 'output/output_out.cue' created."
  mp3splt_args="-E output/out.cue -d $OUTPUT_DIR -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  expected="songs/${O_FILE}.ogg
-48.00\t0.00
50.649979\t60.609886\t433
98.005623\t105.996193\t353"
  check_file_content "mp3splt.log" "$expected"

  check_file_content "output/output_out.cue" 'TITLE "Getting Back From Where I'\''ve Been"
PERFORMER "Kelly Allyn"
FILE "songs/Kelly_Allyn__Whiskey_Can_silence.ogg" OGG
  TRACK 01 AUDIO
    TITLE "Whiskey Can"
    PERFORMER "Kelly Allyn"
    INDEX 01 00:00:00
  TRACK 02 AUDIO
    TITLE "Whiskey Can"
    PERFORMER "Kelly Allyn"
    INDEX 01 00:58:61
  TRACK 03 AUDIO
    TITLE "Whiskey Can"
    PERFORMER "Kelly Allyn"
    INDEX 01 01:44:39'

  p_green "OK"
  echo
}

function test_silence_and_pretend_and_cue_export
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & pretend & cue export"

  expected=" Pretending to split file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.80, Min: 0.00, Remove: NO)

 Total silence points found: 2. (Selected 3 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/${O_FILE}_silence_1.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_2.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_3.ogg\" created
 silence split ok
 Average silence level: -20.26 dB
 CUE file 'output/output_out.cue' created."
  mp3splt_args="-P -E output/out.cue -d $OUTPUT_DIR -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  check_output_directory_number_of_files 1
  check_if_file_does_not_exist "mp3splt.log"

  p_green "OK"
  echo
}

function test_silence_offset
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & offset"

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.00, Min: 0.00, Remove: NO)

 Total silence points found: 2. (Selected 3 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/${O_FILE}_silence_1.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_2.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_3.ogg\" created
 silence split ok
 Average silence level: -20.26 dB"
  mp3splt_args="-d $OUTPUT_DIR -p off=0 -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_1.ogg"
  check_current_ogg_length "0m:50.640s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "1"\
                     "http://www.jamendo.com"
  check_current_file_size "950899"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_2.ogg" 
  check_current_ogg_length "0m:47.359s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "2"\
                     "http://www.jamendo.com"
  check_current_file_size "698641"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_3.ogg" 
  check_current_ogg_length "1m:26.853s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "3"\
                     "http://www.jamendo.com"
  check_current_file_size "1372381"

  expected="songs/${O_FILE}.ogg
-48.00\t0.00
50.649979\t60.609886\t433
98.005623\t105.996193\t353"
  check_file_content "mp3splt.log" "$expected"

  p_green "OK"
  echo
}

function test_silence_threshold
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & threshold"

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -22.3 dB, Off: 0.80, Min: 0.00, Remove: NO)

 Total silence points found: 3. (Selected 4 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/${O_FILE}_silence_1.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_2.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_3.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_4.ogg\" created
 silence split ok
 Average silence level: -20.23 dB"
  mp3splt_args="-d $OUTPUT_DIR -p th=-22.3 -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_1.ogg"
  check_current_ogg_length "0m:58.609s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "1"\
                     "http://www.jamendo.com"
  check_current_file_size "951612"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_2.ogg" 
  check_current_ogg_length "0m:45.789s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "2"\
                     "http://www.jamendo.com"
  check_current_file_size "698521"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_3.ogg" 
  check_current_ogg_length "0m:33.469s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "3"\
                     "http://www.jamendo.com"
  check_current_file_size "572634"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_4.ogg" 
  check_current_ogg_length "0m:46.983s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "4"\
                     "http://www.jamendo.com"
  check_current_file_size "803794"

  expected="songs/${O_FILE}.ogg
-22.30\t0.00
50.626759\t60.609886\t434
98.005623\t105.999092\t354
137.620316\t137.941040\t15"
  check_file_content "mp3splt.log" "$expected"

  p_green "OK"
  echo
}

function test_silence_nt
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & nt"

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: User mode (Th: -48.0 dB, Off: 0.80, Min: 0.00, Remove: NO)

 Total silence points found: 2. (Selected 2 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/${O_FILE}_silence_1.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_2.ogg\" created
 silence split ok
 Average silence level: -20.26 dB"
  mp3splt_args="-d $OUTPUT_DIR -p nt=2 -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_1.ogg"
  check_current_ogg_length "0m:58.609s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "1"\
                     "http://www.jamendo.com"
  check_current_file_size "951612"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_2.ogg" 
  check_current_ogg_length "2m:06.243s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "2"\
                     "http://www.jamendo.com"
  check_current_file_size "2065481"

  expected="songs/${O_FILE}.ogg
-48.00\t0.00
50.649979\t60.609886\t433
98.005623\t105.996193\t353"
  check_file_content "mp3splt.log" "$expected"

  p_green "OK"
  echo
}

function test_silence_rm
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & rm"

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.80, Min: 0.00, Remove: YES)

 Total silence points found: 2. (Selected 3 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/${O_FILE}_silence_1.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_2.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_3.ogg\" created
 silence split ok
 Average silence level: -20.26 dB"
  mp3splt_args="-d $OUTPUT_DIR -p rm -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_1.ogg"
  check_current_ogg_length "0m:50.640s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "1"\
                     "http://www.jamendo.com"
  check_current_file_size "950899"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_2.ogg" 
  check_current_ogg_length "0m:37.399s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "2"\
                     "http://www.jamendo.com"
  check_current_file_size "697756"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_3.ogg" 
  check_current_ogg_length "1m:18.863s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "3"\
                     "http://www.jamendo.com"
  check_current_file_size "1371486"

  expected="songs/${O_FILE}.ogg
-48.00\t0.00
50.649979\t60.609886\t433
98.005623\t105.996193\t353"
  check_file_content "mp3splt.log" "$expected"

  p_green "OK"
  echo
}

function test_silence_rm_and_output_format
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & rm & output format"

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.80, Min: 0.00, Remove: YES)

 Total silence points found: 2. (Selected 3 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/silence_1_00:00:00 00:50:64.ogg\" created
   File \"$OUTPUT_DIR/silence_2_01:00:60 01:38:00.ogg\" created
   File \"$OUTPUT_DIR/silence_3_01:45:99 03:04:85.ogg\" created
 silence split ok
 Average silence level: -20.26 dB"
  mp3splt_args="-d $OUTPUT_DIR -p rm -o \"silence_@n_@m:@s:@h+@M:@S:@H\" -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/silence_1_00:00:00 00:50:64.ogg"
  check_current_ogg_length "0m:50.640s"

  current_file="$OUTPUT_DIR/silence_2_01:00:60 01:38:00.ogg"
  check_current_ogg_length "0m:37.399s"

  current_file="$OUTPUT_DIR/silence_3_01:45:99 03:04:85.ogg"
  check_current_ogg_length "1m:18.863s"

  p_green "OK"
  echo
}

function test_silence_rm_and_overlap
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & rm & overlap"

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.80, Min: 0.00, Remove: YES)

 Total silence points found: 2. (Selected 3 tracks)
 Writing silence log file 'mp3splt.log' ...
 info: overlapping split files with 0.10.0
   File \"$OUTPUT_DIR/silence_1_00:00:00 01:00:64.ogg\" created
   File \"$OUTPUT_DIR/silence_2_01:00:60 01:48:00.ogg\" created
   File \"$OUTPUT_DIR/silence_3_01:45:99 03:04:85.ogg\" created
 silence split ok
 Average silence level: -20.26 dB"
  mp3splt_args="-d $OUTPUT_DIR -O 0.10 -p rm -o \"silence_@n_@m:@s:@h+@M:@S:@H\" -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/silence_1_00:00:00 01:00:64.ogg"
  check_current_ogg_length "1m:00.640s"

  current_file="$OUTPUT_DIR/silence_2_01:00:60 01:48:00.ogg"
  check_current_ogg_length "0m:47.399s"

  current_file="$OUTPUT_DIR/silence_3_01:45:99 03:04:85.ogg"
  check_current_ogg_length "1m:18.863s"

  p_green "OK"
  echo
}

function test_silence_rm_and_custom_tags
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & rm & custom tags"

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.80, Min: 0.00, Remove: YES)

 Total silence points found: 2. (Selected 3 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/${O_FILE}_silence_1.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_2.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_3.ogg\" created
 silence split ok
 Average silence level: -20.26 dB"
  mp3splt_args="-d $OUTPUT_DIR -g %[@o,@N=1,@t=title1][@t=title2][@a=artist3] -p rm -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_1.ogg"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "title1" "2007-07-10 15:45:07" "Southern Rock" "1"\
                     "http://www.jamendo.com"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_2.ogg" 
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "title2" "2007-07-10 15:45:07" "Southern Rock" "2"\
                     "http://www.jamendo.com"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_3.ogg" 
  check_all_ogg_tags "artist3" "Getting Back From Where I've Been"\
                     "title1" "2007-07-10 15:45:07" "Southern Rock" "3"\
                     "http://www.jamendo.com"

  p_green "OK"
  echo
}

function test_silence_rm_and_custom_tags_and_output_format
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & rm & custom tags & output format"

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.80, Min: 0.00, Remove: YES)

 Total silence points found: 2. (Selected 3 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/Kelly Allyn__Getting Back From Where I've Been__title1_1.ogg\" created
   File \"$OUTPUT_DIR/Kelly Allyn__Getting Back From Where I've Been__title2_2.ogg\" created
   File \"$OUTPUT_DIR/artist3__Getting Back From Where I've Been__title1_3.ogg\" created
 silence split ok
 Average silence level: -20.26 dB"
  mp3splt_args="-d $OUTPUT_DIR -g %[@o,@N=1,@t=title1][@t=title2][@a=artist3] -o @a__@b__@t_@n -p rm -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/Kelly Allyn__Getting Back From Where I've Been__title1_1.ogg"
  check_current_ogg_length "0m:50.640s"

  current_file="$OUTPUT_DIR/Kelly Allyn__Getting Back From Where I've Been__title2_2.ogg"
  check_current_ogg_length "0m:37.399s"

  current_file="$OUTPUT_DIR/artist3__Getting Back From Where I've Been__title1_3.ogg" 
  check_current_ogg_length "1m:18.863s"

  p_green "OK"
  echo
}

function test_silence_min
{
  rm -f mp3splt.log
  remove_output_dir

  O_FILE="Kelly_Allyn__Whiskey_Can_silence"

  test_name="silence mode & min"

  expected=" Processing file 'songs/${O_FILE}.ogg' ...
 info: file matches the plugin 'ogg vorbis (libvorbis)'
 info: Ogg Vorbis Stream - 44100 - 156 Kb/s - 2 channels - Total time: 3m.04s
 info: starting silence mode split
 Silence split type: Auto mode (Th: -48.0 dB, Off: 0.80, Min: 9.00, Remove: NO)

 Total silence points found: 1. (Selected 2 tracks)
 Writing silence log file 'mp3splt.log' ...
   File \"$OUTPUT_DIR/${O_FILE}_silence_1.ogg\" created
   File \"$OUTPUT_DIR/${O_FILE}_silence_2.ogg\" created
 silence split ok
 Average silence level: -20.26 dB"
  mp3splt_args="-d $OUTPUT_DIR -p min=9 -s $SILENCE_OGG_FILE" 
  run_check_output "$mp3splt_args" "$expected"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_1.ogg"
  check_current_ogg_length "0m:58.609s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "1"\
                     "http://www.jamendo.com"
  check_current_file_size "951612"

  current_file="$OUTPUT_DIR/${O_FILE}_silence_2.ogg" 
  check_current_ogg_length "2m:06.243s"
  check_all_ogg_tags "Kelly Allyn" "Getting Back From Where I've Been"\
                     "Whiskey Can" "2007-07-10 15:45:07" "Southern Rock" "2"\
                     "http://www.jamendo.com"
  check_current_file_size "2065481"

  expected="songs/${O_FILE}.ogg
-48.00\t9.00
50.649979\t60.609886\t433"
  check_file_content "mp3splt.log" "$expected"

  p_green "OK"
  echo
}

function run_silence_mode_tests
{
  p_blue " SILENCE ogg tests ..."
  echo

  silence_mode_test_functions=$(declare -F | grep " test_silence" | awk '{ print $3 }')

  for test_func in $silence_mode_test_functions;do
    eval $test_func
  done

  p_blue " SILENCE ogg tests DONE."
  echo
}

#main
export LC_ALL="C"
start_date=$(date +%s)

run_silence_mode_tests

end_date=$(date +%s)

p_time_diff_cyan $start_date $end_date "\t"
echo -e '\n'

exit 0

