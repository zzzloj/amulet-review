<?php

use MaxDark\Amulet\OldCode\DBOperations;
use MaxDark\Amulet\OldCode\PageType;

$nn = Request('nn');
if ( ! preg_match('|^[-0-9a-z_]+$|i', $nn)) {
    msg("Неверный синтаксис в логине<br /><anchor>Назад<prev/></anchor>", 'Ошибка', 0, PageType::GUEST);
}

if (DBOperations::nicknameExists($nn)) {
    msg('Этот логин уже занят.<br /><anchor>Назад<prev/></anchor>', 'Ошибка', 0, PageType::GUEST);
}
$stmp = <<<PAGE
</p><p align="center">            
<b>Логин:</b>
<br /><b>$nn</b><br />--------
<br /><b>Пароль</b>:
<br />(a-Z,0-9)
<br /><input name="password" emptyok="true" type="password" value="" maxlength="15" size="15"/>
<br /><b>Ваш Email адрес:</b>
<br /><input name="email" emptyok="true" type="text" maxlength="25" size="25"/> 
<br /><b>Пол персонажа</b>
<br /><select name="sex" value="m">
<option value="m">Муж.</option>
<option value="f">Жен.</option>
</select>
<br /><b>Возраст</b>
<br /><input name="age" format="*N" maxlength="2"/>
<br /><anchor title="next">Продолжить
<go href="?site=reg2" method="post">
<postfield name="nn" value="$nn"/>
<postfield name="email" value="$(email)"/>
<postfield name="pass" value="$(password)"/>
<postfield name="sex" value="$(sex)"/>
<postfield name="age" value="$(age)"/>
</go>
</anchor>
PAGE;
msg($stmp, "Регистрация", 0, PageType::GUEST);
