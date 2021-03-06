<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */

// ступка смешивает ингридиенты и бутылку с водой, получаем зелье

$arr = [    // id, name, dificalt -%, count, need_title, need_id
            1 => ["i.f.k.verh", "копченая верхоплавка", 10, 1, "верхоплавка", "i.f.verh"],
            2 => ["i.f.k.pesk", "копченый пескарь", 20, 1, "пескарь", "i.f.pesk"],
            3 => ["i.f.k.karas", "копченый карась", 10, 1, "карась", "i.f.karas"],
            4 => ["i.f.k.sorozh", "копченая сорожка", 20, 1, "сорожка", "i.f.sorozh"],
            5 => ["i.f.k.jaz", "копченый язь", 20, 1, "язь", "i.f.jaz"],
            6 => ["i.f.k.wjuka", "копченая щука", 40, 1, "щука", "i.f.wjuka"],
            7 => ["i.f.k.som", "копченый сом", 30, 1, "сом", "i.f.som"],

];

$skills = explode("|", $loc_i[$loc][$login]["skills"]);

function tsret($s)
{
    if ($s > 0) {
        return $s;
    } else {
        return 0;
    }
}

if ( ! $to || ! isset($arr[$to])) {
    $stmp = "Выберите что приготовить:";
    foreach (array_keys($arr) as $i) {
        $stmp .= "\n<br/><a href=\"$PHP_SELF?sid=$sid&use=$use&to=$i\">" . $arr[$i][1] . " (" . $arr[$i][3] . " " .
                 $arr[$i][4] . ", шанс: " . tsret($skills[30] * 20 - $arr[$i][2]) . "%)</a>";
    }
    msg($stmp);
}

if ($skills[30] * 20 - $arr[$to][2] > 0) {
    if (manageItems($loc, $login, "", "i.log", "count") == 0) {
        msg("Необходима ветка (которую вы можете срезать с любого дерева)");
    }
    $char[6]                     = time() + 15;
    $loc_i[$loc][$login]["char"] = implode("|", $char);

    manageItems($loc, $login, "", $arr[$to][5], $arr[$to][3], "items", "items", 1, 0, 1);    // удаляем ингридиенты
    manageItems($loc, $login, "", "i.log", 1, "items", "items", 1, 0, 1);            // удаляем ветку
    if (rand(0, 100) < $skills[30] * 20 - $arr[$to][2]) {
        addjournal($loc, $login, "Вы приготовили " . $arr[$to][1]);
        addjournal($loc, "all", $char[0] . " приготовил " . $arr[$to][1], $login);
        manageItems($loc, "", $login, $arr[$to][0], 1);
        if (round($arr[$to][2] / 10)) {
            addexp($loc, $login, round(rand(0, $arr[$to][2] / 10)));
        }
    } else {
        manageItems($loc, "", $login, "i.f.b.empty", 1);
        addjournal($loc, $login, "У вас сгорел" . $arr[$to][1]);
        addjournal($loc, "all", $char[0] . " сжег " . $arr[$to][1], $login);
    }

} else {
    addjournal($loc, $login, "Ваш навык повора слишком низок");
}