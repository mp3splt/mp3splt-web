<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2  class=\"pagetitle\">Subversion build for unix-like OSes</h2>
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
<li><span class=\"colorspan\">gstreamer</span> : download it from the 
<a href=\"http://www.gstreamer.net/\">gstreamer home page</a></li>
<li><span class=\"colorspan\">audacious</span> : download it from the 
<a href=\"http://audacious-media-player.org/\">audacious home page</a></li>
</ul>
</li>

<li>Get the subversion code :
<br />
<code>
svn co http://svn.code.sf.net/p/mp3splt/code/mp3splt-project/trunk mp3splt-project
</code>
</li>

</ol>

<div class=\"title\">Automatic :</div>

<ul>
<li>As root, go  in the <span
class=\"colorspan\">mp3splt-project</span> directory and type :
<br />
<code>
make root_install
</code>
</li>
</ul>

<div class=\"title\">Manual :</div>

<div class=\"section\">Libmp3splt build : </div>

<ol>

<li>Go in the <span class=\"colorspan\">mp3splt-project/libmp3splt</span> directory and
type :
<br />
<code>
./autogen.sh
</code>
</li>

<li>After that, type :
<br />
<code>./configure</code>
<p>You can disable the use of ogg vorbis with \"./configure
--disable-ogg\" but it is not recommended</p>
<p>You can disable the use of id3tag with \"./configure
--disable-id3tag\" but it is not recommended</p>
</li>

<li>Compile the library :
<br />
<code>make</code>
</li>

<li>Install the library : <br />(you have to install the library to compile mp3splt-gtk) 
<br />
<code>make install</code>
<p>You have to be root to install the library</p>
</li>

<li>Type this line as root :
<br />
<code>
if [ -z `grep '/usr/local/lib' /etc/ld.so.conf` ];then `echo
'/usr/local/lib' >> /etc/ld.so.conf` &amp;&amp; ldconfig;else ldconfig;fi
</code>

</li>

</ol>

<div class=\"section\">Mp3splt build : </div>

<ol>
<li>Go in the <span
class=\"colorspan\">mp3splt-project/newmp3splt</span> directory and
type :
<br />
<code>./autogen.sh</code></li>

<li>After that type :
<br />
<code>./configure</code>
</li>

<li>Compile the program :
<br /><code>make</code>
<p>The <span style=\"font-style:italic\">mp3splt</span> binary is in the <span class=\"colorspan\">mp3splt-project/newmp3splt/src</span> directory</p>
</li>

<li>Install the program (optional) :
<br />
<code>make install</code>
<p>You have to be root to install the program.</p>
</li>

</ol>

<div class=\"section\">Mp3splt-gtk build : </div>

<ol>

<li>Go in the <span class=\"colorspan\">mp3splt-project/mp3splt-gtk</span> directory and type
<br />
<code>./autogen.sh</code>
</li>

<li>After that type :
<br />
<code>./configure</code>
<p>You can also use the '--enable-gstreamer' and '--enable-audacious'
parameters to configure. It is recommended to use '--enable-gstreamer'.</p>
</li>

<li>Compile the program :
<br />
<code>make</code>
<p>The <span style=\"font-style:italic\">mp3splt-gtk</span> binary is in the <span class=\"colorspan\">mp3splt-project/mp3splt-gtk/src</span> directory</p>
</li>

<li>Install the program (optional) :
<br />
<code>make install</code>
<p>You have to be root to install the program</p>
</li>

</ol>";
}

begin_document("libmp3splt and mp3splt-gtk GNU/linux build",
	       "default.css",FALSE);

create_table_with_menu("documentation",TRUE);

end_document();
?>
