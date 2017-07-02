#include "sorting.h"

/* function to swap to integers */

void swap (int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
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
