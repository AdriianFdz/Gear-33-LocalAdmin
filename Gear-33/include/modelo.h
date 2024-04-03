#ifndef INCLUDE_MODELO_H_
#define INCLUDE_MODELO_H_
#include "coche.h"

void menuGestModelo();
void opcionMenuGestModelo(int* opcion);

void menuAnadirModelo();
void menuEliminarModelo();
void menuModificarModelo();
void opcionMenuModificarModelo(int* opcion, Modelo* m);

void menuModificarNombreModelo(Modelo* m);
void menuModificarCambioModelo(Modelo* m);
void menuModificarCombustibleModelo(Modelo* m);
void menuModificarMarcaModelo(Modelo* m);
#endif /* INCLUDE_MODELO_H_ */
