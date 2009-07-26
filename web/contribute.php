<?php

include './menu.php';

function create_main_page()
{
  echo "
<h2 class=\"pagetitle\">How to contribute to the mp3splt project ?</h2>
<hr />

<div class=\"indentdiv\">Short answer: by sending a mail to one of the authors.</div>
<br />

<div class=\"indentdiv\">You don't have to be a developer to contribute to the mp3splt
project.</div><br />

<div class=\"featdiv\">
People are needed for the following tasks :
</div><br />

<div class=\"title\">Testing :</div>
<div class=\"indentdiv\">Testing the program is a very important part
of making a software. You are welcome to test the releases or the subversion code and
report us bugs or requests. Even if you don't test the software but
find a bug when using it, you are also welcome to report the bug.
</div>

<br />
<div class=\"title\">Translating :</div>
<div class=\"indentdiv\">Translations are important to many people who
don't speak english or who prefer their native language. If you want
to contribute with translations, please send us a mail.
Hint: <a href=\"http://www.poedit.net/\">poedit</a> can be used to translate the
<a href=\"http://mp3splt.svn.sourceforge.net/viewvc/mp3splt/mp3splt-project/trunk/mp3splt-gtk/po/fr.po?view=markup\">
po file(s)</a>.</div>


<br />
<div class=\"title\">Documenting :</div>
<div class=\"indentdiv\">Libmp3splt and mp3splt-gtk need
documentation. Of course the best documentation is supposed to be the
one written by the developers, but often no documentation is written
due to the lack of time. We will try to document the programs but if
you want to help don't hesitate.</div>


<br />
<div class=\"title\">Moral support :</div>
<div class=\"indentdiv\">A small mail telling the developers
that the software is useful and/or that you like the software is a big
contribution. Knowing that the software you create helps other people
is very motivating.
</div>

<br />
<div class=\"title\">Donations :</div>
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
