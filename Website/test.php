
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
        <h1> <?php echo $name ?> </h1>  
    </div>
</div>
