/*
Nombre: Andrik de la Cruz Martínez
Matrícula: 1863369
Grupo: 006.


Este programa realiza las operaciones de:
	-Insercion,
	-Eliminacion
	-Impresion
	-Ordenar
en listas enlazadas*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

struct nodo
{
	char dato;					//Dato a almacenar en el nodo de la lista
	struct nodo *siguiente;		//Enlace al siguiente nodo de la lista
};

typedef struct nodo NODO;		//Definicion de la estructura nodo como tipo de dato NODO
typedef NODO *NODOSIG;			/*Tipo de dato para generar los nodo de la lista, para no 
								  utilizar punteros de punteros*/

//Funciones del apartado ordenamiento
void submenuordenar(void);
void ordenar_ascendente(NODOSIG *);
void ordenar_descendente(NODOSIG *);


//Funciones de insercion en la lista
void insertar_frente(NODOSIG *, char);
void insertar_final(NODOSIG *, char);
void insertar_medio(NODOSIG *, char);

//Funciones de eliminacion en la lista
char borrar_frente(NODOSIG *);
char borrar_final(NODOSIG *);
char borrar_medio(NODOSIG *, char);

//Funcion de impresion de la lista
void printlista(NODOSIG);

//Funcion del menu de opciones
void instrucciones(void);

int main()
{
	NODOSIG lista = NULL;		//Puntero a una estructura nodo
	int op,op2; 				//op2 se usa en el apartado ordenar para el submenu
	char ele;

	do
	{
		system("cls");
		instrucciones();
		printf("\n\n ? ");
		scanf("%d", &op);
		switch (op) 
		{
			/*Los caso del 1 al 3 son de insercion*/
			case 1:
				printf("\n Introduzca el elemento: ");
				scanf("\n %c", &ele);		//Lectura del elemento a almacenar
				insertar_frente(&lista,ele);//Se envia el inicio de la lista y el valor a insertar
				printlista(lista);			//Se imprime la lista con el valor insertado
				printf("\n\n Oprima cualquier tecla para continuar ");
				getch();
				break;
			case 2:
				printf("\n Introduzca el elemento: ");
				scanf("\n %c", &ele);
				insertar_final(&lista, ele);
				printlista(lista);
				printf("\n\n Oprima cualquier tecla para continuar ");
				getch();
				break;
			case 3:
				printf("\n Introduzca el elemento: ");
				scanf("\n %c", &ele);
				insertar_medio(&lista, ele);
				printlista(lista);
				printf("\n\n Oprima cualquier tecla para continuar ");
				getch();
				break;
			/*Casos de borrar elemento de la lista del 4-6*/
			case 4:
				//Antes de eliminar el dato se pregunta si hay elementos en la lista
				if (!isempty(lista)){
					/*Se envia la lista y se regresa el valor a para indicar que si se elimino un
					  elemento de la lista*/
					if (borrar_frente(&lista)=='a')
					{ 
						printlista(lista);			//Se imprime la lista actualizada
					}
					//Si regresa un valor diferente de a que indica que era el ultimo valor
					else
					{
						printf("\n\n\n\t\tLista esta vacia\n\n");
						//Se libera completamente el espacio que ocupaba la lista
						free(lista);
						lista=NULL;					//Se inicia nuevamente la lista
					}
				}
				else
					printf("\n\n La lista no tiene elementos");
					
				printf("\n\n Oprima cualquier tecla para continuar ");
				getch();
				break;
			case 5:
				if (!isempty(lista))
					if (borrar_final(&lista)=='a')
					{					  
						printlista(lista);
						printf("\n\n Oprima cualquier tecla para continuar ");
				        //getch();
				    }
					else
					{
						printf("\n\n\n\t\tLista esta vacia\n\n");
						free(lista);
						lista=NULL;
						printf("\n\n Oprima cualquier tecla para continuar ");
					}
				getch();
				break;
			case 6:
				if (!isempty(lista)) 
				{/*se pregunta si hay elementos en la lista*/
					printf("Elemento a borrar: ");/*Se solicita el numero que se desea borrar*/
					scanf("\n%c", &ele);/*se lee el elemento a borrar*/
					if (borrar_medio(&lista, ele)) 
					{/*se envia la lista y el elemento a borrar*/
						//Se regresa un valor 1 si este elemento se borro
						printf("%c borrado", ele);
						/*Se indica que el elemento fue borrado y se imprime la lista actualizada*/
						printlista(lista);
					}
					/*Si se regreso un valor diferente de 1, lo que indica que no se encontro 
					  el elemento a borrar*/
					else
						printf("%c no existe \n\n",ele);
				}
				else
				{/*cuando la lista esta vacia se imprime el mesaje*/
					printf("Lista esta vacia\n\n");
					free(lista);/*se libera el espacio ocupado por la lista*/
					lista=NULL;/*se inicia la lista nuevamente*/
				}
				getch();
				break;
			//Agregado: ordenamiento de los elementos de la lista
			case 7:
				system("cls");
				submenuordenar();
				do
				{
					printf("\n\n ? ");
					fflush(stdin);
					scanf("%d", &op2);
				}while(op2<1 || op2>2);
				switch(op2)
				{
					//Agregado: ordenana los elementos de la lista de mayor a menor
					case 1:
						if (!isempty(lista))
						{
							ordenar_descendente(&lista);
							printlista(lista);
						}
						else
						{
							printf("\n\n\n\t\tLista vacia\n\n"
							"\n\n Oprima cualquier tecla para continuar ");
						}
						getch();
						break;
					/*Agregado: ordenana los elementos de la lista de menor a mayor*/
					case 2:
						if (!isempty(lista))
						{
							ordenar_ascendente(&lista);
							printlista(lista);
						}
						else
						{
							printf("\n\n\n\t\tLista vacia\n\n"
							"\n\n Oprima cualquier tecla para continuar ");
						}
						getch();
						break;
				}
				getch();
				break;
		}
	}while (op != 8);/*mientras no se presione la opcion de salir*/
	system("cls");
	printf("\n\n\n\n\n\n\t\t\t\t F I N\n");
	getch();
 return 0;
}

