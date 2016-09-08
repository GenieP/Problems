<form action="buy.php" method="post">
    <fieldset>
    <h1>Stock Purchased</h1>
        <div>
        <br>
        <h3>
        <?php number_format($cost, $decimals = 4, $dec_point = ".", $thousands_sep = ",");
            print("Purchase price of " .$stock["name"]);
            print(" = $" .$cost); ?>
        <br>
        <?php print("New Cash Balance = $" .$balance[0]["cash"]); ?>
        </h3></div>
    </fieldset>
</form>
<br>
<div>
    <a href="logout.php">Log Out</a>
</div>
