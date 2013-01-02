/**
 *  doublyLinkedList
 *
 * 	@file   dll.h
 * 	@author Marc Zimmermann (tooreht@gmail.com)
 * 	@date   December, 2012
 * 	@brief  Implementation of a doubly linked list, header file.
 *
 * 	Structure and function definitions of the doubly linked list implementation.
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

typedef struct Node Node;
struct Node {
	void *data;
	struct Node *prev;
	struct Node *next;
};

typedef struct
{
	Node *head;
	Node *tail;
	Node *curr;
	unsigned int size;
} DLL;

DLL* dll_create();
Node* dll_head(DLL *list);
Node* dll_tail(DLL *list);
Node* dll_curr(DLL *list);
unsigned int dll_size(DLL *list);
int dll_has_next(DLL *list);
Node* dll_next(DLL *list);
int dll_has_prev(DLL *list);
Node* dll_prev(DLL *list);
void dll_traverse(DLL *list, void (*callback)(void*) );
int dll_contains(DLL *list, Node *node);
Node* dll_search(DLL *list, void *data, int (*compare)(void*, void*) );
Node* dll_create_node(void *data);
Node* dll_add_first_node(DLL *list, void *data);
Node* dll_add_begin(DLL *list, void *data);
Node* dll_add_end(DLL *list, void *data);
Node* dll_add_before(DLL *list, Node *node, void *data);
Node* dll_add_after(DLL *list, Node *node, void *data);
void dll_free_node(Node *node, void (*free_data)(void*) );
void dll_delete(DLL *list, void *data, int (*compare)(void*, void*), void (*free_data)(void*) );
void dll_delete_first(DLL *list, void (*free_data)(void*) );
void dll_delete_last(DLL *list, void (*free_data)(void*) );
void dll_destroy(DLL *list, void (*free_data)(void*) );
void dll_reverse(DLL *list);
void dll_sort(DLL *list, int (*compare)(void*, void*) );
void dll_print(DLL *list, void (*print_data)(void*) );
