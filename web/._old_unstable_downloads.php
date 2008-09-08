<?php

include 'menu.php';

function create_main_page()
{
  //download urls
  $download_url="http://prdownloads.sourceforge.net/mp3splt/";
  //$download_suffix="?download";
  $download_suffix="";
  //versions
  $libmp3splt_version="0.4_rc1";
  $mp3splt_version="2.2_rc1";
  $mp3splt_gtk_version="0.4_rc1";
  
  //freebsd versions
  $fbsd_libmp3splt_version=str_replace("_",".",$libmp3splt_version);
  $fbsd_libmp3splt_version=str_replace("rc","r",$fbsd_libmp3splt_version);
  $fbsd_mp3splt_version=str_replace("_",".",$mp3splt_version);
  $fbsd_mp3splt_version=str_replace("rc","r",$fbsd_mp3splt_version);
  $fbsd_mp3splt_gtk_version=str_replace("_",".",$mp3splt_gtk_version);
  $fbsd_mp3splt_gtk_version=str_replace("rc","r",$fbsd_mp3splt_gtk_version);
  
  echo "
<h2  class=\"pagetitle\">Unstable downloads (testing)</h2>
<hr />

<!-- links to downloads on this same page
<a href=\"#source_code\"><img border=0 src=\"icons/thumb/keyboard_thumb.png\" />Source code</a>,
<a href=\"#debian\"><img border=0 src=\"icons/thumb/debian_thumb.png\" />Debian</a>,
<a href=\"#ubuntu\"><img border=0 src=\"icons/thumb/ubuntu_thumb.png\" />Ubuntu</a>,
<a href=\"#arch\"><img border=0 src=\"icons/thumb/arch_thumb.png\" />Arch Linux</a>,
<a href=\"#slackware\"><img border=0 src=\"icons/thumb/slackware_thumb.png\" />Slackware</a>,
<a href=\"#gentoo\"><img border=0 src=\"icons/thumb/gentoo_thumb.png\" />Gentoo</a>,
<a href=\"#rpm\"><img border=0 src=\"icons/thumb/fedora_thumb.png\" />RPMs (Fedora, Mandriva, Suse)</a>,
<a href=\"#gnu_linux\"><img border=0 src=\"icons/thumb/gnu_thumb.png\"
/><img border=0 src=\"icons/thumb/penguin_thumb.png\" />GNU/Linux (static and dynamic)</a>,
<a href=\"#openbsd\"><img border=0 src=\"icons/thumb/openbsd_thumb.png\" />OpenBSD</a>,
<a href=\"#netbsd\"><img border=0 src=\"icons/thumb/netbsd_thumb.png\" />NetBSD</a>,
<a href=\"#freebsd\"><img border=0 src=\"icons/thumb/freebsd_thumb.png\" />FreeBSD</a>,
<a href=\"#macosx\"><img border=0 src=\"icons/thumb/mac_os_x_thumb.png\" />Mac OS X</a>,
<a href=\"#windows\"><img border=0 src=\"icons/thumb/winxp_thumb.png\" />Windows</a>
<hr /> -->

<div>Those releases are unstable.<br />
They are here because the latest version does not work any more with freedb, and for testing
purposes.<br />
You may have problems using those releases (such as crashes
- segmentation faults), becase they haven't been tested.<br />
Also, many of the packages that you find here have not been tested; feel free to
report if a package works or not works.<br />
<span style=\"color:red\">Note : GNU/Linux static packages are broken.</span><br />
Mac OS X packages are not available due to lack of time.<br />
Please report the bugs that you find.</div>

<table class=\"mainpagedownloadtable\">

<!-- top stuff -->
<tr>
<td>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:none;text-align:center\">
<div style=\"font-weight:bold\">Libmp3splt</div>
<div style=\"font-style:italic\">${libmp3splt_version}</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:none;text-align:center\">
<div style=\"font-weight:bold\">Mp3splt</div>
<div style=\"font-style:italic\">${mp3splt_version}</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:none;text-align:center;border-right:none\">
<div style=\"font-weight:bold\">Mp3splt-gtk</div>
<div style=\"font-style:italic\">${mp3splt_gtk_version}</div>
</td>
</tr>

<!-- Source code -->
<tr id=\"source_code\">
<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/keyboard.png\" /><br />
<span style=\"font-weight:bold\">Source code</span>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;\">
<a class=\"source\" href=\"${download_url}libmp3splt-${libmp3splt_version}.tar.gz${download_suffix}\">.tar.gz</a>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;\">
<a class=\"source\" href=\"${download_url}mp3splt-${mp3splt_version}.tar.gz${download_suffix}\">
.tar.gz</a>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none;border-top:solid;border-top-width:1pt;\">
<a class=\"source\" href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}.tar.gz${download_suffix}\">
.tar.gz</a>
</td>
</tr>

<!-- Debian -->
<tr id=\"debian\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center;border-top:solid;border-top-width:1pt;\">
<img alt=\"\" src=\"icons/debian.png\" />
<div class=\"osname\">Debian</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;\">

<!-- i386 -->
<a href=\"${download_url}libmp3splt_${libmp3splt_version}.sarge_i386.deb${download_suffix}\">
sarge_i386.deb</a><br />
<a href=\"${download_url}libmp3splt_${libmp3splt_version}.etch_i386.deb${download_suffix}\">
etch_i386.deb</a><br />
<a href=\"${download_url}libmp3splt_${libmp3splt_version}.sid_i386.deb${download_suffix}\">
sid_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}libmp3splt_${libmp3splt_version}.etch_amd64.deb${download_suffix}\">
etch_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}libmp3splt_${libmp3splt_version}.sid_amd64.deb${download_suffix}\">
sid_amd64.deb</a><br />

