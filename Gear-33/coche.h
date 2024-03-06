
#ifndef COCHE_H_
#define COCHE_H_

typedef struct {
	char matricula[7];
	char color[10];
	int anyo;
	float precioBase;
	char marca [15];
	char modelo [15];
	char cambio [15];
	char combustible[10];

}Coche;

Coche pedirCoche();


#endif /* COCHE_H_ */
