﻿#!/bin/bash
#Colores
ROJO="\033[1;31m"
VERDE="\033[1;32m"
BLANCO="\033[1;37m"
AMARILLO="\033[1;33m"
CIAN="\033[1;36m"
GRIS="\033[0m"
MARRON="\33[38;5;138m"

			cd /home/pi/YSFClients/YSFGateway
			#sudo wget -O YSFHosts.txt http://register.ysfreflector.de/export_csv.php 
           
			curl https://dvref.com/downloads/YSFHosts-resolved.txt > /home/pi/YSFClients/YSFGateway/YSFHosts.txt
			
		
			sleep 3
			sed -i '$a\\21887;ANDALUCIA;ANDALUCIA;51.68.71.60;42000;022' /home/pi/YSFClients/YSFGateway/YSFHosts.txt
			clear
			echo "${VERDE}*********************************"
					echo "* ACTUALIZANDO REFLECTORES YSF  *"
					echo "*********************************"
			sleep 3



