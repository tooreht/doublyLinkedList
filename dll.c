/**
 *  doublyLinkedList
 *
 * 	@file   dll.c
 * 	@author Marc Zimmermann (tooreht@gmail.com)
 * 	@date   December, 2012
 * 	@brief  Implementation of a doubly linked list.
 *
 * 	Function implementations of doublyLinkedList.
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
 * static function definitions
 */
static Node* dll_createNode(void *data);
static Node* dll_addFirstNode(DLL *list, void *data);

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
 * Registers compareDataData callback function on the list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param int (*compareData)(void*, void*): callback function compareData
 */
void dll_registerCompareData(DLL *list, int (*compareData)(void*, void*) )
{
	assert(list);
	assert(compareData);
	
	list->compareData = compareData;
}

/**
 * Registers freeData callback function on the list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param int (*compareData)(void*, void*): callback function compareData
 */
void dll_registerFreeData(DLL *list, void (*freeData)(void*) )
{
	assert(list);
	assert(freeData);

	list->freeData = freeData;
}

/**
 * Registers printData callback function on the list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param int (*compareData)(void*, void*): callback function compareData
 */
void dll_registerPrintData(DLL *list, void (*printData)(void*) )
{
	assert(list);
	assert(printData);

	list->printData = printData;
}

/**
 * Returns the head and sets the current to the head.
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
 * Returns the tail and sets the current to the tail.
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
 * @return unsigned long: size
 */
unsigned long dll_size(DLL *list)
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
int dll_hasNext(DLL *list)
{
	assert(list);

	return list->curr != NULL;
}

/**
 * Returns the next node.
 * If the iterator reaches the tail, it returns NULL as next node,
 * then it continues from the head. 
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
	else if(list->curr && !list->curr->next)
		return list->curr = NULL;
	else
		return list->curr = list->head;
}

/**
 * Checks if the doubly linked list has a previous node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return int: has previous
 */
int dll_hasPrev(DLL *list)
{
	assert(list);

	return list->curr != NULL;
}

/**
 * Returns the previous node.
 * If the iterator reaches the head, it returns NULL as previous node,
 * then it continues from the tail. 
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
	else if(list->curr && !list->curr->prev)
		return list->curr = NULL;
	else
		return list->curr = list->tail;
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

	if(node && list->size)
	{
		Node *n = list->head;

		while(n)
		{
			if(n == node)
				return 1;
			n = n->next;			
		}
	}

	return 0;
}

/**
 * Searches for data from head to tail.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the found node
 */
Node* searchHeadToTail(DLL *list, void *data)
{
	assert(list);
	assert(data);
	
	Node *n = list->head;
	
	if(list->size)
	{
		while(n)
		{
			if(!list->compareData(n->data, data))
				return n;
			n = n->next;			
		}
	}

	return NULL;
}

/**
 * Searches for data from tail to head.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the found node
 */
Node* searchTailToHead(DLL *list, void *data)
{
	assert(list);
	assert(data);
	
	Node *n = list->tail;
	
	if(list->size)
	{
		while(n)
		{
			if(!list->compareData(n->data, data))
				return n;
			n = n->prev;			
		}
	}

	return NULL;
}

/**
 * Searches for data from both, head and tail alternating.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the found node
 */
Node* searchHeadAndTail(DLL *list, void *data)
{
	assert(list);
	assert(data);

	Node *i = list->head, *j = list->tail;

	if(list->size)
	{
		if(list->size % 2)
		{
			do
			{
				if(!list->compareData(i->data, data))
					return i;
				if(!list->compareData(j->data, data))
					return j;

				i = i->next;
				j = j->prev;
			}
			while(i->prev != j->next);
		}
		else
		{
			while(i != j->next)
			{
				if(!list->compareData(i->data, data))
					return i;
				if(!list->compareData(j->data, data))
					return j;

				i = i->next;
				j = j->prev;
			}
		}
	}

	return NULL;
}

/**
 * Searches for a node with the specific data. Sets the current node to the found node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @param int mode: search mode
 * @return Node*: pointer to the found node
 */
Node* dll_search(DLL *list, void *data, int mode)
{
	assert(list);
	assert(data);

	Node *search = NULL;

	switch(mode)
	{
		case 3:
			search = searchHeadAndTail(list, data);
			break;
		case 2:
			search = searchTailToHead(list, data);
			break;
		case 1:
		default:
			search = searchHeadToTail(list, data);
	}

	return list->curr = search;
}

