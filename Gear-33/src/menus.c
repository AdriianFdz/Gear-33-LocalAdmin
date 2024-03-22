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
	}

	printf("ERROR AL INICIAR SESION (PARAMETRO INVALIDO) \n");
	menuLogin();



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
	Coche c = pedirCoche();
	AnadirCoche(c);
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
	/////
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
