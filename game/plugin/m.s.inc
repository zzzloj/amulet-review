<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global item
 * @global loc_water1
 * @global loc_water2
 */

// до 10 минут

// проверим, чтобы в локации не было более 3 призванных существ, остальных отпустим
$counttmp = 0;
foreach (array_keys($loc_i[$loc]) as $i) {
    if (isset($loc_i[$loc][$i]["owner"]) && substr($i, 0, 4) == "n.s.") {
        $owner = explode("|", $loc_i[$loc][$i]["owner"]);
        if ($owner[0] == $login && substr($i, 0, 4) != "n.o.") {
            $counttmp++;
            if ($counttmp > 2) {
                $tchar = explode("|", $loc_i[$loc][$i]["char"]);
                addjournal($loc, $login, $tchar[0] . " покинул вас");
                if ($owner[4]) {
                    manageNPC($i, $loc, "");
                } else {
                    unset($loc_i[$loc][$i]["owner"]);
                }
            }
        }
    }
}
switch ($use) {
    case "m.s.wolf":
        $item = [
            "char" => "призванный волк|20|20|20|20|1|1||0|0||",
            "war" => "70|4|11|5|0|0|5|0|0|0|0|0|зубами|0||",
            "owner" => $login . "|" . $login . "|" . $login . "|" . (time() + rand(1 * 60, 10 * 60)) . "|1",
        ];
        break;
    case "m.s.tree":
        if (isset($loc_i[$loc]["i.s.tree"])) //не работает если нет деревьев
        {
            $item = [
                "char" => "призванное гиганское дерево|80|80|30|30|2|2||0|0||",
                "war" => "90|15|30|10|0|0|10|0|0|20|80|50|ветвями|0||",
                "owner" => $login . "|" . $login . "|" . $login . "|" . (time() + rand(1 * 60, 10 * 60)) . "|1",
            ];
        } else {
            msg("Рядом нет деревьев.");
        }
        break;
    case "m.s.volna":
        include __DIR__ . DIRECTORY_SEPARATOR . 'loc_water.inc';
        // работает только если есть вода
        if (strpos($loc_water1, $loc) !== false || strpos($loc_water2, $loc) !== false)
        {
            $item = [
                "char" => "призванная волна|80|80|30|30|2|2||0|0||",
                "war" => "90|15|30|10|0|0|10|0|0|20|80|50|струей воды|0||",
                "owner" => $login . "|" . $login . "|" . $login . "|" . (time() + rand(1 * 60, 10 * 60)) . "|1",
            ];
        } else {
            msg("Рядом нет воды.");
        }
        break;
    case "m.s.skeleton":
        $item = [
            "char" => "призванный скелет|30|30|20|20|1|1||0|0||",
            "war" => "65|5|16|6|0|0|10|0|0|0|0|0||0||",
            "owner" => $login . "|" . $login . "|" . $login . "|" . (time() + rand(1 * 60, 10 * 60)) . "|1",
        ];
        break;
    case "m.s.golem":
        $item = [
            "char" => "призванный голем|50|50|20|20|1|1||0|0||",
            "war" => "90|8|18|7|0|5|10|0|0|30|50|4||0||",
            "owner" => $login . "|" . $login . "|" . $login . "|" . (time() + rand(1 * 60, 10 * 60)) . "|1",
        ];
        break;
    case "m.s.fantom":
        $item = [
            "char" => "призванный фантом|50|50|1|1|1|1||0|0||",
            "war" => "100|4|12|4|||10|||10|70|40|мaгиeй|0||",
            "owner" => $login . "|" . $login . "|" . $login . "|" . (time() + rand(1 * 60, 10 * 60)) .
                "|1",
        ];
        break;
    case "m.s.tucha":
        $item = [
            "char" => "призванная грозовая туча|50|50|1|1|1|1||0|0||",
            "war" => "200|0|25|4|||10|||10|70|40|молнией|0||",
            "owner" => $login . "|" . $login . "|" . $login . "|" . (time() + rand(1 * 60, 10 * 60)) . "|1",
        ];
        break;
    case "m.s.demon":
        // демон crim и создавший его становится кримом.
        // если не от кого защищать создавшего,
        // то нападает на игроков, в том числе на создавшего :-)
        $item = [
            "char" => "призванный демон|80|80|20|20|1|1||0|1||",
            "war" => "95|10|25|7|0|3|10|0|0|20|70|8||0||",
            "owner" => $login . "|" . $login . "|" . $login . "|" . (time() + rand(1 * 60, 10 * 60)) . "|1",
        ];
        docrim($loc, $login, "вызвал демона");
        break;
    default:
        msg("Заклинания $use не существует");
        break;
}

$id = "n." . substr($use, 2) . "." . rand(1, 99);
while (isset($loc_i[$loc][$id])) {
    $id = "n." . substr($use, 2) . "." . rand(1, 99);
}

$loc_i[$loc][$id] = $item;
manageNPC($id, "", $loc);    // журнал
