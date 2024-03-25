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
int modificarAnyo(char matricula[], int anyo);
int modificarCambio(char matricula[], char cambio[]);
int modificarCombustible(char matricula[], char combustible[]);
int modificarMarcaModelo(char matricula[], int id_modelo);
int imprimirMarcas();
int imprimirModelos(int id_marca);

int imprimirCargosTiendas();
int anadirEmpleado(Empleado e);



#endif /* SQLMANAGER_H_ */
