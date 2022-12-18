<!DOCTYPE html>
<html>
<head>
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

    if (isset($_POST['Name'])){
        echo $_POST['Name'];
        $cny = new mysqli('localhost', 'sql_user', 'sql_pass', 'sql_DB_to_use');
        if ($cnx->connect_error)
            die('Connection failed: ' . $cnx->connect_error);

        $query2 = 'INSERT INTO transactions(name,card,expr,cvv,zip) VALUES (' . $_POST['Name'] . ', ' . $_POST['Card Number'] . ', ' . $_POST['Expiration Date'] . ', ' . $_POST['CVV'] . ', ' . $_POST['Zip code'] . ')';
        $cursor2 = $cnx->query($query2);
   	    $cny -> close();     
    }
    echo '<a href="index.php">Back to Home</a>';
    $input_prod_id = $_GET['prod'];
    $markup_factor = 1.20;
    $cnx = new mysqli('localhost', 'sql_user', 'sql_pass', 'sql_DB_to_use');

    if ($cnx->connect_error)
        die('Connection failed: ' . $cnx->connect_error);

    $query = 'SELECT * FROM products WHERE prod_id="' . $input_prod_id . '"';
    $cursor = $cnx->query($query);
    
    while ($row = $cursor->fetch_assoc()) {
        echo '<p align="center">';
        $image = $row['img_url'];
        $imageData = base64_encode(file_get_contents($image));
        $p = round($markup_factor*$row['price'], 2);
        echo '<img src="data:image/jpeg;base64,'.$imageData.'">';
        echo '<br>' . $row['name'] . '<br>' . 'Total Price: $' . $p . '<br>';
        echo '<p align="center">Name:<input type="text" name="Name"><br>';
        echo '<form method="POST">';
        echo 'Card Number:<input type="text" name="Card Number"><br>';
        echo 'Expiration Date:<input type="text" name="Expiration Date"><br>';
        echo 'CVV:<input type="text" name="CVV"><br>';
        echo 'Zip Code:<input type="text" name="Zip Code"><br>';
        #echo '<input type=submit name="submit" value="Purchase Now!"></form></p>';
        echo '<a href="index.php?purchase=true">Purchase Now!</a>';
        echo '</p>';
    }

    $cnx->close();
?>
</table>
</body>
</html>
