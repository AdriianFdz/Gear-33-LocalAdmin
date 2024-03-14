#include "menus.h"
#include "dibujos.h"
#include "coche.h"
#include <stdio.h>
#include <stdlib.h>

void menuLogin()
{
	dibujoLogo();
	printf("\n------------------------------------------------\n");
	printf("                INICIO DE SESION                  \n");
	printf("------------------------------------------------\n\n");
	printf("Inserte usuario: \n");
	printf("Inserte contrasena:");
}

void menuPrincipal()
{
	int opcion;

	dibujoLogo();
	printf("------------------------------------------------\n\n");
	printf("1. Gestionar coches\n");
	printf("2. Gestionar usuarios\n");
	printf("3. Gestionar empleados\n");
	printf("4. Gestionar tiendas\n");
	printf("0. Salir\n\n");
	printf("Introduce una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&opcion);

	opcionMenuPrincipal(opcion);

}

void opcionMenuPrincipal(int opcion){
	system("cls");
	switch (opcion) {
			case 1:
				menuGestCoches(&opcion);
				break;
			case 2:
				menuGestUsuario(&opcion);
				break;
			case 3:
				menuGestEmpleado(&opcion);
				break;
			case 4:
				menuGestTienda(&opcion);
				break;
			case 0:
				printf("SALIENDO...\n");
				break;
			default:
				printf("El digito introducido no corresponde a ninguno de los anteriores\n");
				menuPrincipal();
				break;
		}
}


void menuGestCoches(int* opcion){
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
	scanf("%d",opcion);
	opcionMenuGestCoches(opcion);

}

void opcionMenuGestCoches(int *opcion) {
	system("cls");
		switch (*opcion) {
				case 1:
					menuAnadirCoche(opcion);
					break;
				case 2:
					menuModificarCoche(opcion);
					break;
				case 3:
					menuEliminarCoche(opcion);
					break;
				case 0:
					menuPrincipal();
					break;
				default:
					printf("El digito introducido no corresponde a ninguno de los anteriores\n");
					menuGestCoches(opcion);
					break;
			}
}

void menuAnadirCoche(int* opcion) {
	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"       Anadir coche\n\n"
	"---------------------------\n\n");
	pedirCoche();
	menuGestCoches(opcion);
}

void menuModificarCoche(int* opcion) {
	char matricula[7] = "";

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Modificar coche\n\n"
	"---------------------------\n\n");
	printf("Introduzca la matricula:  ");
	fflush(stdout);
	fflush(stdin);
	gets(matricula);

	//falta funcion que comprueba si la matricula existe

	//
	fflush(stdout);
	fflush(stdin);
	printf("\n1.Modificar matricula\n"
	       "2.Modificar marca\n"
	       "3.Modificar modelo\n"
	       "4.Modificar color\n"
	       "5.Modificar año\n"
	       "6.Modificar precio\n"
	       "7.Modificar cambio\n"
	       "8.Modificar combustible\n"
	       "0.Volver\n\n"
		   "Introduce una opción: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d", opcion);
	opcionMenuModificarCoches(opcion);

}

void opcionMenuModificarCoches(int *opcion) {
	system("cls");
		switch (*opcion) {
				case 1:
					menuModificarMatricula(opcion);
					break;
				case 2:
					menuModificarMarca(opcion);
					break;
				case 3:
					menuModificarModelo(opcion);
					break;
				case 4:
					menuModificarColor(opcion);
					break;
				case 5:
					menuModificarAnyo(opcion);
					break;
				case 6:
					menuModificarPrecio(opcion);
					break;
				case 7:
					menuModificarCambio(opcion);
					break;
				case 8:
					menuModificarCombustible(opcion);
					break;
				case 0:
					menuGestCoches(opcion);
					break;
				default:
					printf("El digito introducido no corresponde a ninguno de los anteriores\n");
					menuModificarCoche(opcion);
					break;
			}
}

void menuModificarMatricula(int *opcion) {
	char matricula[7];

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"    Modificar matricula\n\n"
	"---------------------------\n\n");
	printf("Introduzca la nueva matricula:  ");
	fflush(stdout);
	fflush(stdin);
	gets(matricula);
	// crear funcion para modificar matricula
	/////
	menuGestCoches(opcion);
}

void menuModificarMarca(int *opcion) {
	char marca[15];

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Modificar marca\n\n"
	"---------------------------\n\n");
	printf("Introduzca la nueva marca:  ");
	fflush(stdout);
	fflush(stdin);
	gets(marca);
	// crear funcion para modificar marca
	/////
	menuGestCoches(opcion);
}

void menuModificarModelo(int *opcion) {
	char modelo[15];

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Modificar modelo\n\n"
	"---------------------------\n\n");
	printf("Introduzca el nuevo modelo:  ");
	fflush(stdout);
	fflush(stdin);
	gets(modelo);
	// crear funcion para modificar modelo
	/////
	menuGestCoches(opcion);
}

void menuModificarColor(int *opcion) {
	char color[10];

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Modificar color\n\n"
	"---------------------------\n\n");
	printf("Introduzca el nuevo color:  ");
	fflush(stdout);
	fflush(stdin);
	gets(color);
	// crear funcion para modificar color
	/////
	menuGestCoches(opcion);
}

