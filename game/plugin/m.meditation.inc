<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */
// переводит все здоровье мага в ману с коэффициентом 0.7

$heal = $char[1] - 1;
$heal = round($heal * 0.7);
if ($heal < 0) {
    $heal = 0;
}
if ($char[3] + $heal > $char[4]) {
    $heal = $char[4] - $char[3];
}
$char[1] = 1;
$char[3] += $heal;
$char[5]                     = time();
$loc_i[$loc][$login]["char"] = implode("|", $char);
addjournal($loc, $login, "Мана +" . $heal);

