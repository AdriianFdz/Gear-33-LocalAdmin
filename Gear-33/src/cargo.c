/*
 * cargo.c
 *
 *  Created on: 29 mar 2024
 *      Author: seven
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/cargo.h"
#include "../include/dibujos.h"
#include "../include/sqlManager.h"
#include "../include/menus.h"

void menuGestCargo(){
	int opcion = 0;
    dibujoPersona();
	printf(
        "---------------------------\n\n"
        "    Gestion de cargos\n\n"
        "---------------------------\n\n"
        "1. Anadir cargo\n"
        "2. Modificar cargo\n"
        "3. Eliminar cargo\n"
        "0. Volver\n\n"
		"Introduce una opcion: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d",&opcion);
	opcionMenuGestCargos(&opcion);
}

void opcionMenuGestCargos(int* opcion){
	system("cls");
	switch (*opcion) {
		case 1:
			menuAnadirCargo();
			break;
		case 2:
			menuModificarCargo();
			break;
		case 3:
			menuEliminarCargo();
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

void menuEliminarCargo(){
	int numeroCargos = 0;
	int cargoSelec = 0;

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"      Eliminar cargo\n\n"
	"---------------------------\n\n");
	obtenerNumeroCargos(&numeroCargos);
	Cargo listaCargos[numeroCargos];
	guardarCargos(listaCargos);
	printf("Cargos:\n");
	imprimirCargosLista(listaCargos, numeroCargos);

	printf("Introduzca el id del cargo: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%d", &cargoSelec);
		int result = eliminarCargo(listaCargos[cargoSelec-1].nombre_cargo);
		system("cls");
		if (result == 1) {
			printf("CARGO ELIMINADO CON EXITO\n");
			menuGestCargo();
		} else {
			printf("CARGO INVALIDO\n");
			menuGestCargo();
		}

}

void menuAnadirCargo(){
	Cargo cargo;
	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"      Anadir cargo\n\n"
	"---------------------------\n\n");
	printf("Introduce el nombre del cargo: ");
	fflush(stdout);
	fflush(stdin);
	gets(cargo.nombre_cargo);
	anadirCargo(cargo);
	menuGestCargo();
}

void menuModificarCargo(){
	int numeroCargos = 0;
	int cargoSelec = 0;
	char nuevoNombre[20];
	Cargo cNull;
	strcpy(cNull.nombre_cargo, "NULL");

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"      Modificar cargo\n\n"
	"---------------------------\n\n");
	obtenerNumeroCargos(&numeroCargos);
	Cargo listaCargos[numeroCargos];
	guardarCargos(listaCargos);
	printf("Cargos:\n");
	imprimirCargosLista(listaCargos, numeroCargos);

	printf("Introduzca el id del cargo: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &cargoSelec);

	system("cls");
	dibujoPersona();
	printf("Antiguo nombre del cargo: %s\n", listaCargos[cargoSelec-1].nombre_cargo);
	do {
		printf("Nuevo nombre del cargo: ");
		fflush(stdout);
		fflush(stdin);
		gets(nuevoNombre);
		if (existeCargo(nuevoNombre, &cNull)) {
			printf("El nombre de cargo introducido ya existe\n");
		}

	} while (existeCargo(nuevoNombre, &cNull));

	int result = modificarNombreCargo(listaCargos[cargoSelec-1].id_cargo, nuevoNombre);
	system("cls");
	if (result == 0) {
		printf("Nombre de cargo modificado con exito\n\n");
	} else {
		printf("Error al modificar el nombre del cargo\n\n");
	}
	menuGestCargo();
}

void imprimirCargosLista(Cargo listaCargos[], int numeroCargos){
	for (int i = 0; i < numeroCargos; i++) {
		printf("%d. %s\n", i+1, listaCargos[i].nombre_cargo);
	}
}
