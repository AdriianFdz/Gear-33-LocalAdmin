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
#include "../include/tienda.h"

// menu gestion empleado
void menuGestEmpleado(){
	int opcion = 0;
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

	scanf("%d",&opcion);
	opcionMenuGestEmpleado(&opcion);

}
void opcionMenuGestEmpleado(int* opcion){
	system("cls");
		switch (*opcion) {
				case 1:
					menuAnadirEmpleado();
					break;
				case 2:
					menuModificarEmpleado();
					break;
				case 3:
					menuEliminarEmpleado();
					break;
				case 0:
					menuPrincipal();
					break;
				default:
					printf("El digito introducido no corresponde a ninguno de los anteriores\n");
					menuGestEmpleado();
					break;
			}
}

	// menu anadir
void menuAnadirEmpleado(){
	dibujoPersona();
	printf(
		"---------------------------\n\n"
		"      Anadir empleado\n\n"
		"---------------------------\n\n");
	Empleado e = pedirEmpleado();
	anadirEmpleado(e);
	menuGestEmpleado();
}

	// menu modificar
void menuModificarEmpleado(){
	char dni[10];
	int opcion = 0;
	Empleado emp;

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"    Modificar empleado\n\n"
	"---------------------------\n\n");
	printf("Introduzca el dni: ");
	fflush(stdout);
	fflush(stdin);
	gets(dni);

	strcpy(emp.dni, dni);
	int existe = existeEmpleado(dni, &emp);

	if (existe == 0) {
		system("cls");
		printf("EL DNI INTRODUCIDO NO EXISTE\n");
		menuGestEmpleado();
	}

	printf("\n1.Modificar dni\n"
	       "2.Modificar nombre\n"
	       "3.Modificar apellido\n"
	       "4.Modificar telefono\n"
	       "5.Modificar fecha de nacimiento\n"
	       "6.Modificar fecha de inicio de contrato\n"
	       "7.Modificar fecha de fin de contrato\n"
	       "8.Modificar tienda\n"
	       "9.Modificar cargo\n"
	       "10.Modificar contrasena\n"
	       "0.Volver\n\n"
		   "Introduce una opción: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d", &opcion);
	opcionMenuModificarEmpleado(&opcion, &emp);
}
void opcionMenuModificarEmpleado(int* opcion, Empleado* emp){
	system("cls");
	switch (*opcion) {
		case 1:
			menuModificarDniEmp(emp->dni);
			break;
		case 2:
			menuModificarNombreEmp(emp);
			break;
		case 3:
			menuModificarApellidoEmp(emp);
			break;
		case 4:
			menuModificarTelefonoEmp(emp);
			break;
		case 5:
			menuModificarFechaNacEmp(emp);
			break;
		case 6:
			menuModificarFechaInicContEmp(emp);
			break;
		case 7:
			menuModificarFechaFinContEmp(emp);
			break;
		case 8:
			menuModificarTiendaEmp(emp);
			break;
		case 9:
			menuModificarCargoEmp(emp);
			break;
		case 10:
			menuModificarContrasenaEmp(emp);
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

		// sub opciones
void menuModificarDniEmp(char dni[10]){
	char dniNuevo[10];
	Empleado e;
	strcpy(e.dni, "NULL");

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"       Modificar DNI\n\n"
	"---------------------------\n\n");
	printf("Antiguo DNI: %s\n", dni);
	do {
		printf("Introduzca el nuevo DNI: ");
		fflush(stdout);
		fflush(stdin);
		gets(dniNuevo);
		if (existeEmpleado(dniNuevo, &e) == 1) {
			printf("El DNI introducido ya existe\n");
		}
	} while (existeEmpleado(dniNuevo, &e) == 1);
	modificarDniEmp(dni, dniNuevo);
	menuGestEmpleado();
}
void menuModificarNombreEmp(Empleado* emp){
	char nombreNuevo[10];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"     Modificar nombre\n\n"
	"---------------------------\n\n");
	printf("Antiguo nombre: %s\n", emp->nombre);
	printf("Introduzca el nuevo nombre: ");
	fflush(stdout);
	fflush(stdin);
	gets(nombreNuevo);
	modificarNombreEmp(emp->dni, nombreNuevo);
	menuGestEmpleado();
}
void menuModificarApellidoEmp(Empleado* emp){
	char apellidoNuevo[10];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"    Modificar apellido\n\n"
	"---------------------------\n\n");
	printf("Antiguo apellido: %s\n", emp->apellido);
	printf("Introduzca el nuevo apellido: ");
	fflush(stdout);
	fflush(stdin);
	gets(apellidoNuevo);
	modificarApellidoEmp(emp->dni, apellidoNuevo);
	menuGestEmpleado();
}
void menuModificarTelefonoEmp(Empleado* emp){
	char telefonoNuevo[10];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"    Modificar telefono\n\n"
	"---------------------------\n\n");
	printf("Antiguo telefono: %s\n", emp->telefono);
	printf("Introduzca el nuevo telefono: ");
	fflush(stdout);
	fflush(stdin);
	gets(telefonoNuevo);
	modificarTelefonoEmp(emp->dni, telefonoNuevo);
	menuGestEmpleado();
}
void menuModificarFechaNacEmp(Empleado* emp){
	char fechaNacNueva[11];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"Modificar fecha de nacimiento\n\n"
	"---------------------------\n\n");
	printf("Antigua fecha de nacimiento: %s\n", emp->fecha_nacimiento);
	printf("Introduzca la nueva fecha de nacimiento: ");
	fflush(stdout);
	fflush(stdin);
	gets(fechaNacNueva);
	modificarFechaNacEmp(emp->dni, fechaNacNueva);
	menuGestEmpleado();
}
void menuModificarFechaInicContEmp(Empleado* emp){
	char fechaInicContNueva[11];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"Modificar fecha inicio de contrato\n\n"
	"---------------------------\n\n");
	printf("Antigua fecha de inicio de contrato: %s\n", emp->fecha_ini_contrato);
	printf("Introduzca la nueva fecha de inicio de contrato: ");
	fflush(stdout);
	fflush(stdin);
	gets(fechaInicContNueva);
	modificarFechaInicContEmp(emp->dni, fechaInicContNueva);
	menuGestEmpleado();
}
void menuModificarFechaFinContEmp(Empleado* emp){
	char fechaFinContNueva[11];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"Modificar fecha fin de contrato\n\n"
	"---------------------------\n\n");
	printf("Antigua fecha de fin de contrato: %s\n", emp->fecha_fin_contrato);
	printf("Introduzca la nueva fecha de fin de contrato: ");
	fflush(stdout);
	fflush(stdin);
	gets(fechaFinContNueva);
	modificarFechaFinContEmp(emp->dni, fechaFinContNueva);
	menuGestEmpleado();
}
void menuModificarTiendaEmp(Empleado* emp){

	int tiendaSelec = 0;

	int numeroTiendas = 0;

	obtenerNumeroTiendas(&numeroTiendas);
	Tienda listaTiendas[numeroTiendas];
	guardarTiendas(listaTiendas);

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"Modificar tienda de empleado\n\n"
	"---------------------------\n\n");
	pedirTiendas(listaTiendas, numeroTiendas, &tiendaSelec, emp);

	modificarIdTiendaEmp(emp->dni, listaTiendas[tiendaSelec-1].id_tienda);
	menuGestEmpleado();
}
void menuModificarCargoEmp(Empleado* emp){
	int cargoSelec = 0;

	int numeroCargos = 0;

	obtenerNumeroCargos(&numeroCargos);
	Cargo listaCargos[numeroCargos];
	guardarCargos(listaCargos);

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"Modificar cargo de empleado\n\n"
	"---------------------------\n\n");
	pedirCargos(listaCargos, numeroCargos, &cargoSelec, emp);

	modificarIdCargoEmp(emp->dni, listaCargos[cargoSelec-1].id_cargo);
	menuGestEmpleado();
}
void menuModificarContrasenaEmp(Empleado* emp){
	char contrasenaNueva[51];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"   Modificar contrasena\n\n"
	"---------------------------\n\n");
	printf("Antigua contrasena: %s\n", emp->contrasena);
	printf("Introduzca la nueva contrasena: ");
	fflush(stdout);
	fflush(stdin);
	gets(contrasenaNueva);
	modificarContrasenaEmp(emp->dni, contrasenaNueva);
	menuGestEmpleado();
}

	// menu eliminar
