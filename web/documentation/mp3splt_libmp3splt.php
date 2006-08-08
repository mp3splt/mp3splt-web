<?php
include "../menu.php";

function create_mp3splt_libmp3splt_table()
{
  echo "
<hr />
<h2  class=\"pagetitle\">Mp3splt 2.1c and Libmp3splt</h2>
<hr />

<table class=\"downloadtable\" style=\"margin:10pt;\">

<tr>
<td class=\"dtablecell1\" align=\"center\"><b>Mp3splt option</b></td>
<td class=\"dtablecell1\" align=\"center\"><b>Option description</b></td>
<td class=\"dtablecell1\" align=\"center\"><b>Libmp3splt implementation</b></td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-w
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
Wrap mode, used to split files created with mp3wrap.
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-l
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
Lists all tracks wrapped in a Mp3Wrap or AlbumWrap archive without any
extraction.
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-e
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
Error mode (mp3 only).  It is useful to split large file derivated
from a concatenation of smaller files. When you have a file to split,
you should always try to use this option.
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-t TIME
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
This option will create an indefinite number of smaller files with a
fixed time length  specified  by  TIME. (minutes.seconds[.hundredths])
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-s
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
Silence  mode, to split with silence detection.
(enables -f by default for mp3)<br />
<div class=\"featdiv\">Parameters : </div>
threshold level (th=FLOAT) : the sound level to be considered  
silence<br />
<span class=\"colorspan\">(it is a float
number between -96 and 0. Default is -48 dB)</span><br />
number of tracks (nt=INTEGER) : the desired number of tracks<br />
<span class=\"colorspan\">(positive integer number of tracks
to be splitted;by default all tracks are splitted)</span><br />
cutpoint offset (off=FLOAT) : the offset of cutpoint in silence<br />
<span class=\"colorspan\">Float number between -2 and 2
and allows you to adjust the offset of
cutpoint in silence time.  <br />0  is  the begin of silence, and 1 the
end;default is 0.8.</span><br />
minimum_length (min=FLOAT) : the minimum silence length in seconds<br />
<span class=\"colorspan\">(positive float of the minimum number of seconds to be
considered a valid splitpoint)</span><br />
remove  silence  (rm) : allows you to remove the silence between splitted tracks

</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-c SOURCE
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
SOURCE may be the name of a  \".CUE\"  file or a \".CDDB\" file, or
\"query\" to get splitpoints from freedb.org. (proxy not supported now)
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">~YES</div> (no proxy)
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-a
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
This option uses silence detection to auto-adjust splitpoints.
(enables -f by default for mp3)<br />
<div class=\"featdiv\">Parameters : </div>
threshold level (th=FLOAT) : the sound level to be considered 
silence<br />
<span class=\"colorspan\">(it is a float
number between -96 and 0. Default is -48 dB)</span><br />
cutpoint offset (off=FLOAT) : the offset of cutpoint in silence<br />
<span class=\"colorspan\">Float number between -2 and 2
and allows you to adjust the offset of
cutpoint in silence time.  <br />0  is  the begin of silence, and 1 the
end;default is 0.8.</span><br />
gap (gap=INTEGER) : the gap value around splitpoint to search for
silence<br />
<span class=\"colorspan\">(positive  integer  for  the  time  to decode before and after
splitpoint;default gap is 30 seconds)</span>
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-p PARAMETERS
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
When using -a and -s option some users parameters can be specified in
the argument and must be in the form:<br />
&lt;name1=value,name2=value,..&gt;
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-f
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
Frame mode (mp3 only). Process all frames, seeking split positions by
counting frames and not with bitrate guessing.
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-k
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
Input not seekable. This allows you to split mp3 and ogg streams which can be read only one
time and can’t be seeked.
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-o FORMAT 
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
Output format, to specify an output filename.
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-d NAME
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
To put all output files in the directory named NAME.
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-n
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
Does not write ID3 or Vorbis comment in outputfile.
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

<tr>
<!-- mp3splt option -->
<td class=\"dtablecell\" align=\"center\">
-q
</td>
<!-- option description -->
<td class=\"dtablecell\" align=\"center\">
Quiet mode.
</td>
<!-- libmp3splt implementation -->
<td class=\"dtablecell\" align=\"center\">
<div class=\"yes\">YES</div>
</td>
</tr>

</table>
";

}

begin_document("mp3splt and libmp3splt",
	       "../default.css");

echo "<br />
&nbsp;&nbsp;&nbsp;&nbsp;
<a href=\"../documentation.php\">&lt;&lt;back</a>";

create_mp3splt_libmp3splt_table();

end_document();

?>