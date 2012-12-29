/**
 * @file   dll.c
 * @author Marc Zimmermann (tooreht@gmail.com)
 * @date   December, 2012
 * @brief  Implementation of a doubly linked list.
 *
 * Function implementations of the doubly linked list.
 */

#include <stdio.h>
#include <stdlib.h>

/* uncomment to ignore the assertions (no debug) */
// #define NDEBUG
#include <assert.h>

#include "dll.h"

/**
 * Creates a new doubly linked list.
 *
 * @param void
 * @return DLL*: pointer of new doubly linked list
 */
DLL* dll_create(void)
{
	DLL *new = malloc(sizeof(DLL));
	new->head = NULL;
	new->tail = NULL;
	new->size = 0;
	return new;
}

/**
 * Traverses the doubly linked list, while providing
 * the data pointer of each node to a callback function.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void (*callback)(void*): callback function
 * @return void
 */
void dll_traverse(DLL *list, void (*callback)(void*) )
{
	assert(list);
	assert(callback);

	Node *i = list->head;

	while(i)
	{
		callback(i->data); // or (*callback)(i);
		i = i->next;
	}
}

/**
 * Checks if a node exists in the doubly linked list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param Node *node: node to test against
 * @return int: success
 */
int dll_contains(DLL *list, Node *node)
{
	assert(list);

	if(!node)
		return 0;

	Node *i = list->head, *j = list->tail;

	while(i != j && i != j->next)
	{
		if(i == node || j == node)
			return 1;
		i = i->next;
		j = j->prev;
	}

	return 0;
}

/**
 * Searches for a node with the specific data.
 *
 * Uses a callback function to compare the data strucures.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @param int (*compare)(void*, void*): callback function compare
 * @return Node*: pointer to found node 
 */
Node* dll_search(DLL *list, void *data, int (*compare)(void*, void*) )
{
	assert(list);
	assert(data);
	assert(compare);

	Node *i = list->head, *j = list->tail;

	while(i != j && i != j->next)
	{
		if(!compare(i->data, data))
			return i;
		if(!compare(j->data, data))
			return j;

		i = i->next;
		j = j->prev;
	}

	if(!compare(j->data, data))
		return j;

	return NULL;
}

/**
 * Creates a new node.
 *
 * @param void *data: data pointer
 * @return Node*: pointer to the new node
 */
Node* dll_create_node(void *data)
{
	assert(data);

	Node *new = malloc(sizeof(Node));
	new->data = data;
	new->prev = new->next = NULL;
	return new;
}

/**
 * Creates the first node of the doubly linked list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the first node
 */
Node* dll_add_first_node(DLL *list, void *data)
{
	assert(list);
	assert(data);

	list->size = 1;
	return list->head = list->tail = dll_create_node(data);
}

/**
 * Adds a new node to the beginning of the doubly linked list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the first node
 */
Node* dll_add_begin(DLL *list, void *data)
{
	assert(list);
	assert(data);

	Node *new = dll_create_node(data);

	if(list->head)
	{
		Node *tmp = list->head;
		new->next = tmp;
		list->head = tmp->prev = new;
		list->size++;
	}
	else
	{
		return dll_add_first_node(list, data);
	}

	return new;
}

/**
 * Adds a new node to the end of the doubly linked list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the last node
 */
Node* dll_add_end(DLL *list, void *data)
{
	assert(list);
	assert(data);

	Node *new = dll_create_node(data);

	if(list->tail)
	{
		Node *tmp = list->tail;
		new->prev = tmp;
		list->tail = tmp->next = new;
		list->size++;
	}
	else
	{
		return dll_add_first_node(list, data);
	}
	
	return new;	
}

/**
 * Adds a new node after a specific node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param Node *node: node to add after
 * @param void *data: data pointer
 * @return Node*: pointer to the first node
 */
Node* dll_add_after(DLL *list, Node *node, void *data)
{
	assert(list);
	assert(node);
	assert(data);

	if(list->head && list->tail)
	{
		Node *new = dll_create_node(data);
		new->prev = node;
		new->next = node->next;
		if(node == list->tail)
			list->tail = new;
		node->next = new;
		if(new->next)
			new->next->prev = new;
		list->size++;
		return new;
	}
	else
	{
		return dll_add_first_node(list, data);
	}
}

