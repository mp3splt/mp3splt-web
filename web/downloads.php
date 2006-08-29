<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2  class=\"pagetitle\">Downloads</h2>
<hr />
<div>For older downloads, see the <a href=\"downloads_archive.php\">downloads archive</a>.</div>
<div>For installation issues, please read <a href=\"documentation.php\">the documentation</a>.</div>
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
<img alt=\"\" src=\"icons/keyboard.png\" /><br />
<span style=\"font-weight:bold\">Source code</span>
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"http://prdownloads.sourceforge.net/mp3splt/libmp3splt-0.3.1.tar.gz?download\">.tar.gz</a>
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-2.1c-src.tar.gz?download\">
.tar.gz</a>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk-0.3.1.tar.gz?download\">
.tar.gz</a>
</td>
</tr>

<!-- Debian -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/debian.png\" /><img alt=\"\" src=\"icons/ubuntu.png\" />
<div class=\"osname\">Debian-based</div>
</td>
<td class=\"mainpagedownloadtd\">
Debian testing,<br /> Ubuntu dapper :<br />
<a href=\"http://prdownloads.sourceforge.net/mp3splt/libmp3splt_0.3.1_i386.deb?download\">
i386.deb</a>
</td>
<td class=\"mainpagedownloadtd\">
Debian testing,<br /> Ubuntu dapper :<br />
<a
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt_2.1-1_i386.deb?download\">
i386.deb</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
Debian testing,<br /> Ubuntu dapper :<br />
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_0.3.1_i386.deb?download\">
i386.deb</a>
</td>
</tr>

<!-- Slackware -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/slackware.png\" /><br />
<div class=\"osname\">Slackware</div>
</td>

<td class=\"mainpagedownloadtd\">
</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">

</td>
</tr>

<!-- Gentoo -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/gentoo.png\" /><br />
<div class=\"osname\">Gentoo</div>
</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">

</td>
</tr>

<!-- RPMs -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/fedora.png\" /><img alt=\"\" src=\"icons/mandriva.png\" /><br />
<img style=\"margin-top:4pt\" alt=\"\" src=\"icons/opensuse.png\" />
<div class=\"osname\">RPMs</div>
</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\">
<a
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-2.1-1.i386.rpm?download\">
i386.rpm</a>
<br />
<a
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-2.1-1.src.rpm?download\"
>i386-src.rpm</a>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">

</td>
</tr>

<!-- GNU/Linux -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/gnu.png\" /><img alt=\"\" src=\"icons/penguin.png\" /><br />
<div class=\"osname\">GNU/Linux</div>
</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\">
<a
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-2.1-bin-i586.tar.gz?download\">
i586.tar.gz</a>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">

</td>
</tr>

<!--
FreeBSD
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/freebsd.png\" /><br />
<div class=\"osname\">FreeBSD</div>
</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">

</td>
</tr>

NetBSD
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/netbsd.png\" /><br />
<div class=\"osname\">NetBSD</div>
</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">

</td>
</tr>

OpenBSD
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/openbsd.png\" /><br />
<div class=\"osname\">OpenBSD</div>
</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">

</td>
</tr>
-->

<!-- Mac OS X -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/mac_os_x.png\" /><br />
<div class=\"osname\">Mac OS X</div>
</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\">
<a href=\"http://fink.sourceforge.net/pdb/package.php/mp3splt\">
 Fink package</a>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a
  href=\"http://alex.primafila.net/albumextractorx/\">AlbumExtractorX</a><br />
mp3splt-gtk compiles
</td>
</tr>

<!-- Windows -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/winxp.png\" /><br />
<div class=\"osname\">Windows</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;\">

</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;\">
<a
 href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-2.1-win32.zip?download\">
win32.zip</a>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-right:none\">
<a	
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_0.3.1.exe?download\">
installer.exe</a>
</td>
</tr>

</table>

<br />
<div style=\"font-size:80%\">Mp3splt-project do not own any of the logo icons of this page. Please see the <a href=\"icons/icons_licenses.txt\">icons licenses</a>.</div>
";
}

begin_document("mp3splt project - download page",
	       "default.css",FALSE);

create_table_with_menu("downloads");

end_document();
?>
