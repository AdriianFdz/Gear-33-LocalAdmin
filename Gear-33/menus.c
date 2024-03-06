#include "menus.h"
#include "dibujos.h"
#include <stdio.h>

char menuPrincipal()
{
	char opcion;
	dibujoLogo();
	printf("------------------------------------------------\n");
	printf("1. Gestionar usuarios\n");
	printf("2. Gestionar coches\n");
	printf("3. Gestionar empleados\n");
	printf("4. Gestionar tiendas\n");
	printf("0. Salir\n\n");
	printf("Elige una opcion: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%c",&opcion);
	return opcion;
}

