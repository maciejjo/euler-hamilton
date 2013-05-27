#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "arrays.h"

void euler_path(list **cykl, list *stos, list **adjacency_list_array, int current_vertex) {
	
	//Dodajemy obecny wierzchołek na stos
	add_to_list(&stos, current_vertex);

	//Poszukujemy dziecka obecnego wierzchołka tylko na nieodwiedzonych krawędziach
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

	//Jeśli takie dziecko jest znalezione trzeba oznaczyć krawędź jako odwiedzoną
	//w obu listach sąsiedztwa (wierzchołka i dziecka)
	if(found) {
		//Oznaczanie odwiedzenia w pierwszej liście
		first_vertex->visited = 1;

		list *second_vertex = adjacency_list_array[first_vertex->data];
		while(second_vertex->data != current_vertex) {
				second_vertex = second_vertex->next;
		}
		//Oznaczanie odwiedzenia w drugiej liście
		second_vertex->visited = 1;

		//Następnie przechodzimy rekurencyjnie do tego dziecka
		euler_path(cykl, stos, adjacency_list_array, first_vertex->data);
	}

	//Jeśli takie dziecko nie zostało znalezione (wierzchołek nie ma już żadnych krawędzi
	//gdzie moglibyśmy pójść) musimy zdejmować elementy ze stosu i przekładać je na
	//wynikową listę tak długo aż nie znajdziemy takiego wierzchołka który ma jeszcze krawędzie
	else {
		int next = 0;
		while(!next) {
			//Jeśli lista wynikowa jest pusta to po prostu wkładamy na nią wierzchołek ze stosu
			if(!(*cykl)) {
				add_to_list(cykl, get_last_element(stos));
			}
			//Jeśli nie jest pusta musimy sprawdzić czy ostatnio położony wierzchołek nie jest
			//tym samym wierzchołkiem który wkładamy obecnie
			else if(get_last_element(*cykl) != get_last_element(stos)) {
				add_to_list(cykl, get_last_element(stos));
			}
			pop_from_stack(&stos);
			
			//Po przełożeniu wierzchołka ze stosu na listę sprawdzamy czy następny wierzchołek na stosie
			//ma jeszcze nieodwiedzone krawędzie
			int found_adj = 0;
			if(stos) {
				//Przejeżdżamy wskaźnikiem po liście sąsiedztwa w poszukiwaniu nieodwiedzonych krawędzi
				list *pointer = adjacency_list_array[get_last_element(stos)];
				while(!found_adj) {
					if(pointer) {
						
						//Jeśli znajdziemy przerywamy pętlę
						if(!(pointer->visited)) {
							found_adj = 1;
							break;
						}
						else
							pointer = pointer->next;
					}
					//Jeśli przejdziemy całą listę sąsiedztwa i nie znajdziemy to przerywamy i następny
					//element stosu zostaje sprawdzony
					else
						break;
				}
					//Jeśli znajdziemy na stosie wierzchołek który ma następnika to przerywamy pętlę 
					//odkładania elementów ze stosu bo musimy go odwiedzić
					if(found_adj)
						next = 1;
			}
			//Jeśli stos jest pusty przerywamy pętlę odkładania elementów ze stosu
			else
				break;
		}
		//Jeśli przerwaliśmy pętlę stosu bo znaleźliśmy element który ma jeszcze krawędzie musimy na nim 
		//rekurencyjnie wykonać algorytm aby go odwiedzić
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
				cycle_array[++(*cycle_count)] = current_vertex;
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

void fill_adjacency_matrix_loop(int **adjacency_matrix, int number_of_vertices) {
	
	int *graph_loop = return_array(number_of_vertices);
	fill_array_with_unique_random(graph_loop, number_of_vertices);

	for(int i = 0; i<number_of_vertices; i++) {
		if(i == 0) {
			adjacency_matrix[graph_loop[i]][graph_loop[i+1]] = 1;
			adjacency_matrix[graph_loop[i]][graph_loop[number_of_vertices-1]] = 1;
		}
		else if(i < (number_of_vertices - 1)) {
			adjacency_matrix[graph_loop[i]][graph_loop[i+1]] = 1;
			adjacency_matrix[graph_loop[i]][graph_loop[i-1]] = 1;
		} 
		else {
			adjacency_matrix[graph_loop[i]][graph_loop[i-1]] = 1;
			adjacency_matrix[graph_loop[i]][graph_loop[0]] = 1;
		}
	}
}
		
void fill_adjacency_matrix_cycles(int **adjacency_matrix, int number_of_vertices, float density) {
	int number_of_edges = (int) (((number_of_vertices*(number_of_vertices-1)) / 2) * density) - (number_of_vertices - 1);

	while(number_of_edges >= 3) {
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
	}
}


void adjacency_list_from_matrix(int **adjacency_matrix, int matrix_size, list **adjacency_list_array) {

	for(int i = 0; i < matrix_size; i++) {
		for(int j = 0; j< matrix_size; j++) {
			if(adjacency_matrix[i][j]) {
				add_to_list(&(adjacency_list_array[i]), j);
			}
		}
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
