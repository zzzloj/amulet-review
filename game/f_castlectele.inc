<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global to
 * @global desc
 * @global exits
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global d
 */
// телепорт в свой замок
if ($clanc && $clanc == $clan) {// только если есть враги
    $tc = substr($ctele, 0, 4);
    loadloc($tc . "main");
    loadloc($tc . "tron");
    loadloc($tc . "sklad");
    if ($loc_i[$tc . "gate"]) {
        foreach (array_keys($loc_i[$tc . "gate"]) as $k) {
            if (substr($k, 0, 2) == "u." && $k != $login) {
                $tchar = explode("|", $loc_i[$tc . "gate"][$k]["char"]);
                if (strpos($tchar[0], "*") === false) {
                    $tclan = "";
                } else {
                    $tclan = substr($tchar[0], strpos($tchar[0], "*") + 1,
                        strrpos($tchar[0], "*") - strpos($tchar[0], "*") - 1);
                }
                if ($tclan != $clan && strpos($d[0], ":" . $k . ":") === false) {
                    manageNPC($login, $loc, $ctele);

                    return;
                }
            }
        }
    }
    if ($loc_i[$tc . "main"]) {
        foreach (array_keys($loc_i[$tc . "main"]) as $k) {
            if (substr($k, 0, 2) == "u." && $k != $login) {
                $tchar = explode("|", $loc_i[$tc . "main"][$k]["char"]);
                if (strpos($tchar[0], "*") === false) {
                    $tclan = "";
                } else {
                    $tclan = substr($tchar[0], strpos($tchar[0], "*") + 1,
                        strrpos($tchar[0], "*") - strpos($tchar[0], "*") - 1);
                }
                if ($tclan != $clan && strpos($d[0], ":" . $k . ":") === false) {
                    manageNPC($login, $loc, $ctele);

                    return;
                }
            }
        }
    }
    if ($loc_i[$tc . "tron"]) {
        foreach (array_keys($loc_i[$tc . "tron"]) as $k) {
            if (substr($k, 0, 2) == "u." && $k != $login) {
                $tchar = explode("|", $loc_i[$tc . "tron"][$k]["char"]);
                if (strpos($tchar[0], "*") === false) {
                    $tclan = "";
                } else {
                    $tclan = substr($tchar[0], strpos($tchar[0], "*") + 1,
                        strrpos($tchar[0], "*") - strpos($tchar[0], "*") - 1);
                }
                if ($tclan != $clan && strpos($d[0], ":" . $k . ":") === false) {
                    manageNPC($login, $loc, $ctele);

                    return;
                }
            }
        }
    }
    if ($loc_i[$tc . "sklad"]) {
        foreach (array_keys($loc_i[$tc . "sklad"]) as $k) {
            if (substr($k, 0, 2) == "u." && $k != $login) {
                $tchar = explode("|", $loc_i[$tc . "sklad"][$k]["char"]);
                if (strpos($tchar[0], "*") === false) {
                    $tclan = "";
                } else {
                    $tclan = substr($tchar[0], strpos($tchar[0], "*") + 1,
                        strrpos($tchar[0], "*") - strpos($tchar[0], "*") - 1);
                }
                if ($tclan != $clan && strpos($d[0], ":" . $k . ":") === false) {
                    manageNPC($login, $loc, $ctele);

                    return;
                }
            }
        }
    }
}