<?php

$datos = json_decode(urldecode($_POST['datos']), true);

$nombre = filter_input(INPUT_POST, 'nombre');
$password = filter_input(INPUT_POST, 'password');

if ($nombre != getenv('NOMBRE_USUARIO') || $password != getenv('PASSWORD_USUARIO')) {
    echo 'error';
    return;
} else {
    $d = urldecode($_POST['datos']);
    $resultado = shell_exec('python ../scripts/arduinojson.py ' . $d);
    echo $resultado;
    return;
}
