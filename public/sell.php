<?php

    // configuration
    require("../includes/config.php"); 
    
    // if form submitted
    if($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate symbol, else apologize
        $stock = ($_POST["symbol"]);
        if(empty($stock))
        {
            apologize("You must provide a valid stock symbol.");
        }
        // if stock is not empty, convert to uppercase, check user owns stock
        else if(!empty($stock))
        {
            $stock = strtoupper($stock);
            $available = query("SELECT * FROM portfolio WHERE id = $_SESSION[id] AND symbol = ?", $stock);
            // if user doesnt own stock, apologize
            if(!$available)
            {
                apologize("You can only sell stock you already own!");
            }
            // if do own stock, lookup data and put in separate table - positions
            else foreach ($available as $avail)
            {
                $sales = lookup($avail["symbol"]);
        
                if($sales !== false)
                {
                    $positions[] = [
                        "name" => $sales["name"],
                        "price" => $sales["price"],
                        "shares" => $avail["shares"],
                        "symbol" => $avail["symbol"]       
                    ];
                }
            }
       
            $delete = query("DELETE FROM portfolio WHERE id = $_SESSION[id] AND symbol = ?", $stock);
            if($delete === false)
            {
                apologize("The stock could not be sold!");
            }
            $update = query("UPDATE users SET cash = cash + $sales[price] WHERE id = $_SESSION[id]");
            if ($update === false)
            {
                apologize("The funds from the sale could not be added to your account!");
            } 
            
            $history = query("INSERT INTO history (id, timestamp, symbol, number, price, transaction) VALUES ($_SESSION[id], NOW(), ?, $positions[shares], $positions[price] , ?", $positions["symbol"], "Sale");
            
            $balance = query("SELECT cash FROM users WHERE id = $_SESSION[id]");
            
            render("sold_form.php", ["positions" => $positions[0], "balance" => $balance[0], "title" => "Stock Sales"]);
        }
    }
    else
    {
        render("sell_form.php", ["title" => "Sell Stock"]);
    }
  
?>