/**
 * Frees data and the node from memory.
 *
 * The data is freed by the callback function free_data.
 *
 * @param Node *node: node to free
 * @param void (*free_data)(void*): callback function free_data
 * @return void
 */
void dll_free_node(Node *node, void (*free_data)(void*) )
{
	assert(node);
	assert(free_data);

	free_data(node->data);
	free(node);
}

/**
 * Deletes the first node with the specific data from the list.
 *
 * Uses a callback function to compare the data strucures.
 * The data is freed by the callback function free_data.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @param int (*compare)(void*, void*): callback function compare
 * @param void (*free_data)(void*): callback function free_data
 * @return void
 */
void dll_delete(DLL *list, void *data, int (*compare)(void*, void*), void (*free_data)(void*) )
{
	assert(list);
	assert(data);
	assert(compare);
	assert(free_data);

	Node *found = dll_search(list, data, compare);

	if(found)
	{
		if(found == list->head && found == list->tail)
			list->head = list->tail = NULL;
		else if(found == list->head)
		{
			list->head = found->next;
			list->head->prev = NULL;
		}
		else if(found == list->tail)
		{
			list->tail = found->prev;
			list->tail->next = NULL;
		}
		else
		{
			found->prev->next = found->next;
			found->next->prev = found->prev;
		}

		dll_free_node(found, free_data);
		list->size--;
	}
}

/**
 * Deletes the first node of the doubly linked list.
 *
 * The data is freed by the callback function free_data.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void (*free_data)(void*): callback function free_data
 * @return void
 */
void dll_delete_first(DLL *list, void (*free_data)(void*) )
{
	assert(list);
	assert(free_data);

	Node *del = list->head;
	list->head = del->next->prev = del->next;

	dll_free_node(del, free_data);
	list->size--;
}

/**
 * Deletes the last node of the doubly linked list.
 *
 * The data is freed by the callback function free_data.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void (*free_data)(void*): callback function free_data
 * @return void
 */
void dll_delete_last(DLL *list, void (*free_data)(void*) )
{
	assert(list);
	assert(free_data);

	Node *del = list->tail;
	list->tail = del->prev->next = del->prev;

	dll_free_node(del, free_data);
	list->size--;
}

/**
 * Destroys the whole list and frees it from memory.
 *
 * The data is freed by the callback function free_data.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void (*free_data)(void*): callback function free_data
 * @return void
 */
void dll_destroy(DLL *list, void (*free_data)(void*) )
{
	assert(free_data);

	if(list)
	{
		list->curr = list->head;

		while(list->curr)
		{
			dll_free_node(list->curr, free_data);
			list->curr = list->curr->next;
		}
		free(list);
		list->head = list->tail = NULL;
		list->size = 0;
	}
}

/**
 * Reverses the list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
void dll_reverse(DLL *list)
{
	assert(list);

	Node *i = list->head, *j = list->tail;

	while(i != j && i != j->next)
	{
		void *data = i->data;
		i->data = j->data;
		j->data = data;

		i = i->next;
		j = j->prev;
	}
}

/**
 * Sorts the list.
 *
 * Uses a callback function to compare the data strucures.
 * The order of the nodes is defined trough the compare function.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param int (*compare)(void*, void*): callback function compare
 * @return void
 */
void dll_sort(DLL *list, int (*compare)(void*, void*) )
{
	assert(list);
	assert(compare);

	Node *i = list->head, *j, *tmp;
	while(i)
	{
		tmp = j = i;

		while(j)
		{
			if(compare(tmp->data, j->data) == 1)
				tmp = j;
			j = j->next;
		}
		void *data = tmp->data;
		tmp->data = i->data;
		i->data = data;

		i = i->next;
	}
}

/**
 * Prints the list.
 *
 * A callback function is used to print the data strucure.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void (*print_data)(void*): callback function print_data
 * @return void
 */
void dll_print(DLL *list, void (*print_data)(void*) )
{
	assert(list);
	assert(print_data);

	printf("--- start ---\n");

	dll_traverse(list, print_data);

	printf("---- end ----\n");
}
