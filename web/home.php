<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h1 class=\"pagetitle\">Mp3splt Project Homepage</h1>
<hr />

<div class=\"title\">Description :</div>
<br />
<div class=\"indentdiv\"><span style=\"font-weight:bold\">Mp3Splt-project</span> is a utility to split mp3 and ogg
files selecting a begin and an end time position, <i>without
decoding</i>. It's very useful to split large mp3/ogg to make smaller
files or to split entire albums to obtain original tracks. If you want
to split an album, you can select split points and filenames manually
or you can get them automatically from CDDB (internet or a local file)
or from .cue files. Supports also automatic silence split, that can be
used also to adjust cddb/cue splitpoints. You can extract tracks from
Mp3Wrap or AlbumWrap files in few seconds. Mp3splt-project is splitted in 3 parts :
libmp3splt, mp3splt and mp3splt-gtk. </div>
<div class=\"indentdiv\">See <a href=\"about.php\">the about section</a> for more details.</div>

<table width=\"100%\">
<tr>
<td>
<br />
<span style=\"font-weight:bold\">OS</span> : GNU Linux (*BSD - MacOS X - BeOS) / Windows<br />
<span style=\"font-weight:bold\">Environment</span> : Console (Text Based) / Graphic GTK2<br />
<span style=\"font-weight:bold\">License</span> : <a href=\"http://www.gnu.org/licenses/gpl.html\">GNU
General Public License</a><br /><br />

<div class=\"title\">Latest releases:</div>
<br />

<table class=\"mainpagedownloadtable\">

<!-- top stuff -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"text-align:center\">
<div style=\"font-weight:bold\">Libmp3splt</div>
<div style=\"font-style:italic\">0.3.1</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"text-align:center\">
<div style=\"font-weight:bold\">Mp3splt</div>
<div style=\"font-style:italic\">2.1</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"text-align:center\">
<div style=\"font-weight:bold\">Mp3splt-gtk</div>
<div style=\"font-style:italic\">0.3.1</div>
</td>
</tr>

<tr>
<td colspan=\"3\">
<div style=\"text-align:center;font-size:140%\">
<a
onmouseover=\"var download_link=document.getElementById('download_link');
download_link.style.backgroundColor='#FFFFCC';
download_link.style.textDecoration='underline';\"
onmouseout=\"var download_link=document.getElementById('download_link');
download_link.style.backgroundColor='white';
download_link.style.textDecoration='none';\"
href=\"downloads.php\">
<img border=\"0\" style=\"display:inline;vertical-align:middle;padding-top:4pt\" alt=\"\"
src=\"icons/download.png\" /></a><a 
onmouseover=\"var download_link=this;
download_link.style.backgroundColor='#FFFFCC';
download_link.style.textDecoration='underline';\"
onmouseout=\"var download_link=this;
download_link.style.backgroundColor='white';
download_link.style.textDecoration='none';\"
id=\"download_link\" href=\"downloads.php\">Download page</a></div>
</td>
</tr>

</table>

</td>
<td>

<a
href=\"screenshots.php\">
<img alt=\"\" border=\"0\" src=\"screenshots/thumb.mp3splt-gtk_0.3_gnu_linux.png\" />
</a>

</td>
</tr>
</table>

Mp3splt-gtk uses SnackAmp as the default player.<br />
Download SnackAmp <span style=\"font-weight:bold\">version >= 3.1.3
Beta</span> from the <a
href=\"http://snackamp.sourceforge.net\">SnackAmp web site</a>.<br />
<br />

<div class=\"title\">News :</div>
<br />
";

  include "news.html";

  echo "
<br />
<div style=\"font-size:80%\">Mp3splt-project do not own the download icon of this page. Please see the <a href=\"icons/icons_licenses.txt\">icons licenses</a>.</div>
";
}

begin_document("mp3 and ogg splitter - mp3splt project home page",
	       "default.css",FALSE);

create_table_with_menu("home");

end_document();
?>
