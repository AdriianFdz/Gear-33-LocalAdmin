/*
 * marca.c
 *
 *  Created on: 30 mar 2024
 *      Author: seven
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/marca.h"
#include "../include/dibujos.h"
#include "../include/sqlManager.h"
#include "../include/menus.h"

void menuGestMarca(){
	int opcion = 0;
	    dibujoCoche();
		printf(
	        "---------------------------\n\n"
	        "    Gestion de marcas\n\n"
	        "---------------------------\n\n"
	        "1. Anadir marca\n"
	        "2. Modificar marca\n"
	        "3. Eliminar marca\n"
	        "0. Volver\n\n"
			"Introduce una opcion: ");

		fflush(stdout);
		fflush(stdin);
		scanf("%d",&opcion);
		opcionMenuGestMarcas(&opcion);
}

void opcionMenuGestMarcas(int* opcion){
	system("cls");
	switch (*opcion) {
		case 1:
			menuAnadirMarca();
			break;
		case 2:
			menuModificarMarca();
			break;
		case 3:
			menuEliminarMarca();
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

void menuAnadirMarca(){
	Marca marca;
	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Anadir marca\n\n"
	"---------------------------\n\n");
	printf("Introduce el nombre de la marca: ");
	fflush(stdout);
	fflush(stdin);
	gets(marca.nombre);
	anadirMarca(marca);
	menuGestMarca();
}

void menuEliminarMarca(){
	int numeroMarcas = 0;
	int marcaSelec = 0;

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Eliminar marca\n\n"
	"---------------------------\n\n");
	obtenerNumeroMarcas(&numeroMarcas);
	Marca listaMarcas[numeroMarcas];
	guardarMarcas(listaMarcas);
	printf("Marcas:\n");
	imprimirMarcasLista(listaMarcas, numeroMarcas);

	printf("Introduzca el id de la marca: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &marcaSelec);
	int result = eliminarMarca(listaMarcas[marcaSelec-1].nombre);
	system("cls");
	if (result == 1) {
		printf("MARCA ELIMINADA CON EXITO\n");
	} else {
		printf("MARCA INVALIDA\n");
	}
	menuGestMarca();

}

void menuModificarMarca(){
	int numeroMarcas = 0;
	int marcaSelec = 0;
	char nuevoNombre[20];
	Marca mNull;
	strcpy(mNull.nombre, "NULL");

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Modificar marca\n\n"
	"---------------------------\n\n");
	obtenerNumeroMarcas(&numeroMarcas);
	Marca listaMarcas[numeroMarcas];
	guardarMarcas(listaMarcas);
	printf("Marcas:\n");
	imprimirMarcasLista(listaMarcas, numeroMarcas);

	printf("Introduzca el id del cargo: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &marcaSelec);

	system("cls");
	dibujoPersona();
	printf("Antiguo nombre de la marca: %s\n", listaMarcas[marcaSelec-1].nombre);
	do {
		printf("Nuevo nombre de la marca: ");
		fflush(stdout);
		fflush(stdin);
		gets(nuevoNombre);
		if (existeMarca(nuevoNombre, &mNull)) {
			printf("El nombre de la marca introducida ya existe\n");
		}

	} while (existeMarca(nuevoNombre, &mNull));

	int result = modificarNombreMarca(listaMarcas[marcaSelec-1].id, nuevoNombre);
	system("cls");
	if (result == 0) {
		printf("Nombre de la marca modificada con exito\n\n");
	} else {
		printf("Error al modificar el nombre de la marca\n\n");
	}
	menuGestMarca();
}
