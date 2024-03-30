
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/coche.h"
#include "../include/dibujos.h"
#include "../include/sqlManager.h"
#include "../include/menus.h"

// menu gestion coche
void menuGestCoches(){
	int opcion = 0;
	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"   Gestion de coches\n\n"
	"---------------------------\n\n"
	"1. Anadir coche\n"
	"2. Modificar coche\n"
	"3. Eliminar coche\n"
	"0. Volver\n\n"
	"Introduce una opcion: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d", &opcion);
	opcionMenuGestCoches(&opcion);

}
void opcionMenuGestCoches(int *opcion) {
	system("cls");
		switch (*opcion) {
			case 1:
				menuAnadirCoche();
				break;
			case 2:
				menuModificarCoche();
				break;
			case 3:
				menuEliminarCoche();
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

	// menu anadir
void menuAnadirCoche() {
	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"       Anadir coche\n\n"
	"---------------------------\n\n");
	Coche c = pedirCoche();
	anadirCoche(c);
	menuGestCoches();
}

	// menu modificar
void menuModificarCoche() {
	int opcion = 0;
	char matricula[8];
	Coche c;

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Modificar coche\n\n"
	"---------------------------\n\n");
	printf("Introduzca la matricula: ");
	fflush(stdout);
	fflush(stdin);
	gets(matricula);

	strcpy(c.matricula, matricula);
	int existe = existeMatricula(matricula, &c);

	if (existe == 0) {
		system("cls");
		printf("LA MATRICULA INTRODUCIDA NO EXISTE\n");
		menuGestCoches();
	}
	printf("\n1.Modificar matricula\n"
	       "2.Modificar marca/modelo\n"
	       "3.Modificar color\n"
	       "4.Modificar año\n"
	       "5.Modificar precio\n"
	       "0.Volver\n\n"
		   "Introduce una opcion: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d", &opcion);
	opcionMenuModificarCoches(&opcion, &c);

}
void opcionMenuModificarCoches(int *opcion, Coche* c) {
	system("cls");
		switch (*opcion) {
				case 1:
					menuModificarMatricula(c->matricula);
					break;
				case 2:
					menuModificarMarcaModeloCoche(c);
					break;
				case 3:
					menuModificarColor(c);
					break;
				case 4:
					menuModificarAnyo(c);
					break;
				case 5:
					menuModificarPrecio(c);
					break;
				case 0:
					menuGestCoches();
					break;
				default:
					printf("El digito introducido no corresponde a ninguno de los anteriores\n");
					menuModificarCoche();
					break;
			}
}

		// sub opciones
void menuModificarMatricula(char matricula[]) {
	char matriculaNueva[8];
	Coche c;
	strcpy(c.matricula, "NULL");
	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"    Modificar matricula\n\n"
	"---------------------------\n\n");

	printf("Antigua matricula: %s\n", matricula);
	do {
		printf("Introduzca la nueva matricula: ");
		fflush(stdout);
		fflush(stdin);
		gets(matriculaNueva);
		if (existeMatricula(matriculaNueva, &c) == 1) {
			printf("La nueva matricula introducida ya existe\n");
		}
	} while (existeMatricula(matriculaNueva, &c) == 1);
	modificarMatricula(matricula, matriculaNueva);
	menuGestCoches();
}
void menuModificarMarcaModeloCoche(Coche* c) {
	int marcaSelec = 0;
	int modeloSelec = 0;

	int numeroModelos = 0;
	int numeroMarcas = 0;
	obtenerNumeroMarcas(&numeroMarcas);
	Marca listaMarcas[numeroMarcas];
	guardarMarcas(listaMarcas);



	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"   Modificar marca/modelo\n\n"
	"---------------------------\n\n");


	pedirMarcas(listaMarcas, numeroMarcas, &marcaSelec, c);

	obtenerNumeroModelos(&numeroModelos, listaMarcas[marcaSelec-1].id);
	Modelo listaModelos[numeroModelos];
	guardarModelos(listaModelos, listaMarcas[marcaSelec-1].id);
	pedirModelos(listaModelos, numeroModelos, &modeloSelec, c);

	modificarMarcaModeloCoche(c->matricula, listaModelos[modeloSelec-1].id);
	menuGestCoches();
}
void menuModificarColor(Coche* c) {
	char color[10];

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Modificar color\n\n"
	"---------------------------\n\n");
	printf("Antiguo color: %s\n", c->color);
	printf("Introduzca el nuevo color: ");
	fflush(stdout);
	fflush(stdin);
	gets(color);
	modificarColor(c->matricula, color);
	menuGestCoches();
}
void menuModificarAnyo(Coche* c) {
	int anyo;

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"       Modificar año\n\n"
	"---------------------------\n\n");
	printf("Antiguo año: %d\n", c->anyo);
	printf("Introduzca el nuevo año: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &anyo);
	modificarAnyo(c->matricula, anyo);
	menuGestCoches();
}
void menuModificarPrecio(Coche* c) {
	float precio;

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Modificar precio\n\n"
	"---------------------------\n\n");
	printf("Antiguo precio: %.2f\n", c->precioBase);
	printf("Introduzca el nuevo precio: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%f", &precio);
	modificarPrecio(c->matricula, precio);
	menuGestCoches();
}

	// menu eliminar
