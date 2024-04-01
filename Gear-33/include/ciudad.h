/*
 * ciudad.h
 *
 *  Created on: 1 abr 2024
 *      Author: Unai
 */

#ifndef INCLUDE_CIUDAD_H_
#define INCLUDE_CIUDAD_H_
#include "tienda.h"

void menuGestCiudad();
void opcionMenuGestCiudad(int* opcion);

void menuAnadirCiudad();
void menuEliminarCiudad();
void menuModificarCiudad();
void opcionMenuModificarCiudad(int* opcion, Ciudad* c);

void menuModificarNombreCiudad(Ciudad* c);

void menuModificarProvinciaCiudad(Ciudad* c);
#endif /* INCLUDE_CIUDAD_H_ */
