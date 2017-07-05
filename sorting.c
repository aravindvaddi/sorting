#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>
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
	printf("\n");
}

/* function to generate a random array of given size */

int *generate_array (int size, int max)
{
	int *array;
	int i;

	/* randomizing the seed for rand to generate unique values */
	srand(time(NULL));

	/* allocating memory from the heap to the array */
	array= malloc(sizeof(int) * size);

	for(i = 0; i < size; i++)
		array[i] = rand() % max;

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

void check_array_and_print(int *array, int size, int code)
{
	switch(code)
	{
		case SELECTION:
			printf("selection sort:\n");
			break;
		case BUBBLE:
			printf("bubble sort:\n");
			break;
		case INSERTION:
			printf("insertion sort:\n");
			break;
		case MERGE:
			printf("merge sort:\n");
			break;
		case QUICK:
			printf("quick sort:\n");
			break;
		case COUNTING:
			printf("counting sort:\n");
			break;
		default :
			printf("unsorted array:\n");
			break;
	}
	print(array, size);
	printf("The array is %s\n\n", is_sorted(array, size) ? "sorted" : "unsorted");
}


/* function to test working of different sorting algorithms */

void test(int size, int max, int code)
{
	int *array;

	array = generate_array(size, max);
	check_array_and_print(array, size, 0);
	switch(code)
	{
		case SELECTION:
			sort_selection(array, size);
			break;
		case BUBBLE:
			sort_bubble(array,size);
			break;
		case INSERTION:
			sort_insertion(array,size);
			break;
		case MERGE:
			sort_merge(array,size);
			break;
		case QUICK:
			sort_quick(array,size);
			break;
		case COUNTING:
			sort_counting(array,size);
			break;
		default :
			break;
	}

	check_array_and_print(array, size, code);
	destroy_array(&array, size);
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

/* function to implement counting sort */

void sort_counting (int *array, int size)
{
	/* initializing result pointer to hold result array, count pointer to hold count of occurances of elements */
	int *result, *count, i, range;

	/* allocation of memory to store result array, size same as input array */
	result = malloc(sizeof(int) * size);

	/* finding max element of the input array, essentially, the range */
	for(i = range = 0; i < size; i++)
		if(array[i] > range)
			range = array[i];

	/* allocation of memory to store count array, to store count of occurances of input elements */
	count = malloc(sizeof(int) * (range + 1));

	/* initializing count to zero */
	memset(count, 0, sizeof(count));

	/* storing count of occurances of input elements */
	for(i = 0; i < size; i++)
		count[array[i]]++;

	/* storing cumulative sum of counts in the next element */
	for(i = 1; i < range + 1; i++)
		count[i] += count[i - 1];

	/* storing result in result array, getting position using cumulative counts stored in count array, subtracting by 1 to adjust offset (consider count[0] = 0, count[1] = 2, 1 should occupy 0,1 in the result. without offset it occupies 1, 2 causing overflow) */
	for(i = 0; i < size; i++)
	{
		result[count[array[i]] - 1] = array[i];
		/* accounting for removal of an element from needing to be sorted */
		count[array[i]]--;
	}

	/* storing result in the given array */
	for(i = 0; i < size; i++)
		array[i] = result[i];

	free(result);
	free(count);
}
