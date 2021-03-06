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
 * @global to
 * @global use
 * @global id
 */
// использование приемов

if (strpos($loc_i[$loc][$login]["equip"], "i.w.r.") !== false) {
    msg("Приемы можно использовать только в рукопашном бою или с холодным оружием ближнего боя");
}

if ($use{2} > 0 && $use{2} < 10) {
    $tm = explode("|", $loc_i[$loc][$login]["priem"]);
    $tc = intval($use{2}) - 1;
    if ($tm[$tc]) {
        $use                           = substr($tm[$tc], 0, strpos($tm[$tc], ":"));
        $loc_i[$loc][$login]["macrol"] = "use|$use|to|$to";
    } else {
        msg("У вас нет приема под номером " . ($tc + 1));
    }
}

$priem = findItemByBaseId($use);

if (strpos($loc_i[$loc][$login]["priem"], $use . ":") === false) {
    msg("Вы не знаете прием " . $priem[0] . ", найдите NPC, который поможет его изучить.");
}
if ($to == $login || ! $to) {
    msg("Нельзя применять прием к самому себе");
}

// для боевых всегда нужна цель, для защитных не действует период
if (substr($use, 0, 4) == "p.d." || substr($use, 0, 4) != "p.d." && isset($loc_i[$loc][$to])) {
    if (substr($use, 0, 4) == "p.d." ||
        time() > intval(preg_replace('/.*' . $use . ':(\d+).*/', "\\1", $loc_i[$loc][$login]["priem"]))
    ) {
        $skills = explode("|", $loc_i[$loc][$login]["skills"]);
        $war    = explode("|", $loc_i[$loc][$login]["war"]);
        // флаг
        if ($game["fid"] == $login && $game["floc"] == $loc) {
            $war[0] += 10;
        }
        $ihit = ($skills[2] - 1) * 10;    // штраф по интеллекту
        if ($char[12]) {
            $ihit += 10;
        }    // штраф если на коне
        // боевой
        if (substr($use, 0, 4) != "p.d.") {
            // период
            $loc_i[$loc][$login]["priem"] = preg_replace('/' . $use . ':(\d+)/', $use . ":" . (time() + $priem[1]),
                $loc_i[$loc][$login]["priem"]);
            $magic                        = $war;
            $magic[0] -= $ihit;

            switch ($use) {
                case "p.b":
                    $magic[1] = round($magic[1] * 0.7);
                    $magic[2] = round($magic[2] * 0.7);
                    $magic[3] = round($magic[3] * 0.5);
                    break;
                case "p.d":
                    $magic[0] -= 15;
                    $magic[3] = -1;
                    break;
                case "p.me":
                    $magic[0] -= 10;
                    $magic[3] = -1;
                    break;
                case "p.m":
                    $magic[1] = round($magic[1] * 0.7);
                    $magic[2] = round($magic[2] * 0.7);
                    $magic[0] += 40;
                    break;
                case "p.n":
                    $magic[1] = round($magic[1] * 0.6);
                    $magic[2] = round($magic[2] * 0.6);
                    break;
                case "p.r":
                    $magic[1] = round($magic[1] * 0.4);
                    $magic[2] = round($magic[2] * 0.4);
                    break;
                case "p.vw":
                    $magic[1] = round($magic[1] * 0.2);
                    $magic[2] = round($magic[2] * 0.2);
                    break;
                case "p.vs":
                    $magic[1] = round($magic[1] * 0.2);
                    $magic[2] = round($magic[2] * 0.2);
                    break;
                case "p.g":
                    $magic[0] -= 30;
                    if (strpos($loc_i[$loc][$login]["equip"], "i.w.") !== false) {
                        $magic[1] += $skills[0] * 2 + $skills[9];
                        $magic[2] += $skills[0] * 2 + $skills[9];
                    } else {
                        $magic[1] += $skills[0] + $skills[8];
                        $magic[2] += $skills[0] + $skills[8];
                    }
                    break;
                case "p.p":
                    $magic[0] -= 20;
                    if (strpos($loc_i[$loc][$login]["equip"], "i.w.") !== false) {
                        $magic[2] += $skills[0] * 3 + $skills[9] * 2;
                    } else {
                        $magic[2] += $skills[0] * 2 + $skills[8];
                    }
                    break;
                case "p.s":
                    $magic[0] -= 10;
                    if (strpos($loc_i[$loc][$login]["equip"], "i.w.") !== false) {
                        $magic[2] += $skills[0] * 2 + $skills[9];
                    } else {
                        $magic[2] += $skills[0] + $skills[8];
                    }
                    break;
            }

            if ($magic[0] < 1) {
                $magic[0] = 5;
            }
            if ($magic[0] > 95) {
                $magic[0] = 95;
            }
            if ($magic[1] < 0) {
                $magic[1] = 0;
            }
            if ($magic[2] < 0) {
                $magic[2] = 0;
            }

            attack($loc, $login, $to, implode("|", $magic), 1, 0, $use, $priem[0]);
            $char = explode("|", $loc_i[$loc][$login]["char"]);
            if ($use == "p.d") {
                attack($loc, $login, $to, implode("|", $magic), 1, 0, $use, $priem[0]);
                $char                        = explode("|", $loc_i[$loc][$login]["char"]);
                $char[6]                     = time() + $war[3];
                $loc_i[$loc][$login]["char"] = implode("|", $char);
            }
            if ($use == "p.me") {
                foreach ($loc_i[$loc] as $key => $i) {
                    if ($key != $login && $key != $to) {
                        attack($loc, $login, $key, implode("|", $magic), 1, 0, $use, $priem[0]);
                    }
                }
                $char                        = explode("|", $loc_i[$loc][$login]["char"]);
                $char[6]                     = time() + $war[3] * 2;
                $loc_i[$loc][$login]["char"] = implode("|", $char);
            }

            // проверки на выбивание
            if (isset($loc_i[$loc][$to])) {
                if ($loc_i[$loc][$to]["def"]) {
                    $tdef = explode("|", $loc_i[$loc][$to]["def"]);
                } else {
                    $tdef = [0, "", ""];
                }
                switch ($use) {
                    case "p.n":
                        if (rand(0, 100) <= $magic[0] - 40 &&
                            ($tdef[0] != "p.d.n" || $tdef[0] == "p.d.n" && rand(0, 100) > $tdef[3])
                        ) {
                            addjournal($loc, $to, "Вас оглушили!");
                            addjournal($loc, "all", substr($to, 2) . " оглушен!", $to);
                            $tc = explode("|", $loc_i[$loc][$to]["char"]);
                            $tc[6] = time() + 15;
                            $loc_i[$loc][$to]["char"] = implode("|", $tc);
                        }
                        if ($tdef[0] == "p.d.n") {
                            $loc_i[$loc][$to]["def"] = "";
                        }
                        break;
                    case "p.r":
                        if (rand(0, 100) <= $magic[0] - 70 &&
                            ($tdef[0] != "p.d.r" || $tdef[0] == "p.d.r" && rand(0, 100) > $tdef[3]) &&
                            strpos($loc_i[$loc][$to]["equip"], "i.w.") !== false
                        ) {
                            addjournal($loc, $to, "У вас выбито оружие!");
                            addjournal($loc, "all", "У " . substr($to, 2) . " выбито оружие!", $to);
                            manageItems($loc, $to, 'loc',
                                preg_replace('/.*?(i\.w\.[^\|]+).*/', "\\1", $loc_i[$loc][$to]["equip"]), 1, "items",
                                "items", 1, -1, 1);
                            $tc = explode("|", $loc_i[$loc][$to]["char"]);
                            $tc[6] = time() + 5;
                            $loc_i[$loc][$to]["char"] = implode("|", $tc);
                        }
                        if ($tdef[0] == "p.d.r") {
                            $loc_i[$loc][$to]["def"] = "";
                        }
                        break;
                    case "p.vw":
                        if (rand(0, 100) <= $magic[0] - 40 && strpos($loc_i[$loc][$to]["equip"], "i.a.s.") !== false) {
                            addjournal($loc, $to, "У вас выбит щит!");
                            addjournal($loc, "all", "У " . substr($to, 2) . " выбит щит!", $to);
                            manageItems($loc, $to, 'loc',
                                preg_replace('/.*?(i\.a\.s\.[^\|]+).*/', "\\1", $loc_i[$loc][$to]["equip"]), 1, "items",
                                "items", 1, -1, 1);
                            $tc = explode("|", $loc_i[$loc][$to]["char"]);
                            $tc[6] = time() + 5;
                            $loc_i[$loc][$to]["char"] = implode("|", $tc);
                        }
                        break;
                    case "p.vs":
                        if (rand(0, 100) <= $magic[0] - 50 &&
                            ($tdef[0] != "p.d.s" || $tdef[0] == "p.d.s" && rand(0, 100) > $tdef[3])
                        ) {
                            $tatk = 1;
                            require("plugin/m.kon.inc");
                        }
                        if ($tdef[0] == "p.d.s") {
                            $loc_i[$loc][$to]["def"] = "";
                        }
                        break;
                }
            }

        } else {
            // защитные
            if ($use == "p.d.p" && strpos($loc_i[$loc][$login]["equip"], "i.a.s.") === false) {
                msg("Щит должен находиться у вас в руках");
            }
            $loc_i[$loc][$login]["def"] = $use . "|" . $priem[0] . "|" . (time() + $priem[1]) . "|" .
                                          ($use == "p.d.c" ? $skills[2] * 16 : ($war[0] - $ihit));
            if ($use == "p.d.o") {
                $char[6]                     = time() + $priem[1];
                $loc_i[$loc][$login]["char"] = implode("|", $char);
            }
        }

    } else {
        addjournal($loc, $login, "Период " . $priem[0] . " не истек (еще " .
                                 (round((intval(preg_replace('/.*' . $use . ':(\d+).*/', "\\1",
                                                     $loc_i[$loc][$login]["priem"])) - time()) / 60) + 1) . " минут)");
    }
} else {
    addjournal($loc, $login, "Нет цели");
}