void menuModificarAnyo(int *opcion) {
	int anyo;

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"       Modificar año\n\n"
	"---------------------------\n\n");
	printf("Introduzca el nuevo año:  ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &anyo);
	// crear funcion para modificar año
	/////
	menuGestCoches(opcion);
}

void menuModificarPrecio(int *opcion) {
	float precio;

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Modificar precio\n\n"
	"---------------------------\n\n");
	printf("Introduzca el nuevo precio:  ");
	fflush(stdout);
	fflush(stdin);
	scanf("%f", &precio);
	// crear funcion para modificar año
	/////
	menuGestCoches(opcion);
}

void menuModificarCambio(int *opcion) {
	char cambio[15];

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Modificar cambio\n\n"
	"---------------------------\n\n");
	printf("Introduzca el nuevo tipo de cambio:  ");
	fflush(stdout);
	fflush(stdin);
	gets(cambio);
	// crear funcion para modificar el cambio
	/////
	menuGestCoches(opcion);
}

void menuModificarCombustible(int *opcion) {
	char combustible[10];

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"   Modificar combustible\n\n"
	"---------------------------\n\n");
	printf("Introduzca el nuevo combustible:  ");
	fflush(stdout);
	fflush(stdin);
	gets(combustible);
	// crear funcion para modificar combustible
	/////
	menuGestCoches(opcion);
}


void menuEliminarCoche(int* opcion) {
	char matricula[7] = "";

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"       Eliminar coche\n\n"
	"---------------------------\n\n");
	printf("Introduzca la matricula:  ");
	fflush(stdout);
	fflush(stdin);
	gets(matricula);
	menuGestCoches(opcion);
}


void menuGestUsuario(int* opcion){
	dibujoPersona();
	 printf(
	        "---------------------------\n\n"
	        "    Gestionar usuario\n\n"
	        "---------------------------\n\n"
	        "1. Anadir usuario\n"
	        "2. Modificar usuario\n"
	        "3. Eliminar usuario\n"
	        "0. Volver\n\n"
			"Introduce una opcion: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d",opcion);
	opcionMenuGestUsuario(opcion);
}
void opcionMenuGestUsuario(int *opcion) {
	system("cls");
		switch (*opcion) {
				case 1:
					menuAnadirUsuario(opcion);
					break;
				case 2:
					menuModificarUsuario(opcion);
					break;
				case 3:
					menuEliminarUsuario(opcion);
					break;
				case 0:
					menuPrincipal();
					break;
				default:
					printf("El digito introducido no corresponde a ninguno de los anteriores\n");
					menuGestUsuario(opcion);
					break;
			}
}
void menuAnadirUsuario(int* opcion) {
	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"       Registro de usuario\n\n"
	"---------------------------\n\n");
	printf("Introduce el nombre \n");
		fflush(stdout);
		fflush(stdin);


		printf("Introduce el apellido \n");
		fflush(stdout);
		fflush(stdin);


		printf("Introduce el dni \n");
		fflush(stdout);
		fflush(stdin);


		printf("Introduce la fecha de nacimiento DD/MM/AAAA \n");
		fflush(stdout);
		fflush(stdin);


		printf("Introduce el teléfono \n");
		fflush(stdout);
		fflush(stdin);


		printf("Introduce la dirección \n");
		fflush(stdout);
		fflush(stdin);


		printf("Introduce la contraseña \n");
		fflush(stdout);
		fflush(stdin);
		menuGestUsuario(opcion);
}
void menuModificarUsuario(int* opcion) {


	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"      Modificar datos\n\n"
	"---------------------------\n\n");
	printf("Introduzca el dni:  ");
	fflush(stdout);
	fflush(stdin);


	//falta funcion que comprueba si el dni existe

	//
	fflush(stdout);
	fflush(stdin);
	printf("\n1.Modificar nombre\n"
	       "2.Modificar apellido\n"
	       "3.Modificar modelo\n"
	       "4.Modificar DNI\n"
	       "5.Modificar fecha de nacimiento\n"
	       "6.Modificar teléfono\n"
	       "7.Modificar dirección\n"
	       "8.Modificar contraseña\n"
	       "0.Volver\n\n"
		   "Introduce una opción: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d", opcion);

}
void menuEliminarUsuario(int* opcion) {


	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"       Eliminar usuario\n\n"
	"---------------------------\n\n");
	printf("Introduzca el dni:  ");
	fflush(stdout);
	fflush(stdin);

}

void menuGestEmpleado(int* opcion){
	dibujoPersona();
    printf(
        "---------------------------\n\n"
        "     Gestionar empleado\n\n"
        "---------------------------\n\n"
        "1. Anadir empleado\n"
        "2. Modificar empleado\n"
        "3. Eliminar empleado\n"
        "0. Volver\n\n"
		"Introduce una opcion: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d",opcion);

}

void menuGestTienda(int* opcion){
    dibujoTienda();
	printf(
        "---------------------------\n\n"
        "    Gestion de tiendas\n\n"
        "---------------------------\n\n"
        "1. Anadir tienda\n"
        "2. Modificar tienda\n"
        "3. Eliminar tienda\n"
        "0. Volver\n\n"
		"Introduce una opcion: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d",opcion);
}
