

#ifndef USUARIO_H_
#define USUARIO_H_
#include "sqlite3.h"


int inicioSesion(char dni[], char contrasena[]);

#endif /* USUARIO_H_ */

#include "sqlite3.h"


	//Usuario
	typedef struct {
		char nombre[];
		char apellido[];
		char dni[9];
		char fecha[];
		char telefono[9];
		char direccion[];
		char contrasena[];


	}Usuario;

	//lista de usuarios
	typedef struct {
		Usuario *lUsuarios;
		int tam;
		int numUsuarios;

	}ListaUsuarios;

	int inicioSesion(char dni[], char contrasena[]);
	void aniadirUsuario(ListaUsuarios *lu, Usuario u);

