<?php
    include_once 'includes/dbh.php';

    $name = "";
    $temp = "";
    $light = "";
    $humidity = "";
    $happy = "";
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Potted Pal</title>
    <link rel="stylesheet" href="css/style.css">
</head>
<body>
    <div id="Left">
        <form method="post" action="">
            <label for="username">Enter id:</label>
            <input type="text" name="id" id="id">
            <input type="submit" name="submit" value="Submit">
        </form>
    </div>

    <?php
    if (isset($_POST['submit'])) {
        $id = $_POST['id'];
                
        if ($conn->connect_error) {
            die('Connection failed: ' . $conn->connect_error);
        }
        
        $sql = "SELECT * FROM users WHERE id = '$id'";
        
        $result = $conn->query($sql);
        
        if ($result->num_rows > 0) {
            while ($row = $result->fetch_assoc()) {
                $name = $row['Name'];
                $temp = $row['Temp'];
                $light = $row['Lightlevel'];
                $humidity = $row['Waterlevel'];
                $happy = $row['Happyness'];
            }
        }
        
        $conn->close();
    }
    ?>



</body>
</html>