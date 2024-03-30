#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/usuario.h"
#include "../include/dibujos.h"
#include "../include/menus.h"
#include "../include/sqlManager.h"
#include "../include/tienda.h"

Usuario pedirUsuario(){
	Usuario u;
	Usuario uNull;
	strcmp(uNull.dni, "NULL");
	int provinciaSelec = 0;
		int ciudadSelec = 0;

		int numeroProvincias = 0;
		int numeroCiudades = 0;
		obtenerNumeroProvincias(&numeroProvincias);
			Provincia listaProvincias[numeroProvincias];

	printf("Introduce el nombre: ");
			fflush(stdout);
			fflush(stdin);
			gets(u.nombre);

			printf("Introduce el apellido: ");
			fflush(stdout);
			fflush(stdin);
			gets(u.apellido);

			printf("Introduce el dni: ");
			fflush(stdout);
			fflush(stdin);
			gets(u.dni);

			printf("Introduce la fecha de nacimiento DD/MM/AAAA: ");
			fflush(stdout);
			fflush(stdin);
			gets(u.fecha);

			printf("Introduce el teléfono: ");
			fflush(stdout);
			fflush(stdin);
			gets(u.telefono);

			printf("Introduce la dirección: ");
			fflush(stdout);
			fflush(stdin);
			gets(u.direccion);

			printf("Introduce la contraseña: ");
			fflush(stdout);
			fflush(stdin);
			gets(u.contrasena);

			guardarProvincias(listaProvincias);
			pedirProvinciasUsuario(listaProvincias, numeroProvincias, &provinciaSelec, &uNull);
			u.provincia.id_provincia = listaProvincias[provinciaSelec-1].id_provincia;

			obtenerNumeroCiudades(&numeroCiudades, u.provincia.id_provincia);
			Ciudad listaCiudades[numeroCiudades];
			guardarCiudades(listaCiudades, u.provincia.id_provincia);
			pedirCiudadesUsuario(listaCiudades, numeroCiudades, &ciudadSelec, &uNull);
			u.ciudad.id_ciudad= listaCiudades[ciudadSelec-1].id_ciudad;

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
	scanf("%d",&opcion);
	opcionMenuGestUsuario(&opcion);
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
void menuAnadirUsuario() {
	dibujoPersona();
	printf(
			"---------------------------\n\n"
			"       Registro de usuario\n\n"
			"---------------------------\n\n");
	Usuario u = pedirUsuario();
	anadirUsuario(u);
	menuGestUsuario();
}
void menuModificarUsuario() {

	char dni[10] = "";
	int opcion = 0;
	Usuario usu;
	dibujoPersona();
	printf(
			"---------------------------\n\n"
			"      Modificar datos\n\n"
			"---------------------------\n\n");
	printf("Introduzca el dni:  ");
	fflush(stdout);
	fflush(stdin);
	gets(dni);


	int existe = existeUsuario(dni, &usu);

		if (existe == 0) {
			system("cls");
			printf("EL DNI INTRODUCIDO NO EXISTE\n");
			menuGestUsuario();
		}
	fflush(stdout);
	fflush(stdin);
	printf("\n1.Modificar nombre\n"
			"2.Modificar apellido\n"
			"3.Modificar DNI\n"
			"4.Modificar fecha de nacimiento\n"
			"5.Modificar teléfono\n"
			"6.Modificar dirección\n"
			"7.Modificar contraseña\n"
			"8.Modificar ciudad\n"
			"0.Volver\n\n"
			"Introduce una opción: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d", &opcion);
	opcionMenuModificarUsuarios(&opcion, &usu);

}
void menuEliminarUsuario() {

		char dni[10]= "";
		dibujoPersona();
		printf(
		"---------------------------\n\n"
		"       Eliminar usuario\n\n"
		"---------------------------\n\n");
		printf("Introduzca el dni:  ");
		fflush(stdout);
		fflush(stdin);
		gets(dni);
		int result = eliminarUsuario(dni);

			if (result == 1) {
				printf("USUARIO ELIMINADO CON EXITO\n");
				menuGestUsuario();
			} else {
				printf("DNI DEL USUARIO INVALIDO\n");
				menuGestUsuario();
			}

	}
void opcionMenuModificarUsuarios(int* opcion, Usuario* usu) {
	system("cls");
		switch (*opcion) {
			case 1:
				menuModificarNombre(usu);
				break;
			case 2:
				menuModificarApellido(usu);
				break;
			case 3:
				menuModificarDni(usu->dni);
				break;
			case 4:
				menuModificarFecha(usu);
				break;
			case 5:
				menuModificarTelefono(usu);
				break;
			case 6:
				menuModificarDireccion(usu);
				break;
			case 7:
				menuModificarContrasena(usu);
				break;
			case 8:
				menuModificarCiudadUsuario(usu);
				break;
			case 0:
				menuGestUsuario();
				break;
			default:
				printf("El digito introducido no corresponde a ninguno de los anteriores\n");
				menuModificarUsuario();
				break;
		}
}
void menuModificarNombre(Usuario* u) {
	char nombreNuevo[10];

	dibujoPersona();
	printf(
			"---------------------------\n\n"
			"    Modificar nombre\n\n"
			"---------------------------\n\n");
	printf("Antiguo nombre: %s\n", u->nombre);
	printf("Introduzca el nuevo nombre:  ");
	fflush(stdout);
	fflush(stdin);
	gets(nombreNuevo);
	modificarNombreUsuario(u->dni, nombreNuevo);
		menuGestUsuario();
}
void menuModificarApellido(Usuario* u) {
	char apellidoNuevo[10];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"    Modificar apellido\n\n"
	"---------------------------\n\n");
	printf("Antiguo apellido: %s\n", u->apellido);
	printf("Introduzca el nuevo apellido:  ");
	fflush(stdout);
	fflush(stdin);
	gets(apellidoNuevo);
	modificarApellidoUsuario(u->dni, apellidoNuevo);
	menuGestUsuario();
}
void menuModificarDni(char dni[10]) {
		char dniNuevo[10];

		dibujoPersona();
		printf(
		"---------------------------\n\n"
		"    Modificar dni\n\n"
		"---------------------------\n\n");
		printf("Antiguo DNI: %s\n", dni);
		printf("Introduzca el nuevo dni:  ");
		fflush(stdout);
		fflush(stdin);
		gets(dniNuevo);
		modificarDniUsuario(dni, dniNuevo);
		menuGestUsuario();
	}
