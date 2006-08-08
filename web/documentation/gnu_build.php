<?php
include '../menu.php';

function create_windowsbuild_page()
{
  echo "
<hr />
<h2  class=\"pagetitle\">Libmp3splt and Mp3splt-gtk GNU/Linux CVS build</h2>
<hr />

<p>mp3splt CVS directory content :</p>
<div style=\"padding-left:70pt\">
-<span class=\"colorspan\">mp3splt</span><br />
&nbsp;&nbsp;&nbsp;+<span class=\"colorspan\">libmp3splt</span><br />
&nbsp;&nbsp;&nbsp;+<span class=\"colorspan\">mp3splt-gtk</span><br />
&nbsp;&nbsp;&nbsp;+mp3splt (mp3splt source code, not needed for
libmp3splt or mp3splt-gtk)<br />
&nbsp;&nbsp;&nbsp;<span class=\"colorspan\">Makefile</span> ...
<br /><br />
The Makefile in this <span class=\"colorspan\">mp3splt</span> directory may not always work, so follow
the steps above :
</div>
<br />

<div class=\"title\">GNU/Linux build:</div>

<p>Make sure you have installed the following libraries : 
(your distribution should have packages for those libraries)
</p>

<ul style=\"padding-left:70pt\">
<li><span class=\"colorspan\">libogg</span> and <span class=\"colorspan\">libvorbis</span>.
You can download them from the 
<a href=\"http://www.xiph.org/downloads/\">vorbis download page</a> </li>
<li><span class=\"colorspan\">libmad</span>. You can download it from 
<a href=\"http://sourceforge.net/projects/mad/\">
MAD sourceforge page</a></li>
</ul>

<p>Get the CVS code as explained on the <a href=\"../cvs.php\">CVS page</a> </p>

<p>Go in the <span class=\"colorspan\">mp3splt/libmp3splt</span> directory and type
<span style=\"font-weight:bold\">./autogen.sh</span></p>

<p>After that type
<span style=\"font-weight:bold\">./configure</span> or 
<span style=\"font-weight:bold\">./configure --prefix=&lt;your
directory&gt;</span> to install in a chosen directory
</p>
<p>Note : you can disable the use of ogg with \"./configure
--disable-ogg\" but it is not recommended</p>
<p>Compile the library : type <span style=\"font-weight:bold\">make</span></p>
<p>You have to be root to install the library if you have not
specified another directory with <span
style=\"font-weight:bold\">./configure --prefix=&lt;your directory&gt;</span></p>
<p>Install the library : type <span style=\"font-weight:bold\">make install</span>
(you have to install the library to compile mp3splt-gtk)</p>

<p>Go in the <span class=\"colorspan\">mp3splt/mp3splt-gtk</span> directory and type
<span style=\"font-weight:bold\">./autogen.sh</span></p>
<p>After that type
<span style=\"font-weight:bold\">./configure</span> or 
<span style=\"font-weight:bold\">./configure --prefix=&lt;your
directory&gt;</span> to install in a chosen directory
</p>
<p>Compile the program : type <span style=\"font-weight:bold\">make</span></p>
<p>Install the program (optional) : type <span
style=\"font-weight:bold\">make install</span></p>
<p>The <span style=\"font-weight:bold\">
mp3splt-gtk</span> binary is in the <span class=\"colorspan\">mp3splt/mp3splt-gtk/src</span> directory</p>
";
}

begin_document("mp3splt and libmp3splt",
	       "../default.css");

echo "<br />
&nbsp;&nbsp;&nbsp;&nbsp;
<a href=\"../documentation.php\">&lt;&lt;back</a>";

create_windowsbuild_page();

echo "
&nbsp;&nbsp;&nbsp;&nbsp;
<a href=\"../documentation.php\">&lt;&lt;back</a>";

end_document();
?>
