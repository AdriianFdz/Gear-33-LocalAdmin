/*
 * config.c
 *
 *  Created on: 22 mar 2024
 *      Author: seven
 */

#include "../include/fichero.h"
#include "../include/tienda.h"
#include "../include/sqlManager.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void leerConfig (CONFIG* configuracion){

	char linea[100];
	char* clave;
	char* valor;

	FILE* f = fopen("../conf/propperties.cfg", "r");

	if (f == NULL) {
		printf("ERROR AL ABRIR ARCHIVO CONFIGURACION\n");
		return;
	}

	while(fgets(linea, sizeof(linea), f)){
		// Eliminar saltos de linea
		linea[strcspn(linea, "\n")] = '\0';

		clave = strtok(linea, "=");
		valor = strtok(NULL, "=");

		if(strcmp(clave, "DATABASE") == 0) {
			strcpy(configuracion -> database, valor);
		} else if(strcmp(clave, "TIENDA") == 0){
			strcpy(configuracion->tienda, valor);
		}
	}

}

void leerTienda(){
	char linea[100];
	CONFIG datosConfig;
	leerConfig(&datosConfig);

	char* direccion;
	char* telefono;
	char* nombreCiudad;
	char* provinciaCiudad;
	Ciudad c;
	Provincia p;

	FILE* f = fopen(datosConfig.tienda, "r");

	while(fgets(linea, sizeof(linea), f)){
		// Eliminar saltos de linea
		linea[strcspn(linea, "\n")] = '\0';

		direccion = strtok(linea, ";");
		telefono = strtok(NULL, ";");
		//falta volcar a las estructuras
		nombreCiudad = strtok(NULL, ";");
		provinciaCiudad = strtok(NULL, ";");

		if (existeProvincia(p.nombre, &p) == 0) {
			anadirProvincia(p);
			existeProvincia(p.nombre, &p);
		} else {
			existeCiudad(c.nombre, p.id_provincia, &c);

			//anadirTienda(t)
			//Compruebo ciudad
		}
	}
}