void menuModificarFecha(Usuario* u) {
			char fechaNacNueva[11];

			dibujoPersona();
			printf(
			"---------------------------\n\n"
			"    Modificar la fecha de nacimiento\n\n"
			"---------------------------\n\n");
			printf("Antigua fecha de nacimiento: %s\n", u->fecha);
			printf("Introduzca la nueva fecha de nacimiento:  ");
			fflush(stdout);
			fflush(stdin);
			gets(fechaNacNueva);
			modificarFechaUsuario(u->dni, fechaNacNueva);
			menuGestUsuario();
		}
void menuModificarTelefono(Usuario* u) {
			char telefonoNuevo[10];
			dibujoPersona();
			printf(
			"---------------------------\n\n"
			"    Modificar el teléfono\n\n"
			"---------------------------\n\n");
			printf("Antiguo telefono: %s\n", u->telefono);
			printf("Introduzca el nuevo teléfono:  ");
			fflush(stdout);
			fflush(stdin);
			gets(telefonoNuevo);
			modificarTelefonoUsuario(u->dni, telefonoNuevo);
			menuGestUsuario();
			}
void menuModificarDireccion(Usuario* u) {
	char direccionNueva[51];

	dibujoPersona();
	printf(
	"---------------------------\n\n"
	"    Modificar la dirección\n\n"
	"---------------------------\n\n");
	printf("Antigua direccion: %s\n", u->direccion);
	printf("Introduzca la nueva dirección:  ");
	fflush(stdout);
	fflush(stdin);
	gets(direccionNueva);
	modificarDireccionUsuario(u->dni, direccionNueva);
	menuGestUsuario();
}
void menuModificarContrasena(Usuario* u) {
			char contrasenaNueva[51];

			dibujoPersona();
			printf(
			"---------------------------\n\n"
			"    Modificar la contraseña\n\n"
			"---------------------------\n\n");
			printf("Antigua contrasena: %s\n", u->contrasena);
			printf("Introduzca la nueva contraseña:  ");
			fflush(stdout);
			fflush(stdin);
			gets(contrasenaNueva);
			modificarContrasenaUsuario(u->dni, contrasenaNueva);
			menuGestUsuario();
		}

