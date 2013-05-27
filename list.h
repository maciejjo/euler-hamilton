#ifndef LIST_H
#define LIST_H

typedef struct list
    {                              
        int data;
	int visited;
        struct list *next;
    } list;

void add_to_list(list **node, int value);
void delete_last_node(list **node);
void delete_list(list **head);
void pop_from_stack(list **stack);
int get_last_element(list *stack);
void print_list(list *node);

#endif
