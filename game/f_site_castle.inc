<?php

use MaxDark\Amulet\OldCode\PageType;

/**
 * @param string $file
 *
 * @return mixed
 */
function load_data($file)
{
    return unserialize((file_get_contents($file)));
}

/**
 * @param string $d
 *
 * @return string
 */
function get_clan_name($d)
{
    return substr($d, strpos($d, "*") + 1, strrpos($d, "*") - strpos($d, "*") - 1);
}

/**
 * @param array $data
 *
 * @return string
 */
function get_clan($data)
{
    $d = explode("|", $data["d"]);

    return (strpos($d[0], "*") === false) ? '' : get_clan_name($d[0]);
}

/**
 * @param integer $id
 *
 * @return string
 */
function get_owner_message($id)
{
    $data = load_data("loc_i/c.{$id}.gate");
    if (empty($data['d'])) {
        $message = '[ошибка загрузки]';
    } else {
        $clan    = get_clan($data);
        $message = empty($clan) ? 'никому не принадлежит' : 'принадлежит клану ' . $clan;
    }

    return $message;
}

/**
 * @return string
 */
function get_castle_page()
{
    $names = [
        1 => 'Замок Санкастар',
        2 => 'Замок Мирра',
        3 => 'Замок Луен',
        4 => 'Замок Танатос',
        5 => 'Замок Вилло',
    ];

    $owners = [];
    foreach ($names as $id => $name) {
        $owners[] = "<b>$name</b>: " . get_owner_message($id);
    }

    return implode('<br/>' . PHP_EOL, $owners);
}

msg(get_castle_page(), "Замки", 0, PageType::GUEST);