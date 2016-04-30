<?php
$db = mysql_connect("localhost","participant", "p4rticip4nt");
if (!$db) {
	die("Database connection failed miserably: " . mysql_error());
}
$db_select = mysql_select_db("experiment3",$db);
if (!$db_select) {
	die("Database selection also failed miserably: " . mysql_error());
}
$array =  array('username', 'achievementScore', 'socialScore', 'immersionScore', 'achievementLevel', 'immersionLevel',
		'question1', 'question2', 'question3', 'question4', 'feedback');
$valid_input = true;

foreach ($array as $var) {
	if(isset($_POST[$var])) {
		${$var} = mysql_real_escape_string($_POST[$var]);
		echo ${$var};	
	}
	else {
		$valid_input = false;
	}
}
$ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
if($valid_input) {
	$sql="INSERT INTO surveyResults (ip, username, achievementScore, socialScore, immersionScore, achievementLevel, immersionLevel,
		question1, question2, question3, question4, feedback)
		VALUES ('$ip', '$username', '$achievementScore', '$socialScore', '$immersionScore', '$achievementLevel', '$immersionLevel',
		'$question1', '$question2', '$question3', '$question4', '$feedback')";

	$result = mysql_query($sql);
	if($result){
		if ($_SERVER['HTTP_X_FORWARDED_FOR']){
			echo $_SERVER['HTTP_X_FORWARDED_FOR'];
		} 
		else{ 
			echo $_SERVER['REMOTE_ADDR'];
		}
	}
	else
		echo "fail";
}
mysql_close();
?>
