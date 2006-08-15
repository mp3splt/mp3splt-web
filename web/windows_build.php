<?php

include 'menu.php';

function create_main_page()
{
  echo "<div style=\"padding-top:5pt;\"><a href=\"documentation.php\">&lt;&lt;documentation</a></div>";
  
  echo "
<h2  class=\"pagetitle\">Libmp3splt and Mp3splt-gtk windows build</h2>
<hr />

<div class=\"title\">Windows build:</div>

<p>1. Download
<a href=\"http://prdownloads.sourceforge.net/mingw/MinGW-4.1.1.exe\">MinGW-4.1.1.exe</a>
and install it in the directory
<span class=\"colorspan\">c:\mp3splt_mingw</span></p>

<p>2. Download 
<a href=\"http://prdownloads.sourceforge.net/mingw/MSYS-1.0.10.exe\">MSYS-1.0.10.exe</a>
and install it in the same directory as
MinGW (<span class=\"colorspan\">c:\mp3splt_mingw</span>). </p>
<p>At the end of the installation, it will ask
you if you want to continue with the post-install. Select yes, and yes
again when it ask if you have mingw installed. When it ask you to
indicate the directory where it is installed, type in <span class=\"colorspan\">c:/mp3splt_mingw</span>
(yes, with a forward slash as the program prefers it that way).</p>

<p>3. Download <a href=\"http://prdownloads.sourceforge.net/mingw/msysDTK-1.0.1.exe\">msysDTK-1.0.1.exe</a>
and install it in the same directory as mingw and msys (<span class=\"colorspan\">c:\mp3splt_mingw</span>)</p>

<p style=\"text-align:left\">4. Download <a href=\"http://prdownloads.sourceforge.net/mp3splt/libmp3splt_mingw_required_libs.tar.bz2\">libmp3splt_mingw_required_libs.tar.bz2</a>,
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_mingw_required_libs.tar.bz2\">mp3splt-gtk_mingw_required_libs.tar.bz2</a>,
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_runtime.tar.bz2\">mp3splt-gtk_runtime.tar.bz2</a> and put them in the home directory of mingw (<span class=\"colorspan\">c:\mp3splt_mingw\home\XXX\</span> where XXX is the username)</p>

<p>5. Double click the msys icon that has been placed on your desktop
during MSYS's installation</p>

<p>6. Download mp3splt-project CVS as anonymous :</p>
<pre style=\"padding-left:50pt\">
cvs -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/mp3splt login
    (when prompted for password, just type return)
cvs -z3 -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/mp3splt co  -P mp3splt
</pre>

<p>7. Download <a href=\"http://nsis.sourceforge.net/Download\">nsis</a> and install it.</p>

<p>8. Copy the <span class=\"colorspan\">nsis</span> directory from the installation directory (usually 
<span class=\"colorspan\">Program Files/nsis</span>)
and put it in the <span class=\"colorspan\">mp3splt</span> directory.</p>

<p>9. Now in the <span class=\"colorspan\">mp3splt</span> directory type 
<pre style=\"padding-left:50pt\">
./compile_win32.sh
</pre>

<p>You will find an executable installer in the
<span class=\"colorspan\">mp3splt</span> directory.</p>

<br />
<div class=\"title\">Cross compiling :</div>
<p>This section explains how to compile mp3splt-gtk for Windows on a
<span style=\"font-weight:bold\">Debian GNU/linux</span> operating system.</p>
<p>1. Install mingw, nsis and wine :</p>
<pre style=\"padding-left:50pt\">
apt-get install mingw32 mingw32-binutils mingw32-runtime nsis wine
</pre>
<p>2. Create the <span class=\"colorspan\">libs</span> directory :</p>
<pre style=\"padding-left:50pt\">
mkdir libs
</pre>
<p style=\"text-align:left\">3. Download <a href=\"http://prdownloads.sourceforge.net/mp3splt/libmp3splt_mingw_required_libs.tar.bz2\">libmp3splt_mingw_required_libs.tar.bz2</a>,
<a href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_mingw_required_libs.tar.bz2\">mp3splt-gtk_mingw_required_libs.tar.bz2</a>,
<a
href=\"http://prdownloads.sourceforge.net/mp3splt/mp3splt-gtk_runtime.tar.bz2\">mp3splt-gtk_runtime.tar.bz2</a> and
put them in the <span class=\"colorspan\">libs</span> directory</p>
<p>4. Download mp3splt-project CVS as anonymous :</p>
<pre style=\"padding-left:50pt\">
cvs -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/mp3splt login
    (when prompted for password, just type return)
cvs -z3 -d:pserver:anonymous@cvs.sourceforge.net:/cvsroot/mp3splt co  -P mp3splt
</pre>
<p>5. Type :</p>
<pre style=\"padding-left:50pt\">
cd mp3splt && ./crosscompile_win32.sh
</pre>
<p>You will find an executable installer in the <span
class=\"colorspan\">mp3splt</span> directory</p>
";
  
  echo "<div style=\"padding-top:5pt;\"><a href=\"documentation.php\">&lt;&lt;documentation</a></div>";
}

begin_document("mp3splt and libmp3splt",
	       "default.css",TRUE);

create_table_with_menu("documentation");

end_document();
?>
