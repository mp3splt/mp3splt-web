<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2  class=\"pagetitle\">Documentation</h2>
<hr />

<!--<div class=\"title\">Installation :</div>
<br />
<div class=\"indentdiv\">- 
<a href=\"installation.php\">Installation instructions</a>
<br />
(debian-based, archlinux, gentoo, slackware, rpm-based, bsd flavors, windows, ...)
</div>
<br /> -->

<div class=\"title\">For users :</div>
<br />
<div class=\"indentdiv\">- mp3splt manual : <a href=\"documentation/man.html\">English
(2.6.1)</a> , <a href=\"documentation/man-de.html\">German (1.9)</a></div>
<br />
<div class=\"indentdiv\">-
<a href=\"faq.php\">Frequently asked questions (English)</a>
</div>

<br />
<div class=\"title\">For developers :</div>
<br />
<div class=\"indentdiv\">- <a href=\"documentation/libmp3splt_api/index.html\">libmp3splt API
documentation</a></div>
<br />
<div class=\"indentdiv\">-
<a href=\"gnu_build.php\">Build for unix-like OSes</a>
</div>
<div class=\"indentdiv\">-
<a href=\"windows_build.php\">Build for windows</a>
</div>
<br />

<!--<div class=\"title\">Other :</div>
<br />
<div class=\"indentdiv\">- 
<a href=\"documentation/mp3splt_libmp3splt.php\">mp3splt 2.1c and
libmp3splt implementation</a></div>-->
";
}

begin_document("mp3splt project - documentation page", "default.css",FALSE);

create_table_with_menu("documentation");

end_document();
?>
