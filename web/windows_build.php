<?php

include 'menu.php';

function create_main_page()
{
  echo "
<h2  class=\"pagetitle\">Subversion build for windows</h2>
<hr />

<div class=\"title\">Windows build:</div>

<ol>
<li>Download
<a href=\"http://prdownloads.sourceforge.net/mingw/mingw-get-inst-20101030.exe\">Mingw-get-inst</a>
and install it in the directory
<span class=\"colorspan\">c:\mp3splt_mingw</span></li>

<p>Select the following extra components to install: 'MSYS Basic System' and 'MinGW Developer ToolKit'.</p>
</li>

<li>Open the MinGW console from <span class=\"colorspan\">Start-&gt;MinGW-&gt;MinGW Shell</span>.</li>

<li>Download <a href=\"../dev/libmp3splt_mingw_required_libs.tar.bz2\">libmp3splt_mingw_required_libs.tar.bz2</a>,
<a href=\"../dev/mp3splt-gtk_mingw_required_libs.tar.bz2\">mp3splt-gtk_mingw_required_libs.tar.bz2</a>,
<a href=\"../dev/mp3splt-gtk_runtime.tar.bz2\">mp3splt-gtk_runtime.tar.bz2</a>
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
<code>https://mp3splt.svn.sourceforge.net/svnroot/mp3splt/mp3splt-project/trunk</code>
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

<p style=\"text-align: left\">Some sources of the dependencies libraries can be found:</p>
</br>

<p style=\"text-align: left\">
<a href=\"../dev/libmp3splt_mingw_required_libs_sources.tar.bz2\">
libmp3splt_mingw_required_libs_sources.tar.bz2</a>,
<a href=\"../dev/mp3splt-gtk_mingw_required_libs_runtime_sources.tar.bz2\">
mp3splt-gtk_mingw_required_libs_runtime_sources.tar.bz2</a>.
</p>

<br /><br />
";
}

begin_document("mp3splt and libmp3splt",
	       "default.css",TRUE);

create_table_with_menu("documentation");

end_document();
?>