</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;\">

<!-- i386 -->
<a href=\"${download_url}mp3splt_${mp3splt_version}.sarge_i386.deb${download_suffix}\">
sarge_i386.deb</a><br />
<a href=\"${download_url}mp3splt_${mp3splt_version}.etch_i386.deb${download_suffix}\">
etch_i386.deb</a><br />
<a href=\"${download_url}mp3splt_${mp3splt_version}.sid_i386.deb${download_suffix}\">
sid_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}mp3splt_${mp3splt_version}.etch_amd64.deb${download_suffix}\">
etch_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt_${mp3splt_version}.sid_amd64.deb${download_suffix}\">
sid_amd64.deb</a><br />

</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none;border-top:solid;border-top-width:1pt;\">

<!-- i386 -->
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.sarge_i386.deb${download_suffix}\">
sarge_i386.deb</a><br />
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.etch_i386.deb${download_suffix}\">
etch_i386.deb</a><br />
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.sid_i386.deb${download_suffix}\">
sid_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.etch_amd64.deb${download_suffix}\">
etch_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.sid_amd64.deb${download_suffix}\">
sid_amd64.deb</a><br />

</td>
</tr>

<!-- Ubuntu -->
<tr id=\"ubuntu\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center;\">
<img alt=\"\" src=\"icons/ubuntu.png\" />
<div class=\"osname\">Ubuntu</div>
</td>
<td class=\"mainpagedownloadtd\">

<!-- i386 -->
<a href=\"${download_url}libmp3splt_${libmp3splt_version}.dapper_i386.deb${download_suffix}\">
dapper_i386.deb</a><br />
<a href=\"${download_url}libmp3splt_${libmp3splt_version}.edgy_i386.deb${download_suffix}\">
edgy_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}libmp3splt_${libmp3splt_version}.dapper_amd64.deb${download_suffix}\">
dapper_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}libmp3splt_${libmp3splt_version}.edgy_amd64.deb${download_suffix}\">
edgy_amd64.deb</a><br />

</td>
<td class=\"mainpagedownloadtd\">

<!-- i386 -->
<a href=\"${download_url}mp3splt_${mp3splt_version}.dapper_i386.deb${download_suffix}\">
dapper_i386.deb</a><br />
<a href=\"${download_url}mp3splt_${mp3splt_version}.edgy_i386.deb${download_suffix}\">
edgy_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}mp3splt_${mp3splt_version}.dapper_amd64.deb${download_suffix}\">
dapper_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt_${mp3splt_version}.edgy_amd64.deb${download_suffix}\">
edgy_amd64.deb</a><br />

</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none;\">

<!-- i386 -->
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.dapper_i386.deb${download_suffix}\">
dapper_i386.deb</a><br />
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.edgy_i386.deb${download_suffix}\">
edgy_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.dapper_amd64.deb${download_suffix}\">
dapper_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.edgy_amd64.deb${download_suffix}\">
edgy_amd64.deb</a><br />

</td>
</tr>

<!-- Archlinux -->
<tr id=\"arch\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/arch.png\" /><br />
<div class=\"osname\">Arch Linux</div>
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"${download_url}libmp3splt-${libmp3splt_version}-1_i686.pkg.tar.gz${download_suffix}\">
i686.pkg.tar.gz</a><br />
<a class=\"amd64\" href=\"${download_url}libmp3splt-${libmp3splt_version}-1_x86_64.pkg.tar.gz${download_suffix}\">
x86_64.pkg.tar.gz</a><br />
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"${download_url}mp3splt-${mp3splt_version}-1_i686.pkg.tar.gz${download_suffix}\">
i686.pkg.tar.gz</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-${mp3splt_version}-1_x86_64.pkg.tar.gz${download_suffix}\">
x86_64.pkg.tar.gz</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}-1_i686.pkg.tar.gz${download_suffix}\">
i686.pkg.tar.gz</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}-1_x86_64.pkg.tar.gz${download_suffix}\">
x86_64.pkg.tar.gz</a><br />
</td>
</tr>

