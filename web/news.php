<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2 class=\"pagetitle\">News</h2>
<hr />

<br />
";
  
  include "news.html";
  include "old_news.html";
  
  echo "<br />";
}

begin_document("mp3splt project - news page", "default.css",FALSE);

create_table_with_menu("news");

end_document();
?>

