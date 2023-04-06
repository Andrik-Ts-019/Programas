#include <stdio.h>

const int num_lineas = 9;
const char blanco = ' ';
const char asterisco = '?';

int main()
{
	int fila, blancos, cuenta_as;
	puts(" ");
	
	for (fila = 1; fila <= num_lineas; fila++)
	{
		putchar('\t');
		
		for (blancos = num_lineas-fila; blancos > 0; blancos--)
			putchar(blanco);
			
		for (cuenta_as = 1; cuenta_as < 2*fila; cuenta_as++)
			putchar(asterisco);
			
		puts(" ");
	}
	
	return 0;
}
