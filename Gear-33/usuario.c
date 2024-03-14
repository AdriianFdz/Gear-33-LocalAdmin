#include <stdio.h>
#include <string.h>
#include "usuario.h"

int inicioSesion(char dni[], char contrasena[]) {
    sqlite3 *db;

    int result = sqlite3_open("Gear-33.db", &db);
    if (result != SQLITE_OK) {
        printf("Error opening database\n");
        return result;
    }
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
    	if (strcmp(dni, sqlite3_column_text(stmt, 0)) == 0 && strcmp(contrasena, sqlite3_column_text(stmt, 1)) == 0) {
    	        return 1;
    	}

    } else if (result != SQLITE_DONE) {
        printf("Error fetching data\n");
        printf("%s\n", sqlite3_errmsg(db));
        return 0;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}

