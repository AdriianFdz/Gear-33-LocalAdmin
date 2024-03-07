#ifndef MENUS_H_
#define MENUS_H_

void menuLogin();

void menuPrincipal();

void opcionMenuPrincipal(int opcion);


void menuGestCoches();
	void opcionMenuGestCoches(int *opcion);
		void menuAnadirCoche(int* opcion);
		void menuModificarCoche(int* opcion);
		void menuEliminarCoche(int* opcion);
void menuGestUsuario(int* opcion);
void menuGestEmpleado(int* opcion);
void menuGestTienda(int* opcion);

#endif /* MENUS_H_ */
