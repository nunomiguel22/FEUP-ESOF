<?php
    $question = @($_GET["question"]);
    $option1 = @($_GET["option1"]);
    $option2 = @($_GET["option2"]);
    $timeout = @($_GET["timeout"]);

    if (!isset($question)){
        print("No question was chosen");
        exit();
    }

    $db = new PDO('sqlite:votes.db');
    $db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $stmt = $db->prepare("select * from votes where question = ?");
    $stmt->execute(array($question));
    $votes = $stmt->fetchAll();
    
    if (empty($votes)) {
        if (!isset($option1) || !isset($option2)){
            print("No options set for a new question");
            exit();
        }

        $insert = $db->prepare("insert into votes values(?, $option1, 0, $option2 ,0)");
        $db_status = $insert->execute(array($question));

        $stmt = $db->prepare("select * from votes where question = ?");
        $stmt->execute(array($question));
        $votes = $stmt->fetchAll();
    }
?>

<!DOCTYPE html>
<html lang="en-US">
<head>
<link rel="stylesheet" type="text/css" href="voting.css">    
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<title>conference-connect voting</title>
</head>
<body>
<h1 id="title">Conference-Connect Voting</h1>

<p id="data_update"></p>
<script>
    $(document).ready(
            function() {
                var question = "<?php echo $question ?>";
                var timeout = "<?php echo $timeout ?>";
                setInterval(function() {
   
                    var xhttp;
                    xhttp = new XMLHttpRequest();
                    xhttp.onreadystatechange = function() {
                        if (this.readyState == 4 && this.status == 200) {
                            document.getElementById("show").innerHTML = this.responseText;
                        }
                    };
                     xhttp.open("GET", "read_votes.php?question="+question, true);
                    xhttp.send();
                    if (timeout != 0){
                        --timeout;
                        document.getElementById("time").innerHTML = "Time Remaining: " + timeout;
                    }    
                }, 1000)});
</script>
 
<br>
<br>
<div id="show"></div>
 
<img id="buttonA" src="images/ubitA.png" alt="uBit Button A">
<img id="buttonB" src="images/ubitB.png" alt="uBit Button B">
<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>

<p id="time"></p>

<p class="footnote"> ESOF Conference Connect: Nuno Marques, Gonçalo Oliveira, João Araújo, Pedro Mendes, Francisco Miranda </p>
</body>
</html>
