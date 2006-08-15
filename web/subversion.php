<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2 class=\"pagetitle\">Subversion</h2>
<hr />

<br />
<div class=\"title\">all the code:</div>
<ul><li>svn co https://svn.sourceforge.net/svnroot/mp3splt/mp3splt-project mp3splt-project</li>
</ul>";
}

begin_document("mp3splt project - Subversion page",
	       "default.css",FALSE);

create_table_with_menu("subversion");

end_document();
?>
