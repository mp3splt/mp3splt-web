<?php 
header("Content-type: text/html; charset=utf-8"); 

//creates the first part of the html document
function begin_document($title, $css_file,$third)
{
  $doctype =
    "<!DOCTYPE html 
     PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"
  \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">
  ";
  
  echo $doctype,
"<html>
<head>
<title>",
    $title,
"
</title>
<link rel=\"stylesheet\" type=\"text/css\" 
href=\"$css_file\" title=\"Normal\" />
</head>";
  
  if ($third)
    {
      echo "<body id=\"bodyid\" style=\"background-color:white\">";
    }
  else
    {
      echo "<body id=\"bodyid\">";
    }
}

//creates the end of the document
function end_document()
{
  echo "</body></html>";
}

//function that creates and draws the menu
function create_menu($page)
{
  //table for the general menu
  $menu = array(0 => "Home",
		1 => "News",
		2 => "About",
		3 => "License",
		4 => "Screenshots",
		5 => "Downloads",
		6 => "Documentation",
		7 => "Subversion",
		8 => "Contribute",
		9 => "Authors");
  
  //set the menu fixed?
  echo "<div style=\"\">";
  // echo "<br />";
  echo "<div class=\"titlemenu\">General</div>";

  //create general menu
  for ($i = 0; $i < count($menu); $i++)
    {
      //convert to lower cases
      $link = strtolower($menu[$i].".php");
      if (strcmp($page,strtolower($menu[$i])) == 0)
	{
	  echo "<div class=\"menudiv\">$menu[$i]</div>";
	}
      else
	{
	  echo "<div class=\"menudiv\">
           <a href=\"$link\">$menu[$i]</a></div>";
	}
    }
  
  //table for the developers menu
  //$menu2 = array(0 => "CVS");
  $menu2 = array();
  
  echo "<br />";
  echo "<div class=\"titlemenu\">Tracker</div>";
  
  //create developers menu
  for ($i = 0; $i < count($menu2); $i++)
    {
      //convert to lower cases
      $link = strtolower($menu2[$i].".php");
      
      echo "<div class=\"menudiv\">
           <a href=\"$link\"> $menu2[$i]</a></div>";
    } 

  //mailing list external link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/mail/?group_id=55130\">
       Mailing list</a></div>";
  //browse CVS external link
  echo "<div class=\"menudiv\">
           <a href=\"http://svn.sourceforge.net/viewvc/mp3splt/mp3splt-project/\">
       Browse SVN</a></div>";
  //bugs external link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/tracker/?atid=476061&amp;group_id=55130&amp;func=browse\">
       Bugs</a></div>";
  //support requests external link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/tracker/?atid=476062&amp;group_id=55130&amp;func=browse\">
       Support Requests</a></div>";
  //patches external link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/tracker/?atid=476063&amp;group_id=55130&amp;func=browse\">
       Patches</a></div>";
  //feature requests external link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/tracker/?atid=476064&amp;group_id=55130&amp;func=browse\">
       Feature Requests</a></div>";

  echo "<br />";
  echo "<div class=\"titlemenu\">Links</div>";
  //sourceforge page link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/projects/mp3splt\">
       Sf.net page</a></div>";
  //mp3wrap link
  echo "<div class=\"menudiv\">
           <a href=\"http://mp3wrap.sourceforge.net/\">
       Mp3Wrap</a></div>";

  echo "<br />";
  //support logo
  echo "<center><a
  href=\"https://sourceforge.net/donate/index.php?group_id=55130\"> <img
  alt=\"\" border=\"0\" src=\"project-support.jpg\" /> </a></center>
  ";

  //sourceforge logo
  echo "
<br />
<center><a href=\"http://sourceforge.net\"> <img
 src=\"http://sourceforge.net/sflogo.php?group_id=55130&amp;type=2\"
 width=\"125\" height=\"37\" border=\"0\" alt=\"SourceForge Logo\" />
 </a> </center>
</div>
";
}

//creates the appropriate page switching $page
function create_page()
{
  create_main_page();
}

//creates a table with the menu and the page passed as parameter
function create_table_with_menu($page)
{
  echo "
<div style=\"width:100%;background-color:black;text-align:center\">
 <img style=\"margin:0pt;padding:0pt;border:0\" src=\"mp3splt.jpg\" alt =\"project\" />
</div>

<table id=\"main_table\" style=\"border-collapse:collapse\">
<tr>
<td id=\"main_menu_column\">
",
    create_menu($page)
    ,"
</td>
<td id=\"main_page_column\">
";
  $child_or_not = FALSE;
  $real_page = substr(strrchr($_SERVER['SCRIPT_FILENAME'],"/"),1,-4);
  if (strcmp($real_page,$page) != 0)
    {
      $child_or_not = TRUE;
    }
  
  #top link
  if ($child_or_not)
    {
      echo "<div style=\"padding-top:5pt;padding-bottom:5pt;\"><a href=\"{$page}.php\">&lt;&lt;{$page}</a></div>";
    }
  
  create_page();
  
  #bottom link
  if ($child_or_not)
    {
      echo "<div style=\"padding-top:0pt;padding-bottom:5pt;\"><a href=\"{$page}.php\">&lt;&lt;{$page}</a></div>";
    }
  
  $the_page = "http://".$_SERVER['SERVER_NAME'].":";
  if ($_SERVER['SERVER_PORT'] != 80)
    {
      $the_page .= $_SERVER['SERVER_PORT'];
    }
  $the_page .= $_SERVER['PHP_SELF'];
  
echo "
</td>
</tr>

<tr>
<td colspan=\"2\">
<div class=\"bottombar\">
<a class=\"bottom\" href=\"http://validator.w3.org/check?uri={$the_page}\">XHTML</a>
<a class=\"bottom\" href=\"http://jigsaw.w3.org/css-validator/validator?uri={$the_page}\">CSS2</a>
</div>
</td>
</tr>

</table>
";
}

?>
