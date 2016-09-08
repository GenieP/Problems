<form action="sell.php" method="post">
    <fieldset>
    <h1>Stock Sales</h1>
        <div>
        <br>
        <h3>
        <?php number_format($positions["price"], $decimals = 4, $dec_point = ".", $thousands_sep = ",");
            print("Sold Price of " .$positions["name"]);
            print(" = $" .$positions["price"]); ?>
            <br>
            <?php print("New Cash Balance: $" .$balance["cash"]);?>
        </h3></div>
    </fieldset>
</form>
<br>
<div>
    <a href="logout.php">Log Out</a>
</div>


        
