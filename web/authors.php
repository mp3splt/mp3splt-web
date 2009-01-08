<?php

include 'menu.php';

function create_main_page()
{
echo "
<h2  class=\"pagetitle\">Authors</h2>
<hr />

<div class=\"title\">mp3splt :</div>
<ul>
<li>Matteo Trotta : author and main maintainer of Mp3Splt Project</li>
<li>Alexandru Munteanu (<a href=\"http://ioalex.net\">home page</a>) : maintainer of Mp3Splt Project</li>
</ul>

People who contributed to mp3splt development :
<br />

<ul>
<li>Marco Papa Manzillo : rpm and deb packager.</li>
<li>Francois Revol : added list option and worked on BeOS porting.</li>
<li>Remo Laubacher : ported mp3splt v. 0.4 for Windows.</li>
<li>Davide Magatti : \"official\" mp3splt beta tester</li>
</ul>

People who contributed to libmp3splt development :

<ul>
<li>Markus Elfring : code checking for return codes, some bad coding techniques and suggestions.</li>
</ul>

People who contributed to mp3splt-gtk development :
<ul>
<li>Roberto Neri : patch from BMP to audacious support</li>
</ul>

";
}

begin_document("mp3splt project - authors page",
	       "default.css",FALSE);

create_table_with_menu("authors");

end_document();
?>
