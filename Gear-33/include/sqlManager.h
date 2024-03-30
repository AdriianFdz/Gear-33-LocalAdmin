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
#include "tienda.h"
#include "usuario.h"

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
int modificarMarcaModeloCoche(char matricula[], int id_modelo);
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

// tienda
int guardarProvincias(Provincia provincias[]);
int obtenerNumeroProvincias(int* numero);
int existeTienda(char direccion[51], int id_ciudad, Tienda* t);
int anadirTienda(Tienda t);
int modificarDirecTienda(int id, char direccionNueva[51]);
int modificarTelefTienda(int id, char telefono[10]);
int modificarCiudadTienda(int id, int id_ciudad);

int eliminarTienda(char direccion[], int id_ciudad);
int obtenerNumeroCiudades(int* numero, int id_provincia);
int guardarCiudades(Ciudad ciudades[], int id_provincia);

// cargo
int anadirCargo(Cargo c);
int eliminarCargo(char nombre[20]);
int modificarNombreCargo(int id_cargo, char nuevoNombre[20]);
int existeCargo(char cargo[20], Cargo* c);

// usuario
int anadirUsuario(Usuario u);
int existeUsuario(char dni[10], Usuario* u);
int eliminarUsuario(char dni[10]);
int modificarDniUsuario(char dni[10], char dniNuevo[10]);
int modificarNombreUsuario(char dni[10], char nombreNuevo[51]);
int modificarApellidoUsuario(char dni[10], char apellidoNuevo[51]);
int modificarFechaUsuario(char dni[10], char fechaNueva[11]);
int modificarTelefonoUsuario(char dni[10], char telefonoNuevo[10]);
int modificarDireccionUsuario(char dni[10], char direccionNueva[51]);
int modificarContrasenaUsuario(char dni[10], char contrasenaNueva[51]);
int modificarCiudadUsuario(char dni[10], int id_ciudad);

// marca
int anadirMarca(Marca m);
int existeMarca(char marca[20], Marca* m);
int eliminarMarca(char nombre[20]);
int modificarNombreMarca(int id_marca, char nuevoNombre[20]);

// modelo
int anadirModelo(Modelo m);
int existeModelo(char nombre[20], int id_marca, char combustible[20], char cambio[20], Modelo* m);
int eliminarModelo(Modelo m);
int modificarNombreModelo(int id_modelo, char nuevoNombre[20]);
int modificarCambioModelo(int id_modelo, char nuevoCambio[20]);
int modificarCombustibleModelo(int id_modelo, char nuevoCombustible[20]);
int modificarMarcaModelo(int id_modelo, int id_marca);
#endif /* SQLMANAGER_H_ */
