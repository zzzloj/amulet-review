<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 */

if (isset($loc_i[$loc][$to]) && substr($to, 0, 2) == 'n.') {
    $tchar                    = explode("|", $loc_i[$loc][$to]["char"]);
    $tchar[7]                 = "";
    $loc_i[$loc][$to]["char"] = implode("|", $tchar);
} else {
    addjournal($login, $login, "Заклинание действует только на NPC");
}