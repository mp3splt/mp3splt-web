<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2 class=\"pagetitle\">Subversion</h2>
<hr />
<br />

<div class=\"title\">unix-like OSes :</div>
<p>
Command line :</p>
<code>svn co
https://mp3splt.svn.sourceforge.net/svnroot/mp3splt/mp3splt-project/trunk
mp3splt-project
</code>
<br />
<br />

<div class=\"title\">windows :</div>
<p>Install <a
href=\"http://sourceforge.net/project/showfiles.php?group_id=138498&amp;package_id=151948\">TortoiseSVN</a>
and create a directory called mp3splt-project. Go in the newly created <span
class=\"colorspan\">mp3splt-project</span> directory, right click
inside the window and select SVN Checkout. Type the following URL of
repository in the newly opened window and then click \"ok\" :</p>
<code>https://mp3splt.svn.sourceforge.net/svnroot/mp3splt/mp3splt-project/trunk</code>

<br /><br />
<div class=\"title\">See also :</div>
<br />
<div class=\"indentdiv\">-
<a href=\"gnu_build.php\">Subversion build for unix-like OSes</a>
</div>
<div class=\"indentdiv\">-
<a href=\"windows_build.php\">Subversion build for windows</a>
</div>

";
}

begin_document("mp3splt project - Subversion page",
	       "default.css",FALSE);

create_table_with_menu("subversion");

end_document();
?>
