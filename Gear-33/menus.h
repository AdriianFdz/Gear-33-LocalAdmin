#ifndef MENUS_H_
#define MENUS_H_

void menuLogin();

void menuPrincipal();

void opcionMenuPrincipal(int opcion);


void menuGestCoches();
	void opcionMenuGestCoches(int *opcion);
		void menuAnadirCoche(int* opcion);
		void menuModificarCoche(int* opcion);
			void opcionMenuModificarCoches(int *opcion);
				void menuModificarMatricula(int *opcion);
				void menuModificarMarca(int *opcion);
				void menuModificarModelo(int *opcion);
				void menuModificarColor(int *opcion);
				void menuModificarAnyo(int *opcion);
				void menuModificarPrecio(int *opcion);
				void menuModificarCambio(int *opcion);
				void menuModificarCombustible(int *opcion);
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
				void menuModificarContraseña(int *opcion);
		void menuEliminarUsuario(int* opcion);
void menuGestEmpleado(int* opcion);
void menuGestTienda(int* opcion);

#endif /* MENUS_H_ */
