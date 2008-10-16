<?php

include 'menu.php';

function create_main_page()
{
  //download urls
  $download_url="http://prdownloads.sourceforge.net/mp3splt/";
  //$download_suffix="?download";
  $download_suffix="";
  //versions
  $libmp3splt_version="0.5.2";
  $mp3splt_version="2.2.1";
  $mp3splt_gtk_version="0.5.2";
  
  //freebsd versions
  $fbsd_libmp3splt_version=str_replace("_",".",$libmp3splt_version);
  $fbsd_libmp3splt_version=str_replace("rc","r",$fbsd_libmp3splt_version);
  $fbsd_mp3splt_version=str_replace("_",".",$mp3splt_version);
  $fbsd_mp3splt_version=str_replace("rc","r",$fbsd_mp3splt_version);
  $fbsd_mp3splt_gtk_version=str_replace("_",".",$mp3splt_gtk_version);
  $fbsd_mp3splt_gtk_version=str_replace("rc","r",$fbsd_mp3splt_gtk_version);
  
  echo "
<h2  class=\"pagetitle\">Downloads</h2>
<hr />

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
</tr>";

echo "<!-- Source code -->
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
</tr>";

echo "<!-- Slackware -->
<tr id=\"slackware\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/slackware.png\" /><br />
<div class=\"osname\">Slackware</div>
</td>

<td class=\"mainpagedownloadtd\">
<a href=\"http://slackbuilds.org/repository/12.1/libraries/libmp3splt/\">
SlackBuild page</a><br />
(slackbuilds.org)
</td>
<td class=\"mainpagedownloadtd\">
<a href=\"http://slackbuilds.org/repository/12.1/audio/mp3splt/\">
SlackBuild page</a><br />
(slackbuilds.org)
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a href=\"http://slackbuilds.org/repository/12.1/audio/mp3splt-gtk/\">
SlackBuild page</a><br />
(slackbuilds.org)
</td>
</tr>";

/*echo "<!-- Debian -->
<tr id=\"debian\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center;border-top:solid;border-top-width:1pt;\">
<img alt=\"\" src=\"icons/debian.png\" />
<div class=\"osname\">Debian</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;\">

<!-- i386 -->
<a href=\"${download_url}libmp3splt_${libmp3splt_version}.lenny_i386.deb${download_suffix}\">
lenny_i386.deb</a><br />
<a href=\"${download_url}libmp3splt_${libmp3splt_version}.unstable_i386.deb${download_suffix}\">
unstable_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}libmp3splt_${libmp3splt_version}.lenny_amd64.deb${download_suffix}\">
lenny_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}libmp3splt_${libmp3splt_version}.unstable_amd64.deb${download_suffix}\">
unstable_amd64.deb</a><br />

</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;\">

<!-- i386 -->
<a href=\"${download_url}mp3splt_${mp3splt_version}.lenny_i386.deb${download_suffix}\">
lenny_i386.deb</a><br />
<a href=\"${download_url}mp3splt_${mp3splt_version}.unstable_i386.deb${download_suffix}\">
unstable_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}mp3splt_${mp3splt_version}.lenny_amd64.deb${download_suffix}\">
lenny_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt_${mp3splt_version}.unstable_amd64.deb${download_suffix}\">
unstable_amd64.deb</a><br />

</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none;border-top:solid;border-top-width:1pt;\">

<!-- i386 -->
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.lenny_i386.deb${download_suffix}\">
lenny_i386.deb</a><br />
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.unstable_i386.deb${download_suffix}\">
unstable_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.lenny_amd64.deb${download_suffix}\">
lenny_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.unstable_amd64.deb${download_suffix}\">
unstable_amd64.deb</a><br />

</td>
</tr>";

echo "<!-- Ubuntu -->
<tr id=\"ubuntu\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center;\">
<img alt=\"\" src=\"icons/ubuntu.png\" />
<div class=\"osname\">Ubuntu</div>
</td>
<td class=\"mainpagedownloadtd\">

<!-- i386 -->
<a href=\"${download_url}libmp3splt_${libmp3splt_version}.gutsy_i386.deb${download_suffix}\">
gutsy_i386.deb</a><br />
<a href=\"${download_url}libmp3splt_${libmp3splt_version}.hardy_i386.deb${download_suffix}\">
hardy_i386.deb</a><br />
<a href=\"${download_url}libmp3splt_${libmp3splt_version}.intrepid_i386.deb${download_suffix}\">
intrepid_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}libmp3splt_${libmp3splt_version}.gutsy_amd64.deb${download_suffix}\">
gutsy_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}libmp3splt_${libmp3splt_version}.hardy_amd64.deb${download_suffix}\">
hardy_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}libmp3splt_${libmp3splt_version}.intrepid_amd64.deb${download_suffix}\">
intrepid_amd64.deb</a><br />

</td>
<td class=\"mainpagedownloadtd\">

<!-- i386 -->
<a href=\"${download_url}mp3splt_${mp3splt_version}.gutsy_i386.deb${download_suffix}\">
gutsy_i386.deb</a><br />
<a href=\"${download_url}mp3splt_${mp3splt_version}.hardy_i386.deb${download_suffix}\">
hardy_i386.deb</a><br />
<a href=\"${download_url}mp3splt_${mp3splt_version}.intrepid_i386.deb${download_suffix}\">
intrepid_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}mp3splt_${mp3splt_version}.gutsy_amd64.deb${download_suffix}\">
gutsy_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt_${mp3splt_version}.hardy_amd64.deb${download_suffix}\">
hardy_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt_${mp3splt_version}.intrepid_amd64.deb${download_suffix}\">
intrepid_amd64.deb</a><br />

</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none;\">

<!-- i386 -->
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.gutsy_i386.deb${download_suffix}\">
gutsy_i386.deb</a><br />
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.hardy_i386.deb${download_suffix}\">
hardy_i386.deb</a><br />
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.intrepid_i386.deb${download_suffix}\">
intrepid_i386.deb</a><br />

<!-- amd64 -->
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.gutsy_amd64.deb${download_suffix}\">
gutsy_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.hardy_amd64.deb${download_suffix}\">
hardy_amd64.deb</a><br />
<a class=\"amd64\" href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}.intrepid_amd64.deb${download_suffix}\">
intrepid_amd64.deb</a><br /> -->

</td>
</tr>";*/

echo "<!-- Mac OS X -->
<tr id=\"macosx\">
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-top:solid;border-top-width:1pt;border-left:none;text-align:center\" >
<img alt=\"\" src=\"icons/mac_os_x.png\" /><br />
<div class=\"osname\">Mac OS X</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-top:solid;border-top-width:1pt;\" >

</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-top:solid;border-top-width:1pt;\" >
<a href=\"http://fink.sourceforge.net/pdb/package.php/mp3splt\">
 Fink package</a><br />(older version)
</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-top:solid;border-top-width:1pt;border-right:none\" >
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
</tr>";

echo "
</table>

<br />
";

echo "<div class=\"indentdiv\">Older downloads can be found on the <a href=\"https://sourceforge.net/project/showfiles.php?group_id=55130\">sourceforge downloads page</a>.";

}

begin_document("mp3splt project - download page",
	       "default.css",FALSE);

create_table_with_menu("downloads");

end_document();
?>
