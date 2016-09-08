<style scoped>
.table, th, td  
{
    width: 400px;
    padding: 20px;
    border: 2px solid gray;
    margin: 0 auto;
    text-align: center;
}
</style>
    <h1>Historical Transactions</h1><br>
    <table>
        <tr style="background-color: #ABCDEF">
            <th>Time and Date</th>
            <th>Company</th>
            <th>Number of Shares</th>
            <th>Price of Shares</th>
            <th>Type of Transaction</th>
        </tr>
        
        <?php foreach ($tblpositions as $tblposition): ?>
        
        <tr>
            <td><?= $tblposition["time"] ?></td>
            <td><?= $tblposition["symbol"] ?></td>
            <td><?= $tblposition["shares"] ?></td>
            <td><?= $tblposition["price"] ?></td>
            <td><?= $tblposition["transaction"] ?></td>
        </tr>
        
        <?php endforeach ?>
        
    </table>
    <br>
    <br>
    <br>
<div>
    <a href="logout.php">Log Out</a>
</div>

