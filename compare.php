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
    echo '<a href="index.php">Back</a>';
    $input_prod_id = $_GET['prod'];
    $double_digit = 0;
    $id_num = substr($input_prod_id, -2);
    $flag = 2;
    if (substr($input_prod_id, -2, 1) != 1 && substr($input_prod_id, -2, 1) !=  2){
        $id_num = substr($input_prod_id, -1);
        $flag = 1;    
    }
    $markup_factor = 1.20;
    $cnx = new mysqli('localhost', 'sql_user', 'sql_pass', 'sql_DB_to_use');

    if ($cnx->connect_error)
        die('Connection failed: ' . $cnx->connect_error);

    $query = 'SELECT * FROM products WHERE prod_id like "%' . $id_num . '"';
    $cursor = $cnx->query($query);

    $i = 1;    
    $array = array();
    while ($row = $cursor->fetch_assoc()) {
        if ($flag == 1)
            if (substr($row['prod_id'], -2, 1) == 1 || substr($row['prod_id'], -2, 1) ==  2)
                continue;
        array_push($array, round($markup_factor*$row['price'], 2));
    }
    $min = min($array);
    
    $query = 'SELECT * FROM products WHERE prod_id like "%' . $id_num . '"';
    $cursor = $cnx->query($query);

    while ($row = $cursor->fetch_assoc()) {
        if ($flag == 1)
            if (substr($row['prod_id'], -2, 1) == 1 || substr($row['prod_id'], -2, 1) ==  2)
                continue;
        $p = round($markup_factor*$row['price'], 2);
        if ($p == $min){
            echo '<tr><p align="center" style="background-color: yellow;">';
            echo '*This Item Is Cheaper*<br>';
        }
        else
            echo '<tr><p align="center">';
        $image = $row['img_url'];
        $imageData = base64_encode(file_get_contents($image));
        echo '<img src="data:image/jpeg;base64,'.$imageData.'">';
        echo '<br>' . $row['name'] . '<br>' . $row['review_score'] .'/5 Stars<br>' . round($row['num_reviews']) . ' Reviews' . '<br>$' . $p . '<br>';
        echo $row['description'] . '<br>';
        echo '<a href="checkout.php?prod='.$row['prod_id'].'">Checkout Here</a>';
        echo '</p></tr>';
        
    }

    $cnx->close();
?>
</table>
</body>
</html>
