#ifndef USUARIO_H_
#define USUARIO_H_
#include "tienda.h"

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
	Ciudad ciudad;
	Provincia provincia;

}Usuario;


Usuario pedirUsuario();


//menus de usuario
void menuGestUsuario();
	void opcionMenuGestUsuario();
		void menuAnadirUsuario();
		void menuModificarUsuario();

			void opcionMenuModificarUsuarios(int *opcion, Usuario* usu);
							void menuModificarNombre(Usuario* usu);
							void menuModificarApellido(Usuario* usu);
							void menuModificarDni(char dni[10]);
							void menuModificarFecha(Usuario* usu);
							void menuModificarTelefono(Usuario* usu);
							void menuModificarDireccion(Usuario* usu);
							void menuModificarContrasena(Usuario* usu);
							void menuModificarCiudadUsuario(Usuario* usu);
		void menuEliminarUsuario();

		// NUEVO

		void imprimirProvinciasListaUsuario(Provincia listaProvincias[], int numeroProvincias);

		void pedirProvinciasUsuario(Provincia listaProvincias[], int numeroProvincias, int* provinciaSelec, Usuario* u);
		void pedirCiudadesUsuario(Ciudad listaCiudades[], int numeroCiudades, int* ciudadSelec, Usuario* u);

		void imprimirCiudadesListaUsuario(Ciudad listaCiudades[], int numeroCiudades);

#endif /* USUARIO_H_ */

