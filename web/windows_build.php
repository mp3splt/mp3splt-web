<?php

include 'menu.php';

function create_main_page()
{
  include 'download_variables.php';

  echo "
<h2  class=\"pagetitle\">Subversion build for windows</h2>
<hr />

<div class=\"title\">Windows build:</div>

<ol>
<li>Download
<a href=\"http://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download\">Mingw-get-setup</a>
and install it in the directory
<span class=\"colorspan\">c:\mp3splt_mingw</span>
<br />
<p>Select the following components to install: mingw-developer-toolkit, mingw32-base, msys-base, mingw32-w32api (dev).</p>
</li>

<li>Open the MinGW console from <span class=\"colorspan\">C:\mp3splt_mingw\msys\1.0\msys.bat</span></li>

<li>Download <a href=\"http://sourceforge.net/projects/mp3splt/files/dev/libmp3splt_mingw_required_libs.tar.bz2/download\">libmp3splt_mingw_required_libs.tar.bz2</a>,
<a href=\"http://sourceforge.net/projects/mp3splt/files/dev/mp3splt-gtk_mingw_required_libs.tar.bz2/download\">mp3splt-gtk_mingw_required_libs.tar.bz2</a>,
<a href=\"http://sourceforge.net/projects/mp3splt/files/dev/mp3splt-gtk_runtime.tar.bz2/download\">mp3splt-gtk_runtime.tar.bz2</a>
and put them in the home directory of mingw (<span class=\"colorspan\">c:\mp3splt_mingw\msys\\1.0\home\XXX\</span> where XXX is the username)</li>

<li>Install <a
href=\"http://sourceforge.net/project/showfiles.php?group_id=138498&amp;package_id=151948\">TortoiseSVN</a>.
Go in the <span class=\"colorspan\">c:\mp3splt_mingw\msys\\1.0\home\XXX\</span> directory (with windows explorer) and create a directory called mp3splt-project.
</li>

<li>
Go in the newly created <span
class=\"colorspan\">mp3splt-project</span> directory, right click
inside the window and select SVN Checkout. Type the following URL of
repository in the newly opened window and then click \"ok\" :
<br />
<code>http://svn.code.sf.net/p/mp3splt/code/mp3splt-project/trunk</code>
</li>
 
<li>Download <a href=\"http://nsis.sourceforge.net/Download\">nsis</a> and install it.</li>

<li>Copy the <span class=\"colorspan\">nsis</span> directory from the installation directory (usually 
<span class=\"colorspan\">Program Files/nsis</span>)
and put it in the <span class=\"colorspan\">mp3splt-project</span> directory.</li>

<li>Double click the msys icon that has been placed on your desktop
during MSYS's installation and type :
<br />
<code>cd mp3splt-project &amp;&amp; ./compile_win32.sh</code>

<p>Then, two executable installers will be found in the <span
class=\"colorspan\">mp3splt-project</span> directory (one for the
command line and the other for the gui)</p>
</li>

</ol>

<p style=\"text-align: left\">Sources of the dependencies:</p>

<p style=\"text-align: left\">
<a href=\"http://sourceforge.net/projects/mp3splt/files/dev/libmp3splt_mingw_required_libs_sources.tar.bz2/download\">
libmp3splt_mingw_required_libs_sources.tar.bz2</a>,
<a href=\"http://sourceforge.net/projects/mp3splt/files/dev/GTK%2B3.6.4_build_system-win32-v4-Alex.zip/download\">
GTK+ 3.6.4 build system</a>,
<a href=\"http://sourceforge.net/projects/mp3splt/files/dev/gstreamer-1.1.14_build_system-win32.zip/download\">
gstreamer 1.1.14 build system</a>.
</p>

<br />
";
}

begin_document("mp3splt project windows build", "default.css",TRUE);

create_table_with_menu("documentation");

end_document();
?>
