#include<stdio.h>
#include <stdlib.h>

struct nodo{
	char dato;
	struct nodo *siguiente;
};

typedef struct nodo NODO;
typedef NODO* nodosig; //El puntero tipo NODO se pasa a llamar nodosig

void insertar_enfrente(nodosig *lista, char valor);
void printlista(nodosig);

int main(){
	nodosig lista=NULL; //head de la lista. Dato  tipo nodosig
	char elemento,op;
	
	printf("\t\t\tLISTAS ENCADENADAS");
	do{
		printf("\n\nIngrese letra\n");
		fflush(stdin);
		scanf("%c",&elemento);
		insertar_enfrente(&lista,elemento);
		printf("\n\n%cDesea ingresar otro valor%c"
			   "\n1.-Si"
			   "\nCualquier tecla.-No\n",168,63);
		fflush(stdin);
		scanf("%c",&op);
	}while(op=='1');
	
	printlista(lista);
	
	return 0;
}

//Paso por referecia
void insertar_enfrente(nodosig *lista, char valor){
	nodosig nuevo;
	nuevo=malloc(sizeof(NODO)); //Comprobamos sí hay memoria disponible
	if(nuevo!=NULL){
		nuevo->dato=valor;
		nuevo->siguiente=NULL;
		nuevo->siguiente=*lista;
		*lista=nuevo;
	}
}


void printlista(nodosig actual)
{
	if (actual == NULL)/*Si no hay elementos en la lista*/
		printf("Lista vacia \n\n");
	else 
	 {/*si hay elementos en la lista*/
		printf("\n\n La lista es: \n\n");
		while (actual != NULL) 
		  {/*se imprimira la lista hasta llegar al final*/
			printf("%c --> ",actual -> dato);/*se imprime el contenido del nodo*/
			actual = actual -> siguiente;/*se avanza la posicion de actual al siguiente nodo*/
		  } 
		printf("NULL \n\n");
	 }
}
