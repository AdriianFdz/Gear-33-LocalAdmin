

#ifndef USUARIO_H_
#define USUARIO_H_

#include "sqlite3.h"



	//Usuario
	typedef struct {
		char nombre[51];
		char apellido[51];
		char dni[10]; // +1 para el /0
		char fecha[11];
		char telefono[10]; // +1 para el /0
		char direccion[51];
		char contrasena[51];


	}Usuario;

	//lista de usuarios
	typedef struct {
		Usuario *lUsuarios;
		int tam;
		int numUsuarios;

	}ListaUsuarios;

	int inicioSesion(char dni[], char contrasena[]);
	void aniadirUsuario(ListaUsuarios *lu, Usuario u);
	Usuario pedirUsuario();

#endif /* USUARIO_H_ */

