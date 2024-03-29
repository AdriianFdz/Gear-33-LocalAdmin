

#ifndef USUARIO_H_
#define USUARIO_H_


//Usuario
// +1 para el /0
typedef struct {
	char nombre[51];
	char apellido[51];
	char dni[10];
	char fecha[11];
	char telefono[10];
	char direccion[51];
	char contrasena[51];


}Usuario;

//lista de usuarios
typedef struct {
	Usuario *lUsuarios;
	int tam;
	int numUsuarios;

}ListaUsuarios;

void aniadirUsuario(ListaUsuarios *lu, Usuario u);
Usuario pedirUsuario();


//menus de usuario
void menuGestUsuario();
	void opcionMenuGestUsuario(int *opcion);
		void menuAnadirUsuario(int* opcion);
		void menuModificarUsuario(int* opcion);
			void opcionMenuModificarUsuarios(int *opcion);
				void menuModificarNombre(int *opcion);
				void menuModificarApellido(int *opcion);
				void menuModificarDni(int *opcion);
				void menuModificarFecha(int *opcion);
				void menuModificarTelefono(int *opcion);
				void menuModificarDireccion(int *opcion);
				void menuModificarContrasena(int *opcion);
		void menuEliminarUsuario(int* opcion);


#endif /* USUARIO_H_ */

