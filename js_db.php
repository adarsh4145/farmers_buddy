<?php
header('Content-Type: application/json');

define('DB_HOST', 'fdb17.biz.nf');
define('DB_USERNAME', '2416991_rtuproject');
define('DB_PASSWORD', 'adarsh4145');
define('DB_NAME', '2416991_rtuproject');

$conn = new mysqli(DB_HOST, DB_USERNAME, DB_PASSWORD, DB_NAME);

if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
} 

$query = sprintf("SELECT Device_ID, Date_Time, Mobile_Num, Location, Temperature, Air_Humidity, Soil_Moisture, Rain FROM SAVE_DATA");

$result = $conn->query($query);

$data = array();
foreach ($result as $row) {
	$data[] = $row;
}

$result->close();

$conn->close();

print json_encode($data);

?>
