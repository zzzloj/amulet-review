<?php
/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global use
 * @global char
 */
// выбивает всадника из седла

if (isset($loc_i[$loc][$to]) && substr($to, 0, 2) == 'u.' && $to != $login) {
    $tchar = explode("|", $loc_i[$loc][$to]["char"]);
    if ($tchar[12]) {
        if ( ! $tatk) {    // если магией, то атакуем, чтобы посчитать крим, при приеме нет
            $mchar                       = explode("|", $loc_i[$loc][$login]["char"]);
            $ttime                       = $mchar[6];
            $mchar[6]                    = 0;
            $loc_i[$loc][$login]["char"] = implode("|", $mchar);
            $war                         = explode("|", $loc_i[$loc][$login]["war"]);
            $war[0]                      = 100;
            $war[1]                      = 0;
            $war[2]                      = 0;
            $war[3]                      = 7;
            $war[4]                      = 0;
            $war[12]                     = "ударом";
            $war[14]                     = "";
            $war                         = implode("|", $war);
            attack($loc, $login, $to, $war);
            $mchar                       = explode("|", $loc_i[$loc][$login]["char"]);
            $mchar[6]                    = $ttime;
            $loc_i[$loc][$login]["char"] = implode("|", $mchar);
        }
        $tc                       = explode(":", $tchar[12]);
        $tchar[12]                = "";
        $tchar[6]                 = time() + 5;
        $loc_i[$loc][$to]["char"] = implode("|", $tchar);
        calcparam($loc, $to);
        $npc    = loadNpcById("n.a.losh");
        $tc1    = explode("|", $npc["char"]);
        $tc1[5] = time();
        if ($tc[1] < $tc1[1]) {
            $tc1[1] = $tc[1];
        }
        if (isset($loc_i[$loc][$to]["name"])) {
            $tc1[0] .= " " . $loc_i[$loc][$to]["name"];
            $npc["name"] = $loc_i[$loc][$to]["name"];
            unset($loc_i[$loc][$to]["name"]);
        }
        $npc["char"]                               = implode("|", $tc1);
        $npc["owner"]                              = $to . "|" . $to . "|0|" . (time() + 60 * 60) . "|1";
        $loc_i[$loc]["n.a.losh." . rand(99, 9999)] = $npc;
        addjournal($loc, "all", $tchar[0] . " выбит из седла", $to);
        addjournal($loc, $to, "Вы выбиты из седла!");
    } else {
        addjournal($loc, $login, "Выбить из седла можно только всадника");
    }
} else {
    addjournal($loc, $login, "Выбить из седла можно только игроков");
}
