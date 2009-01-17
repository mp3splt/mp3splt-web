<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2 class=\"pagetitle\">About</h2>
<hr />

<!-- mp3splt project -->
<div class=\"title\">mp3splt-project :</div>
<br />
<div class=\"indentdiv\">Mp3splt-project is a utility to split mp3 and ogg
files selecting a begin and an end time position, <i>without
decoding</i>. It's very useful to split large mp3/ogg to make smaller
files or to split entire albums to obtain original tracks. If you want
to split an album, you can select split points and filenames manually
or you can get them automatically from CDDB (internet or a local file)
or from .cue files. Supports also automatic silence split, that can be
used also to adjust cddb/cue splitpoints. You can extract tracks from
Mp3Wrap or AlbumWrap files in few seconds. Mp3splt-project is split in 3 parts :
libmp3splt, mp3splt and mp3splt-gtk.</div>
<br />
<!-- mp3splt project common features -->
<div class=\"featdiv\">mp3splt-project common features :</div>
<ul>
<li class=\"lifeatures\">split mp3 and ogg files from a begin time to
an end time <i>without decoding</i></li>
<li class=\"lifeatures\">ID3v1 & ID3v2 tags support for mp3 files (using libid3tag)</i></li>
<li class=\"lifeatures\">split an album with splitpoints from the freedb.org server</li>
<li class=\"lifeatures\">split an album with local .XMCD, .CDDB or .CUE file</li>
<li class=\"lifeatures\">split files automatically with silence detection</li>
<li class=\"lifeatures\">split files by a fixed time length</li>
<li class=\"lifeatures\">split files created with Mp3Wrap or AlbumWrap</li>
<li class=\"lifeatures\">split concatenated mp3 files</li>
<li class=\"lifeatures\">support for mp3 VBR (variable bit rate)</li>
<li class=\"lifeatures\">specify output directory for split files</li>
</ul>

<!-- mp3splt -->
<div class=\"title\">mp3splt :</div>
<br />
<div class=\"indentdiv\">Mp3splt is the command line program from the mp3splt-project.</div>

<!--<br />
<div class=\"featdiv\">mp3splt features :</div>
<ul>
<li class=\"lifeatures\">specify output directory for split files</li>
</ul>-->

<br />

<!-- libmp3splt -->
<div class=\"title\">libmp3splt :</div>
<br />
<div class=\"indentdiv\">Libmp3splt is a library created from mp3splt version 2.1c.</div>

<br />
<!--<div class=\"featdiv\">libmp3splt features :</div>
<ul>
<li class=\"lifeatures\">wrap mode, error mode, time split, silence
auto detection split</li>
</ul>-->

<!-- mp3splt-gtk -->
<div class=\"title\">mp3splt-gtk :</div>
<br />
<div class=\"indentdiv\"> Mp3splt-gtk is a GTK2 gui that uses
libmp3splt.
</div>

<br />
<div class=\"featdiv\">mp3splt-gtk features :</div>
<ul>
<li class=\"lifeatures\">integrated player using gstreamer</li>
<li class=\"lifeatures\">support for snackamp and audacious control</li>
<li class=\"lifeatures\">advanced zoom progress bar with silence wave and splitpoints</li>
</ul>
";
}

begin_document("mp3splt project - about page",
	       "default.css",FALSE);

create_table_with_menu("about");

end_document();
?>
