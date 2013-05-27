#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "arrays.h"
#include "graph.h"
#include "list.h"
		
int main() {
	
	int number_of_vertices = 10;
	int display = 1;
	//int write_to_file = 1;
	//char *filename = "pomiary.csv";
	//time_t start, stop;
	
	srand(time(NULL));
	
	printf("Algorytmy grafowe\n\n");
	

/*	FILE *output_file = NULL;
	int file_opened = 0;
	if(write_to_file) {
		if(strcmp(filename, "") != 0) {
			output_file = fopen(filename, "w");
			file_opened = 1;
		}
	}
*/

	float density[] = { 0.3, 0.7 };

	for(int i = 0; i < 2; i++) {	
		//Tworzenie spójnej macierzy
		printf("Generowanie macierzy n=%d wierzchołków... Wypełnienie %.0f%%\n", number_of_vertices, 100*density[i]);
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
		
		int number_of_edges = (int) (((number_of_vertices*(number_of_vertices-1)) / 2) * density[i]) - (number_of_vertices - 1);

		int main_counter = 0;	
		while(number_of_edges >= 3) {
			if(main_counter == 100){
				main_counter = 0;
				break;
			}
			int repeat = 0;
		
			int first_vertex = rand() % number_of_vertices;
			int second_vertex;
			int second_valid = 0;
			
			int counter = 0;
			while(!second_valid) {
				
				if(counter >= 10) {
					repeat = 1;
					break;
				}
				
				second_vertex = rand() % number_of_vertices;
				if((first_vertex != second_vertex) && !(adjacency_matrix[first_vertex][second_vertex])) 
					second_valid++;
				
				counter++;
				
			}

			int third_vertex;
			int third_valid = 0;
		
			counter = 0;
			while(!repeat && !third_valid) {
				
				if(counter >= 10) {
					repeat = 1;
					break;
				}

				third_vertex = rand() % number_of_vertices;
				if((third_vertex != first_vertex) && (third_vertex != second_vertex) && !(adjacency_matrix[first_vertex][third_vertex]) && !(adjacency_matrix[second_vertex][third_vertex])) {
					adjacency_matrix[first_vertex][second_vertex] = 1;
					adjacency_matrix[first_vertex][third_vertex] = 1;
					adjacency_matrix[second_vertex][first_vertex] = 1;
					adjacency_matrix[second_vertex][third_vertex] = 1;
					adjacency_matrix[third_vertex][first_vertex] = 1;
					adjacency_matrix[third_vertex][second_vertex] = 1;
					number_of_edges -= 3;
					third_valid++;
				}
				
				counter++;
			}
			main_counter++;
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
		printf("\n");
		list **adjacency_list_array = (list **) malloc(number_of_vertices* sizeof(list*));
		list **adjacency_list_array_2 = (list **) malloc(number_of_vertices* sizeof(list*));
		adjacency_list_from_matrix(adjacency_matrix, number_of_vertices, adjacency_list_array);
		adjacency_list_from_matrix(adjacency_matrix, number_of_vertices, adjacency_list_array_2);

		printf("\n");

		
		list *stos = NULL;
		list *cykl = NULL;

		euler_path(&cykl, stos, adjacency_list_array, 0);


		printf("\nCYKL: \n");
		print_list(cykl);
		printf("\n");

	
		int *visited_array = return_array(number_of_vertices);
		int *cycle_array = return_array(number_of_vertices);
		int visited_count = 0;
		int cycle_count = 0;
		
		hamilton_path(&cycle_count, cycle_array, &visited_count, visited_array, adjacency_list_array, number_of_vertices,0,0);
		print_array(cycle_array, number_of_vertices);




					




	}
    	
	//if(file_opened) fclose(output_file);
	return 0;
}
