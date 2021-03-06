<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */
// шлифует указанный камень, набор может сломаться

if ($to) {
    if (substr($to, 0, 4) != "i.c." || substr($to, strlen($to) - 5) == ".good") {
        msg("Шлифовать можно только неограненные драгоценные камни");
    }
    $item = findItemByBaseId($to);
    if (intval(preg_replace('/.*' . $to . ':(\d+).*/', "\\1", $loc_i[$loc][$login]["items"])) < 1) {
        msg("У вас нет " . $item[0] . ", чтобы отшлифовать его");
    }

    $skills = explode("|", $loc_i[$loc][$login]["skills"]);
    if ($skills[28] > 0) {
        $char[6]                     = time() + 6;
        $loc_i[$loc][$login]["char"] = implode("|", $char);

        if (rand(0, 100) < $skills[28] * 10) {
            manageItems($loc, $login, "", $to, 1);
            manageItems($loc, "", $login, $to . ".good", 1);
            addjournal($loc, $login, "Вы отшлифовали камень");
            addjournal($loc, "all", $char[0] . " отшлифовал камень", $login);
            addexp($loc, $login, rand(0, 2));
        } else {
            addjournal($loc, $login, "Вам не удалось отшлифовать камень");
            addjournal($loc, "all", $char[0] . " не смог отшлифовать камень", $login);
        }

        // шлифовалка может сломаться всегда 5%
        if (rand(1, 100) <= 5) {
            addjournal($loc, $login, "Вы сломали набор для шлифования камней");
            addjournal($loc, "all", $char[0] . " сломал набор для шлифования камней", $login);
            manageItems($loc, $login, "", "i.set.shlif", 1);
        }

    } else {
        addjournal($loc, $login, "Ваш навык ювелира равен 0, вы не умеете обрабатывать камни");
    }

} else {
    $list = 'all';
}    // выведем ниже список целей