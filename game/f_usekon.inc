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
 * @global tchar
 * @global id
 */
if ($char[8]) {
    msg("Вы призрак, лошадь вас боится и не подпускает близко");
}
if ( ! isset($loc_i[$loc][$take])) {
    msg("<p>Рядом нет этого коня");
}
if ($char[12]) {
    msg("Вы и так на коне");
}
if ( ! isset($loc_i[$loc][$take]["owner"])) {
    msg("Этот конь не приручен");
}
$owner = explode("|", $loc_i[$loc][$take]["owner"]);
if ($owner[0] != $login && $owner[1] != $login) {
    msg("Этот конь не принадлежит вам");
}
$tc                          = explode("|", $loc_i[$loc][$take]["char"]);
$char[12]                    = "1:" . $tc[1];
$char[6]                     = time() + 3;
$loc_i[$loc][$login]["char"] = implode("|", $char);
calcparam($loc, $login);
addjournal($loc, "all", $char[0] . " сел на лошадь", $login);
if (isset($loc_i[$loc][$take]["name"])) {
    $loc_i[$loc][$login]["name"] = $loc_i[$loc][$take]["name"];
}
unset($loc_i[$loc][$take]);
msg("Вы сели на лошадь и теперь вы всадник");