#include <stdio.h>
#include <string.h>
#include "../include/usuario.h"


void aniadirUsuario(ListaUsuarios *lu, Usuario u)
{
	if(lu->numUsuarios < lu->tam){
			lu->lUsuarios[lu->numUsuarios] = u;
			lu->numUsuarios++;
			printf("Usuario añadido correctamente\n");
		}else{
			printf("Lo sentimos! La lista esta completa\n");
		}
	fflush(stdout);

}
Usuario pedirUsuario(){
	Usuario u;
	printf("Introduce el nombre \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.nombre);

			printf("Introduce el apellido \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.apellido);

			printf("Introduce el dni \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.dni);

			printf("Introduce la fecha de nacimiento DD/MM/AAAA \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.fecha);

			printf("Introduce el teléfono \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.telefono);

			printf("Introduce la dirección \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.direccion);

			printf("Introduce la contraseña \n");
			fflush(stdout);
			fflush(stdin);
			gets(u.contrasena);

			return u;
}
