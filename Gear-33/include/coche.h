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
		void menuAnadirCoche();
		void menuModificarCoche();
			void opcionMenuModificarCoches(int *opcion, char matricula[]);
				void menuModificarMatricula(char matricula[] );
				void menuModificarMarcaModelo(char matricula[]);
				void menuModificarColor(char matricula[]);
				void menuModificarAnyo(char matricula[]);
				void menuModificarPrecio(char matricula[]);
				void menuModificarCambio(char matricula[]);
				void menuModificarCombustible(char matricula[]);
		void menuEliminarCoche();


#endif /* COCHE_H_ */
