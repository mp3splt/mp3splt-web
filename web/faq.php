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
filenames or broken tags.
<br />
<p>Verify the encoding of the cddb or the cue file. Try converting the input file to UTF-8.
Mp3splt expects UTF-8 by default when writing tags.
However, mp3splt has the -I option to specify the input tags encoding that is used to write ID3v2 tags.</p>
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

<li id=\"faq3\">
Why I can't see the ID3v2 tags ?
<br />
<p>Mp3splt is using libid3tag to write ID3v2 tags and the library only supports writing ID3v2 version 2.4 (26/11/2011).
If the software that you are using only supports ID3v2 version 2.3, no tags will be read.
<a href=\"http://en.wikipedia.org/wiki/ID3#ID3v2\">http://en.wikipedia.org/wiki/ID3#ID3v2</a>
</p>
<br /></li>

<li id=\"faq4\">
How can I use mp3splt with cygwin ?
<br />
<p>In order to use mp3splt from cygwin you can do one of the following :
</p>
<p>&nbsp;&nbsp;- use the windows paths insted of the cygwin paths</p>
<p>&nbsp;&nbsp;- use the <span style=\"font-style:italic\">cygpath</span> utility from cygwin
  <a href=\"http://cygwin.com/cygwin-ug-net/using-utils.html#cygpath\">http://cygwin.com/cygwin-ug-net/using-utils.html#cygpath</a>
</p>
<pre>
  Example:
    $ mp3splt.exe -t 1.0 $(cygpath -w /path/to/your/file.ogg)
</pre>
<p>
&nbsp;&nbsp;- use other tools like <span style=\"font-style:italic\">cyg-wrapper.sh</span>
  <a href=\"http://hermitte.free.fr/cygwin/#Win32\">http://hermitte.free.fr/cygwin/#Win32</a>
</p>
<pre>
  Example:
    $ cyg-wrapper.sh mp3splt.exe --binary-opt=-t /path/to/your/file.ogg -t 1.0
</pre>
<br /></li>


</ol>

<br />
";
}

begin_document("mp3splt project FAQ", "default.css",TRUE);

create_table_with_menu("documentation");

end_document();
?>
