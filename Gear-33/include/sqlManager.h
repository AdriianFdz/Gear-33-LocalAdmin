/*
 * sqlManager.h
 *
 *  Created on: 21 mar 2024
 *      Author: seven
 */

#ifndef SQLMANAGER_H_
#define SQLMANAGER_H_

#include "sqlite3.h"


sqlite3* abrirDB();
int inicioSesion(char dni[], char contrasena[]);
int obtenerAnadirMarca(Coche c);
int obtenerAnadirModelo(Coche c);
int AnadirCoche(Coche c);
int EliminarCoche(char matricula[]);
int ExisteMatricula(char matricula[]);
int ModificarMatricula(char matricula[], char matriculaNueva[]);

#endif /* SQLMANAGER_H_ */
