/*
 * sqlManager.c
 *
 *  Created on: 21 mar 2024
 *      Author: seven
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../include/sqlite3.h"
#include "../../include/coche.h"
#include "../../include/sqlManager.h"
#include "../../include/fichero.h"
#include "../../include/empleado.h"
#include "../../include/tienda.h"
#include "../../include/cargo.h"
#include "../../include/usuario.h"

// funciones generales
sqlite3* abrirDB() {
	//CONFIG *datosConfig = malloc(sizeof(CONFIG));
	CONFIG datosConfig;
	leerConfig(&datosConfig);

	sqlite3 *db;

	int result = sqlite3_open(datosConfig.database, &db);
	//free(datosConfig);
	if (result != SQLITE_OK) {
		printf("Error opening database\n");
	}

	return db;
}
int inicioSesion(char dni[], char contrasena[]) {
	sqlite3 *db = abrirDB();
	int result = 0;

	sqlite3_stmt *stmt;

	char sql[] = "SELECT dni, contrasena FROM empleado WHERE dni = ?";

	result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		if (strcmp(dni, (char*) sqlite3_column_text(stmt, 0)) == 0
				&& strcmp(contrasena, (char*) sqlite3_column_text(stmt, 1))
						== 0) {
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return 1;
		}

	} else if (result != SQLITE_DONE) {
		printf("Error fetching data\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 0;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}

// coches
int anadirCoche(Coche c) {
	Coche cNull;
	strcpy(cNull.matricula, "NULL");
	int resultado = existeMatricula(c.matricula, &cNull);

	sqlite3 *db = abrirDB();

	if (resultado != 0) {

		printf("La matricula introducida ya existe\n");
		return 0;
	} else {
		int result;

		sqlite3_stmt *stmt2;
		char sql2[] = "INSERT INTO Coche VALUES (?, ?, ?, ?, ?)";
		result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt2, 1, c.matricula, strlen(c.matricula),
				SQLITE_STATIC);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt2);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_text(stmt2, 2, c.color, strlen(c.color),
				SQLITE_STATIC);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt2);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_double(stmt2, 3, c.precioBase);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt2);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_int(stmt2, 4, c.anyo);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt2);
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_int(stmt2, 5, c.modelo.id);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt2);
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_step(stmt2);

		if (result != SQLITE_DONE) {
			printf("Error executing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt2);
			sqlite3_close(db);
			return 0;
		}

		sqlite3_finalize(stmt2);

	}

	sqlite3_close(db);
	return 0;
}
int eliminarCoche(char matricula[]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "SELECT matricula FROM Coche WHERE matricula = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, matricula, strlen(matricula),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		sqlite3_finalize(stmt);
		sqlite3_stmt *stmt2;
		char sql2[] = "DELETE FROM Coche WHERE matricula = ?";

		result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt2, 1, matricula, strlen(matricula),
				SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt2);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_step(stmt2);

		sqlite3_finalize(stmt2);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;

}
int existeMatricula(char matricula[], Coche *c) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] =
			"SELECT c.*, mo.nombre, mo.cambio, mo.combustible, ma.* FROM Coche c, Modelo mo, Marca ma WHERE c.id_modelo = mo.id AND mo.id_marca = ma.id AND c.matricula = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, matricula, strlen(matricula),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		if (strcmp(c->matricula, "NULL") != 0) {
			strcpy(c->matricula, matricula);
			strcpy(c->color, (char*) sqlite3_column_text(stmt, 1));
			c->precioBase = sqlite3_column_double(stmt, 2);
			c->anyo = sqlite3_column_int(stmt, 3);
			c->modelo.id = sqlite3_column_int(stmt, 4);
			strcpy(c->modelo.nombre, (char*) sqlite3_column_text(stmt, 5));
			strcpy(c->modelo.cambio, (char*) sqlite3_column_text(stmt, 6));
			strcpy(c->modelo.combustible, (char*) sqlite3_column_text(stmt, 7));
			c->marca.id = sqlite3_column_int(stmt, 8);
			strcpy(c->marca.nombre, (char*) sqlite3_column_text(stmt, 9));
		}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;

}
int modificarMatricula(char matricula[], char matriculaNueva[]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Coche SET matricula = ? WHERE matricula = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, matriculaNueva, strlen(matriculaNueva),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, matricula, strlen(matricula),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}

	sqlite3_stmt *stmt2;

	char sql2[] = "UPDATE Adquisicion SET matricula = ? WHERE matricula = ?";

	result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt2, 1, matriculaNueva, strlen(matriculaNueva),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt2);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt2, 2, matricula, strlen(matricula),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt2);

	result = sqlite3_finalize(stmt2);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE2)\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarColor(char matricula[], char color[]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Coche SET color = ? WHERE matricula = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, color, strlen(color), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, matricula, strlen(matricula),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarPrecio(char matricula[], float precio) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Coche SET precio_base = ? WHERE matricula = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_double(stmt, 1, precio);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, matricula, strlen(matricula),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarAnyo(char matricula[], int anyo) {

	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Coche SET anyo = ? WHERE matricula = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, anyo);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, matricula, strlen(matricula),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarMarcaModeloCoche(char matricula[], int id_modelo) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Coche SET id_modelo = ? WHERE matricula = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, id_modelo);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, matricula, strlen(matricula),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int guardarMarcas(Marca marcas[]) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] = "SELECT id, nombre FROM Marca";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	int contador = 0;
	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			marcas[contador].id = sqlite3_column_int(stmt, 0);
			strcpy(marcas[contador].nombre,
					(char*) sqlite3_column_text(stmt, 1));
			contador++;
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;

}
int guardarModelos(Modelo modelos[], int id_marca) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] = "SELECT mo.*, ma.nombre FROM Modelo mo, Marca ma WHERE mo.id_marca = ma.id AND mo.id_marca = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_bind_int(stmt, 1, id_marca);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	int contador = 0;
	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			modelos[contador].id = sqlite3_column_int(stmt, 0);
			strcpy(modelos[contador].nombre,(char*) sqlite3_column_text(stmt, 1));
			strcpy(modelos[contador].cambio,(char*) sqlite3_column_text(stmt, 2));
			strcpy(modelos[contador].combustible,(char*) sqlite3_column_text(stmt, 3));
			modelos[contador].marca.id= sqlite3_column_int(stmt, 4);
			strcpy(modelos[contador].marca.nombre,(char*) sqlite3_column_text(stmt, 5));
			contador++;
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;

}
int obtenerNumeroMarcas(int *numero) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] = "SELECT count(*) FROM Marca";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		*numero = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int obtenerNumeroModelos(int *numero, int id_marca) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] = "SELECT count(*) FROM Modelo WHERE id_marca = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_int(stmt, 1, id_marca);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		*numero = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}

// empleados
int anadirEmpleado(Empleado e) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	Empleado eNull;
	strcpy(eNull.dni, "NULL");
	int resultado = existeEmpleado(e.dni, &eNull);

	if (resultado != 0) {
		printf("El empleado ya existe\n");
		return 0;
	} else {
		char sql2[] =
				"INSERT INTO Empleado VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		int result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt,
				NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result += sqlite3_bind_text(stmt, 1, e.dni, strlen(e.dni),
				SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 2, e.nombre, strlen(e.nombre),
				SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 3, e.apellido, strlen(e.apellido),
				SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 4, e.telefono, strlen(e.telefono),
				SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 5, e.fecha_nacimiento,
				strlen(e.fecha_nacimiento), SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 6, e.fecha_ini_contrato,
				strlen(e.fecha_ini_contrato), SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 7, e.fecha_fin_contrato,
				strlen(e.fecha_fin_contrato), SQLITE_STATIC);
		result += sqlite3_bind_int(stmt, 8, e.tienda.id_tienda);
		result += sqlite3_bind_int(stmt, 9, e.cargo.id_cargo);
		result += sqlite3_bind_text(stmt, 10, e.contrasena,
				strlen(e.contrasena), SQLITE_STATIC);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into Empleado\n");
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		printf("Empleado anadido correctamente\n");
		return 0;
	}
}
int eliminarEmpleado(char dni[10]) {
	sqlite3 *db = abrirDB();
	Empleado e;
	int result = existeEmpleado(dni, &e);

	if (result == 1) {
		sqlite3_stmt *stmt;
		char sql[] = "DELETE FROM Empleado WHERE dni = ?";

		result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_step(stmt);

		sqlite3_finalize(stmt);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_close(db);
	return 0;
}
int existeEmpleado(char dni[10], Empleado *e) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] =
			"SELECT e.*, t.direccion, c.nombre FROM Empleado e, Tienda t, Cargo c WHERE e.id_cargo = c.id AND e.id_tienda = t.id AND dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {

		if (strcmp(e->dni, "NULL") != 0) {
			strcpy(e->dni, dni);
			strcpy(e->nombre, (char*) sqlite3_column_text(stmt, 1));
			strcpy(e->apellido, (char*) sqlite3_column_text(stmt, 2));
			strcpy(e->telefono, (char*) sqlite3_column_text(stmt, 3));
			strcpy(e->fecha_nacimiento, (char*) sqlite3_column_text(stmt, 4));
			strcpy(e->fecha_ini_contrato, (char*) sqlite3_column_text(stmt, 5));
			strcpy(e->fecha_fin_contrato, (char*) sqlite3_column_text(stmt, 6));
			e->tienda.id_tienda = sqlite3_column_int(stmt, 7);
			e->cargo.id_cargo = sqlite3_column_int(stmt, 8);
			strcpy(e->contrasena, (char*) sqlite3_column_text(stmt, 9));
			strcpy(e->tienda.direccion, (char*) sqlite3_column_text(stmt, 10));
			strcpy(e->cargo.nombre_cargo,
					(char*) sqlite3_column_text(stmt, 11));
		}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int modificarDniEmp(char dni[10], char dniNuevo[10]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Empleado SET dni = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, dniNuevo, strlen(dniNuevo),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating DNI empleado\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}
	sqlite3_stmt *stmt2;

	char sql2[] =
			"UPDATE Adquisicion SET dni_empleado = ? WHERE dni_empleado = ?";

	result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt2, 1, dniNuevo, strlen(dniNuevo),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt2);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt2, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt2);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt2);
	if (result != SQLITE_DONE) {
		printf("Error updating DNI\n");
		sqlite3_finalize(stmt2);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_finalize(stmt2);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarNombreEmp(char dni[10], char nombreNuevo[51]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Empleado SET nombre = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, nombreNuevo, strlen(nombreNuevo),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating nombre empleado\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarApellidoEmp(char dni[10], char apellidoNuevo[51]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Empleado SET apellido = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, apellidoNuevo, strlen(apellidoNuevo),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating apellido empleado\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarTelefonoEmp(char dni[10], char telefonoNuevo[10]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Empleado SET telefono = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, telefonoNuevo, strlen(telefonoNuevo),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating telefono empleado\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarFechaNacEmp(char dni[10], char fechaNacNueva[11]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Empleado SET fecha_nacimiento = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, fechaNacNueva, strlen(fechaNacNueva),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating fecha_nacimiento empleado\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarFechaInicContEmp(char dni[10], char fechaInicContNueva[11]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Empleado SET fecha_ini_cont = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, fechaInicContNueva,
			strlen(fechaInicContNueva), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating fecha_ini_cont empleado\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarFechaFinContEmp(char dni[10], char fechaFinContNueva[11]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Empleado SET fecha_fin_cont = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, fechaFinContNueva,
			strlen(fechaFinContNueva), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating fecha_fin_cont empleado\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarIdTiendaEmp(char dni[10], int nuevoIdTienda) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Empleado SET id_tienda = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, nuevoIdTienda);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating id_tienda empleado\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarIdCargoEmp(char dni[10], int nuevoIdCargo) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Empleado SET id_cargo = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, nuevoIdCargo);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating id_cargo empleado\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarContrasenaEmp(char dni[10], char contrasenaNueva[51]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Empleado SET contrasena = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, contrasenaNueva,
			strlen(contrasenaNueva), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating contrasena empleado\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
/*int guardarTiendas(Tienda tiendas[]) {
 sqlite3 *db = abrirDB();
 sqlite3_stmt *stmt;

 char sql[] = "SELECT t.*, c.nombre FROM Tienda t, Ciudad c WHERE t.id_ciudad = c.id";

 int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
 if (result != SQLITE_OK) {
 printf("Error preparing statement\n");
 printf("%s\n", sqlite3_errmsg(db));
 sqlite3_close(db);
 return result;
 }

 int contador = 0;
 do {
 result = sqlite3_step(stmt);
 if (result == SQLITE_ROW) {
 tiendas[contador].id_tienda = sqlite3_column_int(stmt, 0);
 strcpy(tiendas[contador].direccion, (char*)sqlite3_column_text(stmt, 1));
 strcpy(tiendas[contador].telefono, (char*)sqlite3_column_text(stmt, 2));
 tiendas[contador].ciudad.id_ciudad= sqlite3_column_int(stmt, 3);
 strcpy(tiendas[contador].ciudad.nombre, (char*)sqlite3_column_text(stmt, 4));
 contador++;
 }
 } while (result == SQLITE_ROW);

 sqlite3_finalize(stmt);
 sqlite3_close(db);
 return 0;

 }*/
