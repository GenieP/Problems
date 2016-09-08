<?php

    // configuration
    require("../includes/config.php"); 
    
    // lookup user id to display historical transactions
    $rows = query("SELECT * FROM history WHERE id = ?", $_SESSION["id"]);
       
    foreach($rows as $row)
    {
        if(!empty($row))
        {
            $tblpositions[] = [
                "time" => $row["timestamp"],
                "price" => $row["price"],
                "shares" => $row["number"],
                "symbol" => $row["symbol"],
                "transaction" => $row["transaction"]       
             ];
         }
         else
         {
            apologize("You have no transactions to display!");
         }
    }
       
    // render transactions
    render("transactions.php", ["tblpositions" => $tblpositions, "title" => "Historical Transactions"]);

?>
