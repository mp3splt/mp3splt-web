<?php
include './menu.php';

function create_documentation_page()
{
  echo "
<h2  class=\"pagetitle\">Documentation</h2>
<hr />

<div class=\"title\">Installation :</div>
<br />
<div class=\"indentdiv\">- 
<a
href=\"http://cvs.sourceforge.net/viewcvs.py/mp3splt/mp3splt/libmp3splt/INSTALL?view=markup\">
libmp3splt INSTALL file</a>
</div>
<div class=\"indentdiv\">- 
<a
href=\"http://cvs.sourceforge.net/viewcvs.py/mp3splt/mp3splt/mp3splt-gtk/INSTALL?view=markup\">
mp3splt-gtk INSTALL file</a> (contains also windows installation)
</div>
<br />

<div class=\"title\">Usage :</div>
<p>mp3splt manual page (HTML) : <a href=\"documentation/man.html\">English
(2.1)</a> | <a href=\"documentation/man-de.html\">German (1.9)</a></p>

<br />
<div class=\"title\">CVS build :</div>
<br />
<div class=\"featdiv\">
Libmp3splt and Mp3splt-gtk build :
</div><br />
<div class=\"indentdiv\">-
<a href=\"documentation/gnu_build.php\">GNU/Linux CVS build instructions</a>
</div>
<div class=\"indentdiv\">-
<a href=\"documentation/windows_build.php\">Windows CVS build instructions</a>
(includes cross compilation and windows installer instructions)</div>
<br />

<div class=\"title\">Other :</div>
<br />
<div class=\"indentdiv\">- 
<a href=\"documentation/mp3splt_libmp3splt.php\">mp3splt 2.1c and
libmp3splt implementation</a></div>
";
}
?>

<?php
begin_document("mp3splt project - documentation page",
	       "default.css");

create_table_with_menu("documentation");

end_document();
?>