int guardarCargos(Cargo cargos[]) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] = "SELECT * from Cargo";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	int contador = 0;
	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			cargos[contador].id_cargo = sqlite3_column_int(stmt, 0);
			strcpy(cargos[contador].nombre_cargo,
					(char*) sqlite3_column_text(stmt, 1));
			contador++;
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;

}
int imprimirCargosTiendas(char condicion[]) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[100];
	sprintf(sql, "SELECT * FROM %s", condicion);

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			printf("%d. %s\n", sqlite3_column_int(stmt, 0),
					sqlite3_column_text(stmt, 1));
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int obtenerNumeroCargos(int *numero) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] = "SELECT count(*) FROM Cargo";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		*numero = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
/*int obtenerNumeroTiendas(int* numero){
 sqlite3 *db = abrirDB();
 sqlite3_stmt *stmt;

 char sql[] = "SELECT count(*) FROM Tienda";

 int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
 if (result != SQLITE_OK) {
 printf("Error preparing statement\n");
 printf("%s\n", sqlite3_errmsg(db));
 return 0;
 }

 result = sqlite3_step(stmt);
 if (result == SQLITE_ROW) {
 *numero = sqlite3_column_int(stmt, 0);
 }

 sqlite3_finalize(stmt);
 sqlite3_close(db);
 return 0;
 }*/

