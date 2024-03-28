
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

//void aniadirCoche(ListaCoches *lc, Coche c)
//{
//	if(lc->numCoches < lc->tam){
//			lc->lCoches[lc->numCoches] = c;
//			lc->numCoches++;
//			printf("Coche añadido correctamente\n");
//		}else{
//			printf("Lo sentimos! La lista esta completa\n");
//		}
//		fflush(stdout);
//
//}


//menus de coches
void menuGestCoches(){
	int opcion = 0;
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
	scanf("%d", &opcion);
	opcionMenuGestCoches(&opcion);

}
void opcionMenuGestCoches(int *opcion) {
	system("cls");
		switch (*opcion) {
				case 1:
					menuAnadirCoche();
					break;
				case 2:
					menuModificarCoche();
					break;
				case 3:
					menuEliminarCoche();
					break;
				case 0:
					menuPrincipal();
					break;
				default:
					printf("El digito introducido no corresponde a ninguno de los anteriores\n");
					menuGestCoches();
					break;
			}
}
void menuAnadirCoche() {
	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"       Anadir coche\n\n"
	"---------------------------\n\n");
	Coche c = pedirCoche();
	anadirCoche(c);
	menuGestCoches();
}
void menuModificarCoche() {
	int opcion = 0;
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
		menuGestCoches();
	}
	//
	fflush(stdout);
	fflush(stdin);
	printf("\n1.Modificar matricula\n"
	       "2.Modificar marca/modelo\n"
	       "3.Modificar color\n"
	       "4.Modificar año\n"
	       "5.Modificar precio\n"
	       "6.Modificar cambio\n"
	       "7.Modificar combustible\n"
	       "0.Volver\n\n"
		   "Introduce una opción: ");

	fflush(stdout);
	fflush(stdin);
	scanf("%d", &opcion);
	opcionMenuModificarCoches(&opcion, matricula);

}
void opcionMenuModificarCoches(int *opcion, char matricula[]) {
	system("cls");
		switch (*opcion) {
				case 1:
					menuModificarMatricula(matricula);
					break;
				case 2:
					menuModificarMarcaModelo(matricula);
					break;
				case 3:
					menuModificarColor(matricula);
					break;
				case 4:
					menuModificarAnyo(matricula);
					break;
				case 5:
					menuModificarPrecio(matricula);
					break;
				case 6:
					menuModificarCambio(matricula);
					break;
				case 7:
					menuModificarCombustible(matricula);
					break;
				case 0:
					menuGestCoches();
					break;
				default:
					printf("El digito introducido no corresponde a ninguno de los anteriores\n");
					menuModificarCoche();
					break;
			}
}
void menuModificarMatricula(char matricula[]) {
	char matriculaNueva[8];

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"    Modificar matricula\n\n"
	"---------------------------\n\n");
	printf("Introduzca la nueva matricula: ");
	fflush(stdout);
	fflush(stdin);
	gets(matriculaNueva);
	modificarMatricula(matricula, matriculaNueva);
	menuGestCoches();
}
void menuModificarMarcaModelo(char matricula[]) {
	int marca = 0;
	int modelo = 0 ;

	dibujoCoche();
	printf(
	"---------------------------\n\n"
	"   Modificar marca/modelo\n\n"
	"---------------------------\n\n");
	imprimirMarcas();
	fflush(stdout);
	fflush(stdin);
	printf("Introduzca la nueva marca:  ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &marca);
	imprimirModelos(marca);
	fflush(stdout);
	fflush(stdin);
	printf("Introduzca el nuevo modelo:  ");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &modelo);
	modificarMarcaModelo(matricula, modelo);
	menuGestCoches();
}

void menuModificarColor(char matricula[]) {
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
	menuGestCoches();
}
void menuModificarAnyo(char matricula[]) {
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
	menuGestCoches();
}
void menuModificarPrecio(char matricula[]) {
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
	menuGestCoches();
}
void menuModificarCambio(char matricula[]) {
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
	menuGestCoches();
}
void menuModificarCombustible(char matricula[]) {
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
	menuGestCoches();
}
void menuEliminarCoche() {
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
		menuGestCoches();
	} else {
		printf("MATRICULA INVALIDA\n");
		menuGestCoches();
	}

}