void menuModificarCiudadUsuario(Usuario* u){

	Provincia provincia;
		Ciudad ciudad;
		ciudad.id_ciudad = 0;

		int provinciaSelec = 0;
		int ciudadSelec = 0;

		int numeroProvincias = 0;
		int numeroCiudades = 0;

		dibujoPersona();
		printf(
		"---------------------------\n\n"
		"Modificar ciudad de usuario\n\n"
		"---------------------------\n\n");

		obtenerNumeroProvincias(&numeroProvincias);
		Provincia listaProvincias[numeroProvincias];
		guardarProvincias(listaProvincias);
		pedirProvinciasUsuario(listaProvincias, numeroProvincias, &provinciaSelec, u);
		provincia.id_provincia = listaProvincias[provinciaSelec-1].id_provincia;

		obtenerNumeroCiudades(&numeroCiudades, provincia.id_provincia);
		Ciudad listaCiudades[numeroCiudades];
		guardarCiudades(listaCiudades, provincia.id_provincia);


	printf("\nAntigua ciudad: %s\n", u->ciudad.nombre);
	pedirCiudadesUsuario(listaCiudades, numeroCiudades, &ciudadSelec, u);
	if (existeUsuario(u->dni, u) == 1) {
		printf("El usuario introducido ya existe\n");
	}
	ciudad.id_ciudad = listaCiudades[ciudadSelec-1].id_ciudad;
	modificarCiudadUsuario(u->dni, ciudad.id_ciudad);
	menuGestUsuario();
}

// funciones comunes
void pedirProvinciasUsuario(Provincia listaProvincias[], int numeroProvincias, int* provinciaSelec, Usuario* u){
	printf("Provincias:\n");
	imprimirProvinciasListaUsuario(listaProvincias, numeroProvincias);
	if(strcmp(u->dni, "NULL") != 0){
		printf("Antigua provincia: %s\n", u->provincia.nombre);
	}

	do {
		printf("Introduce la provincia: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%d", provinciaSelec);
		if ((*provinciaSelec > numeroProvincias) || (*provinciaSelec < 1)) {
			printf("La provincia seleccionada no existe\n");
		}
	} while(*provinciaSelec > numeroProvincias || *provinciaSelec < 1);
}
void pedirCiudadesUsuario(Ciudad listaCiudades[], int numeroCiudades, int* ciudadSelec, Usuario* u){
	printf("Ciudades:\n");
	imprimirCiudadesListaUsuario(listaCiudades, numeroCiudades);
	if(strcmp(u->dni, "NULL") != 0){
		printf("Antigua ciuadad: %s\n", u->ciudad.nombre);
	}

	do {
		printf("Introduce el id de la ciudad: ");
		fflush(stdout);
		fflush(stdin);
		scanf("%d", ciudadSelec);
		if ((*ciudadSelec > numeroCiudades) || (*ciudadSelec < 1)) {
			printf("La ciudad seleccionada no existe\n");
		}
	} while(*ciudadSelec > numeroCiudades || *ciudadSelec < 1);
}

void imprimirProvinciasListaUsuario(Provincia listaProvincias[], int numeroProvincias){
	for (int i = 0; i < numeroProvincias; i++) {
		printf("%d. %s\n", i+1, listaProvincias[i].nombre);
	}
}
void imprimirCiudadesListaUsuario(Ciudad listaCiudades[], int numeroCiudades){
	for (int i = 0; i < numeroCiudades; i++) {
		printf("%d. %s\n", i+1, listaCiudades[i].nombre);
	}
}



