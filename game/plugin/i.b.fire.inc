<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global game
 * @global char
 * @global to
 * @global use
 * @global id
 */
// взрывается и ранит всех вокруг довольно сильно

$war     = explode("|", $loc_i[$loc][$login]["war"]);
$war[0]  = 100;
$war[1]  = 1;
$war[2]  = 24;
$war[3]  = 10;
$war[4]  = 0;
$war[12] = "огнем";
$war[14] = "";
$war     = implode("|", $war);

$char[6]                     = time() + 10;
$loc_i[$loc][$login]["char"] = implode("|", $char);

manageItems($loc, $login, "", "i.b.fire", 1, "items", "items", 1, 0, 1);

foreach (array_keys($loc_i[$loc]) as $to) {
    if (substr($to, 0, 2) != 'i.' && $to != $login) {
        attack($loc, $login, $to, $war, 0, 1);
    }
}