<!-- Slackware -->
<tr id=\"slackware\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/slackware.png\" /><br />
<div class=\"osname\">Slackware</div>
</td>

<td class=\"mainpagedownloadtd\">
<a href=\"${download_url}libmp3splt-${libmp3splt_version}-i386.tgz${download_suffix}\">
i386.tgz</a><br />
<a class=\"amd64\" href=\"${download_url}libmp3splt-${libmp3splt_version}-x86_64.tgz${download_suffix}\">
x86_64.tgz</a><br />
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"${download_url}mp3splt-${mp3splt_version}-i386.tgz${download_suffix}\">
i386.tgz</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-${mp3splt_version}-x86_64.tgz${download_suffix}\">
x86_64.tgz</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}-i386.tgz${download_suffix}\">
i386.tgz</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}-x86_64.tgz${download_suffix}\">
x86_64.tgz</a><br />
</td>
</tr>

<!-- Gentoo -->
<tr id=\"gentoo\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/gentoo.png\" /><br />
<div class=\"osname\">Gentoo</div>
</td>
<td class=\"mainpagedownloadtd\">
<a class=\"source\" href=\"${download_url}libmp3splt-${libmp3splt_version}_ebuild.tar.gz${download_suffix}\">
ebuild.tar.gz</a><br />
</td>
<td class=\"mainpagedownloadtd\">
<a class=\"source\" href=\"${download_url}mp3splt-${mp3splt_version}_ebuild.tar.gz${download_suffix}\">
ebuild.tar.gz</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a class=\"source\" href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}_ebuild.tar.gz${download_suffix}\">
ebuild.tar.gz</a><br />
</td>
</tr>

<!-- RPMs -->
<tr id=\"rpm\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/fedora.png\" /><img alt=\"\" src=\"icons/mandriva.png\" /><br />
<img style=\"margin-top:4pt\" alt=\"\" src=\"icons/opensuse.png\" />
<div class=\"osname\">RPMs</div>
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"${download_url}libmp3splt-${libmp3splt_version}-1.i386.rpm${download_suffix}\">
i386.rpm</a><br />
<a class=\"amd64\" href=\"${download_url}libmp3splt-${libmp3splt_version}-1.x86_64.rpm${download_suffix}\">
x86_64.rpm</a><br />
<a class=\"source\" href=\"${download_url}libmp3splt-${libmp3splt_version}-1.src.rpm${download_suffix}\">
src.rpm</a><br />
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"${download_url}mp3splt-${mp3splt_version}-1.i386.rpm${download_suffix}\">
i386.rpm</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-${mp3splt_version}-1.x86_64.rpm${download_suffix}\">
x86_64.rpm</a><br />
<a class=\"source\" href=\"${download_url}mp3splt-${mp3splt_version}-1.src.rpm${download_suffix}\">
src.rpm</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}-1.i386.rpm${download_suffix}\">
i386.rpm</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}-1.x86_64.rpm${download_suffix}\">
x86_64.rpm</a><br />
<a class=\"source\" href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}-1.src.rpm${download_suffix}\">
src.rpm</a><br />
</td>
</tr>

<!-- GNU/Linux -->
<tr id=\"gnu_linux\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/gnu.png\" /><img alt=\"\" src=\"icons/penguin.png\" /><br />
<div class=\"osname\">GNU/Linux</div>
</td>
<td class=\"mainpagedownloadtd\">

<!-- dynamic -->
<a href=\"${download_url}libmp3splt-${libmp3splt_version}_dynamic_i386.tar.gz${download_suffix}\">
dynamic_i386.tar.gz</a><br />
<a class=\"amd64\" href=\"${download_url}libmp3splt-${libmp3splt_version}_dynamic_x86_64.tar.gz${download_suffix}\">
dynamic_x86_64.tar.gz</a><br />
<hr size=\"1\"/>

<!-- static -->
<a href=\"${download_url}libmp3splt-${libmp3splt_version}_static_i386.tar.gz${download_suffix}\">
static_i386.tar.gz</a><br />
<a class=\"amd64\" href=\"${download_url}libmp3splt-${libmp3splt_version}_static_x86_64.tar.gz${download_suffix}\">
static_x86_64.tar.gz</a><br />
</td>
<td class=\"mainpagedownloadtd\">

<!-- dynamic -->
<a href=\"${download_url}mp3splt-${mp3splt_version}_dynamic_i386.tar.gz${download_suffix}\">
dynamic_i386.tar.gz</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-${mp3splt_version}_dynamic_x86_64.tar.gz${download_suffix}\">
dynamic_x86_64.tar.gz</a><br />
<hr size=\"1\"/>

