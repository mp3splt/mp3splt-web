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
<p>mp3splt manual page (HTML) : <a href=\"documentation/man.html\">English
(2.1)</a> | <a href=\"documentation/man-de.html\">German (1.9)</a></p>

<br />
<div class=\"title\">Subversion build :</div>
<br />
<div class=\"featdiv\" style=\"margin-bottom:5pt\">
Mp3splt-project build :
</div>
<div class=\"indentdiv\">-
<a href=\"gnu_build.php\">Subversion build instructions</a> (for
unix-like OSes)
</div>
<div class=\"indentdiv\">-
<a href=\"windows_build.php\">Windows Subversion build instructions</a>
(includes cross compilation and windows installer instructions)</div>
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
