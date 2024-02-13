#include <stdio.h>

int main()
{
	int i, j, vege, osztok;

	printf("Meddig?");
	scanf("%d", &vege);

	for (i = 2; i < vege; i++)
	{
		for (j = 2; j < i; j++)
		if (i % j == 0)
		{	
			osztok++;
		}
		
	if (osztok == 0)
	{
		printf("%d ", i);
	}

    osztok = 0;

	}

	return 0;
}