/*
 * provincia.c
 *
 *  Created on: 30 mar 2024
 *      Author: Unai
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/provincia.h"
#include "../include/dibujos.h"
#include "../include/sqlManager.h"
#include "../include/menus.h"
#include "../include/menus.h"
#include "../include/usuario.h"
void menuGestProvincia(){
	int opcion = 0;
    dibujoPersona();
	printf(
        "---------------------------\n\n"
        "    Gestion de provincias\n\n"
        "---------------------------\n\n"
        "1. Anadir provincia\n"
        "2. Modificar provincia\n"
        "3. Eliminar provincia\n"
        "0. Volver\n\n"
		"Introduce una opcion: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d",&opcion);
	opcionMenuGestProvincia(&opcion);
}

void opcionMenuGestProvincia(int* opcion){
	system("cls");
		switch (*opcion) {
			case 1:
				menuAnadirProvincia();
				break;
			case 2:
				menuModificarProvincia();
				break;
			case 3:
				menuEliminarProvincia();
				break;
			case 0:
				menuPrincipal();
				break;
			default:
				printf("El digito introducido no corresponde a ninguno de los anteriores\n");
				menuGestCoches();
				break;
		}
}

void menuEliminarProvincia(){
	int numeroProvincias = 0;
	int provinciaSelec = 0;

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"      Eliminar provincia\n\n"
	"---------------------------\n\n");
	obtenerNumeroProvincias(&numeroProvincias);
	Provincia listaProvincias[numeroProvincias];
	guardarProvincias(listaProvincias);
	printf("Provincias:\n");
	imprimirProvinciasLista(listaProvincias, numeroProvincias);

	printf("Introduzca el id de la provincia: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%d", &provinciaSelec);
		int result = eliminarProvincia(listaProvincias[provinciaSelec-1].nombre);
		system("cls");
		if (result == 1) {
			printf("PROVINCIA ELIMINADA CON EXITO\n");
			menuGestProvincia();
		} else {
			printf("PROVINCIA INVALIDa\n");
			menuGestProvincia();
		}

}

void menuAnadirProvincia(){
	Provincia provincia;
	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"      Anadir provincia\n\n"
	"---------------------------\n\n");
	printf("Introduce el nombre de la provincia: ");
	fflush(stdout);
	fflush(stdin);
	gets(provincia.nombre);
	anadirProvincia(provincia);
	menuGestProvincia();
}

void menuModificarProvincia(){
	int numeroProvincias = 0;
	int provinciaSelec = 0;
	char nuevoNombre[20];
	Provincia pNull;
	strcpy(pNull.nombre, "NULL");

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"      Modificar provincia\n\n"
	"---------------------------\n\n");
	obtenerNumeroProvincias(&numeroProvincias);
	Provincia listaProvincias[numeroProvincias];
	guardarProvincias(listaProvincias);
	printf("Provincias:\n");
	imprimirProvinciasLista(listaProvincias, numeroProvincias);

	printf("Introduzca el id de la provincia: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &provinciaSelec);

	system("cls");
	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"      Modificar provincia\n\n"
	"---------------------------\n\n");
	printf("Antiguo nombre de la provincia: %s\n", listaProvincias[provinciaSelec-1].nombre);
	do {
		printf("Nuevo nombre de la provincia: ");
		fflush(stdout);
		fflush(stdin);
		gets(nuevoNombre);
		if (existeProvincia(nuevoNombre, &pNull)) {
			printf("El nombre de provincia introducido ya existe actualmente\n");
		}

	} while (existeProvincia(nuevoNombre, &pNull));

	int result = modificarNombreProvincia(listaProvincias[provinciaSelec-1].id_provincia, nuevoNombre);
	system("cls");
	if (result == 0) {
		printf("Nombre de la provincia modificada con exito\n\n");
	} else {
		printf("Error al modificar el nombre de la provincia\n\n");
	}
	menuGestProvincia();
}
/*
void imprimirProvinciasLista(Provincia listaProvincias[], int numeroProvincias){
	for (int i = 0; i < numeroProvincias; i++) {
		printf("%d. %s\n", i+1, listaProvincias[i].nombre);
	}

}
*/
