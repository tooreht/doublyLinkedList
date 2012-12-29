/**
 * @file   dll.h
 * @author Marc Zimmermann (tooreht@gmail.com)
 * @date   December, 2012
 * @brief  Implementation of a doubly linked list, header file.
 *
 * Structure and function definitions of the doubly linked list implementation.
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
void dll_traverse(DLL *list, void (*callback)(void*) );
int dll_contains(DLL *list, Node *node);
Node* dll_search(DLL *list, void *data, int (*compare)(void*, void*) );
Node* dll_create_node(void *data);
Node* dll_add_first_node(DLL *list, void *data);
Node* dll_add_begin(DLL *list, void *data);
Node* dll_add_end(DLL *list, void *data);
Node* dll_add_after(DLL *list, Node *node, void *data);
void dll_free_node(Node *node, void (*free_data)(void*) );
void dll_delete(DLL *list, void *data, int (*compare)(void*, void*), void (*free_data)(void*) );
void dll_delete_first(DLL *list, void (*free_data)(void*) );
void dll_delete_last(DLL *list, void (*free_data)(void*) );
void dll_destroy(DLL *list, void (*free_data)(void*) );
void dll_reverse(DLL *list);
void dll_sort(DLL *list, int (*compare)(void*, void*) );
void dll_print(DLL *list, void (*print_data)(void*) );
