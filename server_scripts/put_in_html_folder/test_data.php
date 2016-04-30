<?php
        $db = mysql_connect("localhost","root","");
        if (!$db) {
                die("Database connection failed miserably: " . mysql_error());
        }
        $db_select = mysql_select_db("testdb",$db);
        if (!$db_select) {
                die("Database selection also failed miserably: " . mysql_error()
);
        }
$array =  array('id', 'name');
$valid_input = true;

foreach ($array as $var) {
	if(isset($_POST[$var])) {
		echo $_POST[$var];
		${$var} = mysql_real_escape_string($_POST[$var]);
		echo $var;
		echo ${$var};
	}
	else {
		$valid_input = false;
	}
}
if($valid_input) {
	$sql="INSERT INTO testTable (id, name) VALUES ('$id', '$name')";
	$result = mysql_query($sql);
}
if($result)
if ($_SERVER['HTTP_X_FORWARDED_FOR']){
	echo $_SERVER['HTTP_X_FORWARDED_FOR'];
} 
else{ 
    echo $_SERVER['REMOTE_ADDR'];
}
else
	echo "fail";
mysql_close();
?>
