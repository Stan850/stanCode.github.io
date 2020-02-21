<?php
/* Attempt MySQL server connection. Assuming you are running MySQL
server with default setting (user 'root' with no password) */
$link = mysqli_connect("localhost", "root", "", "demo");

// Check connection
if($link === false){
    die("ERROR: Could not connect. " . mysqli_connect_error());
}

// Print host information
echo "Connect Successfully. Host info: " . mysqli_get_host_info($link);

// Attempt create database query execution
$sql = "CREATE DATABASE IF NOT EXISTS demo";
if(mysqli_query($link, $sql)){
  echo"";
    echo "Database created successfully";
} else{
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
}


// Attempt create table query execution
$sql = "CREATE TABLE IF NOT EXISTS USER_INPUT(
    id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
    first_name VARCHAR(30) NOT NULL,
    last_name VARCHAR(30) NOT NULL,
    email VARCHAR(70) NOT NULL UNIQUE,
    skill_one VARCHAR(40),
    skill_two VARCHAR(40),
    skill_three VARCHAR(40),
    skill_four VARCHAR(40),
    skill_five  VARCHAR(40)
)";
if(mysqli_query($link, $sql)){
    echo "";
    echo "Table created successfully.";
} else{
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
}


// Escape user inputs for security
$first_name = mysqli_real_escape_string($link, $_REQUEST['first_name']);
$last_name = mysqli_real_escape_string($link, $_REQUEST['last_name']);
$email = mysqli_real_escape_string($link, $_REQUEST['email']);
$skill_one = mysqli_real_escape_string($link, $_REQUEST['skill_one']);
$skill_two = mysqli_real_escape_string($link, $_REQUEST['skill_two']);
$skill_three = mysqli_real_escape_string($link, $_REQUEST['skill_three']);
$skill_four = mysqli_real_escape_string($link, $_REQUEST['skill_four']);
$skill_five = mysqli_real_escape_string($link, $_REQUEST['skill_five']);

// attempt insert query execution
$sql = "INSERT INTO USER_INPUT (first_name, last_name, email, skill_one, skill_two,skill_three,skill_four,skill_five) VALUES ('$first_name', '$last_name', '$email','$skill_one','$skill_two', '$skill_three','$skill_four','$skill_five')";
if(mysqli_query($link, $sql)){
    echo "Records added successfully.";
} else{
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
}









// Attempt insert query execution
/*$sql = "INSERT INTO USER_INPUT (first_name, last_name, email, skill_one, skill_two, skill_three, skill_four, skill_five) VALUES
            ('John', 'Rambo', 'johnrambo@mail.com', 'C', 'Blender', 'PremierLight', 'MSOffice', 'SQL'),
            ('Clark', 'Kent', 'clarkkent@mail.com', 'C', 'Python', 'Java', 'AndroidStudio', 'Swift'),
            ('John', 'Carter', 'johncarter@mail.com', 'Python', 'CSharp', '', '', ''),
            ('Harry', 'Potter', 'harrypotter@mail.com', 'FinalCutPro', 'Sketch', 'Excel', 'Verilog', '')";
if(mysqli_query($link, $sql)){
    echo "";
    echo "Records added successfully.";
} else{
    echo "ERROR: Could not able to execute $sql. " . mysqli_error($link);
}*/

// close connection
mysqli_close($link);
?>
