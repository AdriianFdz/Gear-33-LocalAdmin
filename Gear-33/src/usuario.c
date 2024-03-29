#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/usuario.h"
#include "../include/dibujos.h"
#include "../include/menus.h"


void aniadirUsuario(ListaUsuarios *lu, Usuario u)
{
	if(lu->numUsuarios < lu->tam){
			lu->lUsuarios[lu->numUsuarios] = u;
			lu->numUsuarios++;
			printf("Usuario añadido correctamente\n");
		}else{
			printf("Lo sentimos! La lista esta completa\n");
		}
	fflush(stdout);

}
Usuario pedirUsuario(){
	Usuario u;
	printf("Introduce el nombre \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.nombre);

			printf("Introduce el apellido \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.apellido);

			printf("Introduce el dni \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.dni);

			printf("Introduce la fecha de nacimiento DD/MM/AAAA \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.fecha);

			printf("Introduce el teléfono \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.telefono);

			printf("Introduce la dirección \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.direccion);

			printf("Introduce la contraseña \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.contrasena);

			return u;
}


//menus de usuario
void menuGestUsuario(){
	int opcion = 0;
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
	Usuario u = pedirUsuario();

	menuGestUsuario(opcion);
}
void menuModificarUsuario(int* opcion) {

	char dni[9] = "";
	dibujoPersona();
	printf(
			"---------------------------\n\n"
			"      Modificar datos\n\n"
			"---------------------------\n\n");
	printf("Introduzca el dni:  ");
	fflush(stdout);
	fflush(stdin);
	gets(dni);


//falta funcion que comprueba si el dni existe

//
	fflush(stdout);
	fflush(stdin);
	printf("\n1.Modificar nombre\n"
			"2.Modificar apellido\n"
			"3.Modificar DNI\n"
			"4.Modificar fecha de nacimiento\n"
			"5.Modificar teléfono\n"
			"6.Modificar dirección\n"
			"7.Modificar contraseña\n"
			"0.Volver\n\n"
			"Introduce una opción: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d", opcion);
	opcionMenuModificarUsuarios(opcion);

}
void opcionMenuModificarUsuarios(int *opcion) {
	system("cls");
		switch (*opcion) {
			case 1:
				menuModificarNombre(opcion);
				break;
			case 2:
				menuModificarApellido(opcion);
				break;
			case 3:
				menuModificarDni(opcion);
				break;
			case 4:
				menuModificarFecha(opcion);
				break;
			case 5:
				menuModificarTelefono(opcion);
				break;
			case 6:
				menuModificarDireccion(opcion);
				break;
			case 7:
				menuModificarContrasena(opcion);
				break;
			case 0:
				menuGestUsuario(opcion);
				break;
			default:
				printf("El digito introducido no corresponde a ninguno de los anteriores\n");
				menuModificarUsuario(opcion);
				break;
		}
}
void menuModificarNombre(int *opcion) {
	char nombre[51];

	dibujoPersona();
	printf(
			"---------------------------\n\n"
			"    Modificar nombre\n\n"
			"---------------------------\n\n");
	printf("Introduzca el nuevo nombre:  ");
	fflush(stdout);
	fflush(stdin);
	gets(nombre);
// crear funcion para modificar el nombre

	menuGestUsuario(opcion);
}
void menuModificarApellido(int *opcion) {
	char apellido[51];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"    Modificar apellido\n\n"
	"---------------------------\n\n");
	printf("Introduzca el nuevo apellido:  ");
	fflush(stdout);
	fflush(stdin);
	gets(apellido);
	// crear funcion para modificar el apellido
	/////
	menuGestUsuario(opcion);
}
void menuModificarDni(int *opcion) {
		char dni[9];

		dibujoPersona();
		printf(
		"---------------------------\n\n"
		"    Modificar dni\n\n"
		"---------------------------\n\n");
		printf("Introduzca el nuevo dni:  ");
		fflush(stdout);
		fflush(stdin);
		gets(dni);
		// crear funcion para modificar el dni
		/////
		menuGestUsuario(opcion);
	}
void menuModificarFecha(int *opcion) {
			char fecha[11];

			dibujoPersona();
			printf(
			"---------------------------\n\n"
			"    Modificar la fecha de nacimiento\n\n"
			"---------------------------\n\n");
			printf("Introduzca la nueva fecha de nacimiento:  ");
			fflush(stdout);
			fflush(stdin);
			gets(fecha);
			// crear funcion para modificar la fecha de nacimiento
			/////
			menuGestUsuario(opcion);
		}
void menuModificarTelefono(int *opcion) {
			char telefono[9];
			dibujoPersona();
			printf(
			"---------------------------\n\n"
			"    Modificar el teléfono\n\n"
			"---------------------------\n\n");
			printf("Introduzca el nuevo teléfono:  ");
			fflush(stdout);
			fflush(stdin);
			gets(telefono);
			// crear funcion para modificar el teléfono
			/////
			menuGestUsuario(opcion);
			}
void menuModificarDireccion(int *opcion) {
	char direccion[51];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"    Modificar la dirección\n\n"
	"---------------------------\n\n");
	printf("Introduzca la nueva dirección:  ");
	fflush(stdout);
	fflush(stdin);
	gets(direccion);
	// crear funcion para modificar la dirección
	/////
	menuGestUsuario(opcion);
}
void menuModificarContrasena(int *opcion) {
			char contrasena[51];

			dibujoPersona();
			printf(
			"---------------------------\n\n"
			"    Modificar la contraseña\n\n"
			"---------------------------\n\n");
			printf("Introduzca la neuva contraseña:  ");
			fflush(stdout);
			fflush(stdin);
			gets(contrasena);
			// crear funcion para modificar la contraseña
			/////
			menuGestUsuario(opcion);
		}
void menuEliminarUsuario(int* opcion) {

		char dni[9]= "";
		dibujoPersona();
		printf(
		"---------------------------\n\n"
		"       Eliminar usuario\n\n"
		"---------------------------\n\n");
		printf("Introduzca el dni:  ");
		fflush(stdout);
		fflush(stdin);
		gets(dni);
		opcionMenuGestUsuario(opcion);

	}
