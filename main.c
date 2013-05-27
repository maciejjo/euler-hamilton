#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "arrays.h"
#include "graph.h"
#include "list.h"
		
int main() {
	
	int number_of_vertices = 6;
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
		printf("\nGenerowanie macierzy n=%d wierzchołków... Wypełnienie %.0f%%\n", number_of_vertices, 100*density[i]);

		//Alokowanie pamięci na macierz sąsiedztwa
		int **adjacency_matrix = (int **) malloc(number_of_vertices * sizeof(int *));
		for (int i = 0; i<number_of_vertices;i++) {
			adjacency_matrix[i] = (int *) malloc(number_of_vertices * sizeof(int));
		}
		
		
		//Wypełnianie macierzy sąsiedztwa główną pętlą i cyklami do zadanej gęstości
		fill_adjacency_matrix_loop(adjacency_matrix, number_of_vertices);
		fill_adjacency_matrix_cycles(adjacency_matrix, number_of_vertices, density[i]);

		if(display) {
			printf("\n");
			printf("Macierz:\n");
			print_matrix(adjacency_matrix, number_of_vertices);
			printf("\n");
		}


		//Tworzenie listy następników
		list **adjacency_list_array = (list **) malloc(number_of_vertices* sizeof(list*));
		adjacency_list_from_matrix(adjacency_matrix, number_of_vertices, adjacency_list_array);

		if(display) {
			printf("\nLista następników:\n");
			for(int j = 0; j < number_of_vertices; j++) {
				printf("%d: ", j);
				print_list(adjacency_list_array[j]);
			}
			printf("\n");
		}
		
		//Stos i cykl potrzebne do cyklu Eulera
		list *stos = NULL;
		list *cykl = NULL;
		euler_path(&cykl, stos, adjacency_list_array, 0);

		printf("\nCYKL EULERA:\n");
		print_list(cykl);
		printf("\n");


		//Zmienne potrzebne do cyklu Hamiltona
		int *visited_array = return_array(number_of_vertices);
		int *cycle_array = return_array(number_of_vertices);
		int visited_count = 0;
		int cycle_count = 0;
	
		printf("CYKL HAMILTONA:\n");	
		hamilton_path(&cycle_count, cycle_array, &visited_count, visited_array, adjacency_list_array, number_of_vertices,0,0);
		print_array(cycle_array, number_of_vertices);

	}
    	
	//if(file_opened) fclose(output_file);
	return 0;
}
