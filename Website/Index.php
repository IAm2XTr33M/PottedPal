<?php
    include_once 'includes/dbh.php';

    $name = "";
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
<?php
    $sql = "SELECT * FROM users;";
    $result = mysqli_query($conn , $sql);
    $resultCheck = mysqli_num_rows($result);

    if($resultCheck > 0){
        while ($row = mysqli_fetch_assoc($result)){
            $name = $row['Name'];
        }
    }
?>

<div class="header"></div>

<h1><?php echo $name ?></h1>

<script>
    //alert("My name is <?php echo $name ?>")
</script>

</body>
</html>