/**
 * Creates a new node.
 *
 * @param void *data: data pointer
 * @return Node*: pointer to the new node
 */
Node* dll_createNode(void *data)
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
Node* dll_addFirstNode(DLL *list, void *data)
{
	assert(list);
	assert(data);

	list->size = 1;
	return list->head = list->tail = list->curr = dll_createNode(data);
}

/**
 * Pushs a new node to the head of the doubly linked list.
 * Sets the current node to the new node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the pushed node
 */
Node* dll_pushHead(DLL *list, void *data)
{
	assert(list);
	assert(data);

	if(list->head)
	{
		Node *new = dll_createNode(data);

		if(new)
		{
			Node *tmp = list->head;
			new->next = tmp;
			list->head = tmp->prev = new;
			list->size++;
		}

		return list->curr = new;
	}
	else
	{
		return dll_addFirstNode(list, data);
	}
}

/**
 * Pushs a new node to the tail of the doubly linked list.
 * Sets the current node to the new node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the pushed node
 */
Node* dll_pushTail(DLL *list, void *data)
{
	assert(list);
	assert(data);

	if(list->tail)
	{
		Node *new = dll_createNode(data);

		if(new)
		{
			Node *tmp = list->tail;
			new->prev = tmp;
			list->tail = tmp->next = new;
			list->size++;
		}

		return list->curr = new;
	}
	else
	{
		return dll_addFirstNode(list, data);
	}	
}

/**
 * Adds a new node before a specific node.
 * Sets the current node to the new node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param Node *node: node to add before
 * @param void *data: data pointer
 * @return Node*: pointer to the added node
 */
Node* dll_addBefore(DLL *list, Node *node, void *data)
{
	assert(list);
	assert(node);
	assert(data);

	Node *new = NULL;

	if(list->size)
	{
		new = dll_createNode(data);

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
	}

	return list->curr = new;
}

/**
 * Adds a new node after a specific node.
 * Sets the current node to the new node.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param Node *node: node to add after
 * @param void *data: data pointer
 * @return Node*: pointer to the added node
 */
Node* dll_addAfter(DLL *list, Node *node, void *data)
{
	assert(list);
	assert(node);
	assert(data);

	Node *new = NULL;

	if(list->size)
	{
		new = dll_createNode(data);

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
	}

	return list->curr = new;
}

/**
 * Frees data and the node from memory.
 *
 * @param Node *node: node to free
 * @return void
 */
void dll_freeNode(DLL *list, Node *node)
{
	assert(list);
	assert(node);

	list->freeData(node->data);
	node->prev = node->next = node->data = NULL;
	free(node);
}

/**
 * Deletes the first node with the specific data from the list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return void
 */
void dll_delete(DLL *list, void *data)
{
	assert(list);
	assert(data);

	Node *found = dll_search(list, data, 0);

	if(found)
	{
		if(list->head == list->tail)
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

		if(found == list->curr)
			list->curr = NULL;

		dll_freeNode(list, found);
		list->size--;
	}
}

/**
 * Deletes the first node of the doubly linked list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
void dll_popHead(DLL *list)
{
	assert(list);

	Node *del = list->head;

	if(list->size)
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

		if(del == list->curr)
			list->curr = NULL;

		dll_freeNode(list, del);
		list->size--;
	}
}

/**
 * Deletes the last node of the doubly linked list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
void dll_popTail(DLL *list)
{
	assert(list);

	Node *del = list->tail;

	if(list->size)
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

		if(del == list->curr)
			list->curr = NULL;

		dll_freeNode(list, del);
		list->size--;
	}
}

/**
 * Destroys the whole list and frees it from memory.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
void dll_clear(DLL *list)
{
	if(list)
	{
		Node *n = list->head;

		while(n)
		{
			Node *del = n;
			n = n->next;
			dll_freeNode(list, del);
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
 * Sorts the list with the insertion sort algorithm.
 *
 * The order of the nodes is defined through the compareData function.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
void dll_sort(DLL *list)
{
	assert(list);

	Node *i = list->head, *j, *tmp;
	while(i)
	{
		tmp = j = i;

		while(j)
		{
			if(list->compareData(tmp->data, j->data) == 1)
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
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
void dll_print(DLL *list)
{
	assert(list);

	printf("--- head ---\n");

	dll_traverse(list, list->printData);

	printf("--- tail ---\n");
}
