/*
 * empleado.h
 *
 *  Created on: 24 mar 2024
 *      Author: seven
 */

#ifndef INCLUDE_EMPLEADO_H_
#define INCLUDE_EMPLEADO_H_
#include "tienda.h"

typedef struct {
	int id_cargo;
	char nombre_cargo[10];
} Cargo;

typedef struct {
	char dni[10];
	char nombre[51];
	char apellido[51];
	char telefono[10];
	char fecha_nacimiento[11];
	char fecha_ini_contrato[11];
	char fecha_fin_contrato[11];
	Tienda tienda;
	Cargo cargo;
	char contrasena[51];

} Empleado;


// menu gestion empleado
void menuGestEmpleado();
void opcionMenuGestEmpleado(int* opcion);

	// menu anadir
	void menuAnadirEmpleado();

	// menu modificar
	void menuModificarEmpleado();
	void opcionMenuModificarEmpleado(int* opcion, Empleado* emp);

		// sub opciones
		void menuModificarDniEmp(char dni[10]);
		void menuModificarNombreEmp(Empleado* emp);
		void menuModificarApellidoEmp(Empleado* emp);
		void menuModificarTelefonoEmp(Empleado* emp);
		void menuModificarFechaNacEmp(Empleado* emp);
		void menuModificarFechaInicContEmp(Empleado* emp);
		void menuModificarFechaFinContEmp(Empleado* emp);
		void menuModificarTiendaEmp(Empleado* emp);
		void menuModificarCargoEmp(Empleado* emp);
		void menuModificarContrasenaEmp(Empleado* emp);

	// menu eliminar
	void menuEliminarEmpleado();

// funciones comunes
void pedirTiendas(Tienda listaTiendas[], int numeroTiendas, int* tiendaSelec, Empleado* e);
void pedirCargos(Cargo listaCargos[], int numeroCargos, int* cargoSelec, Empleado* e);

void imprimirTiendasLista(Tienda listaTiendas[], int numeroTiendas);
void imprimirCargosLista(Cargo listaCargos[], int numeroCargos);

Empleado pedirEmpleado();
#endif /* INCLUDE_EMPLEADO_H_ */
