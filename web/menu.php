<?php 
header("Content-type: text/html; charset=utf-8"); 

//creates the first part of the html document
function begin_document($title, $css_file)
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
</head>
<body id=\"bodyid\">
";
}

//creates the end of the document
function end_document()
{
  echo "</body></html>";
}

//function that creates and draws the menu
function create_menu()
{
  //table for the general menu
  $menu = array(0 => "Home",
		1 => "News",
		2 => "About",
		3 => "License",
		4 => "Screenshots",
		5 => "Downloads",
		6 => "Documentation",
		7 => "Contribute",
		8 => "Authors");
  
  //set the menu fixed?
  echo "<div style=\"\">";
  // echo "<br />";
  echo "<div class=\"titlemenu\">General</div>";

  //create general menu
  for ($i = 0; $i < count($menu); $i++)
    {
      //convert to lower cases
      $link = strtolower($menu[$i].".php");
      echo "<div class=\"menudiv\">
           <a href=\"$link\">$menu[$i]</a>
       &nbsp;</div>";
    }

  //table for the developers menu
  $menu2 = array(0 => "CVS");
  
  echo "<br />";
  echo "<div class=\"titlemenu\">Tracker</div>";

  //create developers menu
  for ($i = 0; $i < count($menu2); $i++)
    {
      //convert to lower cases
      $link = strtolower($menu2[$i].".php");
      
      echo "<div class=\"menudiv\">
           <a href=\"$link\"> $menu2[$i]</a>
       &nbsp;</div>";
    } 

  echo "external :";
  //mailing list external link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/mail/?group_id=55130\">
       Mailing list</a>
       &nbsp;</div>";
  //browse CVS external link
  echo "<div class=\"menudiv\">
           <a href=\"http://mp3splt.cvs.sourceforge.net/mp3splt/\">
       Browse CVS</a>
       &nbsp;</div>";
  //bugs external link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/tracker/?atid=476061&group_id=55130&func=browse\">
       Bugs</a>
       &nbsp;</div>";
  //support requests external link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/tracker/?atid=476062&group_id=55130&func=browse\">
       Support Requests</a>
       &nbsp;</div>";
  //patches external link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/tracker/?atid=476063&group_id=55130&func=browse\">
       Patches</a>
       &nbsp;</div>";
  //feature requests external link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/tracker/?atid=476064&group_id=55130&func=browse\">
       Feature Requests</a>
       &nbsp;</div>";

  echo "<br />";
  echo "<div class=\"titlemenu\">Links</div>";
  //sourceforge page link
  echo "<div class=\"menudiv\">
           <a href=\"http://sourceforge.net/projects/mp3splt\">
       Sf.net page</a>
       &nbsp;</div>";
  //mp3wrap link
  echo "<div class=\"menudiv\">
           <a href=\"http://mp3wrap.sourceforge.net/\">
       Mp3Wrap</a>
       &nbsp;</div>";

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
function create_page($page)
{
  if ($page == "about")
    create_about_page();
  elseif ($page == "news")
    create_news_page();
  elseif ($page == "home")
    create_home_page();
  elseif ($page == "download")
    create_download_page();
  elseif ($page == "screenshots")
    create_screenshots_page();
  elseif ($page == "license")
    create_license_page();
  elseif ($page == "contact")
    create_contact_page();
  elseif ($page == "documentation")
    create_documentation_page();
  elseif ($page == "contribute")
    create_contribute_page();
  elseif ($page == "cvs")
    create_cvs_page();
}

//creates a table with the menu and the page passed as parameter
function create_table_with_menu($page)
{
  echo "
<div style=\"width:100%;background-color:black;text-align:center\">
 <img style=\"margin:0pt;padding:0pt;border:0\" src=\"mp3splt.jpg\" alt =\"project\" />
</div>

<table id=\"main_table\" style=\"margin:0pt;padding:0pt\">
<tr>
<td id=\"main_menu_column\">
",
    create_menu()
    ,"
</td>
<td id=\"main_page_column\">
",
    create_page($page)
    ,"
</td>
</tr>
</table>
";
}

?>


