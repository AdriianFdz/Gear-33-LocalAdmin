#ifndef LISTACOCHES_H_
#define LISTACOCHES_H_

#include "coche.h"

typedef struct {
	Coche *lCoches;
	int tam;
	int numCoches;

}ListaCoches;

void aniadirCoche(ListaCoches *lc, Coche c);


#endif /* LISTACOCHES_H_ */
