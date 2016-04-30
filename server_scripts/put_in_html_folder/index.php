<?php
$db = mysql_connect("localhost","participant", "p4rticip4nt");
if (!$db) {
        die("Database connection failed miserably: " . mysql_error());
}
$db_select = mysql_select_db("counter",$db);
if (!$db_select) {
        die("Database selection also failed miserably: " . mysql_error());
}
$query = 'SELECT count from count';
$res = mysql_query($query);
$data = mysql_fetch_assoc($res);
$val = $data['count'];
?>
<?php
function update() {
$query='UPDATE count SET count.count = count.count + 1;';                                                                                                                    
$res = mysql_query($query);
}
?>
<script>
function count() {
        var x ="<?php update(); ?>";
	return false;
} 
</script>


<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="icon" href="favicon.ico">

    <title>OpenClonk Experimental Game</title>

    <!-- Bootstrap core CSS -->
    <link href="dist/css/bootstrap.min.css" rel="stylesheet">

    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <link href="assets/css/ie10-viewport-bug-workaround.css" rel="stylesheet">

    <!-- Custom styles for this template -->
    <link href="starter-template.css" rel="stylesheet">

    <!-- Just for debugging purposes. Don't actually copy these 2 lines! -->
    <!--[if lt IE 9]><script src="../../assets/js/ie8-responsive-file-warning.js"></script><![endif]-->
    <script src="assets/js/ie-emulation-modes-warning.js"></script>
    <!-- HTML5 shim and Respond.js for IE8 support of HTML5 elements and media queries -->
    <!--[if lt IE 9]>
      <script src="https://oss.maxcdn.com/html5shiv/3.7.2/html5shiv.min.js"></script>
      <script src="https://oss.maxcdn.com/respond/1.4.2/respond.min.js"></script>
    <![endif]-->
  </head>

  <body>

    <nav class="navbar navbar-inverse navbar-fixed-top">
      <div class="container">
        <div class="navbar-header">
          <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#navbar" aria-expanded="false" aria-controls="navbar">
            <span class="sr-only">Toggle navigation</span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
            <span class="icon-bar"></span>
          </button>
          <a class="navbar-brand" href="#">OpenClonk Experimental Game</a>
        </div>
        <div id="navbar" class="collapse navbar-collapse">
          <ul class="nav navbar-nav">
           
          </ul>
        </div><!--/.nav-collapse -->
      </div>
    </nav>

    <div class="container">

      <div class="starter-template">
      <!--<img src="assets/img/logo.png" > <br>-->
      <img src="assets/img/Screenshot0441.png" >
        <h1>Welcome to the OpenClonk Experimental Game!</h1>
        <br>
        <p class="lead"><b> Description</b></p> OpenClonk is an open source 2D platform game with gameplay mechanics similar to Terraria or Worms. 
            This is a modified version of the original OpenClonk game. 
            <br> <br> 
         <p class="lead"><b>Instructions</b></p> 
            1. <b>Download the game <a id="linky"></a> and install the game.</b><br>
            2. Start and play the game. <br>
            3. Play at least 5 rounds. Each game round should take less than 5 minutes and you can play more if you wish. <br>
            4. A button linking to the post-game survey will appear after 5 rounds are completed. This simple survey has 5 questions to obtain player feedback for game improvement.
            <br> <br>
            Tested on Win 7(64-bit), 10(64-bit).
            If there are any problems/feedback, report them <a href="http://goo.gl/forms/T0aQS73Ebd">here</a>. 
            <br><br>
            <b>Credits: </b> 
            The OpenClonk team. Check them out at <a href="http://www.openclonk.org">www.openclonk.org</a>. 
            
      </div>

    </div><!-- /.container -->


    <!-- Bootstrap core JavaScript
    ================================================== -->
    <!-- Placed at the end of the document so the pages load faster -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
    <script>window.jQuery || document.write('<script src="../../assets/js/vendor/jquery.min.js"><\/script>')</script>
    <script src="dist/js/bootstrap.min.js"></script>
    <!-- IE10 viewport hack for Surface/desktop Windows 8 bug -->
    <script src="assets/js/ie10-viewport-bug-workaround.js"></script>
  </body>
</html>

<script>
var index =<?php echo $val?>;
console.log(index);
index = index%4;
if(index < 0)
        index = 0;
if(index ==0)
        text = "<a href='http://dl.dropbox.com/s/yjgcdix6c0m7oye/OpenClonkE2_Setup.msi?dl=0' onclick=\"count()\">here</a>";
else if (index == 1)
        text = "<a href='http://dl.dropbox.com/s/5i8yyrv9g1h4xtn/OpenClonkE3_Setup.msi?dl=0' onclick=\"count()\">here</a>";
else if (index == 2)
        text = "<a href='http://dl.dropbox.com/s/5a3xoxslqu43b0a/OpenClonkE4_Setup.msi?dl=0' onclick=\"count()\">here</a>";
else if (index == 3)                                                                                                                                                         
        text = "<a href='http://dl.dropbox.com/s/p71lqn9dy7i2wn7/OpenClonkEG_Setup1.msi?dl=0' onclick=\"count()\">here</a>";  
document.getElementById("linky").innerHTML = text;
</script>