//Menú de opciones, para trabajar con la lista
void instrucciones()
{
  printf("\n\n\n\t\t OPERACIONES CON LISTAS ENCADENADAS\n\n");
  printf("\n\t\t\t Que opcion desea :\n\n"
	"   \t\t 1 Insertar frente\n"
	"   \t\t 2 Insertar final\n"
	"   \t\t 3 Insertar en medio\n"
	"   \t\t 4 Eliminar frente\n"
	"   \t\t 5 Eliminar final\n"
	"   \t\t 6 Eliminar en medio\n"
	"   \t\t 7 Ordenar lista\n"		/*Agregado*/
	"   \t\t 8 Salir\n");
}

/*Funcion para insertar un elemento al frente o al inicio de la lista
  recibe como parametro por referencia la lista y por valor
  el valor a insertar*/
void insertar_frente(NODOSIG *lista, char valor)
{
	//Variables temporales para la insercion en la lista del nuevo nodo, es un puntero
	NODOSIG nuevo;
	
	/*Esta operacion crea el nuevo nodo que sera insertado en la lista, realmente intenta 
	  conseguir espacio en memoria*/
	nuevo = malloc(sizeof(NODO));
	
	//Checamos sí se consiguió espacio suficiente para crear un nodo
	if (nuevo != NULL)
	{
		nuevo->dato = valor;		//Se asigna el dato que se quiere insertar
		nuevo->siguiente = NULL;	//Se asigna nulo a la posicion siguiente del nodo creado
		
		//El nuevo nodo en su posicion siguiente toma el inicio de la lista y la lista completa
		nuevo -> siguiente = *lista;
		
		/*Ahora el nuevo inicio de la lista lo tendra nuevo, por lo cual se le asigna la 
		  posicion de memoria a lista, que es en donde iniciara la lista ahora*/
		*lista = nuevo;
	}
	else
		printf("\n\n Espacio insuficiente\n");
}

/*Funcion para insertar un elemento en algun lugar de la lista, dependiendo del valor
  de este, se intenta insertar con cierto orden recibiendo como parametro por referencia 
  la lista y por valor el valor a insertar*/
void insertar_medio(NODOSIG *lista, char valor)
{
	//Variables auxiliares para recorrer la lista e insertar el nodo
	NODOSIG nuevo, previo, actual;
	nuevo = malloc(sizeof(NODO));			//Crea el nuevo nodo
	if (nuevo != NULL)						//Pregunta si se pudo crear el nodo
	{
		nuevo->dato = valor;				//Se almacena el dato
		nuevo->siguiente = NULL;			//Se pone en nulo el sigiente
		previo = NULL;						//Se inicializa previo en nulo
		actual = *lista;					//Se asigna la lista completa a actual
		
		//Se recorre la lista hasta encontrar el lugar adecuado para insertar el nodo
		while ((actual != NULL) && (valor > actual -> dato))
		{
		 	/*El nodo se insertara en forma ordenada, se asigna la posicion de actual a 
			  previo y se avanza al siguiente nodo*/
			previo = actual;
			actual = actual -> siguiente;
		}/*Cuando se llego al lugar indicado para insertar el nodo previo en su posicion 
		   siguiente toma la direccion del nuevo nodo*/
		
		if(previo == NULL){
			/*El nuevo nodo en su posicion siguiente toma la posicion de actual, 
			  lo que quiere decir que se esta insertando el nuevo en la parte de en medio 
			  de la lista*/
		   	nuevo -> siguiente = *lista;
		   	*lista = nuevo;
	    }
	    else
		{
	    	previo -> siguiente = nuevo;
		   	nuevo -> siguiente = actual;
		}
	}
	else
		printf("\n\n Espacio insuficiente\n");
}