// tienda
int guardarProvincias(Provincia provincias[]) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] = "SELECT * FROM Provincia";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	int contador = 0;
	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			provincias[contador].id_provincia = sqlite3_column_int(stmt, 0);
			strcpy(provincias[contador].nombre,
					(char*) sqlite3_column_text(stmt, 1));
			contador++;
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;

}
int guardarCiudades(Ciudad ciudades[], int id_provincia) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] = "SELECT * FROM Ciudad WHERE id_provincia = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, id_provincia);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	int contador = 0;
	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			ciudades[contador].id_ciudad = sqlite3_column_int(stmt, 0);
			strcpy(ciudades[contador].nombre,
					(char*) sqlite3_column_text(stmt, 1));
			contador++;
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;

}
int guardarTiendas(Tienda tiendas[]) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] =
			"SELECT t.*, c.nombre, p.nombre FROM Tienda t, Ciudad c, Provincia p WHERE t.id_ciudad = c.id AND c.id_provincia = p.id";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	int contador = 0;
	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			tiendas[contador].id_tienda = sqlite3_column_int(stmt, 0);
			strcpy(tiendas[contador].direccion,
					(char*) sqlite3_column_text(stmt, 1));
			strcpy(tiendas[contador].telefono,
					(char*) sqlite3_column_text(stmt, 2));
			tiendas[contador].ciudad.id_ciudad = sqlite3_column_int(stmt, 3);
			strcpy(tiendas[contador].ciudad.nombre,
					(char*) sqlite3_column_text(stmt, 4));
			strcpy(tiendas[contador].provincia.nombre,
					(char*) sqlite3_column_text(stmt, 5));
			contador++;
		}
	} while (result == SQLITE_ROW);

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;

}
int obtenerNumeroProvincias(int *numero) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] = "SELECT count(*) FROM Provincia";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		*numero = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int obtenerNumeroCiudades(int *numero, int id_provincia) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] = "SELECT count(*) FROM Ciudad WHERE id_provincia = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_bind_int(stmt, 1, id_provincia);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		*numero = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int obtenerNumeroTiendas(int *numero) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	char sql[] = "SELECT count(*) FROM Tienda";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		return 0;
	}

	result = sqlite3_step(stmt);
	if (result == SQLITE_ROW) {
		*numero = sqlite3_column_int(stmt, 0);
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int anadirTienda(Tienda t) {
	Tienda tNull;
	strcpy(tNull.direccion, "NULL");
	int resultado = existeTienda(t.direccion, t.ciudad.id_ciudad, &tNull);

	sqlite3 *db = abrirDB();

	if (resultado != 0) {

		printf("La tienda introducida ya existe\n");
		return 0;
	} else {
		int result;

		sqlite3_stmt *stmt;
		char sql2[] = "INSERT INTO Tienda VALUES (NULL, ?, ?, ?)";
		result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, t.direccion, strlen(t.direccion),
				SQLITE_STATIC);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_text(stmt, 2, t.telefono, strlen(t.telefono),
				SQLITE_STATIC);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_int(stmt, 3, t.ciudad.id_ciudad);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_step(stmt);

		if (result != SQLITE_DONE) {
			printf("Error executing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return 0;
		}

		sqlite3_finalize(stmt);

	}

	sqlite3_close(db);
	return 0;
}
int modificarDirecTienda(int id, char direccionNueva[51]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Tienda SET direccion = ? WHERE id = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, direccionNueva, strlen(direccionNueva),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, id);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating direccion tienda\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarTelefTienda(int id, char telefono[10]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Tienda SET telefono = ? WHERE id = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, telefono, strlen(telefono),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, id);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating telefono tienda\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarCiudadTienda(int id, int id_ciudad) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Tienda SET id_ciudad = ? WHERE id = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, id_ciudad);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, id);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating ciudad tienda\n");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int eliminarTienda(char direccion[], int id_ciudad) {
	sqlite3 *db = abrirDB();
	Tienda t;
	int result = existeTienda(direccion, id_ciudad, &t);

	if (result == 1) {
		sqlite3_stmt *stmt;
		char sql[] = "DELETE FROM Tienda WHERE direccion = ? AND id_ciudad = ?";

		result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, direccion, strlen(direccion),
				SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_int(stmt, 2, id_ciudad);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_step(stmt);

		sqlite3_finalize(stmt);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_close(db);
	return 0;

}
int existeTienda(char direccion[51], int id_ciudad, Tienda *t) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] =
			"SELECT t.*, c.nombre, p.id, p.nombre FROM Tienda t, Ciudad c, Provincia p WHERE t.id_ciudad = c.id AND c.id_provincia = p.id AND t.direccion = ? AND t.id_ciudad = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, direccion, strlen(direccion),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_bind_int(stmt, 2, id_ciudad);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		if (strcmp(t->direccion, "NULL") != 0) {
			t->id_tienda = sqlite3_column_int(stmt, 0);
			strcpy(t->direccion, (char*) sqlite3_column_text(stmt, 1));
			strcpy(t->telefono, (char*) sqlite3_column_text(stmt, 2));
			t->ciudad.id_ciudad = sqlite3_column_int(stmt, 3);
			strcpy(t->ciudad.nombre, (char*) sqlite3_column_text(stmt, 4));
			t->provincia.id_provincia = sqlite3_column_int(stmt, 5);
			strcpy(t->provincia.nombre, (char*) sqlite3_column_text(stmt, 6));

		}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}

