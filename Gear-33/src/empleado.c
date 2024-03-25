/*
 * empleado.c
 *
 *  Created on: 24 mar 2024
 *      Author: seven
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/empleado.h"
#include "../include/dibujos.h"
#include "../include/sqlManager.h"
#include "../include/menus.h"


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

	scanf("%d",opcion);
	opcionMenuGestEmpleado(opcion);

}

void opcionMenuGestEmpleado(int* opcion){
	system("cls");
		switch (*opcion) {
				case 1:
					menuAnadirEmpleado(opcion);
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

void menuAnadirEmpleado(){
	dibujoPersona();
	printf(
		"---------------------------\n\n"
		"      Anadir empleado\n\n"
		"---------------------------\n\n");
	Empleado e = pedirEmpleado();
	anadirEmpleado(e);

}

Empleado pedirEmpleado(){
	Empleado e;

	printf("Introduce el DNI: ");
	fflush(stdout);
	fflush(stdin);
	gets(e.dni);

	printf("Introduce una contrasena: ");
	fflush(stdout);
	fflush(stdin);
	gets(e.contrasena);

	printf("Introduce el nombre: ");
	fflush(stdout);
	fflush(stdin);
	gets(e.nombre);

	printf("Introduce el apellido: ");
	fflush(stdout);
	fflush(stdin);
	gets(e.apellido);

	printf("Introduce el telefono: ");
	fflush(stdout);
	fflush(stdin);
	gets(e.telefono);

	printf("Introduce la fecha de nacimiento: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%s", e.fecha_nacimiento);

	printf("Introduce la fecha de inicio de contrato: ");
	fflush(stdout);
	fflush(stdin);
	gets(e.fecha_ini_contrato);

	printf("Introduce la fecha de fin de contrato: ");
	fflush(stdout);
	fflush(stdin);
	gets(e.fecha_fin_contrato);

	printf("Tiendas:\n");
	imprimirCargosTiendas("Tienda");
	printf("Introduce el ID de la tienda: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &e.id_tienda);

	printf("Cargos:\n");
	imprimirCargosTiendas("Cargo");
	printf("Introduce el ID del cargo: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &e.id_cargo);
	return e;
}

