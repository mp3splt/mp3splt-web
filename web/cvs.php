<?php
include './menu.php';

function create_cvs_page()
{
  echo "
<h2 class=\"pagetitle\">CVS</h2>
<hr />

<div class=\"title\">all the code:</div>
<br />
<div class=\"featdiv\">anonymous :</div>
<ul><li> cvs -d:pserver:anonymous@mp3splt.cvs.sourceforge.net:/cvsroot/mp3splt login</li>
<li> cvs -z3 -d:pserver:anonymous@mp3splt.cvs.sourceforge.net:/cvsroot/mp3splt co -P mp3splt</li>
</ul>
<div class=\"featdiv\">developer :</div>
<ul><li>export CVS_RSH=ssh</li>
<li> cvs -z3 -d:ext:developername@mp3splt.cvs.sourceforge.net:/cvsroot/mp3splt co -P mp3splt</li>
</ul>
";
}
?>

<?php
begin_document("mp3splt project - cvs page",
	       "default.css");

create_table_with_menu("cvs");

end_document();
?>