// cargo
int existeCargo(char cargo[20], Cargo *c) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "SELECT * FROM Cargo WHERE nombre = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, cargo, strlen(cargo), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		if (strcmp(c->nombre_cargo, "NULL") != 0) {
			c->id_cargo = sqlite3_column_int(stmt, 0);
			strcpy(c->nombre_cargo, (char*) sqlite3_column_text(stmt, 1));
		}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int anadirCargo(Cargo c) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	Cargo cNull;
	strcpy(cNull.nombre_cargo, "NULL");
	int resultado = existeCargo(c.nombre_cargo, &cNull);

	if (resultado != 0) {
		system("cls");
		printf("El cargo ya existe\n");
		return 0;
	} else {
		char sql2[] = "INSERT INTO Cargo VALUES (NULL, ?)";
		int result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt,
				NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, c.nombre_cargo,
				strlen(c.nombre_cargo), SQLITE_STATIC);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into Cargo\n");
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		system("cls");
		printf("Cargo anadido correctamente\n");
		return 0;
	}
}
int eliminarCargo(char nombre[20]) {
	sqlite3 *db = abrirDB();
	Cargo c;
	int result = existeCargo(nombre, &c);

	if (result == 1) {
		sqlite3_stmt *stmt;
		char sql[] = "DELETE FROM Cargo WHERE nombre = ?";

		result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre),
				SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_step(stmt);

		sqlite3_finalize(stmt);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_close(db);
	return 0;

}
int modificarNombreCargo(int id_cargo, char nuevoNombre[20]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Cargo SET nombre = ? WHERE id = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, nuevoNombre, strlen(nuevoNombre),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, id_cargo);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
// provincia

