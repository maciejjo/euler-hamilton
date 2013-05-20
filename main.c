#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "arrays.h"
#include "graph.h"
#include "list.h"

int main() {
	
	int number_of_vertices = 10;
	float density = 0.3;
	int display = 1;
	int write_to_file = 1;
	char *filename = "pomiary.csv";
	//time_t start, stop;
	
	srand(time(NULL));
	
	printf("Algorytmy grafowe\n\n");
	

	FILE *output_file = NULL;
	int file_opened = 0;
	if(write_to_file) {
		if(strcmp(filename, "") != 0) {
			output_file = fopen(filename, "w");
			file_opened = 1;
		}
	}

	for(int i = 0; i < 2; i++) {	
		//Tworzenie spójnej macierzy
		printf("Generowanie macierzy n=%d wierzchołków...\n", number_of_vertices);
		int **adjacency_matrix = (int **) malloc(number_of_vertices * sizeof(int *));
		for (int i = 0; i<number_of_vertices;i++) {
			adjacency_matrix[i] = (int *) malloc(number_of_vertices * sizeof(int));
		}

		int **adjacency_matrix_mirror = (int **) malloc(number_of_vertices * sizeof(int *));
		for (int i = 0; i<number_of_vertices;i++) {
			adjacency_matrix_mirror[i] = (int *) malloc(number_of_vertices * sizeof(int));
		}
		

		int *hamilton = return_array(number_of_vertices);
		fill_array_with_unique_random(hamilton, number_of_vertices);
		print_array(hamilton, number_of_vertices);

		for(int i = 0; i<number_of_vertices; i++) {
			if(i == 0) {
				adjacency_matrix[hamilton[i]][hamilton[i+1]] = 1;
				adjacency_matrix[hamilton[i]][hamilton[number_of_vertices-1]] = 1;
			}
			else if(i < (number_of_vertices - 1)) {
				adjacency_matrix[hamilton[i]][hamilton[i+1]] = 1;
				adjacency_matrix[hamilton[i]][hamilton[i-1]] = 1;
			} 
			else {
				adjacency_matrix[hamilton[i]][hamilton[i-1]] = 1;
				adjacency_matrix[hamilton[i]][hamilton[0]] = 1;
			}
		}
		
		int number_of_edges = (int) (((number_of_vertices*(number_of_vertices-1)) / 2) * density) - (number_of_vertices - 1);

		for(int i = 0; i < number_of_edges; i++) {

		}


		if(display) {
			printf("\n");
			printf("Macierz:\n");
			print_matrix(adjacency_matrix, number_of_vertices);
		}

		//Tworzenie listy następników
		if(display) {
			printf("\nLista następników:\n");
		}
		list **adjacency_list_array = (list **) malloc(number_of_vertices* sizeof(list*));
		adjacency_list_from_matrix(adjacency_matrix, number_of_vertices, adjacency_list_array);

		density = 0.7;
	}
    	
	if(file_opened) fclose(output_file);
	return 0;
}
