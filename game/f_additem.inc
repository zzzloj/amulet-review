<?php
global $g_destroy, $loc_i;

if ($count != "count") {
    $count = intval($count);
    if (gettype($count) != "integer" || $count == 0) {
        msg("Количество равно " . $count);
        if ($journal && $to) addjournal($loc, $to, "Количество равно " . $count);
        $res = 0;
        return 0;
    }
}
if ($time_delete == -1) $time_delete = $g_destroy;
if (strpos($item, "_") !== false) $tk = substr($item, 0, strpos($item, "_")); else $tk = $item;
if (substr($item, 0, 5) == "i.rr.") $title = explode("|", "руна|50"); else if (!file_exists("items/" . $tk)) {
    $res = 0;
    return 0;
} else {
    $title = explode("|", implode("", file("items/" . $tk)));
}
$title = $title[0];
if ($from && $from != "loc" && !isset($loc_i[$loc][$from])) {
    if ($journal && $to) addjournal($loc, $to, "Не от кого забрать " . $title);
    $res = 0;
    return 0;
}
if ($to && $to != "loc" && !isset($loc_i[$loc][$to])) {
    if ($journal && $from) addjournal($loc, $from, "Некому передать " . $title);
    $res = 0;
    return 0;
}

// получение кол-ва
if ($count == "count") {
    if ($from == "loc") {
        if (!isset($loc_i[$loc][$item])) {
            $res = 0;
            return 0;
        } else {
            $tmp = explode("|", $loc_i[$loc][$item]);
            $res = $tmp[1];
            return $tmp[1];
        }
    } else {
        $res = intval(preg_replace('/.*' . $item . ':(\d+).*/', "\\1", $loc_i[$loc][$from][$ft]));
        return $res;
    }
}

if ($item == "i.q.pjpt" || $item == "i.q.pdeath") if (substr($to, 0, 2) == "u." && (strpos($loc_i[$loc][$to][$tt], $item) !== false || $count > 1)) msg("У вас уже есть " . $title . ", нельзя хранить более одного");
if ($item == "i.q.ssword" && substr($to, 0, 2) == "u.") {
    $tcs = intval(preg_replace('/.*' . $item . ':(\d+).*/', "\\1", $loc_i[$loc][$to][$tt]));
    if ($tcs > 1 || $count > 2 || $tcs == 1 && $count == 2) msg("Можно держать одновременно не более 2 стеклянных мечей");
}
if ($to == $from && ($ft == "bank" || $tt == "bank") && substr($to, 0, 2) == "u." && strlen($loc_i[$loc][$to][$tt]) > 800 && strpos($loc_i[$loc][$to][$tt], $item . ":") === false) msg("Нет места для " . $title);
if (substr($item, 0, 4) == "i.s." && (substr($to, 0, 2) == "u." || substr($from, 0, 2) == "u.")) msg("Нельзя передать");

