
#include "coche.h"
#include <stdio.h>

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
