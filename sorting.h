#ifndef SORTING_H
#define SORTING_H

#define SELECTION 1
#define BUBBLE 2
#define INSERTION 3
#define MERGE 4
#define QUICK 5
#define COUNTING 6

/* helper functions */
void swap (int *a, int *b);
void print (int *array, int size);
int *generate_array(int size, int max);
void destroy_array (int **array_reference, int size);
int is_sorted (int *array, int size);

/* testing function */

void test (int size, int max, int code);

/* core sort functions */
void sort_selection (int *array, int size);
void sort_bubble (int *array, int size);
void sort_insertion (int *array, int size);
void sort_merge (int *array, int size);
void sort_quick (int *array, int size);
void sort_counting (int *array, int size);

#endif
