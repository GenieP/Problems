<?php

    // configuration
    require("../includes/config.php"); 
    
    // lookup user id to display currently held shares
    $rows = query("SELECT symbol, shares FROM portfolio WHERE id = ?", $_SESSION["id"]);
       
    foreach($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        
        if($stock !== false)
        {
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"]       
            ];
        }
        else
        {
            apologize("You do not currently hold any stocks!");
        }
    }

    $line = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);
    
    
    // render portfolio
    render("portfolio.php", ["positions" => $positions, "line" => $line,"title" => "Portfolio"]);

?>
