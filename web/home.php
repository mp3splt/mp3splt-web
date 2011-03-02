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
Mp3Wrap or AlbumWrap files in few seconds. For mp3 files, both ID3v1 &amp;
ID3v2 tags are supported. Mp3splt-project is split in 3 parts :
libmp3splt, mp3splt and mp3splt-gtk. </div>
<div class=\"indentdiv\">See <a href=\"about.php\">the about section</a> for more details.</div>

<table width=\"100%\">
<tr>
<td valign='top'>
<br />
<span style=\"font-weight:bold\">OS</span> : GNU Linux, *BSD, MacOS X, BeOS, Windows<br />
<span style=\"font-weight:bold\">Environment</span> : Console (Text Based), Graphic GTK2<br />
<span style=\"font-weight:bold\">License</span> : <a href=\"http://www.gnu.org/licenses/gpl-2.0.html\">GNU
General Public License version 2</a><br /><br />

<div class=\"title\">Latest releases:</div>
<br />

<table class=\"mainpagedownloadtable\">

<!-- top stuff -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"text-align:center\">
<div style=\"font-weight:bold\">Libmp3splt</div>
<div style=\"font-style:italic\">0.6.1</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"text-align:center\">
<div style=\"font-weight:bold\">Mp3splt</div>
<div style=\"font-style:italic\">2.3</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"text-align:center\">
<div style=\"font-weight:bold\">Mp3splt-gtk</div>
<div style=\"font-style:italic\">0.6.1</div>
</td>
</tr>

<tr>
<td colspan=\"3\">

<!-- stable releases -->
<div style=\"text-align:center;font-size:140%\">
<a 
onmouseover=\"var download_link=this;
download_link.style.backgroundColor='#FFFFCC';
download_link.style.color='black';
\"
onmouseout=\"var download_link=this;
download_link.style.backgroundColor='white';
download_link.style.textDecoration='none';
download_link.style.color='#6340FF';
\"
class=\"download\"
id=\"download_link\"
style=\"display:block;border:none;margin:0pt;padding:0pt;padding-top:4pt;padding-bottom:2pt\"
href=\"downloads.php\">
<img border=\"0\" style=\"vertical-align:middle;z-index:1\" alt=\"\"
src=\"icons/download_big.png\" />Download</a></div>

<!-- unstable releases 
<div style=\"text-align:center;font-size:140%\">
<a 
onmouseover=\"var download_link=this;
download_link.style.backgroundColor='#FFFFCC';
download_link.style.color='black';
\"
onmouseout=\"var download_link=this;
download_link.style.backgroundColor='white';
download_link.style.textDecoration='none';
download_link.style.color='#6340FF';
\"
class=\"download\"
id=\"download_link\"
style=\"display:block;border:none;margin:0pt;padding:0pt;padding-top:4pt;padding-bottom:2pt\"
href=\"unstable_downloads.php\">
<img border=\"0\" style=\"vertical-align:middle;z-index:1\" alt=\"\"
src=\"icons/download_big.png\" />Unstable downloads</a></div> -->

<div class=\"title\" style=\"padding-top:5pt;\">News :</div>
<br />

";

  include "news.html";

echo "
</td>
</tr>

</table>

</td>
<td>

<a
href=\"screenshots/mp3splt-gtk_0.6.1.png\">
<img alt=\"\" border=\"0\" src=\"screenshots/small_mp3splt-gtk_0.6.1.png\" />
</a>

</td>
</tr>
</table>
";
}

begin_document("mp3 and ogg splitter - mp3splt project home page",
	       "default.css",FALSE);

create_table_with_menu("home");

end_document();
?>
