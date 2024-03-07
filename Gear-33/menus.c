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
