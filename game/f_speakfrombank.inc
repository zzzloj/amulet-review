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
 */

if ($up || $down) {
    include "f_speakfrombankm.inc";
}

if ($speak == "n.t.bankir" && $char[14] != "t") {
    msg("Извини, услуги банка только для вступивших в Орден Тамплиера.");
}
if ($speak == "n.p.bankir" && $char[14] != "p") {
    msg("Ха, ты не не один из нас. Вначале стань настоящим пиратом, тогда и поговорим.");
}
// список
$items = explode("|", $loc_i[$loc][$login]["bank"]);
if ( ! $items) {
    msg("У вас в банке нет ни одного предмета", $tchar[0]);
}
$stmp = "";
if ( ! $start) {
    $start = 0;
}
$keys = array_keys($items);
for ($i = $start; $i < $start + $g_list && $i < count($keys); $i++) {
    if ($items[$keys[$i]]) {
        $k = explode(":", $items[$keys[$i]]);
        if (strpos($k[0], "_") !== false) {
            $ti = substr($k[0], 0, strpos($k[0], "_"));
        } else {
            $ti = $k[0];
        }
        if (substr($k[0], 0, 5) == "i.rr.") {
            $item = explode("|", "руна|50");
        } else {
            if (file_exists("items/" . $ti)) {
                $item = explode("|", (file_get_contents("items/" . $ti)));
            } else {
                die("err: no items/" . $k[0]);
            }
        }
        $item = $item[0];
        if (strpos($k[0], "..") !== false) {
            $item .= " *";
        }
        if ($k[1] > 1) {
            $item .= " (" . $k[1] . ")";
        }
        $stmp .= "\n<br/><anchor>" . $item . "<go href=\"#menu\"><setvar name=\"to\" value=\"" . $k[0] .
                 "\"/></go></anchor>";
    }
}
if ($stmp) {
    $stmp = "<p>Выберите предмет:" . $stmp;
} else {
    msg("У вас в банке нет ни одного предмета", $tchar[0]);
}
if ($start) {
    $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&speak=$speak&id=$id\">^ </a>";
}
if ($start + $g_list < count($keys)) {
    if ( ! $start) {
        $stmp .= "\n<br/>";
    }
    $stmp .= "<a href=\"$PHP_SELF?sid=$sid&speak=$speak&id=$id&start=" . ($start + $g_list) . "\">+ (" .
             (count($keys) - $start - $g_list) . ")</a>";
}
$stmp .= "\n</p>\n</card>\n<card id=\"menu\" title=\"Меню\">\n<p>\n<a href=\"$PHP_SELF?sid=$sid&speak=$speak&id=$id&start=$start&to=$(to)\">Забрать из банка</a>\n<br/><a href=\"$PHP_SELF?sid=$sid&look=$(to)\">Инфо</a>\n<br/><a href=\"$PHP_SELF?sid=$sid&speak=$speak&id=$id&up=$(to)\">[Вверх</a> | <a href=\"$PHP_SELF?sid=$sid&speak=$speak&id=$id&down=$(to)\">Вниз</a>]";
msg($stmp, $tchar[0]);