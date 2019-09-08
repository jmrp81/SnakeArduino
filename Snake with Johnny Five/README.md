# Snake with Johnny-five

## Pasos Creación Proyecto

* Instalamos Node.js
* Creamos una carpeta para el proyecto
* Creamos archivo package.json (situados en la carpeta) --> npm init
* Instalación firmata  --> npm install firmata --save
* Instalación firmata-party --> npm install -g firmata-party --save
* Instalar Johnny Five --> npm install johnny-five --save
* Instalar Raspi IO --> npm install raspi-io --save
* Crear archivo js para código mismo que indicado en package.json
* Crear nuestro código en [nombre_archivo].js
* Ejecutar código --> node [nombre_archivo].js


## Pasos Raspberry Pi
* Instalar Raspbian
* Actualizar paquetes --> sudo apt full-upgrade –y
* Eliminar versiones antigüas de node:
 - apt-get remove nodered –y
 - apt-get remove nodejs nodejs-legacy -y

* Instalar Node Raspberry Pi 3 B y Raspberry Pi 3 B+
 - curl -sL https://deb.nodesource.com/setup_11.x | sudo -E bash -
 - sudo apt install -y nodejs

* Instalar  Johnny Five js --> npm install Johnny-five –g
* Instalar  Johnny Five js --> npm install raspi-io –g

## Bibliografía

Node: https://nodejs.org/es/
VSCode: https://code.visualstudio.com/
NPM Johnny Five: https://www.npmjs.com/package/johnny-five
Johnny Five: http://johnny-five.io/
Johnny Five Pin: https://github.com/rwaldron/johnny-five/wiki/Pin
http://johnny-five.io/examples/expander-74HC595/
Arduino: https://www.arduino.cc/
Arduino IDE: https://www.arduino.cc/en/Main/Software
Raspberry Pi: https://www.raspberrypi.org/
Raspbian: https://www.raspberrypi.org/downloads/raspbian/
Firmata-party: https://github.com/noopkat/firmata-party
VNC Viewer: https://www.realvnc.com/en/connect/download/viewer/
Libro Arduino Practico: https://www.amazon.es/Arduino-Pr%C3%A1ctico-Edici%C3%B3n-Manuales-Imprescindibles/dp/8441538387/ref=pd_lpo_sbs_14_t_0/261-3399884-8502238?_encoding=UTF8&psc=1&refRID=HP1AF76ACYZNTMJ3G5ZJ
Luis Llamas: https://www.luisllamas.es/tutoriales-de-arduino/
Putty: https://www.putty.org/
Win32DiskImager: https://sourceforge.net/projects/win32diskimager/
Advanced IP Scanner: https://www.advanced-ip-scanner.com/es/