void menuEliminarCoche() {
	char matricula[8] = "";

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"       Eliminar coche\n\n"
	"---------------------------\n\n");
	printf("Introduzca la matricula:  ");
	fflush(stdout);
	fflush(stdin);
	gets(matricula);
	int result = eliminarCoche(matricula);
	system("cls");

	if (result == 1) {
		printf("COCHE ELIMINADO CON EXITO\n");
	} else {
		printf("MATRICULA INVALIDA\n");
	}
	menuGestCoches();

}

// funciones comunes
void pedirMarcas(Marca listaMarcas[], int numeroMarcas, int* marcaSelec, Coche* c){
	printf("Marcas:\n");
	imprimirMarcasLista(listaMarcas, numeroMarcas);
	if(strcmp(c->matricula, "NULL") != 0){
		printf("Antigua marca: %s\n", c->marca.nombre);
	}

	do {
		printf("Introduce la marca: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%d", marcaSelec);
		if ((*marcaSelec > numeroMarcas) || (*marcaSelec < 1)) {
			printf("La marca seleccionada no existe\n");
		}
	} while(*marcaSelec > numeroMarcas || *marcaSelec < 1);
}
void pedirModelos(Modelo listaModelos[], int numeroModelos, int* modeloSelec, Coche* c){
	printf("\nModelos:\n");
	imprimirModelosLista(listaModelos, numeroModelos);
	if(strcmp(c->matricula, "NULL") != 0){
		printf("Antiguo modelo: %s\n", c->modelo.nombre);
	}

	do {
		printf("Introduce el modelo: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%d", modeloSelec);
		if ((*modeloSelec > numeroModelos) || (*modeloSelec< 1)) {
			printf("El modelo seleccionado no existe\n");
		}
	} while(*modeloSelec > numeroModelos || *modeloSelec < 1);
}
Coche pedirCoche()
{
	Coche c;
	Coche cNull;
	strcpy(cNull.matricula, "NULL");
	int marcaSelec = 0;
	int modeloSelec = 0;

	int numeroMarcas = 0;
	int numeroModelos = 0;
	obtenerNumeroMarcas(&numeroMarcas);
	Marca listaMarcas[numeroMarcas];



	printf("Introduce la matricula: ");
	fflush(stdout);
	fflush(stdin);
	gets(c.matricula);

	printf("Introduce el color: ");
	fflush(stdout);
	fflush(stdin);
	gets(c.color);

	printf("Introduce el año: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &c.anyo);

	printf("Introduce el precio: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%f", &c.precioBase);

	guardarMarcas(listaMarcas);
	pedirMarcas(listaMarcas, numeroMarcas, &marcaSelec, &cNull);
	c.marca.id = listaMarcas[marcaSelec-1].id;


	obtenerNumeroModelos(&numeroModelos, c.marca.id);
	Modelo listaModelos[numeroModelos];
	guardarModelos(listaModelos, c.marca.id);
	pedirModelos(listaModelos, numeroModelos, &modeloSelec, &cNull);

	c.modelo.id = listaModelos[modeloSelec-1].id;

	return c;
}

void imprimirMarcasLista(Marca listaMarcas[], int numeroMarcas){
	for (int i = 0; i < numeroMarcas; i++) {
		printf("%d. %s\n", i+1, listaMarcas[i].nombre);
	}
}
void imprimirModelosLista(Modelo listaModelos[], int numeroModelos){
	for (int i = 0; i < numeroModelos; i++) {
		printf("%d. %s, %s, %s\n", i+1, listaModelos[i].nombre, listaModelos[i].cambio, listaModelos[i].combustible);
	}
}

