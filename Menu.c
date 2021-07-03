/* MENÚ */
#include <stdio.h>

int menu();					//Muestra el un menú funcional
void impMenu(int);			//Impresión del menú.

int main()
{
	int e;
	
	e=menu();
	return e;
}

// En Windows 10, para leer teclas funcionales del teclado es necesario leer dos veces.
//	FLECHA_ARRIBA: -32 72
//	FLECHA_ABAJO: -32 80
int menu()
{
	int opc=1;
	char c[2];							//Lectura doble para las taclas flechas.
	
	do
	{
		impMenu(opc);
		
		printf("\n");
		
		c[0]=_getch();
		if(c[0]==13) break;				//Sí se presiona Enter se selecciona una opción.
		c[1]=_getch();
		
		system("cls");
		
		if(c[0]==-32 && c[1]==80 && opc!=6) opc++;
		if(c[0]==-32 && c[1]==72 && opc!=1) opc--;
	}
	while (1);
	
	return opc;
}

//Ejemplo: opción 6 = Salir
void impMenu(int opcion)
{
	switch (opcion)
	{
		case 1:
			printf("\n\t\t\tMEN%c"
		   		   "\n\n"
		  		   "\n\t\t---> 1.-Opci%cn 1 <---"
		  		   "\n\t\t2.-Opci%cn 2"
	  			   "\n\t\t3.-Opci%cn 3"
	   			   "\n\t\t4.-Opci%cn 4"
	 			   "\n\t\t5.-Opci%cn 5"
	   			   "\n\t\t6.-Opci%cn 6",233,162,162,162,162,162,162);
			break;
		case 2:
			printf("\n\t\t\tMEN%c"
	   			   "\n\n"
		   		   "\n\t\t1.-Opci%cn 1"
		   		   "\n\t\t---> 2.-Opci%cn 2 <---"
		   		   "\n\t\t3.-Opci%cn 3"
		   		   "\n\t\t4.-Opci%cn 4"
				   "\n\t\t5.-Opci%cn 5"
	   			   "\n\t\t6.-Opci%cn 6",233,162,162,162,162,162,162);
			break;
		case 3:
			printf("\n\t\t\tMEN%c"
	   			   "\n\n"
			   	   "\n\t\t1.-Opci%cn 1"
		   		   "\n\t\t2.-Opci%cn 2"
		   		   "\n\t\t---> 3.-Opci%cn 3 <---"
				   "\n\t\t4.-Opci%cn 4"
		   		   "\n\t\t5.-Opci%cn 5"
		   		   "\n\t\t6.-Opci%cn 6",233,162,162,162,162,162,162);
			break;
		case 4:
			printf("\n\t\t\tMEN%c"
		   		   "\n\n"
				   "\n\t\t1.-Opci%cn 1"
		   		   "\n\t\t2.-Opci%cn 2"
		   		   "\n\t\t3.-Opci%cn 3"
		   		   "\n\t\t---> 4.-Opci%cn 4 <---"
				   "\n\t\t5.-Opci%cn 5"
	   			   "\n\t\t6.-Opci%cn 6",233,162,162,162,162,162,162);
			break;
		case 5:
			printf("\n\t\t\tMEN%c"
		   		   "\n\n"
		   		   "\n\t\t1.-Opci%cn 1"
		   		   "\n\t\t2.-Opci%cn 2"
		   		   "\n\t\t3.-Opci%cn 3"
		   		   "\n\t\t4.-Opci%cn 4"
		   		   "\n\t\t---> 5.-Opci%cn 5 <---"
		   		   "\n\t\t6.-Opci%cn 6",233,162,162,162,162,162,162);
			break;
		case 6:
			printf("\n\t\t\tMEN%c"
		   		   "\n\n"
		   		   "\n\t\t1.-Opci%cn 1"
		   		   "\n\t\t2.-Opci%cn 2"
		   		   "\n\t\t3.-Opci%cn 3"
		   		   "\n\t\t4.-Opci%cn 4"
		   		   "\n\t\t5.-Opci%cn 5"
		   		   "\n\t\t---> 6.-Opci%cn 6 <---",233,162,162,162,162,162,162);
			break;
	}
	printf("\n\n\tPresionar Enter para seleccionar.");
}