<!-- static -->
<a href=\"${download_url}mp3splt-${mp3splt_version}_static_i386.tar.gz${download_suffix}\">
static_i386.tar.gz</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-${mp3splt_version}_static_x86_64.tar.gz${download_suffix}\">
static_x86_64.tar.gz</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">

<!-- dynamic -->
<a href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}_dynamic_i386.tar.gz${download_suffix}\">
dynamic_i386.tar.gz</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}_dynamic_x86_64.tar.gz${download_suffix}\">
dynamic_x86_64.tar.gz</a><br />
<hr size=\"1\"/>

<!-- static -->
<a href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}_static_i386.tar.gz${download_suffix}\">
static_i386.tar.gz</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}_static_x86_64.tar.gz${download_suffix}\">
static_x86_64.tar.gz</a><br />
</td>
</tr>

<!-- OpenBSD -->
<tr id=\"openbsd\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center;border-top:solid;border-top-width:1pt;\">
<img alt=\"\" src=\"icons/openbsd.png\" /><br />
<div class=\"osname\">OpenBSD</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;\">
<a href=\"${download_url}libmp3splt_obsd_i386-${libmp3splt_version}.tgz${download_suffix}\">
i386.tgz</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;\">
<a href=\"${download_url}mp3splt_obsd_i386-${mp3splt_version}.tgz${download_suffix}\">
i386.tgz</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none;border-top:solid;border-top-width:1pt;\">
<a href=\"${download_url}mp3splt-gtk_obsd_i386-${mp3splt_gtk_version}.tgz${download_suffix}\">
i386.tgz</a><br />
</td>
</tr>

<!-- NetBSD -->
<tr id=\"netbsd\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/netbsd.png\" /><br />
<div class=\"osname\">NetBSD</div>
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"${download_url}libmp3splt_nbsd_i386-${libmp3splt_version}.tgz${download_suffix}\">
i386.tgz</a><br />
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"${download_url}mp3splt_nbsd_i386-${mp3splt_version}.tgz${download_suffix}\">
i386.tgz</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a href=\"${download_url}mp3splt-gtk_nbsd_i386-${mp3splt_gtk_version}.tgz${download_suffix}\">
i386.tgz</a><br />
</td>
</tr>

<!-- FreeBSD -->
<tr id=\"freebsd\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/freebsd.png\" /><br />
<div class=\"osname\">FreeBSD</div>
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"${download_url}libmp3splt_fbsd_i386-${fbsd_libmp3splt_version}.tbz${download_suffix}\">
i386.tbz</a><br />
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"${download_url}mp3splt_fbsd_i386-${fbsd_mp3splt_version}.tbz${download_suffix}\">
i386.tbz</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a href=\"${download_url}mp3splt-gtk_fbsd_i386-${fbsd_mp3splt_gtk_version}.tbz${download_suffix}\">
i386.tbz</a><br />
</td>
</tr>

<!-- Nexenta -->
<tr id=\"nexenta\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<div class=\"osname\">Nexenta<br />
GNU/OpenSolaris</div>
</td>
<td class=\"mainpagedownloadtd\">
<a
href=\"${download_url}libmp3splt_${libmp3splt_version}_solaris-i386.deb${download_suffix}\">i386.deb</a><br />
</td>
<td class=\"mainpagedownloadtd\">
<a
href=\"${download_url}mp3splt_${mp3splt_version}_solaris-i386.deb${download_suffix}\">i386.deb</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a
href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}_solaris-i386.deb${download_suffix}\">i386.deb</a><br />
</td>
</tr>

<!-- Mac OS X -->
<tr id=\"macosx\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/mac_os_x.png\" /><br />
<div class=\"osname\">Mac OS X</div>
</td>
<td class=\"mainpagedownloadtd\">

</td>
<td class=\"mainpagedownloadtd\">
<a href=\"http://fink.sourceforge.net/pdb/package.php/mp3splt\">
 Fink package</a><br />(older version)
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a href=\"http://alex.primafila.net/albumextractorx/\">AlbumExtractorX</a><br />
(other program)
</td>
</tr>

<!-- Windows -->
<tr id=\"windows\">
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-left:none;text-align:center;border-top:solid;border-top-width:1pt;\">
<img alt=\"\" src=\"icons/winxp.png\" /><br />
<div class=\"osname\">Windows</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-top:solid;border-top-width:1pt;\">

</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-top:solid;border-top-width:1pt;\">
<a href=\"${download_url}mp3splt_${mp3splt_version}_i386.exe${download_suffix}\">
installer.exe</a><br />
</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-right:none;border-top:solid;border-top-width:1pt;\">
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}_i386.exe${download_suffix}\">
installer.exe</a><br />
</td>
</tr>

</table>

<br />
";
}

begin_document("mp3splt project - download page",
	       "default.css",FALSE);

create_table_with_menu("downloads");

end_document();
?>
