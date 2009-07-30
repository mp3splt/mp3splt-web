<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2  class=\"pagetitle\">Documentation</h2>
<hr />

<!--<div class=\"title\">Installation :</div>
<br />
<div class=\"indentdiv\">- 
<a href=\"installation.php\">Installation instructions</a>
<br />
(debian-based, archlinux, gentoo, slackware, rpm-based, bsd flavors, windows, ...)
</div>
<br /> -->

<div class=\"title\">Usage :</div>
<br />
<div class=\"indentdiv\">- mp3splt manual page (HTML) : <a href=\"documentation/man.html\">English
(2.2.6a)</a> , <a href=\"documentation/man-de.html\">German (1.9)</a></div>

<br />
<div class=\"title\">Subversion build :</div>
<br />
<div class=\"indentdiv\">-
<a href=\"gnu_build.php\">Build for unix-like OSes</a>
</div>
<div class=\"indentdiv\">-
<a href=\"windows_build.php\">Build for windows</a>
</div>
<br />

<!--<div class=\"title\">Other :</div>
<br />
<div class=\"indentdiv\">- 
<a href=\"documentation/mp3splt_libmp3splt.php\">mp3splt 2.1c and
libmp3splt implementation</a></div>-->
";
}

begin_document("mp3splt project - documentation page", "default.css",FALSE);

create_table_with_menu("documentation");

end_document();
?>
