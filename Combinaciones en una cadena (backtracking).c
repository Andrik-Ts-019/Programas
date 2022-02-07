#include <stdio.h>
#include <string.h>
void permutar(char *a, int l, int r);
void cambio(char *x, char *y);

int main() {
	char str[] = "ABC";
	printf("\tPara %s\n", str);
	int n = strlen(str);
	permutar(str, 0, n-1);
	return 0;
}

void cambio(char *x, char *y) {
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void permutar(char *a, int l, int r) {
	int i;
	if (l == r)
		printf(" -%s\n", a);
	else {
		for (i = l; i <= r; i++) {
			cambio((a+l), (a+i));
			permutar(a, l+1, r);
			cambio((a+l), (a+i));
		}
	}
}



