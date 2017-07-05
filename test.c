#include <stdio.h>
#include "sorting.h"

int main ()
{
	int *a;
	int i, size, max;
	
	printf("Enter size of array: \n");
	scanf("%d", &size);
	printf("\n");

	printf("Enter max range of array: \n");
	scanf("%d", &max);
	printf("\n");

	test(size, max, SELECTION);
	test(size, max, BUBBLE);
	test(size, max, INSERTION);
	test(size, max, MERGE);
	test(size, max, QUICK);
	test(size, max, COUNTING);
	return 0;
}
