<?php

$ruta = '/home/pi/artika/';
$nombre = filter_input(INPUT_POST, 'nombre');
$password = filter_input(INPUT_POST, 'password');
$id = filter_input(INPUT_POST, 'id');
$orden = filter_input(INPUT_POST, 'orden');

$array = [0, 4, 17, 27, 22, 10, 9, 11, 5, 6, 13, 19, 26, 14, 15, 18, 23, 24, 25, 8, 7, 12, 16, 20, 21];
$array_invertido = [4, 17];
$array_comprobar = array_diff($array, $array_invertido);

if (!in_array($array[$id], $array_comprobar)) {
    $orden = $orden == 0 ? 1: 0;
}

if ($nombre != getenv('NOMBRE_USUARIO') || $password != getenv('PASSWORD_USUARIO')) {
    echo 'error';
    return;
} else {
    exec("$ruta/scripts/orden.sh $array[$id] $orden", $res);
    if ($res[0] == 1) {
    echo 'ok';
    } else {
        echo 'error';
    }
}


