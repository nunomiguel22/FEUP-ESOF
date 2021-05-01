<?php
    $db = new PDO('sqlite:votes.db');
    $db->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
    $db->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);


    $question = @($_GET['question']);
    $vote = @($_GET['vote']);

    if ($vote == 'Y') {
        $stmt = $db->prepare("update votes set option1_votes = option1_votes + 1 where question = ?");
        $stmt->execute(array($question));
    } else if ($vote == 'N') {
        $stmt = $db->prepare("update votes set option2_votes = option2_votes + 1 where question = ?");
        $stmt->execute(array($question));
    }

?>
