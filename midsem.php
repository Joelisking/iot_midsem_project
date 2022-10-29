<?php
$servername="localhost";
$username="root";
$password="";    
$dbname="iot_midsem";

$DistanceCm=$_GET['DistanceCm'];
// $LDRValue=$_GET['LDRValue'];
// $Temperature=$_GET['Temperature'];
$con = mysqli_connect($servername,$username,$password,$dbname);

$sql = "INSERT INTO waterreading (WaterLevel) VALUES ('{$DistanceCm}')";

if (mysqli_query($con, $sql)){
echo "New record created successfully";
}
else{
    echo "Failed";
}

?>
