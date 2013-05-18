#ifndef GRAPH_H
#define GRAPH_H
#include "list.h"

void dfs_traversal_matrix(int **adjacency_matrix, int matrix_size, int *vertex_count, int *vertex_array, int *dfs_count, int *dfs_array, int vertex);
void dfs_traversal_list(list **adjacency_list_array, int matrix_size, int *vertex_count, int *vertex_array, int *dfs_count, int *dfs_array, int vertex);
void dfs_traversal_edge_list(int **edge_list, int edge_count, int *vertex_count, int *vertex_array, int *dfs_count, int *dfs_array, int vertex);
void fill_adjacency_matrix_dfg(int **adjacency_matrix, int matrix_size, float density);
void mirror_adjacency_matrix(int **input_matrix, int matrix_size, int **output_matrix);
void adjacency_list_from_matrix(int **adjacency_matrix, int matrix_size, list **adjacency_list_array);
void edge_list_from_adjacency_list(list **adjacency_list_array, int matrix_size, int**edge_list);
void previous_list(list **adjacency_list_array, int matrix_size, list **previous_list);
void print_matrix(int **adjacency_matrix, int matrix_size);

#endif
