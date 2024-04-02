/*
 * config.c
 *
 *  Created on: 22 mar 2024
 *      Author: seven
 */

#include "../include/fichero.h"
#include "../include/tienda.h"
#include "../include/coche.h"
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
		} else if(strcmp(clave, "COCHE") == 0){
			strcpy(configuracion->coche, valor);
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
	Tienda t;

	FILE* f = fopen(datosConfig.tienda, "r");

	while(fgets(linea, sizeof(linea), f)){
		// Eliminar saltos de linea
		linea[strcspn(linea, "\n")] = '\0';

		direccion = strtok(linea, ";");
		telefono = strtok(NULL, ";");
		nombreCiudad = strtok(NULL, ";");
		provinciaCiudad = strtok(NULL, ";");

        strcpy(p.nombre, provinciaCiudad);
        strcpy(c.nombre, nombreCiudad);

        if (existeProvincia(p.nombre, &p) == 0) {
            anadirProvincia(p);
            existeProvincia(p.nombre, &p);
        }
        c.provincia.id_provincia = p.id_provincia;

        if (existeCiudad(c.nombre, p.id_provincia, &c) == 0) {
            anadirCiudad(c);
            existeCiudad(c.nombre, p.id_provincia, &c);
        }

        strcpy(t.direccion, direccion);
        strcpy(t.telefono, telefono);
        t.ciudad.id_ciudad = c.id_ciudad;
        strcpy(t.ciudad.nombre, c.nombre);
        t.provincia.id_provincia = p.id_provincia;
        strcpy(t.provincia.nombre, p.nombre);

        anadirTienda(t);

		}
	}

void leerCoche(){
	char linea[100];
	CONFIG datosConfig;
	leerConfig(&datosConfig);

	char* matricula;
	char* marca;
	char* modelo;
	char* color;
	float precio;
	int anyo;
	char* cambio;
	char* combustible;

	Marca ma;
	Modelo mo;
	Coche c;

	FILE* f = fopen(datosConfig.coche, "r");

	while(fgets(linea, sizeof(linea), f)){
		// Eliminar saltos de linea
		linea[strcspn(linea, "\n")] = '\0';

		matricula = strtok(linea, ";");
		marca = strtok(NULL, ";");
		modelo = strtok(NULL, ";");
		color = strtok(NULL, ";");
		precio = atof(strtok(NULL, ";"));
		anyo = atoi(strtok(NULL, ";"));
		cambio = strtok(NULL, ";");
		combustible = strtok(NULL, ";");

        strcpy(ma.nombre, marca);
        strcpy(mo.nombre, modelo);
        strcpy(mo.cambio, cambio);
        strcpy(mo.combustible, combustible);

        if (existeMarca(ma.nombre, &ma) == 0) {
            anadirMarca(ma);
            existeMarca(ma.nombre, &ma);
        }
        mo.marca.id = ma.id;

        if (existeModelo(mo.nombre, ma.id, mo.combustible, mo.cambio, &mo) == 0) {
            anadirModelo(mo);
            existeModelo(mo.nombre, ma.id, mo.combustible, mo.cambio, &mo);
        }

        strcpy(c.matricula, matricula);
        strcpy(c.color, color);
        c.precioBase = precio;
        c.anyo = anyo;
        c.modelo.id = mo.id;
        c.marca.id = ma.id;

        anadirCoche(c);

		}
	}

