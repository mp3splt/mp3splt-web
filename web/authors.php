<?php
include './menu.php';

function create_contact_page()
{
echo "
<h2  class=\"pagetitle\">Authors</h2>
<hr />

<div class=\"title\">mp3splt :</div>
<ul>
<li> Matteo Trotta : author and main mantainer of Mp3Splt Project</li>
</ul>

People who contributed to mp3splt development :
<br />

<ul>
<li>Marco Papa Manzillo : rpm and deb packager.</li>
<li>Francois Revol : added list option and worked on BeOS porting.</li>
<li>Remo Laubacher : ported mp3splt v. 0.4 for Windows.</li>
<li>Davide Magatti : \"official\" mp3splt beta tester</li>
</ul>

<div class=\"title\">libmp3splt :</div>
<ul>
<li> Munteanu Alexandru : author and main maintainer of libmp3splt</li>
</ul>

<div class=\"title\">mp3splt-gtk :</div>
<ul>
<li> Munteanu Alexandru : author and main maintainer of mp3splt-gtk</li>
</ul>

";

}
?>

<?php
begin_document("mp3splt project - authors page",
	       "default.css");

create_table_with_menu("contact");

end_document();
?>
