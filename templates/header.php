<!DOCTYPE html>

<html>

    <head>

        <link href="/css/bootstrap.min.css" rel="stylesheet"/>
        <link href="/css/bootstrap-theme.min.css" rel="stylesheet"/>
        <link href="/css/styles.css" rel="stylesheet"/>

        <?php if (isset($title)): ?>
            <title>C$50 Holiday: <?= htmlspecialchars($title) ?></title>
        <?php else: ?>
            <title>C$50 Holiday</title>
        <?php endif ?>

        <script src="/js/jquery-1.10.2.min.js"></script>
        <script src="/js/bootstrap.min.js"></script>
        <script src="/js/scripts.js"></script>

    </head>

    <body>

        <div class="container">

            <div id="top">
                <a href="/"><img alt="C$50 Holiday" src="/img/logo.gif"/></a>
                
                <ul class="nav nav-pills nav-justified">
                    <li><a href="/index.php">Portfolio</a></li>
                    <li><a href="/quote.php">Stock Quote</a></li>
                    <li><a href="/buy.php">Buy Stocks</a></li>
                    <li><a href="/sell.php">Sell Stocks</a></li>
                    <li><a href="/history.php">Transaction History</a></li>
                    <li><a href="/password.php">Change Password</a></li>
                </ul>
                <hr>
            </div>

            <div id="middle">
