/**
 *  doublyLinkedList
 *
 * 	@file   dll.h
 * 	@author Marc Zimmermann (tooreht@gmail.com)
 * 	@date   December, 2012
 * 	@brief  Implementation of a doubly linked list, header file.
 *
 * 	Structure and function definitions of the doublyLinkedList implementation.
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
	unsigned long size;
	int (*compareData)(void*, void*);
	void (*freeData)(void*);
	void (*printData)(void*);
} DLL;

DLL* dll_create();
void dll_registerCompareData(DLL *list, int (*compareData)(void*, void*) );
void dll_registerFreeData(DLL *list, void (*freeData)(void*) );
void dll_registerPrintData(DLL *list, void (*printData)(void*) );
Node* dll_head(DLL *list);
Node* dll_tail(DLL *list);
Node* dll_curr(DLL *list);
unsigned long dll_size(DLL *list);
int dll_hasNext(DLL *list);
Node* dll_next(DLL *list);
int dll_hasPrev(DLL *list);
Node* dll_prev(DLL *list);
void dll_traverse(DLL *list, void (*callback)(void*) );
int dll_contains(DLL *list, Node *node);
Node* searchHeadToTail(DLL *list, void *data);
Node* searchTailToHead(DLL *list, void *data);
Node* searchHeadAndTail(DLL *list, void *data);
Node* dll_search(DLL *list, void *data, int mode);
Node* dll_pushHead(DLL *list, void *data);
Node* dll_pushTail(DLL *list, void *data);
Node* dll_addBefore(DLL *list, Node *node, void *data);
Node* dll_addAfter(DLL *list, Node *node, void *data);
void dll_freeNode(DLL *list, Node *node);
void dll_delete(DLL *list, void *data);
void dll_popHead(DLL *list);
void dll_popTail(DLL *list);
void dll_clear(DLL *list);
void dll_reverse(DLL *list);
void dll_sort(DLL *list);
void dll_print(DLL *list);
