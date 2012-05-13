<?php

include 'menu.php';

function create_main_page()
{
echo "
<h2  class=\"pagetitle\">Screenshots</h2>
<hr />

<div class=\"title\">mp3splt :</div>
<br />

<a href=\"screenshots/mp3splt_2.4.2.png\">
<img alt=\"\" border=\"0\" src=\"screenshots/mp3splt_2.4.2.png\" />
</a>
<br />

<br />
<div class=\"title\">mp3splt-gtk :</div>
<br />

<a href=\"screenshots/mp3splt-gtk_0.7.2.png\">
<img alt=\"\" border=\"0\" src=\"screenshots/small_mp3splt-gtk_0.7.2.png\" />
</a>
<br />

<a href=\"screenshots/mp3splt-gtk_0.6.1.png\">
<img alt=\"\" border=\"0\" src=\"screenshots/small_mp3splt-gtk_0.6.1.png\" />
</a>
<br />

";
}

begin_document("mp3splt project - screenshots page", "default.css",FALSE);

create_table_with_menu("screenshots");

end_document();
?>
