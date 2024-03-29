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

// funciones generales
sqlite3* abrirDB();
int inicioSesion(char dni[], char contrasena[]);

// coches
int anadirCoche(Coche c);
int eliminarCoche(char matricula[]);
int existeMatricula(char matricula[], Coche* c);
int modificarMatricula(char matricula[], char matriculaNueva[]);
int modificarColor(char matricula[], char color[]);
int modificarPrecio(char matricula[], float precio);
int modificarAnyo(char matricula[], int anyo);
int modificarMarcaModelo(char matricula[], int id_modelo);
int guardarMarcas(Marca marcas[]);
int guardarModelos(Modelo modelos[], int id_marca);
int obtenerNumeroMarcas(int* numero);
int obtenerNumeroModelos(int* numero, int id_marca);

// empleado
int anadirEmpleado(Empleado e);
int eliminarEmpleado(char dni[10]);
int existeEmpleado(char dni[10], Empleado* e);
int modificarDniEmp(char dni[10], char dniNuevo[10]);
int modificarNombreEmp(char dni[10], char nombreNuevo[51]);
int modificarApellidoEmp(char dni[10], char apellidoNuevo[51]);
int modificarTelefonoEmp(char dni[10], char telefonoNuevo[10]);
int modificarFechaNacEmp(char dni[10], char fechaNacNueva[11]);
int modificarFechaInicContEmp(char dni[10], char fechaInicContNueva[11]);
int modificarFechaFinContEmp(char dni[10], char fechaFinContNueva[11]);
int modificarIdTiendaEmp(char dni[10], int nuevoIdTienda);
int modificarIdCargoEmp(char dni[10], int nuevoIdCargo);
int modificarContrasenaEmp(char dni[10], char contrasenaNueva[51]);
int guardarTiendas(Tienda tiendas[]);
int guardarCargos(Cargo cargos[]);
int imprimirCargosTiendas();
int obtenerNumeroCargos(int* numero);
int obtenerNumeroTiendas(int* numero);
#endif /* SQLMANAGER_H_ */
