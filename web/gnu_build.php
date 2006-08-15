<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2  class=\"pagetitle\">Mp3splt-project subversion build</h2>
<hr />

<div class=\"section\">Prerequisites : </div>

<ol>

<li> Make sure that you have installed the following libraries :
<ul>
<li><span class=\"colorspan\">libmad</span> : download it from 
<a href=\"http://sourceforge.net/projects/mad/\">
MAD sourceforge page</a></li>
</ul>
</li>

<li>It is recommended that you also install those optional libraries :
<ul>
<li><span class=\"colorspan\">libogg</span>  and <span
class=\"colorspan\">libvorbis</span> : download them from the 
<a href=\"http://www.xiph.org/downloads/\">vorbis download page</a></li>
<li><span class=\"colorspan\">libid3tag</span> : download it from 
<a href=\"http://sourceforge.net/projects/mad/\">
MAD sourceforge page</a></li>
</ul>
</li>

<li>You can also install the following programs :
<ul>
<li><span class=\"colorspan\">beep-media-player</span> : download it from the 
<a href=\"http://sourceforge.net/project/showfiles.php?group_id=95272\">bmp download page</a></li>
</ul>
</li>

<li>Get the subversion code as explained on the <a href=\"subversion.php\">subversion page</a>

<p><span class=\"colorspan\">mp3splt-project</span> subversion directory content :
<span class=\"colorspan\">libmp3splt</span>,
<span class=\"colorspan\">mp3splt-gtk</span>,
<span class=\"colorspan\">newmp3splt</span>,...
</p>
</li>

</ol>

<div class=\"title\">Automatic :</div>

<ul>
<li>As root, type <span style=\"font-weight:bold\">make
root_install</span> in the <span
class=\"colorspan\">mp3splt-project</span> directory</li>
</ul>

<div class=\"title\">Manual :</div>

<div class=\"section\">Libmp3splt build : </div>

<ol>

<li>Go in the <span class=\"colorspan\">mp3splt-project/libmp3splt</span> directory and type
<span style=\"font-weight:bold\">./autogen.sh</span></li>

<li>After that type
<span style=\"font-weight:bold\">./configure</span> or 
<span style=\"font-weight:bold\">./configure --prefix=&lt;your
directory&gt;</span> to install in a chosen directory
<p>You can disable the use of ogg with \"./configure
--disable-ogg\" but it is not recommended</p>
<p>You can disable the use of id3tag with \"./configure
--disable-id3tag\" but it is not recommended</p>
</li>

<li>Compile the library : type <span style=\"font-weight:bold\">make</span></li>

<li>Install the library : type <span style=\"font-weight:bold\">make install</span>
(you have to install the library to compile mp3splt-gtk)
<p>You have to be root to install the library if you have not
specified another directory with \"./configure --prefix=&lt;your directory&gt;\"</p>
</li>

<li>Type this line as root : <br />
<code>
if [ -z `grep '/usr/local/lib' /etc/ld.so.conf` ];then `echo
'/usr/local/lib' >> /etc/ld.so.conf` &amp;&amp; ldconfig;fi
</code>

</li>

</ol>

<div class=\"section\">Mp3splt build : </div>

<ol>
<li>Go in the <span class=\"colorspan\">mp3splt-project/newmp3splt</span> directory and type
<span style=\"font-weight:bold\">./autogen.sh</span></li>

<li>After that type
<span style=\"font-weight:bold\">./configure</span> or 
<span style=\"font-weight:bold\">./configure --prefix=&lt;your
directory&gt;</span> to install in a chosen directory
</li>

<li>Compile the program : type <span style=\"font-weight:bold\">make</span>
<p>The <span style=\"font-style:italic\">mp3splt</span> binary is in the <span class=\"colorspan\">mp3splt-project/newmp3splt/src</span> directory</p>
</li>

<li>Install the program (optional) : type <span
style=\"font-weight:bold\">make install</span>
<p>You have to be root to install the library if you have not
specified another directory with \"./configure --prefix=&lt;your directory&gt;\"</p>
</li>

</ol>

<div class=\"section\">Mp3splt-gtk build : </div>

<ol>

<li>Go in the <span class=\"colorspan\">mp3splt-project/mp3splt-gtk</span> directory and type
<span style=\"font-weight:bold\">./autogen.sh</span></li>

<li>After that type
<span style=\"font-weight:bold\">./configure</span> or 
<span style=\"font-weight:bold\">./configure --prefix=&lt;your
directory&gt;</span> to install in a chosen directory
<p>By default, the compilation is without beep-media-player (bmp) support. You can
enable the bmp support with \"./configure --enable-bmp\"</p>
</li>

<li>Compile the program : type <span style=\"font-weight:bold\">make</span>
<p>The <span style=\"font-style:italic\">mp3splt-gtk</span> binary is in the <span class=\"colorspan\">mp3splt-project/mp3splt-gtk/src</span> directory</p>
</li>

<li>Install the program (optional) : type <span
style=\"font-weight:bold\">make install</span>
<p>You have to be root to install the library if you have not
specified another directory with \"./configure --prefix=&lt;your directory&gt;\"</p>
</li>

</ol>";
}

begin_document("libmp3splt and mp3splt-gtk GNU/linux build",
	       "default.css",FALSE);

create_table_with_menu("documentation",TRUE);

end_document();
?>
