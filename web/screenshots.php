<?php

include 'menu.php';

function create_main_page()
{
echo "
<h2  class=\"pagetitle\">Screenshots</h2>
<hr />

<div class=\"title\">mp3splt-gtk :</div>
<br />

<table width=\"100%\">

<tr>
<td>
<a
href=\"screenshots/mp3splt-gtk_0.3_gnu_linux.png\">
<img border=\"0\" src=\"screenshots/thumb.mp3splt-gtk_0.3_gnu_linux.png\" />
</a>
<br />
<div style=\"text-align:left\">mp3splt-gtk v0.3 on GNU/Linux</div>
<br />
</td>
</tr>

<tr>
<td>
<a
href=\"screenshots/mp3splt-gtk_v0.2.1_gnu_linux.png\">
<img border=\"0\" src=\"screenshots/thumb.mp3splt-gtk_v0.2.1_gnu_linux.png\" />
</a>
<br />
<div style=\"text-align:left\">mp3splt-gtk v0.2.1 on GNU/Linux</div>
<br />
</td>
</tr>

<tr>
<td>
<a
href=\"screenshots/mp3splt-gtk_0.2_gnu_linux.png\">
<img border=\"0\" src=\"screenshots/thumb.mp3splt-gtk_0.2_gnu_linux.png\" />
</a>
<br />
<div style=\"text-align:left\">mp3splt-gtk v0.2 on GNU/Linux</div>
</td>

<!--
<td colspan=\"2\">
<a
href=\"screenshots/mp3splt-gtk-0.1.4.jpg\">
<img border=\"0\" src=\"screenshots/thumb.mp3splt-gtk-0.1.4.jpg\" />
</a>
<br />
<div style=\"text-align:left\">mp3splt-gtk v0.1.4 on GNU/Linux</div>
<br />
</td>
</tr>

<tr>
<td>
<a
href=\"screenshots/mp3splt-gtk_v0.1.2.jpg\">
<img border=\"0\" src=\"screenshots/thumb.mp3splt-gtk_v0.1.2.jpg\" />
</a>
<br />
<div style=\"text-align:left\">mp3splt-gtk v0.1.2 on GNU/Linux</div>
</td>

<td>
<a
href=\"screenshots/mp3splt_v0.1.2_win32.jpg\">
<img border=\"0\" src=\"screenshots/thumb.mp3splt_v0.1.2_win32.jpg\" />
</a>
<br />
<div style=\"text-align:left\">mp3splt-gtk v0.1.2 on win32</div>
<br>
</td>
</tr>

<tr>
<td>
<a
href=\"screenshots/mp3splt-0.1.1_gnu_linux.jpg\">
<img border=\"0\" src=\"screenshots/thumb.mp3splt-0.1.1_gnu_linux.jpg\" />
</a>
<br />
<div style=\"text-align:left\">mp3splt-gtk v0.1.1 on GNU/Linux</div>
</td>

<td>
<a
href=\"screenshots/mp3splt-0.1.1_win32.jpg\">
<img border=\"0\" src=\"screenshots/thumb.mp3splt-0.1.1_win32.jpg\" />
</a>
<br />
<div style=\"text-align:left\">mp3splt-gtk v0.1.1 on win32</div>
</td>-->

</tr>
</table>
";
}

begin_document("mp3splt project - screenshots page",
	       "default.css",FALSE);

create_table_with_menu("screenshots");

end_document();
?>
