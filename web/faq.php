<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2  class=\"pagetitle\">Frequently asked questions</h2>
<hr />

<ol>

<li id=\"faq1\">
When using cue or cddb files with characters like ä, ö, ü, ß, mp3splt produces broken
filenames.
<br />
<p>- verify the encoding of the cddb or the cue file; in most cases, it is better to
encode it using UTF-8.</p>
</li>

</ol>

<br />
";
}

begin_document("mp3splt-project FAQ", "default.css",TRUE);

create_table_with_menu("documentation");

end_document();
?>
