<form action="quote.php" method="post">
    <fieldset>
    <h1>Stock Quotation</h1>
        <div>
        <br>
        <h3>
        <?php number_format($stock["price"], $decimals = 4, $dec_point = ".", $thousands_sep = ",");
            print("Current Price of " .$stock["name"]);
            print(" = $" .$stock["price"]); ?>
        </h3></div>
    </fieldset>
</form>
    <br>
<div>
    <a href="logout.php">Log Out</a>
</div>
