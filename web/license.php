<?php

include 'menu.php';

function create_main_page()
{
echo "
<h2  class=\"pagetitle\">License</h2>
<hr />
<br />

<div class=\"indentdiv\">
libmp3splt, mp3splt and mp3splt-gtk are licensed under the 

 <a href=\"http://www.gnu.org/licenses/gpl-2.0.html\">GNU
General Public License version 2</a>
</div>

<br />
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
<br /><br />";
}

begin_document("mp3splt project - license page", "default.css",FALSE);

create_table_with_menu("license");

end_document();
?>
