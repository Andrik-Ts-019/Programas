/*Ejemplo Backtracking */
#include <stdio.h>
#define N 4

void imprimirSolucion(int tablero[N][N]);
int esSeguro(int tablero[N][N], int fila, int columna);
int colocarReina(int tablero[N][N], int columna);
int resolver();

int main() {
	resolver();
	return 0;
}

void imprimirSolucion(int tablero[N][N]) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++)
			printf(" %d ", tablero[i][j]);
		printf("\n");
	}
}

int esSeguro(int tablero[N][N], int fila, int columna) {
	int i, j;

	for (i = 0; i < columna; i++)
		if (tablero[fila][i])
			return 0;
	for (i = fila, j = columna; i >= 0 && j >= 0; i--, j--)
		if (tablero[i][j])
			return 0;
	for (i = fila, j = columna; j >= 0 && i < N; i++, j--)
		if (tablero[i][j])
			return 0;
	return 1;
}
int colocarReina(int tablero[N][N], int columna) {
	int i;
	if (columna >= N)
		return 1;
	for (i = 0; i < N; i++) {
		imprimirSolucion(tablero);
		printf("\n");
		if (esSeguro(tablero, i, columna)) {
			tablero[i][columna] = 1;
			if (colocarReina(tablero, columna + 1))
				return 1;
			tablero[i][columna] = 0; 
		}
	}
	return 0;
}

int resolver() {
	int tablero[N][N] = {0};

	if (colocarReina(tablero, 0) == 0) {
		printf("la solucion no existe");
		return 0;
	}

	imprimirSolucion(tablero);
	return 1;
}

