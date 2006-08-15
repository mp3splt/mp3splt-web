<?php

include './menu.php';

function create_main_page()
{
  echo "
<h2 class=\"pagetitle\">How to contribute to the mp3splt project ?</h2>
<hr />

<br />
<div class=\"indentdiv\">You don't have to be a developer to contribute to the mp3splt
project.</div><br />

<div class=\"featdiv\">
People are needed for the following tasks :
</div><br />

<div class=\"title\">Testing :</div>
<div class=\"indentdiv\">Testing the program is a very important part
of making a software. Sometimes developers don't test the program very
much because they enjoy programming and testing can sometimes be
annoying. You are welcome to test the releases or the subversion version and
report us bugs or requests. Free software developers will always thank
you for reporting a bug. Even if you don't test the software but
find a bug when using it, you are also welcome to report the bug.
Please use the <a href=\"http://sourceforge.net/mail/?group_id=55130\">
 mailing list</a> for bug reporting.
</div>

<br />
<div class=\"title\">Translating :</div>
<div class=\"indentdiv\">Translations are important to many people who
don't speak english or who prefer their native language. If you like
to contribute with the translation of mp3splt-gtk in your language,
please send us a mail. (TODO: describe here a small how-to for the
translation)</div>


<br />
<div class=\"title\">Documenting :</div>
<div class=\"indentdiv\">Libmp3splt and mp3splt-gtk need
documentation. Of course the best documentation is supposed to be the
one written by the developers, but often no documentation is written
due to the lack of time. We will try to document the programs but if
you want to help don't hesitate.</div>


<br />
<div class=\"title\">Packaging :</div>
<div class=\"indentdiv\">Packaging is also important. Binary or not
binary packages are easy to install for the user. A user who tries to
install a software and all the dependencies of the program will get
tired if this takes too long and will finally quit. We maintain the
debian testing packages and the windows installer for libmp3splt and
mp3splt-gtk.</div>


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
