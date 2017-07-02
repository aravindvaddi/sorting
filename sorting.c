#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "sorting.h"

/* function to swap to integers */

void swap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/* function to print a given array */

void print (int *array, int size)
{
	int i;

	for(i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("\n\n");
}

/* function to generate a random array of given size */

int *generate_array (int size)
{
	int *array;
	int i;

	/* randomizing the seed for rand to generate unique values */
	srand(time(NULL));

	/* allocating memory from the heap to the array */
	array= malloc(sizeof(int) * size);

	for(i = 0; i < size; i++)
		array[i] = rand() % INT_MAX;

	/* returning address pointing to array memory block */
	return array;
}

/* function to destroy an array created by generate_array */

void destroy_array (int **array_reference, int size)
{
	int i;
	int *temp = *array_reference;

	/* setting values in the memory to zero */
	for(i = 0; i < size; i++)
		temp[i] = 0;

	/* freeing allocated memory */
	free (temp);

	/* getting rid of the dangling pointer */
	*array_reference = NULL;
}

/* function to check if array is sorted */

int is_sorted (int *array, int size)
{
	int i, flag;

	for(i = 0, flag = 1; i < size - 1; i++)
	{
		if(array[i] > array[i + 1])
		{
			flag = 0;
			break;
		}
	}

	return flag;
}

/* function to implement selection sort on given array of integers */

void sort_selection (int *array, int size)
{
	/* declaring variables to use for counting */
	int c1, c2;

	/* declaring variable to hold minumun value index */
	int minimum;

	for (c1 = 0; c1 < size - 1; c1++)
	{
		for (c2 = c1 + 1, minimum = c1; c2 < size; c2++)
		{
			/* checking if value at c2 is smaller than value at minimum index */
			if (array[c2] < array[minimum])
				minimum = c2;
		}

		/* swapping minimum value with the value at first index */
		swap (&array[c1], &array[minimum]);
	}
}

/* function to implement selection sort on given array of integers */

void sort_bubble (int *array, int size)
{
	/* declaring variable to use for counting */
	int c1, c2;

	/* declaring variable for checking for completion */
	int flag;

	/* traversing through the array size - 1 times */
	for (c1 = 0; c1 < size - 1; c1++)
	{
		/* setting flag to 0, implying that no elements have been swapped */
		flag = 0;

		/* traversing through the array and moving the largest element to the end */
		for (c2 = 0; c2 < size - c1 - 1; c2++)
		{
			/* comparing consecutive elements, each element is checked twice except the first and last */
			if (array[c2] > array[c2 + 1])
			{
				/* flag is set to 1 to imply an element swap has occured */
				flag = 1;
				swap (&array[c2], &array[c2 + 1]);
			}
		}

		/* if flag is not set we break from the loop as this implies no elements have been swapped, i.e the array is sorted */
		if(!flag)
			break;
	}
}
