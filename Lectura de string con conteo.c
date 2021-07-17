#include <stdio.h>
#include <conio.h>
#include <string.h>
#define N 11

void lectura(char *);

int main()
{
	char string[2][N];
	
	lectura(&string[0][0]);
	
	printf("\nString: %s %d", string[0], strlen(string[0]));
	return 0;
}


/* Retroceso: 8 (Backspace) */
void lectura(char *str)
{
	int i, j=0;
	fflush(stdin);
	for(i=0; i<N-1; )
	{
		system("cls");
		printf("\nEscriba algo (espacio disponible: %d)\n", N-i-1);
		
		for(j=0; j!=i; j++) printf("%c",*(str+j));
		
		*(str+i)=_getch();
		
		if(*(str+i)==8 && i==0) i--;	/* Borrar sin tener carácteres */
		if(*(str+i)==8 && i!=0) i-=2;	/* Permite borrar lo que se escribe */
		
		if(*(str+i) == 13)
		{
			*(str+i)='\0';
			break;
		}
		
		i++;							/* Al finalizar un ciclo incrementamos i en 1 */
	}
	
	system("cls");
	printf("\nEscriba algo (espacio disponible: %d)\n", N-i-1);
}
