<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2  class=\"pagetitle\">Documentation</h2>
<hr />

<div class=\"title\">Installation :</div>
<br />
<div class=\"indentdiv\">- 
<a
href=\"http://svn.sourceforge.net/viewvc/mp3splt/mp3splt-project/libmp3splt/INSTALL?view=markup\">
libmp3splt INSTALL file</a>
</div>
<div class=\"indentdiv\">- 
<a
href=\"http://svn.sourceforge.net/viewvc/mp3splt/mp3splt-project/mp3splt-gtk/INSTALL?view=markup\">
mp3splt-gtk INSTALL file</a> (contains also windows installation)
</div>
<br />

<div class=\"title\">Usage :</div>
<br />
<div class=\"indentdiv\">- mp3splt manual page (HTML) : <a href=\"documentation/man.html\">English
(2.1)</a> , <a href=\"documentation/man-de.html\">German (1.9)</a></div>

<br />
<div class=\"title\">Subversion build :</div>
<br />
<div class=\"indentdiv\">-
<a href=\"gnu_build.php\">Build for unix-like OSes</a>
</div>
<div class=\"indentdiv\">-
<a href=\"windows_build.php\">Build for windows</a>
(includes cross compilation)</div>
<br />

<!--<div class=\"title\">Other :</div>
<br />
<div class=\"indentdiv\">- 
<a href=\"documentation/mp3splt_libmp3splt.php\">mp3splt 2.1c and
libmp3splt implementation</a></div>-->
";
}

begin_document("mp3splt project - documentation page",
	       "default.css",FALSE);

create_table_with_menu("documentation");

end_document();
?>
