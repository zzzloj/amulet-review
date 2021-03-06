<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global loc_t
 * @global loc_tt
 * @global game
 * @global sid
 * @global scroll
 * @global char
 * @global to
 * @global use
 * @global id
 */
// кастинг заклинаний && $login!="u.qv"  && substr($use,0,4)=='i.r.'
$tet  = substr($use, 0, 4);
$macr = explode("|", $loc_i[$loc][$login]['macrol']);
if ((strpos($loc_i[$loc][$login]["items"], "i.magicbook:") === false) && $login != "u.qv" &&
    substr($use, 6, 8) != 'godanger' && substr($use, 4, 4) != 'holy' && substr($macr[1], 0, 2) != 'i.' &&
    (substr($use, 0, 4) == 'm.w.' || substr($use, 0, 4) == 'm.s.')
) {
    msg("Чтобы использовать заклинание, у вас в  рюкзаке должна быть книга магии! $macr[1]  ");
}
//if (substr($use,0,4)=="i.r.") msg("ок");
//if ($use{3}=="r") msg("ok");
//if (substr($use,0,3)!="i.r") msg("у вас нет руны");

if ($use{2} > 0 && $use{2} < 10) {
    $tm = explode("|", $loc_i[$loc][$login]["magic"]);
    $tc = intval($use{2}) - 1;
    if ($tm[$tc] && ((strpos($loc_i[$loc][$login]["items"], "i.magicbook:") !== false) || $login == "u.qv" ||
                     substr($use, 6, 8) == 'godanger' || substr($use, 4, 4) == 'holy')
    ) {
        $use                           = substr($tm[$tc], 0, strpos($tm[$tc], ":"));
        $loc_i[$loc][$login]["macrol"] = "use|$use|to|$to";
    } else {
        msg("У вас нет книги магии или в вашей книге заклинаний нет заклинания под номером " . ($tc + 1));
    }
}

$magic = findItemByBaseId($use);
if ( ! $scroll) {
    if (strpos($loc_i[$loc][$login]["magic"], $use . ":") === false) {
        msg("В вашей книге заклинаний нет " . $magic[0] . ", найдите NPC, который поможет его изучить.");
    }
}

// нужна ли цель
if (($magic[6] && $to) || ! $magic[6]) {
    if ($magic[6] && $to && ! isset($loc_i[$loc][$to]) && strpos($loc_i[$loc][$login]["items"], $to . ":") === false ||
        substr($use, 0, 6) == "m.w.a." && count($loc_i[$loc]) == 1
    ) {
        addjournal($loc, $login, "Нет цели");
    } else {
        // хватает ли маны
        if ($char[3] >= $magic[1]) {
            // из книги
            if ($scroll || ! $scroll && time() > intval(preg_replace('/.*' . $use . ':(\d+).*/', "\\1",
                        $loc_i[$loc][$login]["magic"]))
            ) {

                $skills = explode("|", $loc_i[$loc][$login]["skills"]);
                // вероятность кастинга
                $cast = ($skills[13] * 0.5 + $skills[2] * 1.5) * 10 - $magic[2] * 10 + 10 -
                        (max($skills[0], 2) - 2) * 4;
                if ($char[12]) {
                    $cast -= 10;
                }
                if ($game["fid"] == $login && $game["floc"] == $loc) {
                    $cast += 20;
                }    // флаг
                if ($login == "u.qv") {
                    $skills[0] = 1;
                    $cast      = 100;
                }
                if ($cast > 95) {
                    $cast = 95;
                }
                if ($cast > 0 && $skills[13]) {
                    $char[3] -= $magic[1];
                    $char[6]                     = time() + $magic[8] + 3 - $skills[1] + (max($skills[0], 2) - 2) * 4;
                    $loc_i[$loc][$login]["char"] = implode("|", $char);
                    // обновляем период
                    if ( ! $scroll) {
                        if (substr($use, 0, 4) == "m.w.") {
                            $tper = time() + $magic[9] + (max($skills[0], 2) - 2) * 1200;
                        } else {
                            $tper = time() + $magic[9];
                        }
                        $loc_i[$loc][$login]["magic"] = preg_replace('/' . $use . ':(\d+)/', $use . ":" . $tper,
                            $loc_i[$loc][$login]["magic"]);
                    }
                    // удаляем скролл
                    if ($scroll && substr($scroll, 0, 4) == 'i.m.') {
                        manageItems($loc, $login, "", $scroll, 1, "items", "items", 1, -1, 1);
                    }
                    // произносим заклинание
                    if ($magic[3]) {
                        $tw = $char[0] . ": " . $magic[3];
                        if (substr($use, 0, 4) == "m.w." && substr($loc_i[$loc][$login]["def"], 0, 5) == "p.d.c") {
                            $tw .= "(концентрация)";
                        }
                        addjournal($loc, "all", $tw);
                    }
                    if (rand(0, 100) <= $cast) {    // удалось
                        // все заклинания
                        if (substr($use, 0, 4) == "m.w.") {
                            include "plugin/m.w.inc";
                        } elseif (substr($use, 0, 6) == "m.heal") {
                            include "plugin/m.heal.inc";
                        } elseif (substr($use, 0, 4) == "m.s.") {
                            include "plugin/m.s.inc";
                        } else {
                            $inc_plugin = "plugin/" . $use . ".inc"; // остальные в файлах
                            if (file_exists($inc_plugin)) {
                                include $inc_plugin;
                            } else {
                                die("err: no plugin/" . $use . ".inc");
                            }

                        }

                    } else {
                        addjournal($loc, $login, "Заклинание сорвалось");
                        addjournal($loc, "all", $char[0] . "(заклинание сорвалось)", $login);
                        $loss = 1;
                        if (substr($use, 0, 4) == "m.w.") {
                            include "plugin/m.w.inc";
                        }
                    }
                } else {
                    addjournal($loc, $login, "Слишком слабый навык магии");
                }
            } else {
                addjournal($loc, $login, "Период " . $magic[0] . " не истек (еще " .
                                         (round((intval(preg_replace('/.*' . $use . ':(\d+).*/', "\\1",
                                                             $loc_i[$loc][$login]["magic"])) - time()) / 60) + 1) .
                                         " минут)");
            }
        } else {
            addjournal($loc, $login, "Недостаточно маны");
        }
    }// нет цели
} else {
    $list = 'all';
}    // нужна цель