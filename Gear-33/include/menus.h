#ifndef MENUS_H_
#define MENUS_H_

void menuLogin();

void menuPrincipal();

void opcionMenuPrincipal(int opcion);


void menuGestCoches();
	void opcionMenuGestCoches(int *opcion);
		void menuAnadirCoche(int* opcion);
		void menuModificarCoche(int* opcion);
			void opcionMenuModificarCoches(int *opcion, char matricula[]);
				void menuModificarMatricula(int *opcion, char matricula[] );
				void menuModificarMarca(int *opcion, char matricula[]);
				void menuModificarModelo(int *opcion, char matricula[]);
				void menuModificarColor(int *opcion, char matricula[]);
				void menuModificarAnyo(int *opcion, char matricula[]);
				void menuModificarPrecio(int *opcion, char matricula[]);
				void menuModificarCambio(int *opcion, char matricula[]);
				void menuModificarCombustible(int *opcion, char matricula[]);
		void menuEliminarCoche(int* opcion);

void menuGestUsuario(int* opcion);
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
void menuGestEmpleado(int* opcion);
void menuGestTienda(int* opcion);

#endif /* MENUS_H_ */
