#include <stdio.h>
#include "sorting.h"

int main ()
{
	int *a;
	int i, size;
	
	printf("Enter size of array: \n");
	scanf("%d", &size);
	printf("\n");

	a = generate_array(size);
	printf("The array is %s\n", is_sorted(a, size) ? "sorted" : "unsorted");
	print(a, size);

	sort_selection(a, size);
	printf("The array is %s\n", is_sorted(a, size) ? "sorted" : "unsorted");
	print(a, size);

	sort_bubble(a, size);
	printf("The array is %s\n", is_sorted(a, size) ? "sorted" : "unsorted");
	print(a, size);

	sort_bubble(a, size);
	printf("The array is %s\n", is_sorted(a, size) ? "sorted" : "unsorted");
	print(a, size);

	sort_merge(a, size);
	printf("The array is %s\n", is_sorted(a, size) ? "sorted" : "unsorted");
	print(a, size);

	destroy_array(&a, size);

	return 0;
}
