/*   Algoritmo RSA   */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
// Similar al div_t de stdlib.h, para calcular divisiones enteras
// mcd(a,b)=d=a*x+b*y
typedef struct {
	int d;						//mcd(a,b)
	int x;
	int y;
} EE;

/* Algoritmo de euclides: a=e y b=phi
   Obtenci�n del mcd(e,phi)
   Donde mcd(a,b)=D=a*x+b*y => mcd(e,phi)=1=e*x+phi*y
*/
EE extended_euclid(int a, int b) {
	EE ee1, ee2, ee3;
	if (b == 0) {
		ee1.d = a;
		ee1.x = 1;
		ee1.y = 0;
		return ee1;
	} 
	else {
  		ee2 = extended_euclid(b, a % b);
  		ee3.d = ee2.d;
  		ee3.x = ee2.y;
		ee3.y = ee2.x - floor(a / b) * ee2.y;
  		return ee3;
	}
}
 
// Copied from 
// https://stackoverflow.com/questions/11720656/modulo-operation-with-negative-numbers
int modulo(int x, int N){			// x=ee.x y N=phi
	return (x % N + N) % N;			// Tomando en cuenta que div_E(-7,3)=-3 y div_E(-7,3)!=-2
}									//donde x = div_E(x,N)*N + x%b
 
void decimal_to_binary(int op1, int aOp[]){
    int result, i = 0;
    do{
        result = op1 % 2;
        op1 /= 2;
        aOp[i] = result;
        i++;
    }while(op1 > 0);
}
 
int modular_exponentiation(int a, int b, int n){
	int *bb;
 	int count = 0, c = 0, d = 1, i;
 
 	// find out the size of binary b
 	count = (int) (log(b)/log(2)) + 1;
 
 	bb = (int *) malloc(sizeof(int*) * count);
 	decimal_to_binary(b, bb);
 
	for (i = count - 1; i >= 0; i--) {
  		c = 2 * c;
  		d = (d*d) % n;
  		if (bb[i] == 1) {
   			c = c + 1;
   			d = (d*a) % n;
  		}
 	}
 	return d;
}
 
int get_d(int e, int phi){
 	EE ee;
 	ee = extended_euclid(e, phi); //mcd(e,phi)=1=e*x+phi*y
 	return modulo(ee.x, phi);
}
 
int main(int argc, char* argv[]) {
	int p, q, phi, n, e, d, m, c;
 	printf("Enter the value of p: ");
 	scanf("%d", &p);								//Primer n�mero primo
 	printf("Enter the valeu of q: ");
 	scanf("%d", &q);								//Segundo n�mero primo
 	n = p*q;
 	phi = (p - 1) * (q - 1);
 	printf("Enter the value of e: ");
 	scanf("%d", &e);								//e es primo relativo tal que phi > e > 1
 	d = get_d(e, phi);
 	printf("Public Key: (n = %d, e = %d)\n", n, e);
 	printf("Private Key: (n = %d, d = %d)\n", n, d);
 	printf("Enter message to encrypt: ");
 	scanf("%d", &m);
 	c = modular_exponentiation(m, e, n);
 	printf("Encrypted message is: %d\n", c);
 	m = modular_exponentiation(c, d, n);
 	printf("Message is decrypted to %d\n", m);
 	return 0;
}
