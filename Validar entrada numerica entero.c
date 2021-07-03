#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int comprobar_entrada(char p_entrada[' ']);

int main(){
	int n=1,comprobador=0;
	char leern[' '];
	
	do{
		printf("\n\nIngrese la cantidad de alumnos a registrar\n");
		fflush(stdin);
		gets(leern);
		comprobador=comprobar_entrada(leern);
		
		if(comprobador==1){
			system("cls");
			printf("\nDato %s no v%clido\n",leern,160);
		}
		else
			n=atoi(leern); //De char[] a int, si char[] no es int, retorna 0
		
		
		if(n<=0){
			system("cls");
			printf("\nN%cmero %d no v%clido\n",163,n,160);
		}
			
		printf("\natoi %d",n);
	}while(comprobador==1||n<=0);
	return 0;
}

int comprobar_entrada(char p_entrada[' ']){
	int i;
	for(i=0;p_entrada[i];i++){
		if((p_entrada[i]<48||p_entrada[i]>57)&&(p_entrada[i]!=45)){
			return 1; //Inválido: es caracter
		}
	}
	return 0; //Válido: no es caracter
}
