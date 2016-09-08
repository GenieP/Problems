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
        else
        {
            render("quote_reply.php", ["stock" => $stock, "title" => "Stock Quote"]);
            
        }
    }
    else
    {
      // else render form
      render("quote_form.php", ["title" => "Stock Quote"]);
    }
?>

