<?php
define('TIMEZONE', 'Asia/Kolkata');
date_default_timezone_set(TIMEZONE);
$servername = "fdb17.biz.nf";
$username = "2416991_rtuproject";
$password = "adarsh4145";
$dbname = "2416991_rtuproject";
$date_time = date('Y-m-d H:i:s');

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
} 

$sql = "INSERT INTO
 SAVE_DATA (Device_ID, Date_Time, Mobile_Num, Location, Temperature, Air_Humidity, Soil_Moisture, Rain, Suggest_On)
 VALUES
 ('".$_GET["di"]."','".$date_time."','".$_GET["mn"]."','".$_GET["l"]."','".$_GET["t"]."','".$_GET["ah"]."','".$_GET["sm"]."','".$_GET["r"]."','".$_GET["so"]."')"
 ;

if ($conn->query($sql) === TRUE) {
    	echo "New record created successfully";
} 
else {
    	echo "Error: " . $sql . "<br>" . $conn->error;
}
$conn->close();
?>