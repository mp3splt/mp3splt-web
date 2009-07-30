<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2  class=\"pagetitle\">Installation instructions</h2>
<hr />


<br />
";
}

begin_document("mp3splt project - installation page", "default.css",FALSE);

create_table_with_menu("documentation");

end_document();
?>
