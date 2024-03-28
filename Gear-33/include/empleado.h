/*
 * empleado.h
 *
 *  Created on: 24 mar 2024
 *      Author: seven
 */

#ifndef INCLUDE_EMPLEADO_H_
#define INCLUDE_EMPLEADO_H_

typedef struct {
	char dni[10];
	char nombre[51];
	char apellido[51];
	char telefono[10];
	char fecha_nacimiento[11];
	char fecha_ini_contrato[11];
	char fecha_fin_contrato[11];
	int id_tienda;
	int id_cargo;
	char contrasena[51];

} Empleado;

typedef struct {
	int id_cargo;
	char nombre_cargo[10];
} Cargo;


void menuGestEmpleado();
void opcionMenuGestEmpleado(int* opcion);
void menuAnadirEmpleado();
void menuModificarEmpleado();
void menuEliminarEmpleado();

void opcionMenuModificarEmpleado(int* opcion, Empleado* emp);
void menuModificarDniEmp(char dni[10]);
void menuModificarNombreEmp(Empleado* emp);
void menuModificarApellidoEmp(Empleado* emp);
void menuModificarTelefonoEmp(Empleado* emp);
void menuModificarFechaNacEmp(Empleado* emp);
void menuModificarFechaInicContEmp(Empleado* emp);
void menuModificarFechaFinContEmp(Empleado* emp);
void menuModificarTiendaEmp(Empleado* emp);
void menuModificarCargoEmp(Empleado* emp);








Empleado pedirEmpleado();





#endif /* INCLUDE_EMPLEADO_H_ */
