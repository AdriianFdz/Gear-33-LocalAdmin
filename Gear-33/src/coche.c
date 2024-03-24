
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/coche.h"
#include "../include/dibujos.h"
#include "../include/sqlManager.h"
#include "../include/menus.h"

Coche pedirCoche()
{
	Coche c; 

	printf("Introduce la matricula \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.matricula);

	printf("Introduce el color \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.color);

	printf("Introduce el año \n");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &c.anyo);

	printf("Introduce el precio \n");
	fflush(stdout);
	fflush(stdin);
	scanf("%f", &c.precioBase);

	printf("Introduce la marca \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.marca);

	printf("Introduce el modelo \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.modelo);

	printf("Introduce el tipo de cambio \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.cambio);

	printf("Introduce el tipo de combustible \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.combustible);

	return c;
}

void aniadirCoche(ListaCoches *lc, Coche c)
{
	if(lc->numCoches < lc->tam){
			lc->lCoches[lc->numCoches] = c;
			lc->numCoches++;
			printf("Coche añadido correctamente\n");
		}else{
			printf("Lo sentimos! La lista esta completa\n");
		}
		fflush(stdout);

}


//menus de coches
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
	anadirCoche(c);
	menuGestCoches(opcion);
}
void menuModificarCoche(int* opcion) {
	char matricula[8];

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"      Modificar coche\n\n"
	"---------------------------\n\n");
	printf("Introduzca la matricula:  ");
	fflush(stdout);
	fflush(stdin);
	gets(matricula);


	int existe = existeMatricula(matricula);

	if (existe == 0) {
		system("cls");
		printf("LA MATRICULA INTRODUCIDA NO EXISTE\n");
		menuGestCoches(opcion);
	}
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
	opcionMenuModificarCoches(opcion, matricula);

}
void opcionMenuModificarCoches(int *opcion, char matricula[]) {
	system("cls");
		switch (*opcion) {
				case 1:
					menuModificarMatricula(opcion, matricula);
					break;
				case 2:
					menuModificarMarca(opcion, matricula);
					break;
				case 3:
					menuModificarModelo(opcion, matricula);
					break;
				case 4:
					menuModificarColor(opcion, matricula);
					break;
				case 5:
					menuModificarAnyo(opcion, matricula);
					break;
				case 6:
					menuModificarPrecio(opcion, matricula);
					break;
				case 7:
					menuModificarCambio(opcion, matricula);
					break;
				case 8:
					menuModificarCombustible(opcion, matricula);
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
void menuModificarMatricula(int *opcion, char matricula[]) {
	char matriculaNueva[8];

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"    Modificar matricula\n\n"
	"---------------------------\n\n");
	printf("Introduzca la nueva matricula:  ");
	fflush(stdout);
	fflush(stdin);
	gets(matriculaNueva);
	modificarMatricula(matricula, matriculaNueva);
	menuGestCoches(opcion);
}
void menuModificarMarca(int *opcion, char matricula[]) {
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
void menuModificarModelo(int *opcion, char matricula[]) {
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
void menuModificarColor(int *opcion, char matricula[]) {
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
	modificarColor(matricula, color);
	menuGestCoches(opcion);
}
void menuModificarAnyo(int *opcion, char matricula[]) {
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
	modificarAnyo(matricula, anyo);
	menuGestCoches(opcion);
}
void menuModificarPrecio(int *opcion, char matricula[]) {
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
	modificarPrecio(matricula, precio);
	menuGestCoches(opcion);
}
void menuModificarCambio(int *opcion, char matricula[]) {
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
	modificarCambio(matricula, cambio);
	menuGestCoches(opcion);
}
void menuModificarCombustible(int *opcion, char matricula[]) {
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
	modificarCombustible(matricula, combustible);
	menuGestCoches(opcion);
}
void menuEliminarCoche(int* opcion) {
	char matricula[8] = "";

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"       Eliminar coche\n\n"
	"---------------------------\n\n");
	printf("Introduzca la matricula:  ");
	fflush(stdout);
	fflush(stdin);
	gets(matricula);
	int result = eliminarCoche(matricula);
	system("cls");

	if (result == 1) {
		printf("COCHE ELIMINADO CON EXITO\n");
		menuGestCoches(opcion);
	}
	printf("MATRICULA INVALIDA\n");
	menuGestCoches(opcion);

}
