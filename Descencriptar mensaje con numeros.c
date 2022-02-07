#include <stdio.h>
 
int main()
{
 	int t=0, i=0, j=0;
 	
 	scanf("%d", &t);
 	if (t<1 || t>50)
 	{
 		return 0;
	}
	
	char line[t][81];
	fflush(stdin);
	for(i=0; i<t; i++)
	{
		fgets(line[i], 80, stdin);
	}
	
	for(i=0; i<t; i++)
	{
		while(line[i][j] != '\0')
		{
			switch(line[i][j])
			{
				case '0':
					line[i][j]='O';
					break;
				case '1':
					line[i][j]='I';
					break;
				case '2':
					line[i][j]='Z';
					break;
				case '3':
					line[i][j]='E';
					break;
				case '4':
					line[i][j]='A';
					break;
				case '5':
					line[i][j]='S';
					break;
				case '6':
					line[i][j]='G';
					break;
				case '7':
					line[i][j]='T';
					break;
				case '8':
					line[i][j]='B';
					break;
				case '9':
					line[i][j]='P';
					break;
			}
			j+=1;
		}
	}
	
	for(i=0; i<t; i++)
	{
		printf("%s", line[i]);
	}
	
	return 0;
}
