/**
 *  doublyLinkedList
 *
 *  https://github.com/tooreht/doublyLinkedList
 *
 * 	@file   dll.h
 * 	@author Marc Zimmermann (tooreht@gmail.com)
 * 	@date   December, 2012
 * 	@brief  Implementation of a doubly linked list, header file.
 *
 * 	Structure and function definitions of the doublyLinkedList implementation.
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

typedef struct Node
{
	void *data;
	struct Node *prev;
	struct Node *next;
} dll_node_t;

typedef struct doublyLinkedList
{
	dll_node_t *head;
	dll_node_t *tail;
	dll_node_t *curr;
	unsigned long size;
	int (*compareFn)(void*, void*);
	void (*freeFn)(void*);
	void (*printFn)(void*);
} dll_t;

dll_t* dll_create();
void dll_registerCompareFn(dll_t *list, int (*compareFn)(void*, void*) );
void dll_registerFreeFn(dll_t *list, void (*freeFn)(void*) );
void dll_registerPrintFn(dll_t *list, void (*printFn)(void*) );
dll_node_t* dll_head(dll_t *list);
dll_node_t* dll_tail(dll_t *list);
dll_node_t* dll_curr(dll_t *list);
unsigned long dll_size(dll_t *list);
short int dll_hasNext(dll_t *list);
dll_node_t* dll_next(dll_t *list);
short int dll_hasPrev(dll_t *list);
dll_node_t* dll_prev(dll_t *list);
void dll_traverse(dll_t *list, void (*callback)(void*) );
short int dll_contains(dll_t *list, dll_node_t *node);
dll_node_t* dll_get(dll_t *list, unsigned long index);
dll_node_t* dll_searchHeadToTail(dll_t *list, void *data);
dll_node_t* dll_searchTailToHead(dll_t *list, void *data);
dll_node_t* dll_searchHeadAndTail(dll_t *list, void *data);
dll_node_t* dll_search(dll_t *list, void *data, short int mode);
dll_node_t* dll_set(dll_t *list, unsigned long index, void *data);
dll_node_t* dll_pushHead(dll_t *list, void *data);
dll_node_t* dll_pushTail(dll_t *list, void *data);
dll_node_t* dll_addBefore(dll_t *list, dll_node_t *node, void *data);
dll_node_t* dll_addAfter(dll_t *list, dll_node_t *node, void *data);
void dll_delete(dll_t *list, unsigned long index);
void dll_searchAndDelete(dll_t *list, void *data, short int mode);
void dll_popHead(dll_t *list);
void dll_popTail(dll_t *list);
void dll_clear(dll_t *list);
void dll_reverse(dll_t *list);
void dll_sort(dll_t *list);
void dll_print(dll_t *list);
