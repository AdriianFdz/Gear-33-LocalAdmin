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
#include "../../include/config.h"
#include "../../include/empleado.h"


sqlite3* abrirDB() {
	CONFIG* datosConfig = malloc(sizeof(CONFIG));
	leerConfig(datosConfig);

    sqlite3 *db;

    int result = sqlite3_open(datosConfig -> database, &db);
    free(datosConfig);
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
       	if (strcmp(dni, (char*)sqlite3_column_text(stmt, 0)) == 0 && strcmp(contrasena, (char*)sqlite3_column_text(stmt, 1)) == 0) {
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

int obtenerAnadirMarca(Coche c) {
    sqlite3 *db = abrirDB();
    int id_marca = 0;

    sqlite3_stmt *stmt;

    char sql[] = "SELECT id, nombre FROM Marca WHERE nombre = ?";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparing statement\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return result;
    }

    result = sqlite3_bind_text(stmt, 1, c.marca, strlen(c.marca), SQLITE_STATIC);
           if (result != SQLITE_OK) {
               printf("Error binding parameters\n");
               printf("%s\n", sqlite3_errmsg(db));
               sqlite3_finalize(stmt);
               sqlite3_close(db);
               return result;
           }
    result = sqlite3_step(stmt);

    if (result == SQLITE_ROW) {
		id_marca = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);
    } else {
		sqlite3_finalize(stmt);

    	sqlite3_stmt *stmt2;
        char sql2[] = "INSERT INTO Marca VALUES (NULL, ?)";
        result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
        if (result != SQLITE_OK) {
            printf("Error preparing statement\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return result;
        }

        result = sqlite3_bind_text(stmt2, 1, c.marca, strlen(c.marca), SQLITE_STATIC);
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

        id_marca = sqlite3_last_insert_rowid(db);
		sqlite3_finalize(stmt2);
		// Commit de la transacción antes de cerrar la conexión
		//sqlite3_exec(db, "COMMIT", NULL, NULL, NULL);
		//sqlite3_close(db);

	}

	sqlite3_close(db);
	return id_marca;
}
int obtenerAnadirModelo(Coche c) {
	int id_marca = obtenerAnadirMarca(c);
    sqlite3 *db = abrirDB();

    int id_modelo = 0;

    sqlite3_stmt *stmt;

    char sql[] = "SELECT id, nombre FROM Modelo WHERE nombre = ?";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparing statement\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return result;
    }

    result = sqlite3_bind_text(stmt, 1, c.modelo, strlen(c.modelo), SQLITE_STATIC);
           if (result != SQLITE_OK) {
               printf("Error binding parameters\n");
               printf("%s\n", sqlite3_errmsg(db));
               sqlite3_finalize(stmt);
               sqlite3_close(db);
               return result;
           }
    result = sqlite3_step(stmt);

    if (result == SQLITE_ROW) {
		id_modelo = sqlite3_column_int(stmt, 0);
		sqlite3_finalize(stmt);

    } else {
		sqlite3_finalize(stmt);

    	sqlite3_stmt *stmt2;
        char sql2[] = "INSERT INTO Modelo VALUES (NULL, ?, ?, ?, ?)";
        result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
        if (result != SQLITE_OK) {
            printf("Error preparing statement\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return result;
        }

        result = sqlite3_bind_text(stmt2, 1, c.modelo, strlen(c.modelo), SQLITE_STATIC);

        if (result != SQLITE_OK) {
            printf("Error binding parameters\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt2);
            sqlite3_close(db);
            return result;
        }
        result = sqlite3_bind_text(stmt2, 2, c.cambio, strlen(c.cambio), SQLITE_STATIC);

        if (result != SQLITE_OK) {
            printf("Error binding parameters\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt2);
            sqlite3_close(db);
            return result;
        }
        result = sqlite3_bind_text(stmt2, 3, c.combustible, strlen(c.combustible), SQLITE_STATIC);

        if (result != SQLITE_OK) {
            printf("Error binding parameters\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt2);
            sqlite3_close(db);
            return result;
        }
        result = sqlite3_bind_int(stmt2, 4, id_marca);

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

        id_modelo = sqlite3_last_insert_rowid(db);
		sqlite3_finalize(stmt2);

	}

	sqlite3_close(db);
	return id_modelo;
}
int anadirCoche(Coche c) {
	int id_modelo = obtenerAnadirModelo(c);
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

    result = sqlite3_bind_text(stmt, 1, c.matricula, strlen(c.matricula), SQLITE_STATIC);
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
		sqlite3_close(db);
		return 0;

    } else {
		sqlite3_finalize(stmt);

    	sqlite3_stmt *stmt2;
        char sql2[] = "INSERT INTO Coche VALUES (?, ?, ?, ?, ?)";
        result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
        if (result != SQLITE_OK) {
            printf("Error preparing statement\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return result;
        }

        result = sqlite3_bind_text(stmt2, 1, c.matricula, strlen(c.matricula), SQLITE_STATIC);

        if (result != SQLITE_OK) {
            printf("Error binding parameters\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt2);
            sqlite3_close(db);
            return result;
        }
        result = sqlite3_bind_text(stmt2, 2, c.color, strlen(c.color), SQLITE_STATIC);

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

        result = sqlite3_bind_int(stmt2, 5, id_modelo);

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

    result = sqlite3_bind_text(stmt, 1, matricula, strlen(matricula), SQLITE_STATIC);
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

        result = sqlite3_bind_text(stmt2, 1, matricula, strlen(matricula), SQLITE_STATIC);
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
int existeMatricula(char matricula[]) {
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

    result = sqlite3_bind_text(stmt, 1, matricula, strlen(matricula), SQLITE_STATIC);
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

    result = sqlite3_bind_text(stmt, 1, matriculaNueva, strlen(matriculaNueva), SQLITE_STATIC);
    if (result != SQLITE_OK) {
    	printf("Error binding parameters\n");
    	printf("%s\n", sqlite3_errmsg(db));
    	sqlite3_finalize(stmt);
    	sqlite3_close(db);
    	return result;
    }

    result = sqlite3_bind_text(stmt, 2, matricula, strlen(matricula), SQLITE_STATIC);
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

    result = sqlite3_bind_text(stmt, 2, matricula, strlen(matricula), SQLITE_STATIC);
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

    result = sqlite3_bind_text(stmt, 2, matricula, strlen(matricula), SQLITE_STATIC);
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

    result = sqlite3_bind_text(stmt, 2, matricula, strlen(matricula), SQLITE_STATIC);
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
int modificarMarcaModelo(char matricula[], int id_modelo) {
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

    result = sqlite3_bind_text(stmt, 2, matricula, strlen(matricula), SQLITE_STATIC);
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

int imprimirCargosTiendas(char condicion[]){
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

//    result = sqlite3_bind_text(stmt, 1, condicion, strlen(condicion), SQLITE_STATIC);
//
//    if (result != SQLITE_OK) {
//        printf("Error binding parameters\n");
//        printf("%s\n", sqlite3_errmsg(db));
//        sqlite3_finalize(stmt);
//        sqlite3_close(db);
//        return result;
//    }

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			printf("%d. %s\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1));
		}
	} while (result == SQLITE_ROW);


	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}


int modificarCambio(char matricula[], char cambio[]) {
    sqlite3 *db = abrirDB();
    int id_modelo;

    sqlite3_stmt *stmt;

    char sql[] = "SELECT id_modelo FROM Coche WHERE matricula = ?";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparing statement\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return result;
    }

    result = sqlite3_bind_text(stmt, 1, matricula, strlen(matricula), SQLITE_STATIC);
    if (result != SQLITE_OK) {
        printf("Error binding parameters\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }

    result = sqlite3_step(stmt);

    if (result == SQLITE_ROW) {
    	id_modelo = sqlite3_column_int(stmt, 0);

        sqlite3_stmt *stmt2;

        char sql2[] = "UPDATE Modelo SET cambio = ? WHERE id = ?";

        int result = sqlite3_prepare_v2(db, sql2, strlen(sql) + 1, &stmt2, NULL);
        if (result != SQLITE_OK) {
            printf("Error preparing statement\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return result;
        }

        result = sqlite3_bind_text(stmt2, 1, cambio, strlen(cambio), SQLITE_STATIC);
        if (result != SQLITE_OK) {
            printf("Error binding parameters\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return result;
        }

        result = sqlite3_bind_int(stmt2, 2, id_modelo);
        if (result != SQLITE_OK) {
            printf("Error binding parameters\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return result;
        }

        result = sqlite3_step(stmt2);
        sqlite3_finalize(stmt2);

    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}


int modificarCombustible(char matricula[], char combustible[]) {
    sqlite3 *db = abrirDB();
    int id_modelo;

    sqlite3_stmt *stmt;

    char sql[] = "SELECT id_modelo FROM Coche WHERE matricula = ?";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparing statement\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return result;
    }

    result = sqlite3_bind_text(stmt, 1, matricula, strlen(matricula), SQLITE_STATIC);
    if (result != SQLITE_OK) {
        printf("Error binding parameters\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return result;
    }

    result = sqlite3_step(stmt);

    if (result == SQLITE_ROW) {
    	id_modelo = sqlite3_column_int(stmt, 0);

        sqlite3_stmt *stmt2;

        char sql2[] = "UPDATE Modelo SET combustible = ? WHERE id = ?";

        int result = sqlite3_prepare_v2(db, sql2, strlen(sql) + 1, &stmt2, NULL);
        if (result != SQLITE_OK) {
            printf("Error preparing statement\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return result;
        }

        result = sqlite3_bind_text(stmt2, 1, combustible, strlen(combustible), SQLITE_STATIC);
        if (result != SQLITE_OK) {
            printf("Error binding parameters\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return result;
        }

        result = sqlite3_bind_int(stmt2, 2, id_modelo);
        if (result != SQLITE_OK) {
            printf("Error binding parameters\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return result;
        }

        result = sqlite3_step(stmt2);
        sqlite3_finalize(stmt2);

    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

int imprimirMarcas() {
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

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			printf("%d. %s\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1));
		}
	} while (result == SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;

}

int imprimirModelos(int id_marca) {
    sqlite3 *db = abrirDB();
    sqlite3_stmt *stmt;

    char sql[] = "SELECT id, nombre FROM Modelo WHERE id_marca = ?";

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

	do {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			printf("%d. %s\n", sqlite3_column_int(stmt, 0), sqlite3_column_text(stmt, 1));
		}
	} while (result == SQLITE_ROW);

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

