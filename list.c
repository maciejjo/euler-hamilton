#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void add_to_list(list **node, int value) {
	if(*node == NULL) {
		*node = (list *) malloc(sizeof(list));
		(*node)->data = value;
		(*node)->next = NULL;
	}
	else {
		add_to_list(&((*node)->next), value);
	}
}

void delete_last_node(list **node) {
	if((*node)->next == NULL) {
		free((*node)->next);
		(*node)->next = NULL;
	}
	else {
		delete_last_node(&(*node)->next);
	}
}

void delete_list(list **head) {
	while(head != NULL) {
		delete_last_node(head);
	}
}

void pop_from_list(list **stack) {
	list *tmp = *stack;
	*stack = (*stack)->next;
	free(tmp);
}

void print_list(list *node) {
	int i = 1;
	while(node != NULL) {
		printf("-> %d ", node->data);
		node = node->next;
		if(!(i % 10))
			printf("\n");
		i++;
	}
	printf("->\n");
}
