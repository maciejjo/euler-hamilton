#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void euler_path(list **cykl, list *stos, list **adjacency_list_array, int current_vertex) {

	add_to_list(&stos, current_vertex);
	int found = 0;
	list *first_vertex = adjacency_list_array[current_vertex];

	while(!found) {
		if(first_vertex != NULL) {
			if(!(first_vertex->visited)) {
				found = 1;
				break;
			}
			else
				first_vertex = first_vertex->next;
		}
		else
			break;
	}

	if(found) {
		first_vertex->visited = 1;
		list *second_vertex = adjacency_list_array[first_vertex->data];
		while(second_vertex->data != current_vertex) {
				second_vertex = second_vertex->next;
		}
		second_vertex->visited = 1;
		euler_path(cykl, stos, adjacency_list_array, first_vertex->data);
	}
	else {
		int next = 0;
		while(!next) {
			if(!(*cykl)) {
				add_to_list(cykl, get_last_element(stos));
			}
			else if(get_last_element(*cykl) != get_last_element(stos)) {
				add_to_list(cykl, get_last_element(stos));
			}
			pop_from_stack(&stos);
			
			int found_adj = 0;
			if(stos) {
				list *pointer = adjacency_list_array[get_last_element(stos)];
				while(!found_adj) {
					if(pointer) {

						if(!(pointer->visited)) {
							found_adj = 1;
							break;
						}
						else
							pointer = pointer->next;
					}
					else
						break;
				}
					if(found_adj)
						next = 1;
			}
			else
				break;
		}
		if(next)
			euler_path(cykl, stos, adjacency_list_array, get_last_element(stos));
	}
		
}

int hamilton_path(int *cycle_count, int *cycle_array, int *visited_count, int *visited_array, list **adjacency_list_array, int vertex_count, int current_vertex, int first_vertex) {
	
	visited_array[current_vertex] = 1;
	(*visited_count)++;

	list *pointer = adjacency_list_array[current_vertex];
	while(pointer) {
		if(pointer->data == first_vertex) {
			if(*visited_count == vertex_count) {
				cycle_array[0] = current_vertex;
				return 1;
			}
		}
		if(!visited_array[pointer->data]) {
			if(hamilton_path(cycle_count, cycle_array, visited_count, visited_array, adjacency_list_array, vertex_count, pointer->data, first_vertex)) {
				cycle_array[(*cycle_count)++] = current_vertex;
				return 1;
			}
		}
		pointer = pointer->next;
	}

	visited_array[current_vertex] = 0;
	(*visited_count)--;
	return 0;


}
	

void dfs_traversal_matrix(int **adjacency_matrix, int matrix_size, int *vertex_count, int *vertex_array, int *dfs_count, int *dfs_array, int vertex) {
	
	//Dodawanie do listy odwiedzonych i zwiększenie licznika odwiedzonych
	vertex_array[*vertex_count] = vertex;
	(*vertex_count)++;
	
	//Szukanie dzieci danego wierzchołka
	for(int i = 0; i < matrix_size; i++) {
		//Jeśli dane dziecko istnieje
		if(adjacency_matrix[vertex][i]) {
			//Wyszukaj je na liście odwiedzonych
			int found = 0;
			for(int j = 0; j < *vertex_count; j++) {
				//Jeśli znaleziono przerwij pętlę
				if(i == vertex_array[j]) {
					found = 1;
					break;
				}
			}
			//Jeśli nie znaleziono na liście odwiedzonych odwiedź wierzchołek
			if(!found) {
				dfs_traversal_matrix(adjacency_matrix, matrix_size, vertex_count, vertex_array, dfs_count, dfs_array, i);
			}
		}
	}

	//Dodawanie do tablicy DFS
	dfs_array[*dfs_count] = vertex;
	(*dfs_count)++;
}


void dfs_traversal_list(list **adjacency_list_array, int matrix_size, int *vertex_count, int *vertex_array, int *dfs_count, int *dfs_array, int vertex) {
	
	//Dodawanie do listy odwiedzonych i zwiększenie licznika odwiedzonych
	vertex_array[*vertex_count] = vertex;
	(*vertex_count)++;
	
	list *pointer = adjacency_list_array[vertex];
	while(pointer != NULL) {
		int found = 0;
		for(int j = 0; j < *vertex_count; j++) {
			//Jeśli znaleziono przerwij pętlę
			if(pointer->data == vertex_array[j]) {
				found = 1;
				break;
			}
		}
		if(!found) {
			dfs_traversal_list(adjacency_list_array, matrix_size, vertex_count, vertex_array, dfs_count, dfs_array, pointer->data);
		}
		pointer = pointer->next;
	}
	dfs_array[*dfs_count] = vertex;
	(*dfs_count)++;
}

