#ifndef SORTING_H
#define SORTING_H

/* helper functions */
void swap (int *a, int *b);
void print (int *array, int size);
int *generate_array(int size);
void destroy_array (int **array_reference, int size);
int is_sorted (int *array, int size);

/* core sort functions */
void sort_selection (int *array, int size);
void sort_bubble (int *array, int size);
void sort_insertion (int *array, int size);
void sort_merge (int *array, int size);
void sort_quick (int *array, int size);

#endif
