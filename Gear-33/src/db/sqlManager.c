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
int anadirEmpleado(Empleado e){
	sqlite3 *db = abrirDB();
	sqlite3_stmt *stmt;
	char sql[] = "SELECT * FROM Empleado WHERE dni = ?";

	int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
	if (result != SQLITE_OK) {
		printf("Error preparing statement\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_bind_text(stmt, 1, e.dni, strlen(e.dni), SQLITE_STATIC);
	if (result != SQLITE_OK) {
		printf("Error binding parameters\n");
		printf("%s\n", sqlite3_errmsg(db));
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return result;
	}

	result = sqlite3_step(stmt);

	if (result == SQLITE_ROW) {
		printf("El empleado ya existe");
		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 0;
	} else {
		char sql2[] = "INSERT INTO Empleado VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
		int result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt, NULL);
		if (result != SQLITE_OK) {
			printf("Error preparing statement\n");
			printf("%s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
			return result;
		}

		result += sqlite3_bind_text(stmt, 1, e.dni, strlen(e.dni), SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 2, e.nombre, strlen(e.nombre), SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 3, e.apellido, strlen(e.apellido), SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 4, e.telefono, strlen(e.telefono), SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 5, e.fecha_nacimiento, strlen(e.fecha_nacimiento), SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 6, e.fecha_ini_contrato, strlen(e.fecha_ini_contrato), SQLITE_STATIC);
		result += sqlite3_bind_text(stmt, 7, e.fecha_fin_contrato, strlen(e.fecha_fin_contrato), SQLITE_STATIC);
		result += sqlite3_bind_int(stmt, 8, e.id_tienda);
		result += sqlite3_bind_int(stmt, 9, e.id_cargo);
		result += sqlite3_bind_text(stmt, 10, e.contrasena, strlen(e.contrasena), SQLITE_STATIC);

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
			return result;
		}
		printf("Empleado anadido correctamente");
		return 0;
	}
}
int existeEmpleado(char dni[10], Empleado* e){
    sqlite3 *db = abrirDB();

    sqlite3_stmt *stmt;

    char sql[] = "SELECT * FROM Empleado WHERE dni = ?";

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
    	strcpy(e->dni, dni);
    	strcpy(e->nombre, (char*)sqlite3_column_text(stmt, 1));
    	strcpy(e->apellido, (char*)sqlite3_column_text(stmt, 2));
    	strcpy(e->telefono, (char*)sqlite3_column_text(stmt, 3));
    	strcpy(e->fecha_nacimiento, (char*)sqlite3_column_text(stmt, 4));
    	strcpy(e->fecha_ini_contrato, (char*)sqlite3_column_text(stmt, 5));
    	strcpy(e->fecha_fin_contrato, (char*)sqlite3_column_text(stmt, 6));
    	e->id_tienda = sqlite3_column_int(stmt, 7);
    	e->id_cargo = sqlite3_column_int(stmt, 8);
    	strcpy(e->contrasena, (char*)sqlite3_column_text(stmt, 9));


		sqlite3_finalize(stmt);
		sqlite3_close(db);
		return 1;
    }

	sqlite3_finalize(stmt);
	sqlite3_close(db);
	return 0;
}
int eliminarEmpleado(char dni[10]){
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
int modificarDniEmp(char dni[10], char dniNuevo[10]){
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

    result = sqlite3_bind_text(stmt, 1, dniNuevo, strlen(dniNuevo), SQLITE_STATIC);
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
		return result;
	}
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK) {
		printf("Error finalizing statement (UPDATE)\n");
		printf("%s\n", sqlite3_errmsg(db));
		return result;
	}
    sqlite3_stmt *stmt2;

    char sql2[] = "UPDATE Adquisicion SET dni_empleado = ? WHERE dni_empleado = ?";

        result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
        if (result != SQLITE_OK) {
            printf("Error preparing statement\n");
            printf("%s\n", sqlite3_errmsg(db));
            sqlite3_close(db);
            return result;
        }

        result = sqlite3_bind_text(stmt2, 1, dniNuevo, strlen(dniNuevo), SQLITE_STATIC);
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
int modificarNombreEmp(char dni[10], char nombreNuevo[51]){
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

    result = sqlite3_bind_text(stmt, 1, nombreNuevo, strlen(nombreNuevo), SQLITE_STATIC);
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
int modificarApellidoEmp(char dni[10], char apellidoNuevo[51]){
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

    result = sqlite3_bind_text(stmt, 1, apellidoNuevo, strlen(apellidoNuevo), SQLITE_STATIC);
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
int modificarTelefonoEmp(char dni[10], char telefonoNuevo[10]){
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

    result = sqlite3_bind_text(stmt, 1, telefonoNuevo, strlen(telefonoNuevo), SQLITE_STATIC);
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
int modificarFechaNacEmp(char dni[10], char fechaNacNueva[11]){
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

    result = sqlite3_bind_text(stmt, 1, fechaNacNueva, strlen(fechaNacNueva), SQLITE_STATIC);
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
int modificarFechaInicContEmp(char dni[10], char fechaInicContNueva[11]){
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

    result = sqlite3_bind_text(stmt, 1, fechaInicContNueva, strlen(fechaInicContNueva), SQLITE_STATIC);
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
int modificarFechaFinContEmp(char dni[10], char fechaFinContNueva[11]){
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

    result = sqlite3_bind_text(stmt, 1, fechaFinContNueva, strlen(fechaFinContNueva), SQLITE_STATIC);
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
int modificarIdTiendaEmp(char dni[10], int nuevoIdTienda){
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
int modificarIdCargoEmp(char dni[10], int nuevoIdCargo){
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
int modificarContrasenaEmp(char dni[10], char contrasenaNueva[51]){
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

    result = sqlite3_bind_text(stmt, 1, contrasenaNueva, strlen(contrasenaNueva), SQLITE_STATIC);
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
