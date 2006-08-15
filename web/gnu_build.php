<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2  class=\"pagetitle\">Libmp3splt and Mp3splt-gtk GNU/Linux Subversion build</h2>
<hr />

<p>mp3splt-project subversion directory content :</p>
<div style=\"padding-left:60pt\">
<!---<span class=\"colorspan\">mp3splt-project</span><br />-->
<span class=\"colorspan\">libmp3splt</span><br />
<span class=\"colorspan\">mp3splt-gtk</span><br />
<span class=\"colorspan\">newmp3splt</span><br />
</div>
<br />

<div class=\"title\">GNU/Linux build:</div>

<ol>

<li> Make sure you have installed the following libraries : 
(your distribution should have packages for those libraries)
<ul style=\"padding-left:20pt\">
<li><span class=\"colorspan\">libmad</span>. You can download it from 
<a href=\"http://sourceforge.net/projects/mad/\">
MAD sourceforge page</a></li>
</ul>
</li>

<li>It is recommended that you also install those optional libraries :
<ul style=\"padding-left:20pt\">
<li><span class=\"colorspan\">libogg</span>  and <span
class=\"colorspan\">libvorbis</span>.
You can download them from the 
<a href=\"http://www.xiph.org/downloads/\">vorbis download page</a></li>
<li><span class=\"colorspan\">libid3tag</span>. You can download it from 
<a href=\"http://sourceforge.net/projects/mad/\">
MAD sourceforge page</a></li>
</ul>
</li>

<li>Get the subversion code as explained on the <a href=\"subversion.php\">subversion page</a></li>

<li>Go in the <span class=\"colorspan\">mp3splt-project/libmp3splt</span> directory and type
<span style=\"font-weight:bold\">./autogen.sh</span></li>

<li>After that type
<span style=\"font-weight:bold\">./configure</span> or 
<span style=\"font-weight:bold\">./configure --prefix=&lt;your
directory&gt;</span> to install in a chosen directory
<p>Note : you can disable the use of ogg with \"./configure
--disable-ogg\" but it is not recommended</p>
</li>

<li>Compile the library : type <span style=\"font-weight:bold\">make</span>
<p>You have to be root to install the library if you have not
specified another directory with <span
style=\"font-weight:bold\">./configure --prefix=&lt;your directory&gt;</span></p>
</li>

<li>Install the library : type <span style=\"font-weight:bold\">make install</span>
(you have to install the library to compile mp3splt-gtk)</li>

<li>Go in the <span class=\"colorspan\">mp3splt-project/mp3splt-gtk</span> directory and type
<span style=\"font-weight:bold\">./autogen.sh</span></li>

<li>After that type
<span style=\"font-weight:bold\">./configure</span> or 
<span style=\"font-weight:bold\">./configure --prefix=&lt;your
directory&gt;</span> to install in a chosen directory
</li>

<li>Compile the program : type <span style=\"font-weight:bold\">make</span>
<p>The <span style=\"font-weight:bold\">
mp3splt-gtk</span> binary is in the <span class=\"colorspan\">mp3splt-project/mp3splt-gtk/src</span> directory</p>
</li>

<li>Install the program (optional) : type <span
style=\"font-weight:bold\">make install</span></li>
</ol>";
}

begin_document("libmp3splt and mp3splt-gtk GNU/linux build",
	       "default.css",FALSE);

create_table_with_menu("documentation",TRUE);

end_document();
?>
