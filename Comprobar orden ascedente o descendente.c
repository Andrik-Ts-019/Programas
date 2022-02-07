#include <stdio.h>

int main()
{
	int t=0, i=0, j=0;
 	
 	scanf("%d", &t);
 	if (t<1 || t>20)
 	{
 		return 0;
	}
	
	int beards[10][t];
	for(i=0; i<t; i++)
	{
		scanf("%d %d %d %d %d %d %d %d %d %d",
			&beards[0][i], &beards[1][i], &beards[2][i], &beards[3][i], &beards[4][i], 
			&beards[5][i], &beards[6][i], &beards[7][i], &beards[8][i], &beards[9][i]);
	}
	
	for(i=0; i<t; i++)
	{
		for(j=0; j<10; j++)
		{
			if(beards[j][i]<1 || beards[j][i]>100) return 0;
		}
	}
	
	j=0;
	for(i=0; i<t; i++)
	{
		if(beards[j][i] > beards[j+1][i])
		{
			for(; j<9; j++)
			{
				if(beards[j][i] < beards[j+1][i])
				{
					printf("Unordered\n");
					break;
				}
			}
			if(j==9) printf("Ordered\n");
			j=0;
		}
		
		if(beards[j][i] < beards[j+1][i])
		{
			for(; j<9; j++)
			{
				if(beards[j][i] > beards[j+1][i])
				{
					printf("Unordered\n");
					break;
				}
			}
			if(j==9) printf("Ordered\n");
			j=0;
		}
		
		if(beards[j][i] == beards[j+1][i])
		{
			j+=1;
			if(j==9) printf("Ordered\n");
			else i-=1;
		}	
	}
	
	return 0;
}
