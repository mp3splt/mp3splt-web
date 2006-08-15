<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2 class=\"pagetitle\">About</h2>
<hr />
<div class=\"title\">mp3splt :</div>
<br />
<div class=\"indentdiv\">Mp3Splt is a command line utility to split mp3 (VBR supported) and ogg
files selecting a begin and an end time position, without
decoding. It's very useful to split large mp3/ogg to make smaller
files or to split entire albums to obtain original tracks. </div>
<div class=\"indentdiv\">If you want
to split an album, you can select split points and filenames manually
or you can get them automatically from CDDB (internet or a local file)
or from .cue files.
Supports also automatic silence split, that can be
used also to adjust cddb/cue splitpoints. Otherwise if you have a file created either with Mp3Wrap or AlbumWrap
you can extract tracks just in few seconds.</div>

<br />
<div class=\"featdiv\">mp3splt features :</div>
<ul>
<li class=\"lifeatures\">split mp3 and ogg files from a begin time to
an end time <i>without decoding</i></li>
<li class=\"lifeatures\">split an album with splitpoints from the freedb.org server</li>
<li class=\"lifeatures\">split an album with local .XMCD, .CDDB or .CUE file</li>
<li class=\"lifeatures\">split files automatically with silence detection</li>
<li class=\"lifeatures\">split files by a fixed time length</li>
<li class=\"lifeatures\">split files created with Mp3Wrap or AlbumWrap</li>
<li class=\"lifeatures\">support for mp3 VBR (variable bit rate)</li>
<li class=\"lifeatures\">specify output directory for splitted files</li>
</ul>

<br />
<div class=\"title\">mp3splt-gtk :</div>
<br />
<div class=\"indentdiv\"> Mp3splt-gtk is a GTK2 gui that uses
libmp3splt. Note that you have to install libmp3splt in order to
compile mp3splt-gtk.
</div>

<br />
<div class=\"featdiv\">mp3splt-gtk features :</div>
<ul>
<li class=\"lifeatures\">supports mp3 and ogg split with unlimited
splipoints for a song</li>
<li class=\"lifeatures\">split files in a chosen directory</li>
<li class=\"lifeatures\">integrated snackamp and beep-media-player
control</li>
<li class=\"lifeatures\">queueing or playing splitted files to player</li>
<li class=\"lifeatures\">advanced zoom progress bar with splitpoints</li>
<li class=\"lifeatures\">cddb and cue files supported</li>
<li class=\"lifeatures\">split file according to a freedb.org album
(includes freedb.org search)</li>
<li class=\"lifeatures\">wrap mode, error mode, time split, silence
auto detection split</li>
<li class=\"lifeatures\">auto-adjust silence split, frame mode option,
input not seekable option</li>
</ul>

<br />
<div class=\"title\">libmp3splt :</div>
<br />
<div class=\"indentdiv\">Libmp3splt is a library created from
mp3splt version 2.1c.</div>

<br />
<div class=\"featdiv\">libmp3splt features :</div>
<ul>
<li class=\"lifeatures\">supports mp3/ogg split with multiple splitpoints</li>
<li class=\"lifeatures\">search through freedb.org for albums</li>
<li class=\"lifeatures\">support for cddb and cue files</li>
<li class=\"lifeatures\">having a name for each file splitted is possible</li>
<li class=\"lifeatures\">support for splitting in a chosen directory</li>
<li class=\"lifeatures\">support for getting the splitted filenames</li>
<li class=\"lifeatures\">wrap mode, error mode, time split, silence
auto detection split</li>
<li class=\"lifeatures\">auto-adjust silence split, frame mode option,
input not seekable option</li>
</ul>
";
}

begin_document("mp3splt project - about page",
	       "default.css",FALSE);

create_table_with_menu("about");

end_document();
?>
