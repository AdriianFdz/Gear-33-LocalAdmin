/*
 * modelo.c
 *
 *  Created on: 30 mar 2024
 *      Author: seven
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/modelo.h"
#include "../include/dibujos.h"
#include "../include/sqlManager.h"
#include "../include/menus.h"
#include "../include/marca.h"

void menuGestModelo(){
	int opcion = 0;
	    dibujoCoche();
		printf(
	        "---------------------------\n\n"
	        "    Gestion de modelos\n\n"
	        "---------------------------\n\n"
	        "1. Anadir modelo\n"
	        "2. Modificar modelo\n"
	        "3. Eliminar modelo\n"
	        "0. Volver\n\n"
			"Introduce una opcion: ");

		fflush(stdout);
		fflush(stdin);
		scanf("%d",&opcion);
		opcionMenuGestModelo(&opcion);
}

void opcionMenuGestModelo(int* opcion){
	system("cls");
	switch (*opcion) {
		case 1:
			menuAnadirModelo();
			break;
		case 2:
			menuModificarModelo();
			break;
		case 3:
			menuEliminarModelo();
			break;
		case 0:
			menuPrincipal();
			break;
		default:
			printf("El digito introducido no corresponde a ninguno de los anteriores\n");
			menuGestModelo();
			break;
	}
}
void menuAnadirModelo(){
	Coche cNull;
	Modelo m;
	strcpy(cNull.matricula, "NULL");

	int marcaSelec = 0;
	int numeroMarcas = 0;
	obtenerNumeroMarcas(&numeroMarcas);
	Marca listaMarcas[numeroMarcas];

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Anadir modelo\n\n"
	"---------------------------\n\n");
	guardarMarcas(listaMarcas);
	pedirMarcas(listaMarcas, numeroMarcas, &marcaSelec, &cNull);
	m.marca.id = listaMarcas[marcaSelec-1].id;

	printf("Introduce el nombre del modelo: ");
	fflush(stdout);
	fflush(stdin);
	gets(m.nombre);

	printf("Introduce el cambio: ");
	fflush(stdout);
	fflush(stdin);
	gets(m.cambio);

	printf("Introduce el combustible: ");
	fflush(stdout);
	fflush(stdin);
	gets(m.combustible);

	anadirModelo(m);
	menuGestModelo();
}
void menuEliminarModelo(){
	Marca marca;

	int numeroMarcas = 0;
	int marcaSelec = 0;

	int numeroModelos = 0;
	int modeloSelec = 0;

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Eliminar modelo\n\n"
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
	marca.id = listaMarcas[marcaSelec-1].id;

	obtenerNumeroModelos(&numeroModelos, marca.id);
	Modelo listaModelos[numeroModelos];
	guardarModelos(listaModelos, marca.id);
	printf("Modelos:\n");
	imprimirModelosLista(listaModelos, numeroModelos);
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &modeloSelec);
	int result = eliminarModelo(listaModelos[modeloSelec-1]);

	system("cls");
	if (result == 1) {
		printf("MODELO ELIMINADO CON EXITO\n");
	} else {
		printf("MODELO INVALIDO\n");
	}
	menuGestModelo();

}
void menuModificarModelo() {
	int opcion = 0;
	Coche cNull;
	strcpy(cNull.matricula, "NULL");

	Modelo m;

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"     Modificar modelo\n\n"
	"---------------------------\n\n");
	int numeroMarcas = 0;
	int marcaSelec = 0;
	obtenerNumeroMarcas(&numeroMarcas);
	Marca listaMarcas[numeroMarcas];
	guardarMarcas(listaMarcas);
	pedirMarcas(listaMarcas, numeroMarcas, &marcaSelec, &cNull);

	int numeroModelos = 0;
	int modeloSelec = 0;
	obtenerNumeroModelos(&numeroModelos, listaMarcas[marcaSelec-1].id);
	Modelo listaModelos[numeroModelos];
	guardarModelos(listaModelos, listaMarcas[marcaSelec-1].id);
	pedirModelos(listaModelos, numeroModelos, &modeloSelec, &cNull);

	m.id = listaModelos[modeloSelec-1].id;
	strcpy(m.nombre, listaModelos[modeloSelec-1].nombre);
	strcpy(m.cambio, listaModelos[modeloSelec-1].cambio);
	strcpy(m.combustible, listaModelos[modeloSelec-1].combustible);
	m.marca.id = listaModelos[modeloSelec-1].marca.id;

	system("cls");
	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"     Modificar modelo\n\n"
	"---------------------------\n\n");
	printf("\n1.Modificar nombre\n"
	       "2.Modificar cambio\n"
	       "3.Modificar combustible\n"
	       "4.Modificar marca\n"
	       "0.Volver\n\n"
		   "Introduce una opcion: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d", &opcion);
	opcionMenuModificarModelo(&opcion, &m);

}

void opcionMenuModificarModelo(int* opcion, Modelo* m){
	switch (*opcion) {
		case 1:
			menuModificarNombreModelo(m);
			break;
		case 2:
			menuModificarCambioModelo(m);
			break;
		case 3:
			menuModificarCombustibleModelo(m);
			break;
		case 4:
			menuModificarMarcaModelo(m);
			break;
		default:
			break;
	}
}

void menuModificarNombreModelo(Modelo* m) {
	char nombreNuevo[20];
	Modelo mNull;
	strcpy(mNull.nombre, "NULL");
	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"Modificar nombre del modelo\n\n"
	"---------------------------\n\n");

	printf("Antiguo nombre del modelo: %s\n", m->nombre);
	do {
		printf("Introduzca el nuevo nombre del modelo: ");
		fflush(stdout);
		fflush(stdin);
		gets(nombreNuevo);
		if (existeModelo(nombreNuevo, m->marca.id, m->combustible, m->cambio, &mNull) == 1) {
			printf("El modelo introducido ya existe\n");
		}
	} while (existeModelo(nombreNuevo, m->marca.id, m->combustible, m->cambio, &mNull) == 1);

	modificarNombreModelo(m->id, nombreNuevo);
	menuGestModelo();
}
void menuModificarCambioModelo(Modelo* m) {
	char cambioNuevo[20];
	Modelo mNull;
	strcpy(mNull.nombre, "NULL");
	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"Modificar cambio del modelo\n\n"
	"---------------------------\n\n");

	printf("Antiguo cambio del modelo: %s\n", m->cambio);
	do {
		printf("Introduzca el nuevo cambio del modelo: ");
		fflush(stdout);
		fflush(stdin);
		gets(cambioNuevo);
		if (existeModelo(m->nombre, m->marca.id, m->combustible, cambioNuevo, &mNull) == 1) {
			printf("El modelo introducido ya existe\n");
		}
	} while (existeModelo(m->nombre, m->marca.id, m->combustible, cambioNuevo, &mNull) == 1);

	modificarCambioModelo(m->id, cambioNuevo);
	menuGestModelo();
}
void menuModificarCombustibleModelo(Modelo* m) {
	char combustibleNuevo[20];
	Modelo mNull;
	strcpy(mNull.nombre, "NULL");
	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"Modificar combustible del modelo\n\n"
	"---------------------------\n\n");

	printf("Antiguo combustible del modelo: %s\n", m->combustible);
	do {
		printf("Introduzca el nuevo combustible del modelo: ");
		fflush(stdout);
		fflush(stdin);
		gets(combustibleNuevo);
		if (existeModelo(m->nombre, m->marca.id, combustibleNuevo, m->cambio, &mNull) == 1) {
			printf("El modelo introducido ya existe\n");
		}
	} while (existeModelo(m->nombre, m->marca.id, combustibleNuevo, m->cambio, &mNull) == 1);

	modificarCombustibleModelo(m->id, combustibleNuevo);
	menuGestModelo();
}
void menuModificarMarcaModelo(Modelo* m) {
	int id_marca = 0;
	Modelo mNull;
	Coche cNull;
	strcpy(mNull.nombre, "NULL");
	strcpy(cNull.matricula, "NULL");

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"Modificar marca del modelo\n\n"
	"---------------------------\n\n");

	int numeroMarcas = 0;
	int marcaSelec = 0;
	obtenerNumeroMarcas(&numeroMarcas);
	Marca listaMarcas[numeroMarcas];
	guardarMarcas(listaMarcas);
	pedirMarcas(listaMarcas, numeroMarcas, &marcaSelec, &cNull);
	id_marca = listaMarcas[marcaSelec-1].id;

	if(existeModelo(m->nombre, id_marca, m->combustible, m->cambio, &mNull) == 1){
		printf("El modelo introducido ya existe\n");
	} else {
		modificarMarcaModelo(m->id, id_marca);
	}

	menuGestModelo();
}
