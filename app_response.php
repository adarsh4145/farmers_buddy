<?php
define('TIMEZONE', 'Asia/Kolkata');
date_default_timezone_set(TIMEZONE);
$sim = $_GET["s"];
$device_id = $_GET["di"];
$response = $_GET["r"];
$on_off = $_GET["o"];
$file_name = $device_id.".txt";
$text = $on_off."\n".$sim;
$location="app_response/".$file_name;

if($response == 1){
        $servername = "fdb17.biz.nf";
        $username = "2416991_rtuproject";
        $password = "adarsh4145";
        $dbname = "2416991_rtuproject";

        $my_file = fopen($location, "w") or die("Unable to open file!");
        fwrite($my_file, $text);
        echo "response submitted successfully!";
        fclose($my_file);
        $conn = new mysqli($servername, $username, $password, $dbname);
        // Check connection
        if ($conn->connect_error) {
                die("Connection failed: " . $conn->connect_error);
        }
        if($on_off == 1){
                $current_stat=true;
                $request_on = date('Y-m-d H:i:s');
                $sql = "INSERT INTO SAVE_RESPONSE (Device_ID, Current_Stat, Request_On) VALUES ('".$device_id."','".$current_stat."','".$request_on."')";
                
                if ($conn->query($sql) === TRUE) {
                        echo "New record created successfully";
                }
                else {
                        echo "Error: " . $sql . "<br>" . $conn->error;
                }
        }
        else{
                $current_stat=false;
                $request_off = date('Y-m-d H:i:s');
                //mysql_query("INSERT INTO `table` (`dateposted`) VALUES ('$date')");
                $my_file = fopen($location, "w") or die("Unable to open file!");
                fwrite($my_file, $text);
                echo "response submitted successfully!";
                fclose($my_file);
                $sql = "UPDATE SAVE_RESPONSE SET Request_Off='".$request_off."' WHERE Device_Id = $device_id";
                if ($conn->query($sql) === TRUE) {
                        ;
                }
                else {
                        echo "Error: " . $sql . "<br>" . $conn->error;
                }
                $sql = "UPDATE SAVE_RESPONSE SET Current_Stat='".$current_stat."' WHERE Request_Off = '".$request_off."'";
                if ($conn->query($sql) === TRUE) {
                        ;
                }
                else {
                        echo "Error: " . $sql . "<br>" . $conn->error;
                }
        }
        $conn->close();
}
?>