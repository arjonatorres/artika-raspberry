# Artika Raspberry
Archivos a instalar en una Raspberry Pi para poder usar la aplicación web [Artika](https://github.com/arjonatorres/artika). En la carpeta `arduino` está el código a subir al ***Arduino UNO***. Éste irá conectado a la Raspberry a través de un cable USB.

Para que funcione correctamente hay que tener una Raspberry Pi con las siguientes características:

## La distribución **Raspbian** instalada
Podéis descargarla en su sitio [oficial](https://www.raspberrypi.org/downloads/).

## Tener una ip fija dentro del router
Configurar el archivo `/etc/dhcpcd.conf` y añadir al final:
```bash
# Example static IP configuration:
interface eth0
static ip_address=192.168.1.15
#static ip6_address=fd51:42f8:caae:d92e::ff/64
static routers=192.168.1.1
static domain_name_servers=8.8.8.8
static domain_search=8.8.4.4
```
Si al usar el comando ifconfig os sale como nombre de red 'enx...', para cambiarlo a `eth0` añadir el siguiente archivo `/etc/udev/rules.d/70-persistent-net.rules` con el siguiente contenido:
```
SUBSYSTEM=="net", ACTION=="add", DRIVERS=="?*", ATTR{dev_id}=="0x0", ATTR{type}=="1", KERNEL=="eth*", NAME="eth0"
```

## Instalar y configurar Apache
Instalar apache con el siguiente comando: `sudo apt install apache2`.

Crear un enlace simbólico dentro de `/var/www/html` que apunte al directorio `web` de este proyecto. Usando el comando: `sudo ln -s $HOME/web .`

Cambiar el document root en el archivo `/etc/apache2/sites-available/000-default.conf` para que apunte al enlace simbólico que acabamos de crear:
```
DocumentRoot /var/www/html/web
```

Cambiar el puerto por defecto `80` por el `8082` por ejemplo, en los siguientes archivos:
* `/etc/apache2/ports.conf`
```
Listen 8082
```
* `/etc/apache2/sites-available/000-default.conf`
```
<VirtualHost *:8082>
```

Configurar el router para que el puerto 8082 apunte hacia la ip fija interna, p.e. `192.168.1.15`

## Dirección de internet
La dirección de internet habrá que introducirla en la aplicación en el apartado ***Servidor***. Yo usé [no-ip](https://www.noip.com/).

## Instalar php7
Instalar php con la versión 7 con el siguiente comando: `sudo apt install libapache2-mod-php7* php7.0-cli`

## Variables de entorno
Añadir las variables de entorno **NOMBRE_USUARIO** y **PASSWORD_USUARIO** en `/etc/apache2/envvars`. El *PASSWORD_USUARIO* debe ser el token de seguridad que te da la aplicación al guardar la *URL* y *puerto* en el apartado ***Servidor***.

## Cámara de videovigilancia
Para conectar una webcam a la Raspberry habrá que instalar el programa **Motion**: `sudo apt install motion`. Después editamos el archivo de configuración con el siguiente comando: `sudo nano /etc/motion/motion.conf`, y aseguraos que los siguiente parámetros están en el siguiente estado:
```
daemon on

width 640
height 480

output_pictures off

ffmpeg_output_movies off

stream_port 8081

webcontrol_port 8080
```

Para que el programa **Motion** se ejecute siempre al iniciar la Raspberry tenéis que ejecutar `crontab -e` y añadir al final:
```
@reboot sudo motion
```