int existeProvincia(char provincia[20], Provincia* p){
    sqlite3 *db = abrirDB();

    sqlite3_stmt *stmt;

    char sql[] = "SELECT * FROM Provincia WHERE nombre = ?";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparing statement\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return result;
    }

    result = sqlite3_bind_text(stmt, 1, provincia, strlen(provincia), SQLITE_STATIC);
           if (result != SQLITE_OK) {
               printf("Error binding parameters\n");
               printf("%s\n", sqlite3_errmsg(db));
               sqlite3_finalize(stmt);
               sqlite3_close(db);
               return result;
           }
    result = sqlite3_step(stmt);

    if (result == SQLITE_ROW) {
    	if (strcmp(p->nombre, "NULL") != 0){
			p->id_provincia= sqlite3_column_int(stmt, 0);
			strcpy(p->nombre, (char*)sqlite3_column_text(stmt, 1));
    	}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 1;
    }

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int anadirProvincia(Provincia p){
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	Provincia pNull;
	strcpy(pNull.nombre, "NULL");
	int resultado = existeProvincia(p.nombre, &pNull);

	if (resultado != 0) {
		system("cls");
		printf("La provincia ya existe\n");
		return 0;
	} else {
		char sql2[] = "INSERT INTO Provincia VALUES (NULL, ?)";
		int result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, p.nombre, strlen(p.nombre), SQLITE_STATIC);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into Provincia\n");
        	sqlite3_finalize(stmt);
        	sqlite3_close(db);
			return result;
		}
		system("cls");
		printf("Provincia anadida correctamente\n");
		return 0;
	}
}
int eliminarProvincia(char nombre[20]) {
    sqlite3 *db = abrirDB();
    Provincia p;
    int result = existeProvincia(nombre, &p);

    if (result == 1) {
		sqlite3_stmt *stmt;
		char sql[] = "DELETE FROM Provincia WHERE nombre = ?";

		result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
		if (result != SQLITE_OK) {
		   printf("Error binding parameters\n");
		   printf("%s\n", sqlite3_errmsg(db));
		   sqlite3_finalize(stmt);
		   sqlite3_close(db);
		   return result;
		}
		result = sqlite3_step(stmt);

		sqlite3_finalize(stmt);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_close(db);
	return 0;

}
int modificarNombreProvincia(int id_provincia, char nuevoNombre[20]){
	 sqlite3 *db = abrirDB();

	    sqlite3_stmt *stmt;

	    char sql[] = "UPDATE Provincia SET nombre = ? WHERE id = ?";

	    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	    if (result != SQLITE_OK) {
	        printf("Error preparing statement\n");
	        printf("%s\n", sqlite3_errmsg(db));
	        sqlite3_close(db);
	        return result;
	    }

	    result = sqlite3_bind_text(stmt, 1, nuevoNombre, strlen(nuevoNombre), SQLITE_STATIC);
	    if (result != SQLITE_OK) {
	    	printf("Error binding parameters\n");
	    	printf("%s\n", sqlite3_errmsg(db));
	    	sqlite3_finalize(stmt);
	    	sqlite3_close(db);
	    	return result;
	    }

	    result = sqlite3_bind_int(stmt, 2, id_provincia);
	    if (result != SQLITE_OK) {
	    	printf("Error binding parameters\n");
	    	printf("%s\n", sqlite3_errmsg(db));
	    	sqlite3_finalize(stmt);
	    	sqlite3_close(db);
	    	return result;
	    }

	    sqlite3_step(stmt);

	    result = sqlite3_finalize(stmt);
	    if (result != SQLITE_OK) {
			printf("Error finalizing statement (UPDATE)\n");
			printf("%s\n", sqlite3_errmsg(db));
			return result;
		}
	    sqlite3_close(db);
	    return 0;
}

// ciudad

int anadirCiudad(Ciudad c) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	Ciudad cNull;
	strcpy(cNull.nombre, "NULL");
	int resultado = existeCiudad(c.nombre, c.provincia.id_provincia, &cNull);

	if (resultado != 0) {
		system("cls");
		printf("La ciudad ya existe\n");
		return 0;
	} else {
		char sql2[] = "INSERT INTO Ciudad VALUES (NULL, ?, ?)";
		int result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt,
				NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, c.nombre, strlen(c.nombre),
				SQLITE_STATIC);

		result += sqlite3_bind_int(stmt, 2, c.provincia.id_provincia);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into Ciudad\n");
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		system("cls");
		printf("Ciudad anadida correctamente\n");
		return 0;
	}
}

