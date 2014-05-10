<?php

include 'menu.php';

$os_version=$_GET['version'];
$os_version_lower = strtolower($os_version);

function create_main_page()
{
  include 'download_variables.php';

  global $os_version, $os_version_lower;

  echo "
<h2  class=\"pagetitle\">Ubuntu $os_version packages</h2>
<hr />";

  echo "<div class=\"title\">From repository:</div>";

  echo "<ol><li>Add the repositories:<br/>";
  echo "<code>add-apt-repository \"deb http://ppa.launchpad.net/gstreamer-developers/ppa/ubuntu $os_version_lower main\"</code><br />";
  echo "<code>add-apt-repository \"deb http://ppa.launchpad.net/m-ioalex/mp3splt/ubuntu $os_version_lower main\"</code></li>";

  echo "<li>Update the packages:<br />";
  echo "<code>apt-get update</code></li>";

  echo "<li>Install mp3splt and mp3splt-gtk:<br/>";
  echo "<code>apt-get install libmp3splt0-mp3 libmp3splt0-ogg libmp3splt0-flac libmp3splt-doc libmp3splt-dev mp3splt mp3splt-gtk</code></li>";
  echo "</ol>";

echo "<div style='padding-left:10pt'>You can also go to the <a href=\"https://launchpad.net/~m-ioalex/+archive/mp3splt\">mp3splt-project PPA repository page</a>.</div><br />";

echo "libmp3splt0 - main library needed for both mp3splt and mp3splt-gtk<br /><br />";

echo "libmp3splt0-mp3 - mp3 plugin<br />";
echo "libmp3splt0-ogg - ogg vorbis plugin<br />";
echo "libmp3splt0-flac - native FLAC plugin<br /><br />";

echo "libmp3splt-dev - development package<br />";
echo "libmp3splt-doc - libmp3splt API documentation<br /><br/>";

echo "mp3splt - command line client<br /><br/>";
echo "mp3splt-gtk - graphical user interface client<br /><br/>";

}

begin_document("mp3splt project - ubuntu downloads", "default.css",FALSE);

create_table_with_menu("downloads");

end_document();

?>

