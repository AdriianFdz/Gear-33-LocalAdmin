#ifndef COCHE_H_
#define COCHE_H_

//coche
typedef struct{
	int id;
	char nombre[15];
} Marca;

typedef struct{
	int id;
	char nombre[15];
	char cambio[15];
	char combustible[15];
	int id_marca;
} Modelo;

typedef struct {
	char matricula[8];
	char color[10];
	int anyo;
	float precioBase;
	Marca marca;
	Modelo modelo;
} Coche;


// menu gestion coche
void menuGestCoches();
void opcionMenuGestCoches(int *opcion);

	// menu anadir
	void menuAnadirCoche();

	// menu modificar
	void menuModificarCoche();

		// sub opciones

		void opcionMenuModificarCoches(int *opcion, Coche* c);
		void menuModificarMatricula(char matricula[] );
		void menuModificarMarcaModelo(Coche* c);
		void menuModificarColor(Coche* c);
		void menuModificarAnyo(Coche* c);
		void menuModificarPrecio(Coche* c);

	// menu eliminar
	void menuEliminarCoche();

	// funciones generales
	void pedirMarcas(Marca listaMarcas[], int numeroMarcas, int* marcaSelec, Coche* c);
	void pedirModelos(Modelo listaModelos[], int numeroModelos, int* modeloSelec, Coche* c);
	Coche pedirCoche();

	void imprimirMarcasLista(Marca listaMarcas[], int numeroMarcas);
	void imprimirModelosLista(Modelo listaModelos[], int numeroModelos);
#endif /* COCHE_H_ */