int eliminarCiudad(Ciudad c) {
	sqlite3 *db = abrirDB();
	Ciudad cNull;
	strcpy(cNull.nombre, "NULL");
	int result = existeCiudad(c.nombre, c.provincia.id_provincia, &cNull);

	if (result == 1) {
		sqlite3_stmt *stmt;
		char sql[] = "DELETE FROM Ciudad WHERE id = ?";

		result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_int(stmt, 1, c.id_ciudad);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_step(stmt);

		sqlite3_finalize(stmt);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_close(db);
	return 0;

}
int modificarNombreCiudad(int id_ciudad, char nuevoNombre[20]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Ciudad SET nombre = ? WHERE id = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, nuevoNombre, strlen(nuevoNombre),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, id_ciudad);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}

int modificarProvinciaCiudad(int id_ciudad, int id_provincia) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Ciudad SET id_provincia = ? WHERE id = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, id_provincia);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, id_ciudad);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}




int existeCiudad(char ciudad[20], int id_prov, Ciudad* c){
    sqlite3 *db = abrirDB();

    sqlite3_stmt *stmt;

    char sql[] = "SELECT * FROM Ciudad WHERE nombre = ? AND id_provincia = ?";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparing statement\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return result;
    }

    result = sqlite3_bind_text(stmt, 1, ciudad, strlen(ciudad), SQLITE_STATIC);
    result = sqlite3_bind_int(stmt, 2, c->provincia.id_provincia);
    if (result != SQLITE_OK) {
    	printf("Error binding parameters\n");
    	printf("%s\n", sqlite3_errmsg(db));
    	sqlite3_finalize(stmt);
    	sqlite3_close(db);
    	return result;
    }


    result = sqlite3_step(stmt);

    if (result == SQLITE_ROW) {
    	if (strcmp(c->nombre, "NULL") != 0){
			c->id_ciudad= sqlite3_column_int(stmt, 0);
			strcpy(c->nombre, (char*)sqlite3_column_text(stmt, 1));
			c->provincia.id_provincia= sqlite3_column_int(stmt, 2);
    	}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 1;
    }

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}


