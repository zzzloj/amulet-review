<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global to
 * @global game
 * @global sid
 * @global PHP_SELF
 * @global char
 * @global up
 * @global down
 * @global items
 */
// перемещение в инвентори
if ($up) {
    if (strpos($loc_i[$loc][$login]["items"], $up . ":") === false) {
        msg("Нет такого предмета");
    }
    for ($i = 0; $i < count($items); $i++) {
        if (strpos($items[$i], $up . ":") !== false) {
            break;
        }
    }
    if ($i == 0) {
        array_push($items, $items[$i]);
        array_shift($items);
    } else {
        $tc            = $items[$i - 1];
        $items[$i - 1] = $items[$i];
        $items[$i]     = $tc;
    }
    $loc_i[$loc][$login]["items"] = implode("|", $items);
    msg("Предмет передвинут вверх.");
}
if ($down) {
    $up = $down;
    if (strpos($loc_i[$loc][$login]["items"], $up . ":") === false) {
        msg("Нет такого предмета");
    }
    for ($i = 0; $i < count($items); $i++) {
        if (strpos($items[$i], $up . ":") !== false) {
            break;
        }
    }
    if ($i == count($items) - 1) {
        array_unshift($items, $items[$i]);
        array_pop($items);
    } else {
        $tc            = $items[$i + 1];
        $items[$i + 1] = $items[$i];
        $items[$i]     = $tc;
    }

    $loc_i[$loc][$login]["items"] = implode("|", $items);
    msg("Предмет передвинут вниз.");
}