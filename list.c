#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void init_list(list_t *ptr_list)
{
	ptr_list->head = NULL;
	ptr_list->tail = NULL;
}

void add_at_end(list_t *ptr_list, const state_t *ptr_state)
{
	node_t* temp = (node_t*)malloc(sizeof(node_t));
	temp->st = *ptr_state;
	// empty list
	if(ptr_list->head == NULL)
	{
		temp->next = NULL;
		temp->prev = ptr_list->tail;
		ptr_list->head = temp;
		ptr_list->tail = temp;
	}
	// non-empty list
	else
	{
		temp->next = NULL;
		temp->prev = ptr_list->tail;
		ptr_list->tail->next = temp;
		ptr_list->tail = temp;
	}
}

void remove_at_end(list_t *ptr_list)
{
	// empty list
	if(ptr_list->head == NULL)
	{
		printf("empty list\n");
	}
	// one node list
	else if(ptr_list->head == ptr_list->tail)
	{
		node_t* temp = ptr_list->tail;
		ptr_list->tail = temp->prev;
		ptr_list->head = NULL;
		free(temp);
	}
	// multi node list
	else
	{
		node_t* temp = ptr_list->tail;
		ptr_list->tail = temp->prev;
		ptr_list->tail->next = NULL;
		free(temp);
	}
}

void disp_list(const list_t *ptr_list)
{
	node_t* temp = ptr_list->head;
	while(temp)
	{	
		disp_state(&temp->st);
		temp = temp->next;
	}
}
int is_repeated(const list_t *ptr_list, const state_t *ptr_state)
{
	node_t* temp = ptr_list->head;
	while(temp)
	{	
		if (are_same(&temp->st, ptr_state))
			return 1;
		temp = temp->next;
	}
	return 0;
}



