<form action="password.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autofocus class="form-control" name="password" placeholder="Current Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="new_password" placeholder="New Password" type="password"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="confirmation" placeholder="Confirm New Password" type="password"/>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Change Password</button>
        </div>
    </fieldset>
</form>
<div>
    <a href="logout.php">Log Out</a>
</div>
