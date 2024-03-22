/*
 * config.c
 *
 *  Created on: 22 mar 2024
 *      Author: seven
 */

#include "../include/config.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void leerConfig (CONFIG* configuracion){

	char linea[100];
	char* clave;
	char* valor;

	FILE* f = fopen("../conf/propperties.cfg", "r");

	if (f == NULL) {
		printf("ERROR AL ABRIR ARCHIVO CONFIGURACION");
		return;
	}

	while(fgets(linea, sizeof(linea), f)){
		// Eliminar saltos de linea
		linea[strcspn(linea, "\n")] = '\0';

		clave = strtok(linea, "=");
		valor = strtok(NULL, "=");

		if(strcmp(clave, "DATABASE") == 0) {
			strcpy(configuracion -> database, valor);
		}

	}

}
