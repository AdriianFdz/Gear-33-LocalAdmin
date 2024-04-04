#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/tienda.h"
#include "../include/ciudad.h"
#include "../include/fichero.h"
#include "../include/dibujos.h"
#include "../include/sqlManager.h"
#include "../include/menus.h"

void menuGestTienda(){
	int opcion = 0;
    dibujoTienda();
	printf(
        "---------------------------\n\n"
        "    Gestion de tiendas\n\n"
        "---------------------------\n\n"
        "1. Anadir tienda\n"
		"2. Importar tiendas desde fichero\n"
        "3. Modificar tienda\n"
        "4. Eliminar tienda\n"
        "0. Volver\n\n"
		"Introduce una opcion: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d",&opcion);
	opcionMenuGestTiendas(&opcion);
}



void opcionMenuGestTiendas(int* opcion){
	system("cls");
		switch (*opcion) {
			case 1:
				menuAnadirTienda();
				break;
			case 2:
				menuImportarTienda();
				break;
			case 3:
				menuModificarTienda();
				break;
			case 4:
				menuEliminarTienda();
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
void menuAnadirTienda() {
	dibujoTienda();
	printf(
	"---------------------------\n\n"
	"       Anadir tienda\n\n"
	"---------------------------\n\n");
	Tienda t = pedirTienda();
	system("cls");
	anadirTienda(t);
	menuGestTienda();
}

	// menu importar
void menuImportarTienda() {
	system("cls");
	leerTienda();
	menuGestTienda();
}

	// menu modificar
void menuModificarTienda(){
	int tiendaSelec = 0;
	Tienda t;

	Empleado eNull;
	strcpy(eNull.dni, "NULL");

	dibujoTienda();
	printf(
	"---------------------------\n\n"
	"      Modificar tienda\n\n"
	"---------------------------\n\n");
	int numeroTiendas = 0;
	obtenerNumeroTiendas(&numeroTiendas);
	Tienda listaTiendas[numeroTiendas];
	guardarTiendas(listaTiendas);

	pedirTiendas(listaTiendas, numeroTiendas, &tiendaSelec, &eNull);

	int existe = existeTienda(listaTiendas[tiendaSelec-1].direccion, listaTiendas[tiendaSelec-1].ciudad.id_ciudad, &t);
	if (existe == 0) {
		system("cls");
		printf("LA TIENDA INTRODUCIDA NO EXISTE\n");
		menuGestTienda();
	}

	int opcion = 0;
	printf("\n1.Modificar direccion\n"
	       "2.Modificar telefono\n"
	       "3.Modificar ciudad\n"
	       "0.Volver\n\n"
		   "Introduce una opcion: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d", &opcion);
	opcionMenuModificarTienda(&opcion, &t);
}
void opcionMenuModificarTienda(int* opcion, Tienda* t){
	system("cls");
	switch (*opcion) {
		case 1:
			menuModificarDireccionTienda(t);
			break;
		case 2:
			menuModificarTelefonoTienda(t);
			break;
		case 3:
			menuModificarCiudadTienda(t);
			break;
		case 0:
			menuGestEmpleado();
			break;
		default:
			printf("El digito introducido no corresponde a ninguno de los anteriores\n");
			menuModificarEmpleado();
			break;
		}
}
		//sub opciones
void menuModificarDireccionTienda(Tienda* t){
	char direccion[51] = "";
	Tienda tNull;
	strcpy(tNull.direccion, "NULL");

	dibujoTienda();
	printf(
	"---------------------------\n\n"
	"    Modificar direccion\n\n"
	"---------------------------\n\n");
	printf("Antigua direccion: %s\n", t->direccion);
	do {
		printf("Introduzca la nueva direccion: ");
		fflush(stdout);
		fflush(stdin);
		gets(direccion);
		if (existeTienda(direccion, t->ciudad.id_ciudad, &tNull) == 1) {
			printf("La tienda introducida ya existe\n");
		}
	} while (existeTienda(direccion, t->ciudad.id_ciudad, &tNull) == 1);

	system("cls");
	modificarDirecTienda(t->id_tienda, direccion);
	menuGestTienda();
}
void menuModificarTelefonoTienda(Tienda* t){
	char telefono[10] = "";
	Tienda tNull;
	strcpy(tNull.direccion, "NULL");

	dibujoTienda();
	printf(
	"---------------------------\n\n"
	"     Modificar telefono\n\n"
	"---------------------------\n\n");
	printf("Antiguo telefono: %s\n", t->telefono);
	printf("Introduzca el nuevo telefono: ");
	fflush(stdout);
	fflush(stdin);
	gets(telefono);

	system("cls");
	modificarTelefTienda(t->id_tienda, telefono);
	menuGestTienda();
}
void menuModificarCiudadTienda(Tienda* t){
	Provincia provincia;
	Ciudad ciudad;
	ciudad.id_ciudad = 0;

	Tienda tNull;
	strcpy(tNull.direccion, "NULL");

	int provinciaSelec = 0;
	int ciudadSelec = 0;

	int numeroProvincias = 0;
	int numeroCiudades = 0;
	obtenerNumeroProvincias(&numeroProvincias);
	Provincia listaProvincias[numeroProvincias];

	dibujoTienda();
	printf(
	"---------------------------\n\n"
	"     Modificar ciudad\n\n"
	"---------------------------\n\n");

	guardarProvincias(listaProvincias);
	pedirProvincias(listaProvincias, numeroProvincias, &provinciaSelec, &tNull);
	provincia.id_provincia = listaProvincias[provinciaSelec-1].id_provincia;

	obtenerNumeroCiudades(&numeroCiudades, provincia.id_provincia);
	Ciudad listaCiudades[numeroCiudades];
	guardarCiudades(listaCiudades, provincia.id_provincia);

	printf("Antigua ciudad: %s\n", t->ciudad.nombre);
	do {
		pedirCiudades(listaCiudades, numeroCiudades, &ciudadSelec, &tNull);
		if (existeTienda(t->direccion, ciudad.id_ciudad, &tNull) == 1) {
			printf("La tienda introducida ya existe\n");
		}
	} while (existeTienda(t->direccion, ciudad.id_ciudad, &tNull) == 1);

	ciudad.id_ciudad = listaCiudades[ciudadSelec-1].id_ciudad;

	system("cls");
	modificarCiudadTienda(t->id_tienda, ciudad.id_ciudad);
	menuGestTienda();
}

	// menu eliminar
void menuEliminarTienda() {
	int tiendaSelec = 0;

	Empleado eNull;
	strcpy(eNull.dni, "NULL");

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Eliminar tienda\n\n"
	"---------------------------\n\n");
	printf("Al eliminar una tienda se eliminaran los empleados de dicha tienda (0 para cancelar)");
	int numeroTiendas = 0;
	obtenerNumeroTiendas(&numeroTiendas);
	Tienda listaTiendas[numeroTiendas];
	guardarTiendas(listaTiendas);

	imprimirTiendasLista(listaTiendas, numeroTiendas);
	pedirTiendas(listaTiendas, numeroTiendas, &tiendaSelec, &eNull);

	int result = eliminarTienda(listaTiendas[tiendaSelec-1].direccion, listaTiendas[tiendaSelec-1].ciudad.id_ciudad);
	system("cls");

	if (result == 1) {
		printf("TIENDA ELIMINADA CON EXITO\n");
	} else {
		printf("TIENDA INVALIDA\n");
	}
	menuGestTienda();

}
// funciones comunes
void pedirProvincias(Provincia listaProvincias[], int numeroProvincias, int* provinciaSelec, Tienda* t){
	printf("Provincias:\n");
	imprimirProvinciasLista(listaProvincias, numeroProvincias);
	if(strcmp(t->direccion, "NULL") != 0){
		printf("Antigua provincia: %s\n", t->provincia.nombre);
	}

	do {
		printf("Introduce la provincia: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%d", provinciaSelec);
		if ((*provinciaSelec > numeroProvincias) || (*provinciaSelec < 1)) {
			printf("La provincia seleccionada no existe\n");
		}
		if (*provinciaSelec == 0) {
			system("cls");
			menuGestCiudad();
		}
	} while(*provinciaSelec > numeroProvincias || *provinciaSelec < 1);
}
void pedirCiudades(Ciudad listaCiudades[], int numeroCiudades, int* ciudadSelec, Tienda* t){
	printf("Ciudades:\n");
	imprimirCiudadesLista(listaCiudades, numeroCiudades);
	if(strcmp(t->direccion, "NULL") != 0){
		printf("Antigua ciuadad: %s\n", t->ciudad.nombre);
	}

	do {
		printf("Introduce el id de la ciudad: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%d", ciudadSelec);
		if ((*ciudadSelec > numeroCiudades) || (*ciudadSelec < 0)) {
			printf("La ciudad seleccionada no existe\n");
		}
		if (*ciudadSelec == 0) {
			system("cls");
			menuGestCiudad();
		}
	} while(*ciudadSelec > numeroCiudades || *ciudadSelec < 1);
}

void imprimirProvinciasLista(Provincia listaProvincias[], int numeroProvincias){
	for (int i = 0; i < numeroProvincias; i++) {
		printf("%d. %s\n", i+1, listaProvincias[i].nombre);
	}
}
void imprimirCiudadesLista(Ciudad listaCiudades[], int numeroCiudades){
	for (int i = 0; i < numeroCiudades; i++) {
		printf("%d. %s\n", i+1, listaCiudades[i].nombre);
	}
}
void imprimirTiendasLista(Tienda listaTiendas[], int numeroTiendas){
	for (int i = 0; i < numeroTiendas; i++) {
		printf("%d. %s, %s, %s\n", i+1, listaTiendas[i].direccion, listaTiendas[i].ciudad.nombre, listaTiendas[i].provincia.nombre);
	}
}

Tienda pedirTienda(){
	Tienda t;
	Tienda tNull;
	strcpy(tNull.direccion, "NULL");

	int provinciaSelec = 0;
	int ciudadSelec = 0;

	int numeroProvincias = 0;
	int numeroCiudades = 0;
	obtenerNumeroProvincias(&numeroProvincias);
	Provincia listaProvincias[numeroProvincias];


	printf("Introduce la direccion: ");
	fflush(stdout);
	fflush(stdin);
	gets(t.direccion);

	printf("Introduce el telefono: ");
	fflush(stdout);
	fflush(stdin);
	gets(t.telefono);

	guardarProvincias(listaProvincias);
	pedirProvincias(listaProvincias, numeroProvincias, &provinciaSelec, &tNull);
	t.provincia.id_provincia = listaProvincias[provinciaSelec-1].id_provincia;

	obtenerNumeroCiudades(&numeroCiudades, t.provincia.id_provincia);
	Ciudad listaCiudades[numeroCiudades];
	guardarCiudades(listaCiudades, t.provincia.id_provincia);
	pedirCiudades(listaCiudades, numeroCiudades, &ciudadSelec, &tNull);
	t.ciudad.id_ciudad= listaCiudades[ciudadSelec-1].id_ciudad;

	return t;
}

