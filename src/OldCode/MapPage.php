<?php
/**
 * @copyright Copyright (C) 2016-2017. Max Dark maxim.dark@gmail.com
 * @license   MIT; see LICENSE.txt
 */

// для вывода картинки использует m.php!!! (чтобы лишний раз не обращаться к игре)

namespace MaxDark\Amulet\OldCode;

class MapPage
{
    /**
     * @param string $location
     * @param array $game
     * @param int $map_type
     * @param string $PHP_SELF
     * @param string $sid
     *
     * @return string
     */
    public static function buildPage($location, $game, $map_type, $PHP_SELF, $sid)
    {
        $char_coord = MapTool::calculateCoordinates($location);
        $flag_coord = MapTool::calculateCoordinates($game["floc"]);

        $description = [
            "основной территории.",
            "территории Ансалона.",
            "Волчьем острове."
        ];

        srand((float)microtime() * 10000000);
        $stmp = '<p align="center">' . "<img alt=\"map\" src=\"m.php?l=$location&amp;f=" . $game["floc"] .
            "&amp;img=1&amp;r=" . rand(99, 999) . "&amp;bw=$map_type\"/>" .
            "<br/><a href=\"$PHP_SELF?sid=$sid\">В игру</a></p>";
        $stmp .= "<p>Вы на " . $description[$char_coord[0]];
        if (empty($game["floc"])) {
            $fc = "неизвестно у кого (попробуйте обновить карту) ";
        } else {
            if (empty($game["fid"])) {
                $fc = "сейчас никому не принадлежит ";
            } else {
                $fc = "у " . $game["fchar"] . " ";
            }
        }
        $stmp .= '<br/>Флаг лидерства [<a href="m.php?flag=1">?</a>] ' . $fc;
        if ($flag_coord[0] != $char_coord[0]) {
            $stmp .= "на " . $description[$flag_coord[0]];
        }

        $stmp .= '<br/><a href="m.php?info=1">Помощь</a>';

        return $stmp;
    }
}
