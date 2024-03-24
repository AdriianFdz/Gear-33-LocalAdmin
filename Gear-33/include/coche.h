#ifndef COCHE_H_
#define COCHE_H_

//coche
typedef struct {
	char matricula[8];
	char color[10];
	int anyo;
	float precioBase;
	char marca [15];
	char modelo [15];
	char cambio [15];
	char combustible[10];

}Coche;

Coche pedirCoche();

//lista coches
typedef struct {
	Coche *lCoches;
	int tam;
	int numCoches;

}ListaCoches;

void aniadirCoche(ListaCoches *lc, Coche c);

int aniadirCocheBD(Coche c);



//menus de coches
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


#endif /* COCHE_H_ */
