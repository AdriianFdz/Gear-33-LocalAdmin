#ifndef INCLUDE_TIENDA_H_
#define INCLUDE_TIENDA_H_

typedef struct{
	int id_provincia;
	char nombre[51];
} Provincia;
typedef struct{
	int id_ciudad;
	char nombre[51];
	Provincia provincia;
} Ciudad;
typedef struct{
	int id_tienda;
	char direccion[51];
	char telefono[10];
	Ciudad ciudad;
	Provincia provincia;
} Tienda;





// menu gestion tienda
void menuGestTienda();
void opcionMenuGestTiendas(int* opcion);

	// menu anadir
	void menuAnadirTienda();

	//menu importar
	void menuImportarTienda();

	// menu modificar
	void menuModificarTienda();
	void opcionMenuModificarTienda(int* opcion, Tienda* t);
	void menuModificarDireccionTienda(Tienda* t);
	void menuModificarTelefonoTienda(Tienda* t);
	void menuModificarCiudadTienda(Tienda* t);

	// menu eliminar
	void menuEliminarTienda();


	void imprimirProvinciasLista(Provincia listaProvincias[], int numeroProvincias);
	Tienda pedirTienda();
	void pedirProvincias(Provincia listaProvincias[], int numeroProvincias, int* provinciaSelec, Tienda* t);
	void pedirCiudades(Ciudad listaCiudades[], int numeroCiudades, int* ciudadSelec, Tienda* t);

	void imprimirCiudadesLista(Ciudad listaCiudades[], int numeroCiudades);
	void imprimirTiendasLista(Tienda listaTiendas[], int numeroTiendas);

#endif /* INCLUDE_TIENDA_H_ */