// usuario
int anadirUsuario(Usuario u) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;
	char sql[] = "SELECT * FROM Usuario WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, u.dni, strlen(u.dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		printf("El usuario ya existe");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 0;
	} else {
		char sql2[] = "INSERT INTO Usuario VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
		int result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt,
				NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, u.dni, strlen(u.dni),
				SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_text(stmt, 2, u.nombre, strlen(u.nombre),
				SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_text(stmt, 3, u.apellido, strlen(u.apellido),
				SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_text(stmt, 4, u.fecha, strlen(u.fecha),
				SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_text(stmt, 5, u.telefono, strlen(u.telefono),
				SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_text(stmt, 6, u.direccion, strlen(u.direccion),
				SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_text(stmt, 7, u.contrasena, strlen(u.contrasena),
				SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_bind_int(stmt, 8, u.ciudad.id_ciudad); // ESTO ES ALGO AÑADIDO EN LA BD

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into Usuario\n");
			return result;
		}
		printf("Usuario anadido correctamente\n");
		return 0;
	}
}
int existeUsuario(char dni[10], Usuario *u) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

//    char sql[] = "SELECT * FROM Usuario WHERE dni = ?";
	char sql[] =
			"SELECT u.*, c.nombre, p.id, p.nombre FROM Usuario u, Ciudad c, Provincia p WHERE u.id_ciudad = c.id AND c.id_provincia = p.id AND u.dni = ?";
	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		strcpy(u->dni, (char*) sqlite3_column_text(stmt, 0));
		strcpy(u->nombre, (char*) sqlite3_column_text(stmt, 1));
		strcpy(u->apellido, (char*) sqlite3_column_text(stmt, 2));
		strcpy(u->fecha, (char*) sqlite3_column_text(stmt, 3));
		strcpy(u->telefono, (char*) sqlite3_column_text(stmt, 4));
		strcpy(u->direccion, (char*) sqlite3_column_text(stmt, 5));
		strcpy(u->contrasena, (char*) sqlite3_column_text(stmt, 6));
		u->ciudad.id_ciudad = sqlite3_column_int(stmt, 7);
		strcpy(u->ciudad.nombre, (char*) sqlite3_column_text(stmt, 8));
		u->provincia.id_provincia = sqlite3_column_int(stmt, 9);
		strcpy(u->provincia.nombre, (char*) sqlite3_column_text(stmt, 10));

		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int eliminarUsuario(char dni[10]) {
	sqlite3 *db = abrirDB();
	Usuario u;
	int result = existeUsuario(dni, &u);

	if (result == 1) {
		sqlite3_stmt *stmt;
		char sql[] = "DELETE FROM Usuario WHERE dni = ?";

		result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, dni, strlen(dni), SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_step(stmt);

		sqlite3_finalize(stmt);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_close(db);
	return 0;
}
int modificarDniUsuario(char dni[10], char dniNuevo[10]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Usuario SET dni = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, dniNuevo, strlen(dniNuevo),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating DNI usuario\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_stmt *stmt2;

    char sql2[] = "UPDATE Adquisicion SET dni_usuario = ? WHERE dni_usuario = ?";

	result = sqlite3_bind_text(stmt2, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt2);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt2);
	if (result != SQLITE_DONE) {
		printf("Error updating DNI\n");
		return result;
	}

	result = sqlite3_finalize(stmt2);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarNombreUsuario(char dni[10], char nombreNuevo[51]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Usuario SET nombre = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, nombreNuevo, strlen(nombreNuevo),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating nombre usuario\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarApellidoUsuario(char dni[10], char apellidoNuevo[51]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Usuario SET apellido = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, apellidoNuevo, strlen(apellidoNuevo),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating apellido usuario\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarFechaUsuario(char dni[10], char fechaNueva[11]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Usuario SET fecha_nacimiento = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, fechaNueva, strlen(fechaNueva),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating fecha nacimiento usuario\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarTelefonoUsuario(char dni[10], char telefonoNuevo[10]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Usuario SET telefono = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, telefonoNuevo, strlen(telefonoNuevo),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating telefono usuario\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarDireccionUsuario(char dni[10], char direccionNueva[51]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Usuario SET direccion = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, direccionNueva, strlen(direccionNueva),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating direccion usuario\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarContrasenaUsuario(char dni[10], char contrasenaNueva[51]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Usuario SET contrasena = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, contrasenaNueva,
			strlen(contrasenaNueva), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating contrasena usuario\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarCiudadUsuario(char dni[10], int id_ciudad) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Usuario SET id_ciudad = ? WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, id_ciudad);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 2, dni, strlen(dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE) {
		printf("Error updating id_ciudad usuario\n");
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}

// marca
int anadirMarca(Marca m) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	Marca mNull;
	strcpy(mNull.nombre, "NULL");
	int resultado = existeMarca(m.nombre, &mNull);

	if (resultado != 0) {
		system("cls");
		printf("La marca ya existe\n");
		return 0;
	} else {
		char sql2[] = "INSERT INTO Marca VALUES (NULL, ?)";
		int result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt,
				NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, m.nombre, strlen(m.nombre),
				SQLITE_STATIC);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into Marca\n");
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		system("cls");
		printf("Marca anadido correctamente\n");
		return 0;
	}
}
int existeMarca(char marca[20], Marca *m) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "SELECT * FROM Marca WHERE nombre = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, marca, strlen(marca), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		if (strcmp(m->nombre, "NULL") != 0) {
			m->id = sqlite3_column_int(stmt, 0);
			strcpy(m->nombre, (char*) sqlite3_column_text(stmt, 1));
		}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int eliminarMarca(char nombre[20]) {
	sqlite3 *db = abrirDB();
	Marca m;
	int result = existeMarca(nombre, &m);

	if (result == 1) {
		sqlite3_stmt *stmt;
		char sql[] = "DELETE FROM Marca WHERE nombre = ?";

		result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre),
				SQLITE_STATIC);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_step(stmt);

		sqlite3_finalize(stmt);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_close(db);
	return 0;

}
int modificarNombreMarca(int id_marca, char nuevoNombre[20]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Marca SET nombre = ? WHERE id = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, nuevoNombre, strlen(nuevoNombre),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, id_marca);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}

// modelo
int anadirModelo(Modelo m) {
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;

	Modelo mNull;
	strcpy(mNull.nombre, "NULL");
	int resultado = existeModelo(m.nombre, m.marca.id, m.combustible, m.cambio, &mNull);

	if (resultado != 0) {
		system("cls");
		printf("El modelo ya existe\n");
		return 0;
	} else {
		char sql2[] = "INSERT INTO Modelo VALUES (NULL, ?, ?, ?, ?)";
		int result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt,
				NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_text(stmt, 1, m.nombre, strlen(m.nombre),
				SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 2, m.cambio, strlen(m.cambio),
				SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 3, m.combustible,
				strlen(m.combustible), SQLITE_STATIC);
		result += sqlite3_bind_int(stmt, 4, m.marca.id);

		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_step(stmt);
		if (result != SQLITE_DONE) {
			printf("Error inserting new data into Modelo\n");
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		system("cls");
		printf("Modelo anadido correctamente\n");
		return 0;
	}
}
int existeModelo(char nombre[20], int id_marca, char combustible[20],char cambio[20], Modelo *m) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] =
			"SELECT mo.*, ma.nombre FROM Modelo mo, Marca ma WHERE mo.id_marca = ma.id AND mo.nombre = ? AND mo.cambio = ? AND mo.combustible = ? and mo.id_marca = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, nombre, strlen(nombre), SQLITE_STATIC);
	result += sqlite3_bind_text(stmt, 2, cambio, strlen(cambio), SQLITE_STATIC);
	result += sqlite3_bind_text(stmt, 3, combustible, strlen(combustible),
			SQLITE_STATIC);
	result += sqlite3_bind_int(stmt, 4, id_marca);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}
	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		if (strcmp(m->nombre, "NULL") != 0) {
			m->id = sqlite3_column_int(stmt, 0);
			strcpy(m->nombre, (char*) sqlite3_column_text(stmt, 1));
			strcpy(m->cambio, (char*) sqlite3_column_text(stmt, 2));
			strcpy(m->combustible, (char*) sqlite3_column_text(stmt, 3));
			m->marca.id = sqlite3_column_int(stmt, 4);
		}
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 1;
	}

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int eliminarModelo(Modelo m) {
	sqlite3 *db = abrirDB();
	Modelo mNull;
	strcpy(mNull.nombre, "NULL");
	int result = existeModelo(m.nombre, m.marca.id, m.combustible, m.cambio, &mNull);

	if (result == 1) {
		sqlite3_stmt *stmt;
		char sql[] = "DELETE FROM Modelo WHERE id = ?";

		result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result = sqlite3_bind_int(stmt, 1, m.id);
		if (result != SQLITE_OK) {
			printf("Error binding parameters\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_finalize(stmt);
			sqlite3_close(db);
			return result;
		}
		result = sqlite3_step(stmt);

		sqlite3_finalize(stmt);
		sqlite3_close(db);

		return 1;
	}

	sqlite3_close(db);
	return 0;

}
int modificarNombreModelo(int id_modelo, char nuevoNombre[20]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Modelo SET nombre = ? WHERE id = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, nuevoNombre, strlen(nuevoNombre),
			SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, id_modelo);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarCambioModelo(int id_modelo, char nuevoCambio[20]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Modelo SET cambio = ? WHERE id = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, nuevoCambio, strlen(nuevoCambio), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, id_modelo);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarCombustibleModelo(int id_modelo, char nuevoCombustible[20]) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Modelo SET combustible = ? WHERE id = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, nuevoCombustible, strlen(nuevoCombustible), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, id_modelo);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
int modificarMarcaModelo(int id_modelo, int id_marca) {
	sqlite3 *db = abrirDB();

	sqlite3_stmt *stmt;

	char sql[] = "UPDATE Modelo SET id_marca = ? WHERE id = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 1, id_marca);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_int(stmt, 2, id_modelo);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	sqlite3_step(stmt);

	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
	sqlite3_close(db);
	return 0;
}
