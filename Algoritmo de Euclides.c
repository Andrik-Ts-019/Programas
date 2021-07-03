/*
	Obtención del Máximo Común Divisor de dos números
	mcd(a,b)
*/

#include <stdio.h>
#include <stdlib.h> 				//Necesario para la función div()

int AltEuclides(int,int);
int divEntera();

int main(){
	int a, b;
	int mcd;
	
	printf("\nIngrese a: ");
	scanf("%d",&a);
	printf("\nIngrese b: ");
	scanf("%d",&b);
	
	mcd=AEuclides(a,b);
	if(a>b)	printf("\n\nMCD(%d,%d)=%d",a,b,mcd);
	else	printf("\n\nMCD(%d,%d)=%d",b,a,mcd);
	
	return 0;
}

//Máximo Común Divisor
//a = bq + r => mcd(a,b) = mcd(b,r)
int AEuclides(int a, int b){
	div_t resultado;
	
	if(a<b){
		int aux;
		aux = a;
		a=b;
		b=aux;
	}
	
	resultado=div(a,b);
	
	if(resultado.rem==0)	return b;
	
	AEuclides(b,resultado.rem);
}
