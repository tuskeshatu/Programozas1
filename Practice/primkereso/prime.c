// prim e

#include <stdio.h>

int main()
{

	int i, szam, osztok;

	scanf("%d", &szam);

	for (i = 2 ; i < szam/2; i++)
	{
		if (szam % i == 0)
		{
			printf("nem prim");

			return 1;
		}
	}
	
	printf("prim");
	
	return 0;
}