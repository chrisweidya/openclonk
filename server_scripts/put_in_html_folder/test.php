<?php
        $db = mysql_connect("localhost","root","");
        if (!$db) {
                die("Database connection failed miserably: " . mysql_error());
        }
        $db_select = mysql_select_db("testdb",$db);
        if (!$db_select) {
                die("Database selection also failed miserably: " . mysql_error());
        }
?>
<html>
<head>
</head>
<body>
<?php
        $result = mysql_query("SELECT user FROM mysql.user", $db);
                if (!$result) {
                        die("Database query failed: " . mysql_error());
                }
//Step4
        while ($row = mysql_fetch_array($result)) {
                echo $row[0];
        }
?>
        <form action="test_data.php" method="post">
                <p hidden>
                        <label>id:</label>
                        <input name="id" required="required" type="text">
                </p>
                <p>
                        <label>name:</label>
                        <input name="participant_name" required="required" type="text">
                </p>
        	<p>
			<input value="Submit" type="submit">
		</p>
	</form>
</body>
</html>
