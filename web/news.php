<?php
include './menu.php';

function create_news_page()
{
  echo "
<h2 class=\"pagetitle\">News</h2>
<hr />

<br />
";
 
  include "news.html";
}

?>

<?php
begin_document("mp3splt project - news page",
	       "default.css");

create_table_with_menu("news");

end_document();
?>

