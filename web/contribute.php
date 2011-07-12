<?php

include './menu.php';

function create_main_page()
{
  echo "
<h2 class=\"pagetitle\">How to contribute to the mp3splt project ?</h2>
<hr />

<div class=\"indentdiv\">Short answer: by sending a mail to one of the main <a
href=\"authors.php\">authors</a>.</div>
<br />

<div class=\"title\">Coding:</div>
<div class=\"indentdiv\">There are a lot of feature requests <a
href=\"https://sourceforge.net/tracker/?group_id=55130&amp;atid=476064\">here</a>.</div>
<br />

<div class=\"title\">Testing:</div>
<div class=\"indentdiv\">Testing the program is a very important part
of making a software. You are welcome to test the releases or the subversion code and
report us bugs or requests. Even if you don't test the software but
find a bug when using it, you are also welcome to report the bug.
</div>

<br />
<div class=\"title\">Translations:</div>
<div class=\"indentdiv\">Translations are important to many people who
don't speak english or who prefer their native language. If you want
to contribute with translations. <a href=\"http://www.poedit.net/\">poedit</a> can be used to translate the
files from <a href=\"http://www.transifex.net/projects/p/mp3splt-gtk/\">transifex</a>.
The 'mp3splt-gtk' project from transifex also contains the translation for the library and
the command line mp3splt client.</div>

<br />
<div class=\"title\">Documentation:</div>
<div class=\"indentdiv\">Libmp3splt and mp3splt-gtk need
documentation. The best documentation is supposed to be the
one written by the developers, but often no documentation is not written
due to the lack of time.</div>

<br />
<div class=\"title\">Moral support:</div>
<div class=\"indentdiv\">A small mail telling the developers
that the software is useful and/or that you like the software is a big
contribution. Knowing that the software you create helps other people
is very motivating.
</div>

<br />
<div class=\"title\">Donations:</div>
<div class=\"indentdiv\">If you have no time to contribute to the
project but want to, you can also support it by donating.</div>


<br />
<div class=\"featdiv\">
Of course, any other contributions are welcome :)
</div>
<br />
";
}

begin_document("mp3splt project - contribution page",
	       "default.css",FALSE);

create_table_with_menu("contribute");

end_document();
?>