/*Funcion para insertar un elemento en al final de la lista
  recibe como parametro por referencia la lista y por valor
  el valor a insertar, para ser insertado el elemento en la
  lista este debe recorrer toda la lista hasta llegar al final de ella*/
void insertar_final(NODOSIG *lista, char valor)
{
	//Variables auxiliares para recorrer y crear el nodo en la lista
	NODOSIG nuevo, previo, actual;
	
	nuevo = malloc(sizeof(NODO));			//Se genera el espacio del nuevo nodo
	
	//Se se pudo crear el espacio de memoria para el nodo
	if (nuevo != NULL)
	{
		nuevo->dato = valor;				//Se almacena el dato
		nuevo->siguiente = NULL;			//Se pone en nulo el siguiente
		
		//Se inicializa el previo que sera para verificar en donde se insertara el nodo
		previo = NULL;
		actual = *lista;					//Actual toma el inicio y la lista completa
		
		//Recorrera la lista hata llegar al final, pero la direccion del ultimo nodo
		while (actual != NULL) 
		{
			/*Quedara almacenado en previo, el cual permitira el enlace entre la lista y el 
			  nuevo nodo*/
			previo = actual;
			
			//Se avanza actual al siguiente nodo para llegar al final de la lista
			actual = actual -> siguiente;
		}/*Se llego al final de la lista y se asiga a previo en su posicion siguiente la 
		   posicion del nuevo nodo*/
		
		if (previo == NULL) 
		{
			nuevo -> siguiente = *lista;
			*lista = nuevo;
		}
		else 
		{
			previo -> siguiente = nuevo;
			nuevo -> siguiente = actual;
		}
	}
	else
		printf("\nEspacio insuficiente");
}

/*Funcion para imprimir la lista completa, recibe como parametro por valor
  el inicio y la lista completa*/
void printlista(NODOSIG actual)
{
	if (actual == NULL)						 //Si no hay elementos en la lista
		printf("Lista vacia \n\n");
	else 
	{										 //Si hay elementos en la lista
		printf("\n\n La lista es: \n\n");
		while (actual != NULL)
		{									 //Se imprimira la lista hasta llegar al final
			printf("%c --> ",actual -> dato);//Se imprime el contenido del nodo
			actual = actual -> siguiente;	 //Se avanza la posicion de actual al siguiente nodo
		} 
		printf("NULL \n\n");
	}
}

/*Funcion para borrar un elemento al principio de la lista
  recibe como parametro por referencia la lista*/
char borrar_frente(NODOSIG *lista)
{
	/*temporal es la variable la cual contendra la direccion del nodo que se va a borrar
	  previo se utiliza para determinar si es el ultimo nodo en la lista*/
	NODOSIG  temporal,previo;
	

	previo= (*lista)-> siguiente;	//Toma la posicion del siguiente nodo en la lista
	if (previo != NULL) 
	{								//Si no es el ultimo nodo
		//Temporal toma la posicion del nodo que se borrara en la lista
		temporal = *lista;
		/*La lista toma la direccion del siguiente nodo para que este sea el nuevo inicio 
		  de la lista*/
		*lista = (*lista) -> siguiente;
		free(temporal);				//Se libera el espacio ocupado por el nodo
		//Se retorna un valor para indicar que no era al ultimo nodo en la lista
		return 'a';
	}
	//Este valor de retorno indica que es el ultimo nodo en la lista
	return '\0';
}

/*Funcion para borrar un elemento al final de la lista
  recibe como parametro por referencia la lista*/
char borrar_final(NODOSIG *lista)
{
	NODOSIG  previo, actual, temporal;/*variables auxiliares*/
	previo = NULL;/*se inicializa el en nulo el previo que es el que contendra la lista*/
	actual = *lista;/*se asigna a actual el inicio y la lista completa*/
	if (actual->siguiente != NULL) 
	{/*pregunta si no es el ultimo nodo en la lista*/
		while (actual->siguiente != NULL )
		{/*se recorrera la lista sin llegar al ultimo elemento de la lista*/
			previo = actual;/*se asigna la posicion de actual a previo*/
			actual = actual -> siguiente;/*se avanza al siguiente nodo*/
		}/*se llego hasta un nodo antes del final y se asigna a temporal la lista*/
		
		//Para que este sea borrado y asi liberar el espacio ocupado por el elemento
		temporal=actual;
		//Se le asigna a previo en su posicion siguiente nulo, es decir, el fin de la lista
		previo->siguiente = NULL;
		free(temporal);/*se libera el espacio del nodo a borrar*/
		return 'a';/*se regresa un valor para indicar que no era el ultimo nodo*/
	}  
	return '\0';/*se regresa este valor para indicar que es el ultimo nodo*/
}

