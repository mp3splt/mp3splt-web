<?php

include 'menu.php';

function create_main_page()
{
echo "
<h2  class=\"pagetitle\">Screenshots</h2>
<hr />

<div class=\"title\">mp3splt-gtk :</div>
<br />

<a href=\"screenshots/mp3splt-gtk_0.6.1.png\">
<img alt=\"\" border=\"0\" src=\"screenshots/small_mp3splt-gtk_0.6.1.png\" />
</a>
<br />
<div style=\"text-align:left\">mp3splt-gtk v0.6.1</div>
<br />

";
}

begin_document("mp3splt project - screenshots page", "default.css",FALSE);

create_table_with_menu("screenshots");

end_document();
?>
