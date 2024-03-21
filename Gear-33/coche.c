
#include <stdio.h>
#include <string.h>

#include "coche.h"
#include "sqlite3.h"

Coche pedirCoche()
{
	Coche c; 

	printf("Introduce la matricula \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.matricula);

	printf("Introduce el color \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.color);

	printf("Introduce el año \n");
	fflush(stdout);
	fflush(stdin);
	scanf("%d", &c.anyo);

	printf("Introduce el precio \n");
	fflush(stdout);
	fflush(stdin);
	scanf("%f", &c.precioBase);

	printf("Introduce la marca \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.marca);

	printf("Introduce el modelo \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.modelo);

	printf("Introduce el tipo de cambio \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.cambio);

	printf("Introduce el tipo de combustible \n");
	fflush(stdout);
	fflush(stdin);
	gets(c.combustible);

	return c;
}

void aniadirCoche(ListaCoches *lc, Coche c)
{
	if(lc->numCoches < lc->tam){
			lc->lCoches[lc->numCoches] = c;
			lc->numCoches++;
			printf("Coche añadido correctamente\n");
		}else{
			printf("Lo sentimos! La lista esta completa\n");
		}
		fflush(stdout);

}

sqlite3* abrirDB() {
    sqlite3 *db;

    int result = sqlite3_open("Gear-33.db", &db);
    if (result != SQLITE_OK) {
        printf("Error opening database\n");
    }

    return db;
}


int id_marca(Coche c) {
    sqlite3 *db = abrirDB();
    int id_marca = 0;
    int ultimo_id = 0;

    if (db == NULL) {
        printf("Error al abrir la base de datos\n");
        return 0;
    }

    sqlite3_stmt *stmt;

    char sql[] = "SELECT id, nombre from Marca";

    int result = sqlite3_prepare_v2(db, sql, strlen(sql) + 1, &stmt, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparing statement\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
    }


    result = sqlite3_exec(db, "BEGIN TRANSACTION", NULL, NULL, NULL);
    if (result != SQLITE_OK) {
        printf("Error starting transaction\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 0;
    }

    result = sqlite3_step(stmt);
    while (result == SQLITE_ROW) {
        if (strcmp(c.marca, (const char*)sqlite3_column_text(stmt, 1)) == 0) {
            id_marca = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            // Commit de la transacción antes de cerrar la conexión
            sqlite3_exec(db, "COMMIT", NULL, NULL, NULL);
            sqlite3_close(db);
            return id_marca;
        }
        result = sqlite3_step(stmt);
    }

    sqlite3_finalize(stmt);

    sqlite3_stmt *stmt2;
    char sql2[] = "INSERT INTO Marca VALUES (NULL, ?)";
    result = sqlite3_prepare_v2(db, sql2, strlen(sql2) + 1, &stmt2, NULL);
    if (result != SQLITE_OK) {
        printf("Error preparing statement\n");
        printf("%s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 0;
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

    // Obtenemos el último ID insertado
    ultimo_id = sqlite3_last_insert_rowid(db);

    sqlite3_finalize(stmt2);
    // Commit de la transacción antes de cerrar la conexión
    sqlite3_exec(db, "COMMIT", NULL, NULL, NULL);
    sqlite3_close(db);

    return ultimo_id;
}

//int aniadirCocheBD(Coche c) {
//
//
//
//}

