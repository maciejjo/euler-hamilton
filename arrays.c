#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "arrays.h"

int *return_array(int number_of_elements) {
	int *array = (int *) malloc(number_of_elements * sizeof(int));
	return array;
}

void fill_array_with_unique_random(int *array, int array_size) {
	for(int i = 0; i < array_size; i++) {
		array[i] = i;

	}
    	
	if (array_size > 1) {
        	for (int i = 0; i < array_size - 1; i++) {
          		int j = i + rand() / (RAND_MAX / (array_size - i) + 1);
          		int t = array[j];
          		array[j] = array[i];
          		array[i] = t;
        	}
    	}
}

void print_array(int *array, int array_size) {
	for(int i = 0; i < array_size; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

