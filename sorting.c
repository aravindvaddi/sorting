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

/* function to implement insertion sort on given array of integers */

void sort_insertion (int *array, int size)
{
	int val, separator, counter;

	/*
		separator separates the sorted and unsorted part of an array.
		array to the left of the separator is sorted and from the separator is unsorted
		initially there's just one element in the sorted part as set of one is always sorted.
	*/

	for(separator = 1; separator < size; separator++)
	{
		/* storing value at the separator in the val variable, this will be inserted in it's appropriate place in the array */
		for(counter = separator, val = array[separator]; counter > 0 && array[counter - 1] > val; counter--)
		{
			/* as long as the element before the counter pointing element is greater, counter pointing value gets updated to it. */
			array[counter] = array[counter - 1];
		}
		/* counter value is at it's appropriate place */
		array[counter] = val;
	}
}

/* function to implement mergesort on a given array of integers */

void sort_merge(int *array, int size)
{
	/*
		variables for:
			- right array size
			- left array size
			- counter variables
			- pointers to hold left and right sub arrays
	*/
	int rs, ls, i, j, k;
	int *left, *right;

	/* base case */
	if(size < 2)
		return;

	/* deciding size of left and right sub arrays */
	ls = size / 2;
	rs = size - ls;

	/* allocating memory for the sub arrays from the heap */
	left = malloc(sizeof(int) * ls);
	right = malloc(sizeof(int) * rs);

	/* copying values into left and right sub arrays from the main array */
	for(i = k = 0; i < ls; i++, k++)
		left[i] = array[k];

	for(j = 0; j < rs; j++, k++)
		right[j] = array[k];

	/* recursive calls to divide the problem */
	sort_merge(left, ls);
	sort_merge(right, rs);

	/* merging the sorted subarrays (base case where an array of size 1 is already sorted is being utilized)*/
	for(i = j = k = 0; i < ls && j < rs; k++)
	{
		if(left[i] <= right[j])
			array[k] = left[i++];
		else
			array[k] = right[j++];
	}

	/* adding the remaining elements incase the arrays are not equally exhausted */
	while(i < ls)
		array[k++] = left[i++];

	while(j < rs)
		array[k++] = right[j++];

	/* freeing allocated memory */
	free(left);
	free(right);
}

/*
	library function to help quick sort.

		- partitions an array and returns a pivot index
		- elements to the left of pivot are smaller and right are greater
*/

int lib_qsort_partition (int *array, int start, int end)
{
	int pivot, partition_index, i;

	/* setting the pivot value to the element at the last index */
	pivot = array[end];

	/* traversing the remaining array (except the last index) to partition it */
	for(i = partition_index = start; i < end; i++)
	{
		/* if a value at a position is less than the pivot value it is swapped to the left of pivot index */
		if(array[i] <= pivot)
		{
			/* swapping the current element with the element at partition_index and incrementing it */
			swap(&array[i], &array[partition_index]);
			partition_index++;
		}
	}

	/* swapping the element at partition index with the pivot element, that is the last element (as we assumed last element to be the pivot) */
	swap(&array[end], &array[partition_index]);

	/* returning the index of pivot */
	return partition_index;
}

/*
	library function to help quick sort
		- randomizes the selection of a pivot element
		- this highly decreases probability of hitting worst case on every recursive call
*/

int lib_qsort_randomized_partition (int *array, int start, int end)
{
	int partition_index;

	/* seeding rand() */
	srand(time(NULL));

	/* selecting a random partition index between start and end */
	partition_index = (rand() % (end - start + 1)) + start;

	/* making the element at partition index the pivot (because partition function chooses the element at the end as a pivot) */
	swap(&array[partition_index], &array[end]);

	/* calling partition function so we can return a pivot index */
	return lib_qsort_partition(array, start, end);
}

/*
	library function to help quick sort
		- partitions the given array
		- calls itself recursively on the left and right of the pivot acquired by partitioning
*/

void lib_qsort(int *array, int start, int end)
{
	int partition_index;

	/* base case to end recursion */
	if(start < end)
	{
		partition_index = lib_qsort_randomized_partition (array, start, end);
		lib_qsort(array, start, partition_index - 1);
		lib_qsort(array, partition_index + 1, end);
	}
}

/* function to implement quick sort on a given array of integers */

void sort_quick (int *array, int size)
{
	int start, end;

	start = 0;
	end = size - 1;

	if(start < end)
		lib_qsort(array, start, end);
}