/*Funcion para borrar un elemento elejido por el usuario
  recibe como parametro por referencia la lista y por
  valor el valor a eliminar de la lista*/
char borrar_medio(NODOSIG *lista, char valor)
{
	NODOSIG  previo, actual, temporal;/*variables auxiliares*/
	previo = *lista;/*previo toma el inicio de la lista*/
	actual = (*lista) -> siguiente;/*actual toma la posicion del siguiente nodo*/
	while (actual != NULL && actual -> dato != valor)
	{/*mientras no se llege al final de la lista y no sea el numero que se quiere borrar*/
		previo = actual;/*previo toma la posicion de actual*/
		actual = actual -> siguiente;/*actual avanza al siguiente nodo*/
	}
	if (actual != NULL) 
	{/*pregunta si no es el ultimo nodo en la lista*/
		temporal = actual;/*temporal toma la posicion de alctual que es el nodo a borrar*/
		//Previo en siguiente toma el enlace al siguiente nodo
		previo -> siguiente = actual -> siguiente;
		free(temporal);/*de actual y entonces se libera el espacio que ocupaba el nodo a borrar*/
		return(valor);/*regresa el elemento borrado*/
	}
	return '\0';/*regresa este valor para indicar que es el ultimo nodo en la lista*/
}

/*Funcion para determinar si hay elementos en la lista, recibe como parametro
  por valor la el inicio de la lista*/
int isempty(NODOSIG lista)
{
	/*Pregunta si hay elemento en la lista, regresa nulo si no hay de lo contrario 
	  regresa un valor diferente*/
	return lista == NULL;
}
 
/*Agregado: sub-menú del apartado ordenar*/
 void submenuordenar(){
	printf("\n\n\t\tSelecione una opcion\n\n"
		"	\t\t 1 ordenar de forma descendente\n"
		"	\t\t 2 ordenar de forma ascendente\n");
 }
 
 /*Agregado:ordenar de forma ascendente*/
void ordenar_ascendente(NODOSIG *lista)
{
	NODOSIG previo,actual,aux=NULL;
	previo=*lista;
	actual=(*lista)->siguiente;
	/*Comprueba que hay más de dos elementos y que aun hay cosas  desacomodadas 
	  (existen elementos antes del nodo al que apunta aux)*/
	while(aux!=*lista && actual!=NULL){
		while(actual!=NULL){			//comprueba si existe nodo
			/*Ve avanzando el aux, todo nodo despues del nodo donde aux apunta ya estan ordenados*/
			if(actual==aux){			
				aux=previo;
				break;
			}
			/*Inicia el intercambio, si el nodo despues de previo es menor, actual 
			  se inserta al inicio*/
			if((actual->dato) < (previo->dato)){
				aux=previo;
				previo->siguiente=actual->siguiente;
				actual->siguiente=*lista;
				*lista=actual;
				actual=previo->siguiente;
			}
			else{				/*mueve los punteros*/
				previo=actual;
				actual=actual->siguiente;
			}
		}
		/*Si aux es igual a nulo, la cadena ya estaba ordenada de forma descendente*/
		if(aux==NULL)
		break;
		previo=*lista;					/*vuelve empezar y termina cuando te encuentres con aux*/
		actual=(*lista)->siguiente;
	}
 }
 
 /*Agregado: ordenar de forma descendente*/
void ordenar_descendente(NODOSIG *lista){
	NODOSIG previo,actual,aux=NULL;
	previo=*lista;
	actual=(*lista)->siguiente;
	
	/*Comprueba que hay más de dos elementos y que aun hay cosas  desacomodadas 
	  (existen elementos antes del nodo al que apunta aux)*/
	while(aux!=*lista && actual!=NULL){
		while(actual!=NULL){			/*comprueba si existe nodo*/
			/*Ve avanzando el aux, todo nodo despues del nodo donde aux apunta ya estan ordenados*/
			if(actual==aux){
				aux=previo;
				break;
			}
			/*Inicia el intercambio, si el nodo despues de previo es menor, actual 
			  se inseta al inicio*/
			if((actual->dato) > (previo->dato)){
				aux=previo;
				previo->siguiente=actual->siguiente;
				actual->siguiente=*lista;
				*lista=actual;
				actual=previo->siguiente;
			}
			else{				/*mueve los punteros*/
				previo=actual;
				actual=actual->siguiente;
			}
		}
		//Si aux es igual a nulo, la cadena ya estaba ordenada de forma descendente
		if(aux==NULL)
		break;
		previo=*lista;					/*vuelve empezar y termina cuando te encuentres con aux*/
		actual=(*lista)->siguiente;
	}
 }
