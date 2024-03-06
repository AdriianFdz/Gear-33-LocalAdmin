#include "listaCoches.h"
#include <stdio.h>


void aniadirUsuario(ListaCoches *lc, Coche c)
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


