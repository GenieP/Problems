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
    <h1>Portfolio</h1><br>
    <table>
        <tr style="background-color: #ABCDEF">
            <th>Company</th>
            <th>No. of Shares</th>
            <th>Cash Value</th>
        </tr>
        
        <?php foreach ($positions as $position): ?>
        
        <tr>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td><?= $position["price"] ?></td>
        </tr>
        
        <?php endforeach ?>
        
    </table>
    <br><h4>
        <?php print("Current Cash Balance: $".$line[0]["cash"]) ?>
        </h4>
    <br>
    <br>
<div>
    <a href="logout.php">Log Out</a>
</div>

