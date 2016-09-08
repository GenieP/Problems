<?php

    // configuration
    require("../includes/config.php"); 
    
    // if form submitted
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate symbol, else apologize
        $stock = lookup($_POST["symbol"]);
        if(empty($stock))
        {
            apologize("You must provide a valid stock symbol.");
        }
        // check whole number of shares
        else if(!empty($stock))
        {
            if((preg_match("/^\d+$/", $_POST["shares"])) != true)
            {
                apologize("You must provide a whole number of shares to purchase!");
            }
            else
            {   
                // multiply stock cost by number of shares
                number_format($stock["price"], $decimals = 4, $dec_point = ".", $thousands_sep = ",");
                $cost = ($stock["price"]) * ($_POST["shares"]);
                $balance = query("SELECT cash FROM users WHERE id = $_SESSION[id]");
            }
            
            // check user has enough funds, else apologize
            if($cost > $balance)
            {
                apologize("You do not have enough cash to buy that number of shares!");
            }
            else
            {
                // insert new shares into portfolio, else apologize
                $buy = query("INSERT INTO portfolio (id, symbol, shares) VALUES ($_SESSION[id], ?, $_POST[shares]) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $stock["symbol"]);
                
                // update to new cash balance, else apologize    
                $updatecash = query("UPDATE users SET cash = cash - $cost WHERE id = $_SESSION[id]");
                $history = query("INSERT INTO history (id, timestamp, symbol, number, price, transaction) VALUES ($_SESSION[id], NOW(), ?, $_POST[shares], $cost, ?)", $stock["symbol"], "Purchase");
            }
            
            $balance = query("SELECT cash FROM users WHERE id = $_SESSION[id]");
            
            render("bought_form.php", ["stock" => $stock, "balance" => $balance, "cost" => $cost, "title" => "Stock Purchased"]);
        }
    }
    else
    {
        // if no post information, render buy form
        render("buy_form.php", [ "title" => "Buy Stocks"]);
    }
 ?>    
