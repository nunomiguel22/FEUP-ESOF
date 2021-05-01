<link rel="stylesheet" type="text/css" href="voting.css">

<?php
    $question = @($_GET["question"]);

    if (!isset($question)){
        echo("No question was chosen");
        exit();
    }

    $db = new PDO('sqlite:votes.db');
    $db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $stmt = $db->prepare("select * from votes where question = ?");
    $stmt->execute(array($question));
    $votes = $stmt->fetchAll();
    
    if (empty($votes)) {
        echo "No such survey";
        echo "<br>";
        exit();
    }

    echo "<br>";
    echo '<p id="question">' . $question . '</p>';
    echo "<br>";
    echo "<br>";
    echo "<br>";
    echo "<br>";
    echo "<div id=\"option\">";
    echo "<div class=\"option1\">";
    echo '<span>'. $votes[0]['option1_votes']. '</span>';
    echo '<div class="smalltext">'. $votes[0]['option1']. '</div>';
    echo "</div>";
    echo "<div class=\"option2\">";
    echo '<span>'. $votes[0]['option2_votes']. '</span>';
    echo '<div class="smalltext">'. $votes[0]['option2']. '</div>';
    echo "</div>";
    echo "</div>";
    echo "<br>";
?>
