/**
 *  doublyLinkedList
 *
 * 	@file   dll.c
 * 	@author Marc Zimmermann (tooreht@gmail.com)
 * 	@date   December, 2012
 * 	@brief  Implementation of a doubly linked list.
 *
 * 	Function implementations of the doubly linked list.
 *
 *  Copyright (C) 2012  Marc Zimmermann (tooreht@gmail.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
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

	if(new)
	{
		new->head = new->tail = new->curr = NULL;
		new->size = 0;
	}
	else
	{
		puts("ERROR: Out of memory");
	}

	return new;
}

/**
 * Returns the head.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return Node*: tail node
 */
Node* dll_head(DLL *list)
{
	assert(list);

	return list->curr = list->head;
}

/**
 * Returns the tail.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return Node*: tail node
 */
Node* dll_tail(DLL *list)
{
	assert(list);

	return list->curr = list->tail;
}

/**
 * Returns the current node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return Node*: current node
 */
Node* dll_curr(DLL *list)
{
	assert(list);

	return list->curr;
}

/**
 * Returns the size of the doubly linked list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return unsigned int: size
 */
unsigned int dll_size(DLL *list)
{
	assert(list);

	return list->size;
}

/**
 * Checks if the doubly linked list has a next node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return int: has next
 */
int dll_has_next(DLL *list)
{
	assert(list);

	return list->curr != NULL;
}

/**
 * Returns the next node.
 * Use dll_head to initialize list->curr as head
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return Node*: next node
 */
Node* dll_next(DLL *list)
{
	assert(list);

	if(list->curr && list->curr->next)
		return list->curr = list->curr->next;
	else
		return list->curr = NULL;
}

/**
 * Checks if the doubly linked list has a previous node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return int: has previous
 */
int dll_has_prev(DLL *list)
{
	assert(list);

	return list->curr != NULL;
}

/**
 * Returns the previous node.
 * Use dll_tail to initialize list->curr as tail
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return Node*: previous node
 */
Node* dll_prev(DLL *list)
{
	assert(list);

	if(list->curr && list->curr->prev)
		return list->curr = list->curr->prev;
	else
		return list->curr = NULL;
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

	Node *n = list->head;

	while(n)
	{
		callback(n->data); // or (*callback)(i);
		n = n->next;
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

	if(node && list->head && list->tail)
	{
		Node *i = list->head, *j = list->tail;

		while(i != j && i != j->next)
		{
			if(i == node || j == node)
				return 1;
			i = i->next;
			j = j->prev;
		}

		if(i == node)
			return 1;
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
 * @return Node*: pointer to the found node 
 */
Node* dll_search(DLL *list, void *data, int (*compare)(void*, void*) )
{
	assert(list);
	assert(data);
	assert(compare);

	if(list->head && list->tail)
	{
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

		if(!compare(i->data, data))
			return i;
	}

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

	if (new)
	{
		new->data = data;
		new->prev = new->next = NULL;
	}
	else
	{
		puts("ERROR: Out of memory");
	}

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
 * @return Node*: pointer to the added node
 */
Node* dll_add_begin(DLL *list, void *data)
{
	assert(list);
	assert(data);

	if(list->head)
	{
		Node *new = dll_create_node(data);

		if(new)
		{
			Node *tmp = list->head;
			new->next = tmp;
			list->head = tmp->prev = new;
			list->size++;
		}

		return new;
	}
	else
	{
		return dll_add_first_node(list, data);
	}
}

/**
 * Adds a new node to the end of the doubly linked list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the added node
 */
Node* dll_add_end(DLL *list, void *data)
{
	assert(list);
	assert(data);

	if(list->tail)
	{
		Node *new = dll_create_node(data);

		if(new)
		{
			Node *tmp = list->tail;
			new->prev = tmp;
			list->tail = tmp->next = new;
			list->size++;
		}

		return new;
	}
	else
	{
		return dll_add_first_node(list, data);
	}	
}

/**
 * Adds a new node before a specific node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param Node *node: node to add before
 * @param void *data: data pointer
 * @return Node*: pointer to the added node
 */
Node* dll_add_before(DLL *list, Node *node, void *data)
{
	assert(list);
	assert(node);
	assert(data);

	if(list->head && list->tail)
	{
		Node *new = dll_create_node(data);

		if(new)
		{
			new->next = node;
			new->prev = node->prev;
			if(node == list->head)
				list->head = new;
			node->prev = new;
			if(new->prev)
				new->prev->next = new;
			list->size++;
		}

		return new;
	}

	return NULL;
}

/**
 * Adds a new node after a specific node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param Node *node: node to add after
 * @param void *data: data pointer
 * @return Node*: pointer to the added node
 */
Node* dll_add_after(DLL *list, Node *node, void *data)
{
	assert(list);
	assert(node);
	assert(data);

	if(list->head && list->tail)
	{
		Node *new = dll_create_node(data);

		if(new)
		{
			new->prev = node;
			new->next = node->next;
			if(node == list->tail)
				list->tail = new;
			node->next = new;
			if(new->next)
				new->next->prev = new;
			list->size++;
		}

		return new;
	}

	return NULL;
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
	node->prev = node->next = node->data = NULL;
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

	if(list->head && list->tail)
	{
		if(list->head == list->tail)
		{
			list->head = list->tail = NULL;
		}
		else
		{
			list->head = del->next;
			list->head->prev = NULL;
		}

		dll_free_node(del, free_data);
		list->size--;
	}
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

	if(list->head && list->tail)
	{
		if(list->head == list->tail)
		{
			list->head = list->tail = NULL;
		}
		else
		{
			list->tail = del->prev;
			list->tail->next = NULL;
		}

		dll_free_node(del, free_data);
		list->size--;
	}
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
		Node *n = list->head;

		while(n)
		{
			Node *del = n;
			n = n->next;
			dll_free_node(del, free_data);
		}
		list->head = list->tail = list->curr = NULL;
		list->size = 0;
		free(list);
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
 * The order of the nodes is defined through the compare function.
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
