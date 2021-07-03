#include<stdio.h>

int main(){
	char a;
	int i,j;
	for(j=122;j>=97;j--){
		for(i=j;i>=97;i--){
			a=i;
			printf("%c",a);
			if(i==97){
				printf("\n");
			}
		}
	}
	return 0;
}
