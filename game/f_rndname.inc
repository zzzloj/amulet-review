<?php
$arr_rndnames = array('cor', 'ur', 'ae', 'li', 'sim', 'na', 'vax', 'vin', 'lib', 'er', 'mac', 'cam', 'is', 'ta', 'gor', 'i', 'ca', 'um', 'mu', 'og', 'os', 'na', 'tru', 'ver', 'vay', 'an', 'as', 'prin', 'su', 'oc', 'dor', 'a', 'mor', 'ia', 'gon', 'ar', 'nor', 'ang', 'dai', 'mar', 'grace', 'van', 'dir', 'am', 'va', 'ber', 'em', 'je', 'tar', 'she', 'eru', 'ilu', 'rat', 'gil', 'do', 'ge', 'lad', 'le', 'go', 'bins', 'las', 'gim', 'li', 'fro', 'tor', 'tol', 'mab', 'den', 'va', 'dag', 'tir', 'na', 'nogt', 'es', 'ka', 'bur', 'du', 'ran', 'dal', 'ken', 'vap', 'dlo', 'negn', 'mur', 'kok', 'mel', 'rul', 'sa', 'ru', 'gan', 'uuk', 'map', 'blo', 'son', 'eva', 'nul', 'eng', 'zah', 'vat', 'obi', 'no', 'rip', 'bi', 'car', 'ma', 'lan', 'be', 'ril', 'log', 'raf', 'hill', 'nart', 'bosk', 'ir', 'gard', 'is', 'en', 'ged', 'gob', 'cri', 'sa', 'ru', 'man', 'shna', 'god', 're', 'vur', 'ar', 'tur', 'el', 'eri', 'ker', 'shed', 'gae', 'bol', 'der', 'desh', 'nol', 'nek', 'dur', 'vek', 'nang', 'zug', 'cup', 'ida', 'lum', 'ir', 'si', 'jai', 'kon', 'nel', 'jer', 'lorn', 'gan', 'fax', 'ber', 'sa', 'got', 'vald', 'lance', 'der', 'feld', 'kay', 'had', 'ja', 'gun', 'tal', 'nai', 'ven', 'det', 'nog', 'aro', 'kle', 'vam', 'dam', 'sic', 'erg', 'unk', 'ils', 'dol', 'dul', 'gu', 'arc', 'jin', 'shel', 'chri', 'chra', 'gec', 'apr', 'anu', 'al', 'van', 'a', 'e', 'si', 'an', 'na', 'u', 'ol', 'it', 'du', 'uv', 'ai', 'go', 'she', 'zu');
$stmp = "";
srand((float)microtime() * 10000000);        // FIX: на некоторых версия PHP надо, на нек. нет
while (strlen($stmp) < rand(4, 6)) $stmp .= $arr_rndnames[rand(0, count($arr_rndnames) - 1)];
$stmp{0} = strtoupper($stmp{0});