void menuEliminarEmpleado(){
	char dni[10] = "";
	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"     Eliminar empleado\n\n"
	"---------------------------\n\n");
	printf("Introduce el DNI: ");
	fflush(stdout);
	fflush(stdin);
	gets(dni);

	int result = eliminarEmpleado(dni);

	if (result == 1) {
		printf("EMPLEADO ELIMINADO CON EXITO\n");
		menuGestEmpleado();
	} else {
		printf("DNI DEL EMPLEADO INVALIDO\n");
		menuGestEmpleado();
	}

}


// funciones comunes
void pedirTiendas(Tienda listaTiendas[], int numeroTiendas, int* tiendaSelec, Empleado* e){
	printf("Tiendas:\n");
	imprimirTiendasLista(listaTiendas, numeroTiendas);
	if(strcmp(e->dni, "NULL") != 0){
		printf("Antigua tienda: %s\n", e->tienda.direccion);
	}

	do {
		printf("Introduce la tienda: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%d", tiendaSelec);
		if ((*tiendaSelec > numeroTiendas) || (*tiendaSelec < 1)) {
			printf("La tienda seleccionada no existe\n");
		}
	} while(*tiendaSelec> numeroTiendas|| *tiendaSelec < 1);
}
void pedirCargos(Cargo listaCargos[], int numeroCargos, int* cargoSelec, Empleado* e){
	printf("Cargos:\n");
	imprimirCargosLista(listaCargos, numeroCargos);
	if(strcmp(e->dni, "NULL") != 0){
		printf("Antiguo cargo: %s\n", e->cargo.nombre_cargo);
	}

	do {
		printf("Introduce el cargo: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%d", cargoSelec);
		if ((*cargoSelec > numeroCargos) || (*cargoSelec < 1)) {
			printf("El cargo seleccionada no existe\n");
		}
	} while(*cargoSelec> numeroCargos|| *cargoSelec < 1);
}

Empleado pedirEmpleado(){


	Empleado e;
	Empleado eNull;
	strcpy(eNull.dni, "NULL");
	int tiendaSelec = 0;
	int cargoSelec = 0;

	int numeroTiendas = 0;
	obtenerNumeroTiendas(&numeroTiendas);
	Tienda listaTiendas[numeroTiendas];

	int numeroCargos = 0;
	obtenerNumeroCargos(&numeroCargos);
	Cargo listaCargos[numeroCargos];


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

	guardarTiendas(listaTiendas);
	pedirTiendas(listaTiendas, numeroTiendas, &tiendaSelec, &eNull);
	e.tienda.id_tienda = listaTiendas[tiendaSelec-1].id_tienda;

	guardarCargos(listaCargos);
	pedirCargos(listaCargos, numeroCargos, &cargoSelec, &eNull);
	e.cargo.id_cargo = listaCargos[cargoSelec-1].id_cargo;

	return e;
}

