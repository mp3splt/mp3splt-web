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
<p>Verify the encoding of the cddb or the cue file; in most cases, it is better to
encode it using UTF-8.</p>
<br /></li>

<li id=\"faq2\">
Why there is no player graph or amplitude wave shown in the graphical user interface
(mp3splt-gtk) ?
<br />
<p>- if the used player does not recognize the total length, there is no
wave because the graphical interface uses the total time provided by the
player.</p>
<p>- try splitting from 0 to a big number of seconds (bigger than the
possible total length of the file), and then work with this newly created file; the newly created file should be more \"readable\".</p>
<br /></li>

</ol>

<br />
";
}

begin_document("mp3splt-project FAQ", "default.css",TRUE);

create_table_with_menu("documentation");

end_document();
?>
