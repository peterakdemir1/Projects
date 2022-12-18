<!DOCTYPE html>
<html>
<style>
table, th, tr{
  border: 1px solid black;
  border-collapse: collapse;
}
</style>
</head>
<body>
<table>
<?php
    if (isset($_GET['purchase']))
        echo '<p align="center">Thank you for your purchase!</p>';
    echo '<p align="center">Welcome to The Swim Emporium<br></p>';
    $cnx = new mysqli('localhost', 'sql_user', 'sql_pass', 'sql_DB_to_use');

    if ($cnx->connect_error)
        die('Connection failed: ' . $cnx->connect_error);

    $query = 'SELECT * FROM products';
    $cursor = $cnx->query($query);
    while ($row = $cursor->fetch_assoc()) {
        echo '<tr><p align="center">';
        $image = $row['img_url'];
        $imageData = base64_encode(file_get_contents($image));
        echo '<img src="data:image/jpeg;base64,'.$imageData.'">';
        echo '<br>' . $row['name'] . '<br>';
        echo '<a href="compare.php?prod='.$row['prod_id'].'">Click Here for More Info!</a>';
        echo '</p></tr>';
    }

    $cnx->close();
?>
</table>
</body>
</html>
