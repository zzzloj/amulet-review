<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global id
 * @global locai
 * @global tchar
 * @global g_list
 * @global trader
 * @global up
 * @global down
 * @global to
 */

// диалог с патрулем

$owner = explode("|", $loc_i[$loc][$speak]["owner"]);
$tc    = explode("|", $loc_i[$loc][$speak]["char"]);
if ($owner[0] == $login) {
    msg("Не будем терять времени, " . $char[0] .
        ", пошли туда, где ты считаешь могут находиться бандиты. У меня в запасе еще около " .
        round(($tc[11] - time()) / 60) . " минут");
} else {
    msg("Извини, " . $char[0] . ", я при исполнении служебных обязанностей и следую за " . substr($owner[0], 2) .
        " по поручению офицера Санчеса.");
}