if ($from) {
    if ($from == "loc") {
        if (!isset($loc_i[$loc][$item])) {
            if ($journal && $to) addjournal($loc, $to, $title . " отсутствует");
            $res = 0;
            return 0;
        } else {
            $tmp = explode("|", $loc_i[$loc][$item]);
            if ($tmp[1] < $count) {
                if ($journal && $to) addjournal($loc, $to, "Количество " . $title . " меньше, чем " . $count);
                $res = 0;
                return 0;
            }
            $tmp[1] -= $count;
            if ($tmp[1] == 0) unset($loc_i[$loc][$item]); else $loc_i[$loc][$item] = implode("|", $tmp);
        }
    }

    if ($from != "loc") {
        if (substr($from, 0, 6) == "i.s.d.") $d = 1; else $d = 0;
        if (!$d) {
            $ftitle = explode("|", $loc_i[$loc][$from]["char"]);
            $ftitle = $ftitle[0];
            $items = $loc_i[$loc][$from][$ft];
        } else {
            $tdied = explode("|", $loc_i[$loc][$from]);
            $items = str_replace(",", "|", $tdied[3]);
        }
        $items = preg_replace("/\|{2,}/", "|", $items);
        if (substr($items, 0, 1) == "|") $items = substr($items, 1);
        if (substr($items, strlen($items) - 1, 1) == "|") $items = substr($items, 0, strlen($items) - 1);

        $tcount = intval(preg_replace('/.*' . $item . ':(\d+).*/', "\\1", $items));
        if ($tcount == 0) {
            if ($msg) msg("У вас нет " . $title);
            if ($journal && $to) addjournal($loc, $to, "Количество " . $title . " равно нулю");
            if ($journal && !$d) addjournal($loc, $from, "У вас нет " . $title);
            $res = 0;
            return 0;
        } else {
            if ($tcount < $count) {
                if ($msg) msg("У вас недостаточно " . $title . " (надо " . $count . ")");
                if ($journal && $to) addjournal($loc, $to, "Количество " . $title . " меньше, чем " . $count);
                if ($journal && !$d) addjournal($loc, $from, "У вас количество " . $title . " меньше, чем " . $count);
                $res = 0;
                return 0;
            }
            if ($tcount == $count && strpos($items, "=" . $item . ":" . $tcount) === false) {    // удаляем предмет (кроме торговцев, у кот. ver|min|max=id:count), проверяем equip
                $items = preg_replace('/\|?' . $item . ':(\d+)/', "", $items);
                $equip = $loc_i[$loc][$from]["equip"];
                $tbp = strpos($loc_i[$loc][$from]["equip"], $item);
                if ($tbp === false) $tb = "a"; else $tb = $loc_i[$loc][$from]["equip"]{$tbp + strlen($item)};
                if (!$d && $equip && ($tb == "|" || $tb == "")) {
                    $equip = preg_replace('/' . $item . '\|?/', "", $equip);
                    $equip = preg_replace("/\|{2,}/", "|", $equip);
                    if (substr($equip, 0, 1) == "|") $equip = substr($equip, 1);
                    if (substr($equip, strlen($equip) - 1, 1) == "|") $equip = substr($equip, 0, strlen($equip) - 1);
                    $loc_i[$loc][$from]["equip"] = $equip;
                    $loc_i[$loc][$from][$ft] = $items;
                    calcparam($loc, $from);
                }
            } else {
                $tcount -= $count;
                $items = preg_replace('/' . $item . ':(\d+)/', $item . ":" . $tcount, $items);
            }
            if (!$d) $loc_i[$loc][$from][$ft] = $items; else {
                if (strpos($tdied[0], "*") === false) $clan = ""; else $clan = substr($tdied[0], strpos($tdied[0], "*") + 1, strrpos($tdied[0], "*") - strpos($tdied[0], "*") - 1);
                if ($to) $tc = explode("|", $loc_i[$loc][$to]["char"]); else $tc[0] = "";
                if (strpos($tc[0], "*") === false) $clan1 = ""; else $clan1 = substr($tc[0], strpos($tc[0], "*") + 1, strrpos($tc[0], "*") - strpos($tc[0], "*") - 1);
                if ($tc[13]) $wife = substr($from, 6, strrpos($from, ".") - 6) == substr($tc[13], 0, strlen(substr($from, 6, strrpos($from, ".") - 6))); else $wife = 0;
                if (!$tdied[1] && $to && substr($from, 0, strlen("i.s.d." . $to)) != "i.s.d." . $to && (!$clan1 || ($clan1 && $clan1 != $clan)) && !$wife && substr($from, 0, 11) != "i.s.d.u.qv.") docrim($loc, $to, "мародер");
                $tdied[3] = str_replace("|", ",", $items);
                $loc_i[$loc][$from] = implode("|", $tdied);
            }
            if ($journal && $to == "loc") {
                if ($journal && !$d) addjournal($loc, $from, "Вы бросили " . $count . " " . $title);
                if ($journal && !$d) addjournal($loc, "all", $ftitle . " бросил " . $count . " " . $title, $from);
            }
            if ($journal && $to != "loc") if ($journal && !$d) addjournal($loc, $from, "Вы потеряли " . $count . " " . $title);
        }
    }
}


if ($to) {

    if ($to != "loc") {
        if (substr($to, 0, 6) == "i.s.d.") $d = 1; else $d = 0;
        if (!$d) {
            $ftitle = explode("|", $loc_i[$loc][$to]["char"]);
            $ftitle = $ftitle[0];
            $items = $loc_i[$loc][$to][$tt];
        } else {
            $tdied = explode("|", $loc_i[$loc][$to]);
            $items = str_replace(",", "|", $tdied[3]);
        }

        $items = preg_replace("/\|{2,}/", "|", $items);
        if (substr($items, 0, 1) == "|") $items = substr($items, 1);
        if (substr($items, strlen($items) - 1, 1) == "|") $items = substr($items, 0, strlen($items) - 1);

        if (substr($to, 0, 2) == "u.") {
            if (strlen($items) > 800 && strpos($items, $item . ":") === false) {
                addjournal($loc, $to, "Не хватает места, " . $title . " упал вам под ноги");
                $to = "loc";
            }
        }

        if ($to != "loc") {
            $tcount = intval(preg_replace('/.*' . $item . ':(\d+).*/', "\\1", $items));

            if ($tcount == 0) {    // торговцам новый предмет в банк не добавляем
                if (strpos($items, "=" . $item . ":" . $tcount) === false) if ($items == "") $items = $item . ":" . $count; else $items .= "|" . $item . ":" . $count;
            } else {
                $tcount += $count;
                $items = preg_replace('/' . $item . ':(\d+)/', $item . ":" . $tcount, $items);
            }
            if (!$d) $loc_i[$loc][$to][$tt] = $items; else {
                $tdied[3] = str_replace("|", ",", $items);
                $loc_i[$loc][$to] = implode("|", $tdied);
            }
            if ($journal && $from == "loc") {
                if ($journal && !$d) addjournal($loc, $to, "Вы подняли " . $count . " " . $title);
                if ($journal && !$d) addjournal($loc, "all", $ftitle . " поднял " . $count . " " . $title, $to);
            }
            if ($journal && $from != "loc") if ($journal && !$d) addjournal($loc, $to, "Вы получили " . $count . " " . $title);
        }
    }

    if ($to == "loc") {
        if (!isset($loc_i[$loc][$item])) {
            $loc_i[$loc][$item] = $title . "|" . $count . "|" . (time() + $time_delete);
        } else {
            $tmp = explode("|", $loc_i[$loc][$item]);
            $tmp[1] += $count;
            $tmp[2] = time() + $time_delete;
            $loc_i[$loc][$item] = implode("|", $tmp);
        }
    }
}
$res = 1;
return 1;    // ок

