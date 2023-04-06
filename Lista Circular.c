#include <stdio.h>
#include <stdlib.h>

typedef int Item;

typedef struct Elemento
{
	Item numero;
	struct Elemento* siguiente;
} Nodo;

//typedef Nodo** NCabeza;

Nodo* NuevoNodo(Item dato);

void InsertarNodo(/*NCabeza*/Nodo** LCircular, Item nuevoDato);

void EliminarNodo(/*NCabeza*/Nodo** LCircular, Item nuevoDato);

int main()
{
	int dato;
	Nodo* LC;
	
	printf("\nIngrese un dato: ");
	scanf("%d", &dato);
	
	InsertarNodo(&LC,dato);
	
	return 0;
}

Nodo* NuevoNodo(Item dato)
{
	Nodo* nodo;
	
	nodo = (Nodo*)malloc(sizeof(Nodo));
	
	nodo->numero = dato;
	
	//Al ser una lista circular debe apuntar a si mismo
	nodo->siguiente = nodo;
	
	return nodo;
}

void InsertarNodo(/*NCabeza*/Nodo** LCircular, Item nuevoDato)
{
	Nodo* nuevoNodo;
	
	nuevoNodo = NuevoNodo(nuevoDato);
	
	//Lista Circular con elementos: LCircular dierente a NULL
	if (*LCircular)
	{
		nuevoNodo->siguiente = (*LCircular)->siguiente;
		(*LCircular)->siguiente = nuevoNodo;
	}
	
	*LCircular = nuevoNodo;
}

void EliminarNodo(/*NCabeza*/Nodo** LCircular, Item dato)
{
	Nodo* actual;
	
	int encontrado = 0;
	
	actual = *LCircular;
	
	/*Busqueda*/
	while ((actual->siguiente != *LCircular) && (!encontrado)) 
	{
		encontrado = (actual->siguiente->numero == dato);
		
		if (!encontrado)
		{
			actual = actual->siguiente;
		}
	}
	
	encontrado = (actual->siguiente->numero == dato);
	
	if (encontrado)
	{
		Nodo* p;
		
		p = actual->siguiente;
		
		if (*LCircular == (*LCircular)->siguiente)
			*LCircular = NULL;
		
		else
		{
			if(p == *LCircular)
			{
				*LCircular = actual;
			}
			
			actual->siguiente = p->siguiente;
		}
		
		free(p);
	}
}
