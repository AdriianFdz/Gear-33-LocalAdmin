#include "../include/menus.h"
#include "../include/dibujos.h"
#include "../include/coche.h"
#include <stdio.h>
#include <stdlib.h>
#include "../include/usuario.h"
#include "../include/sqlManager.h"
#include "../include/empleado.h"
#include "../include/cargo.h"

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
	printf("5. Gestionar cargos\n");
	printf("6. Gestionar marcas\n");
	printf("7. Gestionar modelos\n");
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
				menuGestCoches();
				break;
			case 2:
				menuGestUsuario();
				break;
			case 3:
				menuGestEmpleado();
				break;
			case 4:
				menuGestTienda();
				break;
			case 5:
				menuGestCargo();
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



