/*
 * ciudad.c
 *
 *  Created on: 1 abr 2024
 *      Author: Unai
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/ciudad.h"
#include "../include/dibujos.h"
#include "../include/sqlManager.h"
#include "../include/menus.h"
#include "../include/provincia.h"

void menuGestCiudad(){
	int opcion = 0;
	    dibujoPersona();
		printf(
	        "---------------------------\n\n"
	        "    Gestion de ciudades\n\n"
	        "---------------------------\n\n"
	        "1. Anadir ciudad\n"
	        "2. Modificar ciudad\n"
	        "3. Eliminar ciudad\n"
	        "0. Volver\n\n"
			"Introduce una opcion: ");

		fflush(stdout);
		fflush(stdin);
		scanf("%d",&opcion);
		opcionMenuGestCiudad(&opcion);
}

void opcionMenuGestCiudad(int* opcion){
	system("cls");
	switch (*opcion) {
		case 1:
			menuAnadirCiudad();
			break;
		case 2:
			menuModificarCiudad();
			break;
		case 3:
			menuEliminarCiudad();
			break;
		case 0:
			menuPrincipal();
			break;
		default:
			printf("El digito introducido no corresponde a ninguno de los anteriores\n");
			menuGestCiudad();
			break;
	}
}
void menuAnadirCiudad(){
	Tienda tNull;
	Ciudad c;
	strcpy(tNull.direccion, "NULL");

	int provinciaSelec = 0;
	int numeroProvincias = 0;
	obtenerNumeroProvincias(&numeroProvincias);
	Provincia listaProvincias[numeroProvincias];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"      Anadir ciudad\n\n"
	"---------------------------\n\n");
	guardarProvincias(listaProvincias);
	pedirProvincias(listaProvincias, numeroProvincias, &provinciaSelec, &tNull);
	c.provincia.id_provincia = listaProvincias[provinciaSelec-1].id_provincia;

	printf("Introduce el nombre de la ciudad: ");
	fflush(stdout);
	fflush(stdin);
	gets(c.nombre);

	anadirCiudad(c);
	menuGestCiudad();
}
void menuEliminarCiudad(){
	Provincia provincia;

	Tienda tNull;
	strcpy(tNull.direccion, "NULL");

	int numeroProvincias = 0;
	int provinciaSelec = 0;

	int numeroCiudades = 0;
	int ciudadSelec = 0;

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"      Eliminar ciudad\n\n"
	"---------------------------\n\n");
	obtenerNumeroProvincias(&numeroProvincias);
	Provincia listaProvincias[numeroProvincias];
	guardarProvincias(listaProvincias);
	pedirProvincias(listaProvincias, numeroProvincias, &provinciaSelec, &tNull);
	provincia.id_provincia = listaProvincias[provinciaSelec-1].id_provincia;

	obtenerNumeroCiudades(&numeroCiudades, provincia.id_provincia);
	Ciudad listaCiudades[numeroCiudades];
	guardarCiudades(listaCiudades, provincia.id_provincia);
	pedirCiudades(listaCiudades, numeroCiudades, &ciudadSelec, &tNull);


	int result = eliminarCiudad(listaCiudades[ciudadSelec-1]);

	system("cls");
	if (result == 1) {
		printf("CIUDAD ELIMINADA CON EXITO\n");
	} else {
		printf("CIUDAD INVALIDA\n");
	}
	menuGestCiudad();

}
void menuModificarCiudad() {
	int opcion = 0;
	Tienda tNull;
	strcpy(tNull.direccion, "NULL");

	Ciudad c;

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"     Modificar ciudad\n\n"
	"---------------------------\n\n");
	int numeroProvincias = 0;
	int provinciaSelec = 0;
	obtenerNumeroProvincias(&numeroProvincias);
	Provincia listaProvincias[numeroProvincias];
	guardarProvincias(listaProvincias);
	pedirProvincias(listaProvincias, numeroProvincias, &provinciaSelec, &tNull);

	int numeroCiudades = 0;
	int ciudadSelec = 0;
	obtenerNumeroCiudades(&numeroCiudades, listaProvincias[provinciaSelec-1].id_provincia);
	Ciudad listaCiudades[numeroCiudades];
	guardarCiudades(listaCiudades, listaProvincias[provinciaSelec-1].id_provincia);
	pedirCiudades(listaCiudades, numeroCiudades, &ciudadSelec, &tNull);

	c.id_ciudad = listaCiudades[ciudadSelec-1].id_ciudad;
	strcpy(c.nombre, listaCiudades[ciudadSelec-1].nombre);

	c.provincia.id_provincia = listaCiudades[ciudadSelec-1].provincia.id_provincia;

	system("cls");
	menuModificarNombreCiudad(&c);
}

void menuModificarNombreCiudad(Ciudad* c) {
	char nombreNuevo[20];
	Ciudad cNull;
	strcpy(cNull.nombre, "NULL");
	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"Modificar nombre de la ciudad\n\n"
	"---------------------------\n\n");

	printf("Antiguo nombre de la ciudad: %s\n", c->nombre);
	do {
		printf("Introduzca el nuevo nombre de la ciudad: ");
		fflush(stdout);
		fflush(stdin);
		gets(nombreNuevo);
		if (existeCiudad(nombreNuevo, c->provincia.id_provincia, &cNull) == 1) {
			printf("La ciudad introducida ya existe\n");
		}
	} while (existeCiudad(nombreNuevo, c->provincia.id_provincia, &cNull) == 1);

	modificarNombreCiudad(c->id_ciudad, nombreNuevo);
	menuGestCiudad();
}

void menuModificarProvinciaCiudad(Ciudad* c) {
	int id_provincia = 0;
	Ciudad cNull;
	Tienda tNull;
	strcpy(cNull.nombre, "NULL");
	strcpy(tNull.direccion, "NULL");

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"Modificar provincia de la ciudad\n\n"
	"---------------------------\n\n");

	int numeroProvincias = 0;
	int provinciaSelec = 0;
	obtenerNumeroProvincias(&numeroProvincias);
	Provincia listaProvincias[numeroProvincias];
	guardarProvincias(listaProvincias);
	pedirProvincias(listaProvincias, numeroProvincias, &provinciaSelec, &tNull);
	id_provincia = listaProvincias[provinciaSelec-1].id_provincia;

	if(existeCiudad(c->nombre, id_provincia, &cNull) == 1){
		printf("La ciudad introducida ya existe\n");
	} else {
		modificarProvinciaCiudad(c->id_ciudad, id_provincia);
	}

	menuGestCiudad();
}

