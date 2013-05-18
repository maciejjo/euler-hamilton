#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "graph.h"
#include "list.h"

int main() {
	
	int number_of_vertices = 1000;
	int display = 0;
	int write_to_file = 1;
	char *filename = "pomiary.csv";
	time_t start, stop;
	
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

	for(int i = 0; i < 10; i++) {	
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
		
		int dfs_count;
		int *dfs_array = (int *) malloc(sizeof(int) * number_of_vertices);
		
		int vertex_count;
		int *vertex_array = (int *) malloc(sizeof(int) * number_of_vertices);
		

		int connected = 0;
		while(!connected) {

			for (int i = 0; i<number_of_vertices;i++) {
				for( int j = 0; j<number_of_vertices;j++) {
					adjacency_matrix[i][j] = 0;
					adjacency_matrix_mirror[i][j] = 0;
				}
			}
			
			start = clock();
			fill_adjacency_matrix_dfg(adjacency_matrix, number_of_vertices, 0.5);
			mirror_adjacency_matrix(adjacency_matrix, number_of_vertices, adjacency_matrix_mirror);
			stop = clock();
			
			printf("Pomiar czasu: %.2f\n\n", (float) (stop - start)/CLOCKS_PER_SEC);
			
			printf("Sprawdzanie spójności...\n");
			
			vertex_count = dfs_count = 0;
			for(int i = 0; i<number_of_vertices; i++) {
				dfs_array[i] = 0;
				vertex_array[i] = 0;
			}
			
			start = clock();
			dfs_traversal_matrix(adjacency_matrix_mirror, number_of_vertices, &vertex_count, vertex_array, &dfs_count, dfs_array, 0);
			stop = clock();
		printf("Pomiar czasu: %.2f\n\n", (float) (stop - start)/CLOCKS_PER_SEC);

			if(vertex_count == number_of_vertices) {
				printf("Graf jest spójny\n");
				connected = 1;
			}
			else {
				printf("Graf niespójny, ponawiam generację\n");
			}
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


		if(display) {
			printf("\nLista krawędzi:\n");
		}
		//Tworzenie listy krawędzi
		int number_of_arcs = (int) ((number_of_vertices*(number_of_vertices-1)) / 2) * 0.5;
		int **edge_list = (int **) malloc(number_of_arcs * sizeof(int *));
		for (int i = 0; i<number_of_arcs;i++) {
			edge_list[i] = (int *) malloc(2 * sizeof(int));
		}
		edge_list_from_adjacency_list(adjacency_list_array, number_of_vertices, edge_list);

		printf("\n");
		

		//DFS dla macierzy
		printf("Sortowanie topologiczne macierzy...\n");
		
		vertex_count = dfs_count = 0;
		for(int i = 0; i<number_of_vertices; i++) {
			dfs_array[i] = 0;
			vertex_array[i] = 0;
		}

		start = clock();
		for(int i = 0; i < number_of_vertices; i++) {
			int visited = 0;
			for(int j = 0; j < vertex_count; j++) {
				if(vertex_array[j] == i) 
					visited = 1;
			}
			if(!visited) {
				dfs_traversal_matrix(adjacency_matrix, number_of_vertices, &vertex_count, vertex_array, &dfs_count, dfs_array, i);
			}
		}
		stop = clock();
		
		if(display) {
			for(int i = number_of_vertices-1; i>=0; i--) {
				printf("%d ", dfs_array[i]);
			}
		}

		
		float time_measurment = (float) (stop - start)/CLOCKS_PER_SEC;

		if(write_to_file)
			fprintf(output_file, "%s,%d,%.2f\n", "Adjacency matrix", number_of_vertices, time_measurment);
		printf("\n");
		printf("Pomiar czasu: %.2f\n\n", (float) (stop - start)/CLOCKS_PER_SEC);
		
		
		//DFS dla listy następników	
		printf("Sortowanie topologiczne listy następników...\n");
		
		vertex_count = dfs_count = 0;
		for(int i = 0; i<number_of_vertices; i++) {
			dfs_array[i] = 0;
			vertex_array[i] = 0;
		}
		
		start = clock();
		for(int i = 0; i < number_of_vertices; i++) {
			int visited = 0;
			for(int j = 0; j < vertex_count; j++) {
				if(vertex_array[j] == i) 
					visited = 1;
			}
			if(!visited) {
				dfs_traversal_list(adjacency_list_array, number_of_vertices, &vertex_count, vertex_array, &dfs_count, dfs_array, i);
			}
		}
		stop = clock();
		
		if(display) {
			for(int i = number_of_vertices-1; i>=0; i--) {
				printf("%d ", dfs_array[i]);
			}
		}
		
		printf("\n");
		time_measurment = (float) (stop - start)/CLOCKS_PER_SEC;

		if(write_to_file)
			fprintf(output_file, "%s,%d,%.2f\n", "Adjacency list", number_of_vertices, time_measurment);
		printf("\n");
		printf("Pomiar czasu: %.2f\n\n", (float) (stop - start)/CLOCKS_PER_SEC);
		
		printf("Sortowanie topologiczne listy krawędzi...\n");
		
		vertex_count = dfs_count = 0;
		for(int i = 0; i<number_of_vertices; i++) {
			dfs_array[i] = 0;
			vertex_array[i] = 0;
		}
		
		start = clock();
		for(int i = 0; i < number_of_vertices; i++) {
			int visited = 0;
			for(int j = 0; j < vertex_count; j++) {
				if(vertex_array[j] == i) 
					visited = 1;
			}
			if(!visited) {
				dfs_traversal_edge_list(edge_list, number_of_arcs, &vertex_count, vertex_array, &dfs_count, dfs_array, i);
			}
		}
		stop = clock();
		
		if(display) {
			for(int i = number_of_vertices-1; i>=0; i--) {
				printf("%d ", dfs_array[i]);
			}
		}
		printf("\n");
		
		time_measurment = (float) (stop - start)/CLOCKS_PER_SEC;

		if(write_to_file)
			fprintf(output_file, "%s,%d,%.2f\n", "Edge list", number_of_vertices, time_measurment);
		printf("\n");
		printf("Pomiar czasu: %.2f\n\n", (float) (stop - start)/CLOCKS_PER_SEC);
		number_of_vertices += 100;
	}


    	if(file_opened) fclose(output_file);
	return 0;
}

