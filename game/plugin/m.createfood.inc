<?php

/**
 * @global login
 * @global loc
 * @global loc_i
 * @global to
 * @global id
 * @global char
 */
$rnd = rand(0, 100);
if ($rnd <= 20) {
    $id = "i.f.apple";
}
if ($rnd > 20 && $rnd <= 35) {
    $id = "i.f.cabbage";
}
if ($rnd > 35 && $rnd <= 55) {
    $id = "i.f.bread";
}
if ($rnd > 55 && $rnd <= 75) {
    $id = "i.f.sandwich";
}
if ($rnd > 75 && $rnd <= 85) {
    $id = "i.f.mushroom";
}
if ($rnd > 85 && $rnd <= 100) {
    $id = "i.f.sausage";
}
// добавляем в локацию
manageItems($loc, "", "loc", $id, 1);