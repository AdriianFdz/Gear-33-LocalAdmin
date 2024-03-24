/*
 * sqlManager.h
 *
 *  Created on: 21 mar 2024
 *      Author: seven
 */

#ifndef SQLMANAGER_H_
#define SQLMANAGER_H_

#include "sqlite3.h"
#include "coche.h"
#include "empleado.h"


sqlite3* abrirDB();
int inicioSesion(char dni[], char contrasena[]);
int obtenerAnadirMarca(Coche c);
int obtenerAnadirModelo(Coche c);
int anadirCoche(Coche c);
int eliminarCoche(char matricula[]);
int existeMatricula(char matricula[]);
int modificarMatricula(char matricula[], char matriculaNueva[]);
int modificarColor(char matricula[], char color[]);
int modificarPrecio(char matricula[], float precio);

int imprimirCargosTiendas();
int imprimirTiendas();

#endif /* SQLMANAGER_H_ */
