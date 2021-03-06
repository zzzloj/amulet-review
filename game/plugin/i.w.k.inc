<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */
if (substr($to, 0, 6) == 'i.s.d.' && isset($loc_i[$loc][$to])) {
    $died = explode("|", $loc_i[$loc][$to]);
    if ($died[4]) {
        // добавляем трофеи в инвентарь трупа
        if ($died[3]) {
            $died[3] .= "," . $died[4];
        } else {
            $died[3] = $died[4];
        }
        $died[4]          = "";
        $loc_i[$loc][$to] = implode("|", $died);
        addjournal($loc, $login, "Вы освежевали " . $died[0]);
        if (rand(1, 100) < 5) {
            addexp($loc, $login, 1);
        }
    } else {
        addjournal($loc, $login, "На трупе нет трофеев");
    }
} else {
    addjournal($loc, $login, "Нож можно использовать для разделки только трупов");
}