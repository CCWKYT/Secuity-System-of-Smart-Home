<html>
<head>
<meta http-equiv="refresh" content="3">
</head> 
<body>
<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "tutor";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 

$sql = "SELECT * FROM esp8266 ORDER by id DESC LIMIT 5";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // output data of each row
	echo "<table border='1'><th>ID</th><th>TEMP</th><th>DATETIME</th>";
    while($row = $result->fetch_assoc()) {
		echo "<tr>";
		echo "<td>".$row['id']."</td>";
		echo "<td>".$row['temp']."</td>";
		echo "<td>".$row['day']."</td>";
		echo "</tr>";
    }
	echo "</table>";
} else {
    echo "0 results";
}
$conn->close();
?>
</body>
</html>