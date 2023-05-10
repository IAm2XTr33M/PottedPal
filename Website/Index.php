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
    <link rel="stylesheet" href="style.css">
</head>
<body>

<img src="Img/Logo.png" class="backGroundLogo">


<?php
    $sql = "SELECT * FROM users;";
    $result = mysqli_query($conn , $sql);
    $resultCheck = mysqli_num_rows($result);

    if($resultCheck > 0){
        while ($row = mysqli_fetch_assoc($result)){
            $name = $row['Name'];
            $temp = $row['Temp'];
            $light = $row['LightLevel'];
            $humidity = $row['WaterLevel'];
            $happy = $row['Happyness'];
        }
    }
?>

<div class="container">
    <div class="mainDiv">
        <h1><?php echo $name ?></h1>  
        
        <div class="graphMaxWidth">
            <h1>Temperature</h1>
            <div class="graph" style="width:<?php echo $temp ?>%;background-color: blue"></div>
            <h1>Humidity</h1>
            <div class="graph" style="width:<?php echo $humidity ?>%;background-color: yellow"></div>
            <h1>Light Level</h1>
            <div class="graph" style="width:<?php echo $light ?>%;background-color: red"></div>
            <h1>Happyness</h1>
            <div class="graph" style="width:<?php echo $happy ?>%;background-color: pink"></div>
                        
        </div>
    </div>
</div>

<script>
    //alert("My name is <?php echo $name ?>")
</script>
</body>
</html>