void dfs_traversal_edge_list(int **edge_list, int edge_count, int *vertex_count, int *vertex_array, int *dfs_count, int *dfs_array, int vertex) {

	vertex_array[*vertex_count] = vertex;
	(*vertex_count)++;

	for(int i = 0; i < edge_count; i++) {
		if(edge_list[i][0] == vertex) {
			int found = 0;
			for(int j = 0; j < *vertex_count; j++) {
				if(edge_list[i][1] == vertex_array[j]) {
					found = 1;
					break;
				}
			}
			if(!found) {
				dfs_traversal_edge_list(edge_list, edge_count, vertex_count, vertex_array, dfs_count, dfs_array, edge_list[i][1]);
			}
		}
	}
		
	dfs_array[*dfs_count] = vertex;
	(*dfs_count)++;
}

void mirror_adjacency_matrix(int **input_matrix, int matrix_size, int **output_matrix) {
	for(int i = 0; i<matrix_size; i++) {
		for(int j = 0; j<matrix_size; j++) {
			if(input_matrix[i][j])
			{
				output_matrix[i][j] = 1;
				output_matrix[j][i] = 1;
			}
		}
	}
}


void fill_adjacency_matrix_dfg(int **adjacency_matrix, int matrix_size, float density) {

	// Wyzerowanie macierzy
	for(int i = 0; i<matrix_size; i++) {
		for(int j = 0; j<matrix_size; j++) {
			adjacency_matrix[i][j] = 0;
		}
	}
	
	//Obliczenie ilości łuków w zależności od zagęszczenia
	int number_of_arcs = (int) ((matrix_size*(matrix_size-1)) / 2) * density;

	while(number_of_arcs) {
		//Losowanie współrzędnych w macierzy
		int x = rand() % matrix_size;
		int y = rand() % matrix_size;
		//Jeśli są różne (nie są na przekątnej)
		if(x != y)
		{	
			if(x>y) {
				if(adjacency_matrix[y][x] == 0) {
					adjacency_matrix[y][x] = 1;
					number_of_arcs--;
				}
			}
			else {
				if(adjacency_matrix[x][y] == 0) {
					adjacency_matrix[x][y] = 1;
					number_of_arcs--;
				}
			}
		}
	}
}

void adjacency_list_from_matrix(int **adjacency_matrix, int matrix_size, list **adjacency_list_array) {

	for(int i = 0; i < matrix_size; i++) {
		for(int j = 0; j< matrix_size; j++) {
			if(adjacency_matrix[i][j]) {
				add_to_list(&(adjacency_list_array[i]), j);
			}
		}
		printf("%d:\n",i);
		print_list(adjacency_list_array[i]);
	}
}

void previous_list(list **adjacency_list_array, int matrix_size, list **previous_list) {

	for(int i = 0; i < matrix_size; i++) {
		list *pointer = adjacency_list_array[i];
		while(pointer != NULL) {
			for(int j = 0; j <matrix_size; j++) {

			if(pointer->data == j) {
				add_to_list(&(previous_list[pointer->data]), i);
			}
			}
			pointer = pointer->next;
		}
	}
}
			
		

void edge_list_from_adjacency_list(list **adjacency_list_array, int matrix_size, int **edge_list) {
	int j = 0;
	for(int i = 0; i < matrix_size; i++) {
		list *pointer = adjacency_list_array[i];
		while(pointer != NULL) {
			edge_list[j][0] = i;
			edge_list[j][1] = pointer->data;
			printf("%d -> %d\n", edge_list[j][0], edge_list[j][1]);
			j++;
			pointer = pointer->next;
		}
	}
}

void print_matrix(int **adjacency_matrix, int matrix_size) {
	for(int i = 0; i < matrix_size; i++) {
		for(int j = 0; j < matrix_size; j++) {
			printf("%d ", adjacency_matrix[i][j]);
		}
		printf("\n");
	}
}
