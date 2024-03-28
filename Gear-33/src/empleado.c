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

	int existe = existeEmpleado(dni, &emp);

	if (existe == 0) {
		system("cls");
		printf("EL DNI INTRODUCIDO NO EXISTE\n");
		menuGestEmpleado();
	}
	fflush(stdout);
	fflush(stdin);
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

void menuModificarDniEmp(char dni[10]){
	char dniNuevo[10];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"       Modificar DNI\n\n"
	"---------------------------\n\n");
	printf("Antiguo DNI: %s\n", dni);
	printf("Introduzca el nuevo DNI: ");
	fflush(stdout);
	fflush(stdin);
	gets(dniNuevo);
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
	int idTiendaNueva;

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"Modificar tienda de empleado\n\n"
	"---------------------------\n\n");
	printf("Tiendas:\n");
	imprimirCargosTiendas("Tienda");

	printf("\nAntiguo id de tienda: %d\n", emp->id_tienda);
	printf("Introduzca el nuevo id de tienda: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &idTiendaNueva);
	modificarIdTiendaEmp(emp->dni, idTiendaNueva);
	menuGestEmpleado();
}
void menuModificarCargoEmp(Empleado* emp){
	int idCargoNuevo;

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"Modificar cargo de empleado\n\n"
	"---------------------------\n\n");
	printf("Cargos:\n");
	imprimirCargosTiendas("Cargo");

	printf("\nAntiguo id de cargo: %d\n", emp->id_cargo);
	printf("Introduzca el nuevo id de cargo: ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &idCargoNuevo);
	modificarIdCargoEmp(emp->dni, idCargoNuevo);
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

