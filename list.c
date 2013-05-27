#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void add_to_list(list **node, int value) {
	if(*node == NULL) {
		*node = (list *) malloc(sizeof(list));
		(*node)->data = value;
		(*node)->visited = 0;
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

void pop_from_stack(list **stack) {
	if((*stack)->next) {
		list *previous = *stack;
		list *current  = (*stack)->next;
		while(current->next != NULL) {
	//		printf("Przesuwany\n");
			current = current->next;
			previous = previous->next;
		//	printf("%d -> ", current->data);
		}
	//	printf("%d\n", current->data);
		//printf("\n");
		free(current);
		previous->next = NULL;
	}
	else {
		free(*stack);
		*stack = NULL;
	}
}

int get_last_element(list *stack) {
	while(stack->next) {
		stack = stack->next;
	}
	return(stack->data);
}


void print_list(list *node) {
	int i = 1;
	while(node != NULL) {
		printf("-> %d\t", node->data);
		node = node->next;
		if(!(i % 10))
			printf("\n");
		i++;
	}
	printf("->\n");
}
