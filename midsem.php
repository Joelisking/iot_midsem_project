<?php
$servername="localhost";
$username="root";
$password="";    
$dbname="midsem_proj";

$DistanceCm=$_GET['DistanceCm'];
// $LDRValue=$_GET['LDRValue'];
// $Temperature=$_GET['Temperature'];
$con = mysqli_connect($servername,$username,$password,$dbname);

$sql = "INSERT INTO tanks (water_level, owner_id) VALUES ('{$DistanceCm}', '1')";

if (mysqli_query($con, $sql)){
echo "New record created successfully";
}
else{
    echo "Failed";
}

?>
