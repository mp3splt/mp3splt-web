<?php

include 'menu.php';

function create_main_page()
{
  include 'download_variables.php';

  echo "
<h2  class=\"pagetitle\">Downloads</h2>
<hr />";

create_source_code_table();

create_debian_ubuntu_table();

echo "<br/><div class=\"title\">All other:</div><br />";

echo "
<table class=\"mainpagedownloadtable\">

<!-- top stuff -->
<tr>
<td>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:none;text-align:center\">
<div style=\"font-weight:bold\">Libmp3splt</div>
<!--<div style=\"font-style:italic\">${libmp3splt_version}</div>-->
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:none;text-align:center\">
<div style=\"font-weight:bold\">Mp3splt</div>
<!--<div style=\"font-style:italic\">${mp3splt_version}</div>-->
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:none;text-align:center;border-right:none\">
<div style=\"font-weight:bold\">Mp3splt-gtk</div>
<!--<div style=\"font-style:italic\">${mp3splt_gtk_version}</div>-->
</td>
</tr>";

echo "
<!-- openSUSE -->
<tr id=\"opensuse\">
<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/opensuse.png\" /><br />
<div class=\"osname\">openSUSE</div>
</td>

<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;\">
<a href=\"http://packman.links2linux.org/package/libmp3splt\">
PackMan</a><br />
(links2linux.org)
</td>

<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;\">
<a href=\"http://packman.links2linux.org/package/mp3splt\">
PackMan</a><br />
(links2linux.org)
</td>

<td class=\"mainpagedownloadtd\" style=\"border-right:none;border-top:solid;border-top-width:1pt;\">
<a href=\"http://packman.links2linux.org/package/mp3splt-gtk\">
PackMan</a><br />
(links2linux.org)
</td>
</tr>";


echo "
<!-- Slackware -->
<tr id=\"slackware\">
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/slackware.png\" /><br />
<div class=\"osname\">Slackware</div>
</td>

<td class=\"mainpagedownloadtd\">
<a href=\"http://slackbuilds.org/result/?search=libmp3splt&sv=\">
SlackBuild page</a><br />
(slackbuilds.org)
</td>

<td class=\"mainpagedownloadtd\">
<a href=\"http://slackbuilds.org/result/?search=mp3splt&sv=\">
SlackBuild page</a><br />
(slackbuilds.org)
</td>

<td class=\"mainpagedownloadtd\" style=\"border-right:none;\">
<a href=\"http://slackbuilds.org/result/?search=mp3splt-gtk&sv=\">
SlackBuild page</a><br />
(slackbuilds.org)
</td>
</tr>";

echo "<!-- RPMs -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/fedora.png\" /><br />
<div class=\"osname\">Fedora/Red Hat</div>
</td>

<td class=\"mainpagedownloadtd\">
<a href=\"http://atrpms.net/name/libmp3splt\">atrpms page</a><br />
(atrpms.net)
</td>

<td class=\"mainpagedownloadtd\">
<a href=\"http://atrpms.net/name/mp3splt\">atrpms page</a><br />
(atrpms.net)
</td>

<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
<a href=\"http://atrpms.net/name/mp3splt-gtk\">atrpms page</a><br />
(atrpms.net)
</td>

</tr>";

echo "<!-- CRUX -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/crux.png\" /><br />
<div class=\"osname\">CRUX</div>
</td>

<td class=\"mainpagedownloadtd\" style=\"\">
<a href=\"http://crux.nu/portdb/?a=search&q=libmp3splt\">Crux port</a><br />
(crux.nu)
</td>

<td class=\"mainpagedownloadtd\">
<a href=\"http://crux.nu/portdb/?a=search&q=mp3splt\">Crux port</a><br />
(crux.nu)
</td>

<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
</td>

</tr>";

echo "<!-- Mac OS X -->
<tr id=\"macosx\">
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-left:none;text-align:center\" >
<img alt=\"\" src=\"icons/mac_os_x.png\" /><br />
<div class=\"osname\">Mac OS X</div>
</td>

<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;\" >
<a href=\"https://github.com/mxcl/homebrew/blob/master/Library/Formula/libmp3splt.rb\">
 Homebrew</a><br />(github)
<br />

<a href=\"http://trac.macports.org/browser/trunk/dports/audio/libmp3splt/Portfile\">
 Mac Portfile</a><br />(macports.org)
<br />

<a href=\"http://pdb.finkproject.org/pdb/package.php/libmp3splt\">
 Fink package</a><br />(finkproject.org)
<br />
</td>

<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;\" >
<a href=\"https://github.com/mxcl/homebrew/blob/master/Library/Formula/mp3splt.rb\">
 Homebrew</a><br />(github)
 <br />

<a href=\"http://trac.macports.org/browser/trunk/dports/audio/mp3splt/Portfile\">
 Mac Portfile</a><br />(macports.org)
<br />

<a href=\"http://pdb.finkproject.org/pdb/package.php/mp3splt\">
 Fink package</a><br />(finkproject.org)
<br />

</td>

<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-right:none\" >
<br /><br />

<a href=\"http://trac.macports.org/browser/trunk/dports/audio/mp3splt-gtk/Portfile\">
 Mac Portfile</a><br />(macports.org)
<br />

<a href=\"http://pdb.finkproject.org/pdb/package.php/mp3splt-gtk\">
 Fink package</a><br />(finkproject.org)
<br />

</td>
</tr>

<!-- Windows -->
<tr id=\"windows\">
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-left:none;text-align:center;\">
<img alt=\"\" src=\"icons/winxp.png\" /><br />
<div class=\"osname\">Windows</div>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;\">

</td>
<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;\">
<a href=\"${download_url}mp3splt_${mp3splt_version}_i386.exe${download_suffix}\">
installer.exe</a><br />
<a href=\"${download_url}mp3splt_${mp3splt_version}_i386.zip${download_suffix}\">
zip archive</a>
</td>

<td class=\"mainpagedownloadtd\" style=\"border-bottom:none;border-right:none;\">
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}_i386.exe${download_suffix}\">
installer.exe</a><br />
<a href=\"${download_url}mp3splt-gtk_${mp3splt_gtk_version}_i386.zip${download_suffix}\">
zip archive</a><br />
<hr style=\"width:50%;border:dashed;border-width:1px\" />
<a href=\"http://portableapps.com/apps/music_video/mp3splt-portable\">Portable version</a>
<br />
(portableapps.com)
<hr style=\"width:50%;border:dashed;border-width:1px\" />
<a href=\"http://www.winpenpack.com/main/download.php?view.1254\">Portable version</a>
<br />
(winPenPack.com)
</td>

