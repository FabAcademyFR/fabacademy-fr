<?php
require 'php-sdk/src/temboo.php';
if(isset($_GET['msg']) ){
    $msg = $_GET['msg'];
}else{
    $msg = 'Quack'.date('s');
}
if(isset($_GET['xxxx']) ){
    $xxxx = $_GET['xxxx'];
}else{
    $xxxx = "0";
}


// Instantiate the Choreo, using a previously instantiated Temboo_Session object, eg:
$session = new Temboo_Session('xxxxxxxxxxxxxxxxxx', 'myFirstApp', 'xxxxxxxxxxxxxxxxxx');

$statusesUpdate = new Twitter_Tweets_StatusesUpdate($session);

// Get an input object for the Choreo
$statusesUpdateInputs = $statusesUpdate->newInputs();



// Set inputs
$statusesUpdateInputs->setAccessToken("xxxx")->setAccessTokenSecret("xxxx")->setConsumerSecret("xxxx")->setStatusUpdate($msg)->setConsumerKey("xxxx");

if($xxxx == "xxxxxxxxxxxxxxxxxx"){
// Execute Choreo and get results
$statusesUpdateResults = $statusesUpdate->execute($statusesUpdateInputs)->getResults();
echo "ok";
}else{
echo "no permission";
}

?>