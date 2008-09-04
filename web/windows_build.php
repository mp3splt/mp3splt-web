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
<a href=\"http://prdownloads.sourceforge.net/mingw/MinGW-4.1.1.exe\">MinGW-4.1.1.exe</a>
and install it in the directory
<span class=\"colorspan\">c:\mp3splt_mingw</span></li>

<li>Download 
<a href=\"http://prdownloads.sourceforge.net/mingw/MSYS-1.0.10.exe\">MSYS-1.0.10.exe</a>
and install it in the same directory as
MinGW (<span class=\"colorspan\">c:\mp3splt_mingw</span>).

<p>At the end of the installation, it will ask
you if you want to continue with the post-install. Select yes, and yes
again when it ask if you have mingw installed. When it ask you to
indicate the directory where it is installed, type in <span class=\"colorspan\">c:/mp3splt_mingw</span>
(yes, with a forward slash as the program prefers it that way).</p>
</li>

<li>Download <a href=\"http://prdownloads.sourceforge.net/mingw/msysDTK-1.0.1.exe\">msysDTK-1.0.1.exe</a>
and install it in the same directory as mingw and msys (<span class=\"colorspan\">c:\mp3splt_mingw</span>)</li>

<li>Download <a href=\"http://prdownloads.sourceforge.net/mp3splt/libmp3splt_mingw_required_libs.tar.bz2\">libmp3splt_mingw_required_libs.tar.bz2</a>,
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_mingw_required_libs.tar.bz2\">mp3splt-gtk_mingw_required_libs.tar.bz2</a>,
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_runtime.tar.bz2\">mp3splt-gtk_runtime.tar.bz2</a> and put them in the home directory of mingw (<span class=\"colorspan\">c:\mp3splt_mingw\home\XXX\</span> where XXX is the username)</li>

<li>Install <a href=\"http://sourceforge.net/project/showfiles.php?group_id=138498&amp;package_id=151948\">TortoiseSVN</a>. Go in the <span class=\"colorspan\">c:\mp3splt_mingw\home\XXX\</span> directory (with windows explorer) and create a directory called mp3splt-project.
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

<p>You will find two executables installers in the <span
class=\"colorspan\">mp3splt-project</span> directory (one for the
command line and the other for the gui)</p>
</li>

</ol>

Info : some sources of the dependencies libraries can be found : 
<a href=\"http://prdownloads.sourceforge.net/mp3splt/libmp3splt_mingw_required_libs_sources\">
libmp3splt_mingw_required_libs_sources.tar.bz2</a>,
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_mingw_required_libs_sources.tar.bz2\">
mp3splt-gtk_mingw_required_libs_sources.tar.bz2</a>.
<br /><br />

<!--<div class=\"title\">Cross compiling :</div>
<p>This section explains how to compile mp3splt-project for Windows on a
<span style=\"font-weight:bold\">Debian GNU/linux</span> operating system.</p>

<ol>

<li>Install mingw, nsis and wine as root :
<br />
<code>apt-get install mingw32 mingw32-binutils mingw32-runtime nsis wine subversion</code>
</li>

<li>Create the <span class=\"colorspan\">libs</span> directory :
<br />
<code>mkdir libs</code>
</li>

<li>Download <a href=\"http://prdownloads.sourceforge.net/mp3splt/libmp3splt_mingw_required_libs.tar.bz2\">libmp3splt_mingw_required_libs.tar.bz2</a>,
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_mingw_required_libs.tar.bz2\">mp3splt-gtk_mingw_required_libs.tar.bz2</a>,
<a
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_runtime.tar.bz2\">mp3splt-gtk_runtime.tar.bz2</a> and
put them in the <span class=\"colorspan\">libs</span> directory</li>

<li>Download mp3splt-project subversion code :
<br />
<code>svn co https://mp3splt.svn.sourceforge.net/svnroot/mp3splt/mp3splt-project mp3splt-project</code>
</li>

<li>Type :
<br />
<code>cd mp3splt-project &amp;&amp; make windows_cross_installers</code>

<p>You will find two executables installers in the <span
class=\"colorspan\">mp3splt-project</span> directory (one for the
command line and the other for the gui)</p>
</li>

</ol>-->
";
}

begin_document("mp3splt and libmp3splt",
	       "default.css",TRUE);

create_table_with_menu("documentation");

end_document();
?>
