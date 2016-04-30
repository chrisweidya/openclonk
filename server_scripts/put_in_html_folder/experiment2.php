<?php
$db = mysql_connect("localhost","participant", "p4rticip4nt");
if (!$db) {
	die("Database connection failed miserably: " . mysql_error());
}
$db_select = mysql_select_db("experiment2",$db);
if (!$db_select) {
	die("Database selection also failed miserably: " . mysql_error());
}
$array =  array('username', 'achievementScore', 'socialScore', 'immersionScore', 'achievementLevel', 'immersionLevel',
		'achResult','immResult',
		 'round', 'seed', 'restarts', 'immersionChoices',
		'achievementChoices', 'roundTime', 'keyboardAPM', 'mouseAPM', 'playerDeaths',
		'batDeaths', 'treesChopped', 'immersionTime', 'achievementTime', 'objectiveCompleted');
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
	$sql="INSERT INTO data (ip, username, achievementScore, socialScore, immersionScore, achievementLevel, immersionLevel, 
		achResult, immResult,round, seed, restarts, immersionChoices,
		achievementChoices, roundTime, keyboardAPM, mouseAPM, playerDeaths,
		batDeaths, treesChopped, immersionTime, achievementTime, objectiveCompleted)
		VALUES ('$ip', '$username', '$achievementScore', '$socialScore', '$immersionScore', '$achievementLevel', '$immersionLevel',
		'$achResult', '$immResult', '$round', '$seed', '$restarts', '$immersionChoices',
		'$achievementChoices', '$roundTime', '$keyboardAPM', '$mouseAPM', '$playerDeaths',
		'$batDeaths', '$treesChopped', '$immersionTime', '$achievementTime', '$objectiveCompleted')";

	$result = mysql_query($sql) or die(mysql_error());
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
