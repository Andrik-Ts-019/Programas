#include <stdio.h>
int par(int n) ;
int impar(int n);

int main (void)
{
	int n;
	do {
	
	/* Entrada: entero > 0 */
	printf ("\nEntero > 0: ");
	scanf ("%d", &n) ;
	} while (n<=0);
	/* Llamda a la funcion par() */
	if (par(n))
		printf ( "El numero %d es par" ,n);
	else
		printf ( "El numero %d es impar", n);
	return 0;	
}

int par(int n)
{
	if (n == 0)
		return 1; /* es par */
	else			
		return impar(n-1);
}

int impar(int n)
{
	if (n == 0)
		return 0; /* es impar */
	else
		return par(n-1);
}