</tr>";

echo "<!-- Maemo -->
<tr>
<td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center\">
<img alt=\"\" src=\"icons/maemo.png\" /><br />
<div class=\"osname\">Maemo</div>
</td>

<td class=\"mainpagedownloadtd\" style=\"\">
</td>

<td class=\"mainpagedownloadtd\">
<a href=\"http://maemo.org/downloads/product/OS2008/mp3splt\">Maemo package</a><br />
(maemo.org)
</td>

<td class=\"mainpagedownloadtd\" style=\"border-right:none\">
</td>

</tr>";


echo "</table>

<br />
";

echo "<div class=\"indentdiv\">Older downloads can be found on the <a
 href=\"https://sourceforge.net/projects/mp3splt/files\">sourceforge downloads page</a>.</div>";

}

function create_source_code_table()
{
  include 'download_variables.php';

  echo "<div class=\"title\">Source code:</div><br />";

echo "
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

echo "
<tr id=\"source_code\">
<td class=\"mainpagedownloadtd\"
style=\"border-top:solid;border-top-width:1pt;border-left:none;text-align:center;border-bottom:none\">
<img alt=\"\" src=\"icons/keyboard.png\" /><br />
<span style=\"font-weight:bold\">Source code</span>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-top:solid;border-top-width:1pt;border-bottom:none\">
<a class=\"source\" href=\"${download_url}libmp3splt-${libmp3splt_version}.tar.gz${download_suffix}\">.tar.gz</a>
</td>
<td class=\"mainpagedownloadtd\"
style=\"border-top:solid;border-top-width:1pt;border-bottom:none\">
<a class=\"source\" href=\"${download_url}mp3splt-${mp3splt_version}.tar.gz${download_suffix}\">
.tar.gz</a>
</td>
<td class=\"mainpagedownloadtd\" style=\"border-right:none;border-top:solid;border-top-width:1pt;border-bottom:none\">
<a class=\"source\" href=\"${download_url}mp3splt-gtk-${mp3splt_gtk_version}.tar.gz${download_suffix}\">
.tar.gz</a>
</td>
</tr>";

echo "</table><br />";
}

function create_debian_ubuntu_table()
{
  include 'download_variables.php';

  echo "<div class=\"title\">Debian &amp; Ubuntu:</div><br />";

  echo "<table class=\"mainpagedownloadtable\">";

  echo "<tr id=\"debian\">
    <td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center;border-top:none\">
    <img alt=\"\" src=\"icons/debian.png\" />
    <div class=\"osname\">Debian</div>
    </td>

    <td class=\"mainpagedownloadtd\" style=\"border-right:none;border-top:none\">";

  foreach ($debian_versions as $debian_version => $extra)
  {
    echo "<a href=\"debian_downloads.php?version=$debian_version\">$debian_version</a> $extra <br/>";
  }

  echo "
    </td>

    </tr>";

  echo "
    <tr id=\"ubuntu\">
    <td class=\"mainpagedownloadtd\" style=\"border-left:none;text-align:center;border-bottom:none\">
    <img alt=\"\" src=\"icons/ubuntu.png\" />
    <div class=\"osname\">Ubuntu</div>
    </td>

    <td class=\"mainpagedownloadtd\" style=\"border-right:none;border-bottom:none\">";

    echo "<a href=\"ppa_downloads.php?version=Precise\">Precise</a> (12.04 LTS) <br/>";

  foreach ($ubuntu_versions as $ubuntu_version => $extra)
  {
    echo "<a href=\"debian_downloads.php?version=$ubuntu_version&amp;ubuntu=true\">$ubuntu_version</a> $extra <br/>";
  }

  echo "</td></tr></table>";
}

begin_document("mp3splt project - download page", "default.css",FALSE);

create_table_with_menu("downloads");

end_document();

?>

