<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2  class=\"pagetitle\">Downloads</h2>
<hr />
<div>For older downloads, see the <a href=\"downloads_archive.php\">downloads archive</a>.</div>
<div>Note : in order to compile mp3splt-gtk, you need libmp3splt.</div>
<br />

<table class=\"mainpagedownloadtable\">

<!-- top stuff -->
<tr>
<td>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:none;text-align:center\">
<div style=\"font-weight:bold\">Libmp3splt</div>
<div style=\"font-style:italic\">0.3.1</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:none;text-align:center\">
<div style=\"font-weight:bold\">Mp3splt</div>
<div style=\"font-style:italic\">2.1</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:none;text-align:center;border-right:none\">
<div style=\"font-weight:bold\">Mp3splt-gtk</div>
<div style=\"font-style:italic\">0.3.1</div>
</td>
</tr>

<!-- Source code -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img src=\"icons/keyboard.png\" /><br />
<span style=\"font-weight:bold\">Source code</span>
</td>
<td class=\"mainpagedownloadtd\">
<a>Mp3splt</a>
</td>
<td class=\"mainpagedownloadtd\">
Mp3splt-gtk
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
Mp3splt-gtk
</td>
</tr>

<!-- Debian -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img src=\"icons/debian.png\" /><img src=\"icons/ubuntu.png\" />
<div class=\"osname\">Debian-based</div>
</td>
<td class=\"mainpagedownloadtd\">
<a>Mp3splt</a>
</td>
<td class=\"mainpagedownloadtd\">
Mp3splt-gtk
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
Mp3splt-gtk
</td>
</tr>

<!-- Slackware -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img src=\"icons/slackware.png\" /><br />
<div class=\"osname\">Slackware</div>
</td>
<td class=\"mainpagedownloadtd\">
<a>Mp3splt</a>
</td>
<td class=\"mainpagedownloadtd\">
Mp3splt-gtk
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
Mp3splt-gtk
</td>
</tr>

<!-- Gentoo -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img src=\"icons/gentoo.png\" /><br />
<div class=\"osname\">Gentoo</div>
</td>
<td class=\"mainpagedownloadtd\">
<a>Mp3splt</a>
</td>
<td class=\"mainpagedownloadtd\">
Mp3splt-gtk
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
Mp3splt-gtk
</td>
</tr>

<!-- RPMs -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img src=\"icons/fedora.png\" /><img src=\"icons/mandriva.png\" /><br />
<div class=\"osname\">RPMs</div>
</td>
<td class=\"mainpagedownloadtd\">
<a>Mp3splt</a>
</td>
<td class=\"mainpagedownloadtd\">
Mp3splt-gtk
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
Mp3splt-gtk
</td>
</tr>

<!-- GNU/Linux -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img src=\"icons/gnu.png\" /><img src=\"icons/penguin.png\" /><br />
<div class=\"osname\">GNU/Linux</div>
</td>
<td class=\"mainpagedownloadtd\">
<a>Mp3splt</a>
</td>
<td class=\"mainpagedownloadtd\">
Mp3splt-gtk
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
Mp3splt-gtk
</td>
</tr>

<!-- FreeBSD -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img src=\"icons/freebsd.png\" /><br />
<div class=\"osname\">FreeBSD</div>
</td>
<td class=\"mainpagedownloadtd\">
<a>Mp3splt</a>
</td>
<td class=\"mainpagedownloadtd\">
Mp3splt-gtk
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
Mp3splt-gtk
</td>
</tr>

<!-- NetBSD -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img src=\"icons/netbsd.png\" /><br />
<div class=\"osname\">NetBSD</div>
</td>
<td class=\"mainpagedownloadtd\">
<a>Mp3splt</a>
</td>
<td class=\"mainpagedownloadtd\">
Mp3splt-gtk
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
Mp3splt-gtk
</td>
</tr>

<!-- OpenBSD -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img src=\"icons/openbsd.png\" /><br />
<div class=\"osname\">OpenBSD</div>
</td>
<td class=\"mainpagedownloadtd\">
<a>Mp3splt</a>
</td>
<td class=\"mainpagedownloadtd\">
Mp3splt-gtk
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
Mp3splt-gtk
</td>
</tr>

<!-- Windows -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-left:none;text-align:center\">
<img src=\"icons/winxp.png\" /><br />
<div class=\"osname\">Windows</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;\">
<a>Mp3splt</a>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;\">
Mp3splt-gtk
</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-right:none\">
Mp3splt-gtk
</td>
</tr>

</table>

<br />
<div>Mp3splt-project do not own any of the icons from this page. Please see the <a href=\"icons/icons_licenses.txt\">icons licenses</a>.</div>
<br />
";
}

begin_document("mp3splt project - download page",
	       "default.css",FALSE);

create_table_with_menu("downloads");

end_document();
?>

