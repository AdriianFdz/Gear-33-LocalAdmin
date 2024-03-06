#include "menus.h"
#include "dibujos.h"
#include <stdio.h>
#include <stdlib.h>


void menuPrincipal()
{
	int opcion;

	dibujoLogo();
	printf("------------------------------------------------\n");
	printf("1. Gestionar coches\n");
	printf("2. Gestionar usuarios\n");
	printf("3. Gestionar empleados\n");
	printf("4. Gestionar tiendas\n");
	printf("0. Salir\n\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d",&opcion);

	opcionMenuPrincipal(opcion);

}

void opcionMenuPrincipal(int opcion){
	system("cls");
	switch (opcion) {
			case 0:
				printf("SALIENDO...\n");
				break;
			case 1:
				menuGestCoches();
				break;
			case 2:
				printf("GESTIONANDO USUARIOS...\n");
				break;
			case 3:
				printf("GESTIONANDO EMPLEADOS...\n");
				break;
			case 4:
				printf("GESTIONANDO TIENDAS...\n");
				break;
			default:
				printf("El digito introducido no corresponde a ninguno de los anteriores\n");
				menuPrincipal();
				break;
		}
}


void menuGestCoches(){
	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"   Gestion de coches\n\n"
	"---------------------------\n"
	"1. Anadir coche\n"
	"2. Modificar coche\n"
	"3. Eliminar coche\n"
	"4. Volver\n"
	"Introduce una opcion: \n");
}
