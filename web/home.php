<?php
include './menu.php';

function create_home_page()
{
  echo "
<h1 class=\"pagetitle\">Mp3splt Project Homepage</h1>
<hr />

<div class=\"title\">Description :</div>
<br />
<div class=\"indentdiv\"><span style=\"font-weight:bold\">Mp3Splt</span> is a command line utility to split mp3 and ogg
files selecting a begin and an end time position, <i>without
decoding</i>. It's very useful to split large mp3/ogg to make smaller
files or to split entire albums to obtain original tracks. </div>
<div class=\"indentdiv\">If you want
to split an album, you can select split points and filenames manually
or you can get them automatically from CDDB (internet or a local file)
or from .cue files.
Supports also automatic silence split, that can be
used also to adjust cddb/cue splitpoints. You can extract tracks from
Mp3Wrap or AlbumWrap files in few seconds.</div>
<div class=\"indentdiv\"><span
style=\"font-weight:bold\">Libmp3splt</span> is a library created from
mp3splt version 2.1c.</div>
<div class=\"indentdiv\"><span style=\"font-weight:bold\">Mp3splt-gtk</span> is a GTK2 gui that uses
libmp3splt. </div>
<div style=\"margin:0pt;padding:0pt;text-align:right;padding-right:5pt;\">
- see <a href=\"about.php\">the about section</a> for more details</div>
<br />

<table width=\"100%\">
<tr>
<td>
<span style=\"font-weight:bold\">OS</span> : GNU Linux (*BSD - MacOS X - BeOS) / Windows<br />
<span style=\"font-weight:bold\">Environment</span> : Console (Text Based) / Graphic GTK2<br />
<span style=\"font-weight:bold\">License</span> : <a href=\"http://www.gnu.org/licenses/gpl.html\">GNU
General Public License</a><br /><br />
<br />
Please use the
<a href=\"http://sourceforge.net/mail/?group_id=55130\">
 mailing list</a> for bug reporting.
<br /><br />
Non-windows users need libmp3splt for mp3splt-gtk.
</td>
<td>

<a
href=\"screenshots/mp3splt-gtk_0.3_gnu_linux.png\">
<img alt=\"\" border=\"0\" src=\"screenshots/thumb.mp3splt-gtk_0.3_gnu_linux.png\" />
</a>

</td>
</tr>
</table>

<div class=\"title\">Latest releases:</div>
<br />

<table align=\"center\" class=\"downloadtable\">

<tr>
<td align=\"center\"><br /></td>
<td class=\"dtablecell1\" align=\"center\"><span
style=\"font-weight:bold\">Source code</span></td> 
<td class=\"dtablecell1\" align=\"center\"><span style=\"font-weight:bold\">GNU/Linux</span></td>
<td class=\"dtablecell1\" align=\"center\"><span style=\"font-weight:bold\">Windows</span></td>
<td class=\"dtablecell1\" align=\"center\"><span style=\"font-weight:bold\">MacOSX</span></td>

</tr>
<tr>

<td class=\"dtablecell1\" align=\"center\"><span style=\"font-weight:bold\">Command Line</span></td>
<td class=\"dtablecell\" align=\"center\">
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-2.1c-src.tar.gz?download\">
mp3splt v2.1 (src)</a>
</td>
<td class=\"dtablecell\" align=\"center\">
<a
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt_2.1-1_i386.deb?download\">
i386 debian package</a><br />
<a
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-2.1-1.i386.rpm?download\">
i386 rpm package</a><br />
<a
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-2.1-1.src.rpm?download\"
>rpm package (src)</a><br />
<a
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-2.1-bin-i586.tar.gz?download\">
i586 binary
</a>
</td>
<td class=\"dtablecell\" align=\"center\"> <a
 href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-2.1-win32.zip?download\">
mp3splt v2.1</a>
</td>
<td class=\"dtablecell\" align=\"center\"> <a
 href=\"http://fink.sourceforge.net/pdb/package.php/mp3splt\">
 Fink package</a> 
</td>

</tr>
<tr>

<td class=\"dtablecell1\" align=\"center\"> <span style=\"font-weight:bold\">Graphic (GUI)</span></td>
<td class=\"dtablecell\" align=\"center\">
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk-0.3.1.tar.gz?download\">
mp3splt-gtk v0.3.1 (src)</a>
</td>
<td class=\"dtablecell\" align=\"center\">
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_0.3.1_i386.deb?download\">
i386 debian package</a>
</td>
<td class=\"dtablecell\" align=\"center\"> 
<a	
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_0.3.1.exe?download\">
mp3splt-gtk v0.3.1</a><br />(installer)
</td>
<td class=\"dtablecell\" align=\"center\"> <a
  href=\"http://alex.primafila.net/albumextractorx/\">AlbumExtractorX</a>
<br />
mp3splt-gtk compiles
</td>
</tr>

<tr>
<td class=\"dtablecell1\" align=\"center\"> <span style=\"font-weight:bold\">Library</span></td>
<td class=\"dtablecell\" align=\"center\" colspan=\"1\">
<a href=\"http://prdownloads.sourceforge.net/mp3splt/libmp3splt-0.3.1.tar.gz?download\">
libmp3splt v0.3.1 (src)</a>
</td>
<td class=\"dtablecell\" align=\"center\" colspan=\"1\">
<a href=\"http://prdownloads.sourceforge.net/mp3splt/libmp3splt_0.3.1_i386.deb?download\">
i386 debian package</a>
</td>
<td class=\"dtablecell\" align=\"center\" colspan=\"1\">
compiles
</td>
<td class=\"dtablecell\" align=\"center\" colspan=\"1\">
compiles
</td>
</tr>
</table>

<br />
Thanks to Tom Wilkason for the (remote) socket server implemetation and for
his support :)
<br />You can download SnackAmp on the <a
href=\"http://snackamp.sourceforge.net\">SnackAmp web site</a> -
(download version >= 3.1.3 Beta)
<br /><br />

<div class=\"title\">News :</div>
<br />
";

  include "news.html";

  echo "
<br />

";

  //<center><font face=\"Arial\" size=\"2\">by <i>Matteo Trotta</i> - 2005</font></center>
}
?>

<?php
begin_document("mp3 and ogg splitter - mp3splt project home page",
	       "default.css",FALSE);

create_table_with_menu("home");

end_document();
?>
