#include "../include/menus.h"
#include "../include/dibujos.h"
#include "../include/coche.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/usuario.h"
#include "../include/sqlManager.h"

void menuLogin()
{
	int comprobar;
	char dni[8];
	char contrasena[8];

	dibujoLogo();
	printf("\n------------------------------------------------\n");
	printf("                INICIO DE SESION                  \n");
	printf("------------------------------------------------\n\n");
	printf("Inserte dni: ");
	fflush(stdout);
	fflush(stdin);
	gets(dni);
	printf("Inserte contrasena: ");
	fflush(stdout);
	fflush(stdin);
	gets(contrasena);
	printf("\n");
	comprobar = inicioSesion(dni, contrasena);
	if (comprobar == 1) {
		menuPrincipal();
	}else {
		system("cls");
		printf("ERROR AL INICIAR SESION (PARAMETRO INVALIDO) \n");
		menuLogin();
	}



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
void opcionMenuGestEmpleado(int* opcion){
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
