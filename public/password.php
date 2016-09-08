<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["password"]))
        {
            apologize("You must provide your previous password.");
        }
        
        // query database for user
        $rows = query("SELECT * FROM users WHERE id = ?", $_SESSION["id"]);

        // if we found user, check password
        if (count($rows) == 1)
        {
            // first (and only) row
            $row = $rows[0];

            // compare hash of user's password against hash that's in database
            if (crypt($_POST["password"], $row["hash"]) == $row["hash"])
            {
                if($_POST["new_password"] === $_POST["confirmation"])
                {
                    $update = query("UPDATE users SET hash = $_POST[new_password] WHERE id = $_SESSION[id]");
                    render("p_changed.php", ["title" => "Changed Password"]);
                }
                else
                {
                    apologize("Your new password and confirmation do not match!");
                }
            }
            else
            {
                apologize("Your typed password does not match our records!");
            }
        }

    }
    else
    {
        // else render form
        render("p_change.php", ["title" => "Change Your Password"]);
    }

?>
