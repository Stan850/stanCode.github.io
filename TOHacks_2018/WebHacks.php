<!DOCTYPE html>
<html>
<body>

<?php
echo "AutoJob";
echo "<br>";
echo "This document will keep track of a database that contains information pertaining to companies!";
echo "<br>";

$servername = "localhost";
$username = "webHacks18";
$password = "sokoHack2018";

// Create connection
$conn = mysqli_connect($servername, $username, $password);
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

// Create database
$sql = "CREATE DATABASE myDB";
if (mysqli_query($conn, $sql)) {
    echo "Database created successfully";
} else {
    echo "Error creating database: " . mysqli_error($conn);
}

mysqli_close($conn);
?>

</body> 
</html>