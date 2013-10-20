/**
 *  doublyLinkedList
 *
 *  https://github.com/tooreht/doublyLinkedList
 *
 *  @file   dll.c
 *  @author Marc Zimmermann (tooreht@gmail.com)
 *  @date   December, 2012
 *  @brief  Implementation of a doubly linked list.
 *
 *  Function implementations of doublyLinkedList.
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
static dll_node_t* dll_createNode(void *data);
static dll_node_t* dll_addFirstNode(dll_t *list, void *data);
static void dll_freeNode(dll_t *list, dll_node_t *del);

/**
 * Creates a new doubly linked list.
 *
 * @param void
 * @return dll_t*: pointer of new doubly linked list
 */
dll_t* dll_create(void)
{
    dll_t *new = malloc(sizeof(dll_t));

    if (new)
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
 * Registers compareFn callback function on the list.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param int (*compareFn)(void*, void*): callback function compareFn
 * @return void
 */
void dll_registerCompareFn(dll_t *list, int (*compareFn)(void*, void*) )
{
    assert(list);
    assert(compareFn);

    list->compareFn = compareFn;
}

/**
 * Registers freeFn callback function on the list.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param int (*compareFn)(void*, void*): callback function compareFn
 * @return void
 */
void dll_registerFreeFn(dll_t *list, void (*freeFn)(void*) )
{
    assert(list);
    assert(freeFn);

    list->freeFn = freeFn;
}

/**
 * Registers printFn callback function on the list.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param int (*compareFn)(void*, void*): callback function compareFn
 * @return void
 */
void dll_registerPrintFn(dll_t *list, void (*printFn)(void*) )
{
    assert(list);
    assert(printFn);

    list->printFn = printFn;
}

/**
 * Returns the head and sets the current to the head.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @return dll_node_t*: tail node
 */
dll_node_t* dll_head(dll_t *list)
{
    assert(list);

    return list->curr = list->head;
}

/**
 * Returns the tail and sets the current to the tail.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @return dll_node_t*: tail node
 */
dll_node_t* dll_tail(dll_t *list)
{
    assert(list);

    return list->curr = list->tail;
}

/**
 * Returns the current node.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @return dll_node_t*: current node
 */
dll_node_t* dll_curr(dll_t *list)
{
    assert(list);

    return list->curr;
}

/**
 * Returns the size of the doubly linked list.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @return unsigned long: size
 */
unsigned long dll_size(dll_t *list)
{
    assert(list);

    return list->size;
}

/**
 * Checks if the doubly linked list has a next node.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @return int: has next
 */
short int dll_hasNext(dll_t *list)
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
 * @param dll_t *list: pointer to the doubly linked list
 * @return dll_node_t*: next node
 */
dll_node_t* dll_next(dll_t *list)
{
    assert(list);

    if (list->curr && list->curr->next)
        return list->curr = list->curr->next;
    else if (list->curr && !list->curr->next)
        return list->curr = NULL;
    else
        return list->curr = list->head;
}

/**
 * Checks if the doubly linked list has a previous node.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @return int: has previous
 */
short int dll_hasPrev(dll_t *list)
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
 * @param dll_t *list: pointer to the doubly linked list
 * @return dll_node_t*: previous node
 */
dll_node_t* dll_prev(dll_t *list)
{
    assert(list);

    if (list->curr && list->curr->prev)
        return list->curr = list->curr->prev;
    else if (list->curr && !list->curr->prev)
        return list->curr = NULL;
    else
        return list->curr = list->tail;
}

/**
 * Traverses the doubly linked list, while providing
 * the data pointer of each node to a callback function.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param void (*callback)(void*): callback function
 * @return void
 */
void dll_traverse(dll_t *list, void (*callback)(void*) )
{
    assert(list);
    assert(callback);

    dll_node_t *n = list->head;

    while (n)
    {
        callback(n->data); // or (*callback)(i);
        n = n->next;
    }
}

/**
 * Checks if a node exists in the doubly linked list.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param dll_node_t *node: node to test against
 * @return int: success
 */
short int dll_contains(dll_t *list, dll_node_t *node)
{
    assert(list);

    if (node && list->size)
    {
        dll_node_t *n = list->head;

        while (n)
        {
            if (n == node)
                return 1;
            n = n->next;
        }
    }

    return 0;
}

/**
 * Gets the node at the index.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param unsigned long index: index
 * @return dll_node_t*: pointer to the pushed node
 */
dll_node_t* dll_get(dll_t *list, unsigned long index)
{
    assert(list);
    assert(index < list->size);

    if (index < list->size / 2)
    {
        list->curr = list->head;

        while (index--)
        {
            list->curr = list->curr->next;
        }
    }
    else
    {
        index = list->size - index - 1;
        list->curr = list->tail;

        while (index--)
        {
            list->curr = list->curr->prev;
        }
    }

    return list->curr;
}

/**
 * Searches for data from head to tail.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return dll_node_t*: pointer to the found node
 */
dll_node_t* dll_searchHeadToTail(dll_t *list, void *data)
{
    assert(list);
    assert(list->compareFn);
    assert(data);

    dll_node_t *n = list->head;

    if (list->size)
    {
        while (n)
        {
            if (!list->compareFn(n->data, data))
                return n;
            n = n->next;
        }
    }

    return NULL;
}

/**
 * Searches for data from tail to head.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return dll_node_t*: pointer to the found node
 */
dll_node_t* dll_searchTailToHead(dll_t *list, void *data)
{
    assert(list);
    assert(list->compareFn);
    assert(data);

    dll_node_t *n = list->tail;

    if (list->size)
    {
        while (n)
        {
            if (!list->compareFn(n->data, data))
                return n;
            n = n->prev;
        }
    }

    return NULL;
}

/**
 * Searches for data from both, head and tail alternating.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return dll_node_t*: pointer to the found node
 */
dll_node_t* dll_searchHeadAndTail(dll_t *list, void *data)
{
    assert(list);
    assert(list->compareFn);
    assert(data);

    dll_node_t *i = list->head, *j = list->tail;

    if (list->size)
    {
        if (list->size % 2)
        {
            do
            {
                if (!list->compareFn(i->data, data))
                    return i;
                if (!list->compareFn(j->data, data))
                    return j;

                i = i->next;
                j = j->prev;
            }
            while (i->prev != j->next);
        }
        else
        {
            while (i != j->next)
            {
                if (!list->compareFn(i->data, data))
                    return i;
                if (!list->compareFn(j->data, data))
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
 * @param dll_t *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @param int mode: search mode
 * @return dll_node_t*: pointer to the found node
 */
dll_node_t* dll_search(dll_t *list, void *data, short int mode)
{
    assert(list);
    assert(data);

    dll_node_t *search = NULL;

    switch (mode)
    {
    case 3:
        search = dll_searchHeadAndTail(list, data);
        break;
    case 2:
        search = dll_searchTailToHead(list, data);
        break;
    case 1:
    default:
        search = dll_searchHeadToTail(list, data);
    }

    return list->curr = search;
}

/**
 * Creates a new node.
 *
 * @param void *data: data pointer
 * @return dll_node_t*: pointer to the new node
 */
dll_node_t* dll_createNode(void *data)
{
    assert(data);

    dll_node_t *new = malloc(sizeof(dll_node_t));

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
 * @param dll_t *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return dll_node_t*: pointer to the first node
 */
dll_node_t* dll_addFirstNode(dll_t *list, void *data)
{
    assert(list);
    assert(data);

    list->size = 1;

    return list->head = list->tail = list->curr = dll_createNode(data);
}

/**
 * Sets the node at the index to a specific value.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param unsigned long index: index
 * @param void *data: data pointer
 * @return dll_node_t*: pointer to the pushed node
za */
dll_node_t* dll_set(dll_t *list, unsigned long index, void *data)
{
    list->curr = dll_get(list, index);
    list->curr->data = data;

    return list->curr;
}

/**
 * Pushs a new node to the head of the doubly linked list.
 * Sets the current node to the new node.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return dll_node_t*: pointer to the pushed node
 */
dll_node_t* dll_pushHead(dll_t *list, void *data)
{
    assert(list);
    assert(data);

    if (list->head)
    {
        dll_node_t *new = dll_createNode(data);

        if (new)
        {
            dll_node_t *tmp = list->head;
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
 * @param dll_t *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return dll_node_t*: pointer to the pushed node
 */
dll_node_t* dll_pushTail(dll_t *list, void *data)
{
    assert(list);
    assert(data);

    if (list->tail)
    {
        dll_node_t *new = dll_createNode(data);

        if (new)
        {
            dll_node_t *tmp = list->tail;
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
 * @param dll_t *list: pointer to the doubly linked list
 * @param dll_node_t *node: node to add before
 * @param void *data: data pointer
 * @return dll_node_t*: pointer to the added node
 */
dll_node_t* dll_addBefore(dll_t *list, dll_node_t *node, void *data)
{
    assert(list);
    assert(node);
    assert(data);

    dll_node_t *new = NULL;

    if (list->size)
    {
        new = dll_createNode(data);

        if (new)
        {
            new->next = node;
            new->prev = node->prev;
            if (node == list->head)
                list->head = new;
            node->prev = new;
            if (new->prev)
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
 * @param dll_t *list: pointer to the doubly linked list
 * @param dll_node_t *node: node to add after
 * @param void *data: data pointer
 * @return dll_node_t*: pointer to the added node
 */
dll_node_t* dll_addAfter(dll_t *list, dll_node_t *node, void *data)
{
    assert(list);
    assert(node);
    assert(data);

    dll_node_t *new = NULL;

    if (list->size)
    {
        new = dll_createNode(data);

        if (new)
        {
            new->prev = node;
            new->next = node->next;
            if (node == list->tail)
                list->tail = new;
            node->next = new;
            if (new->next)
                new->next->prev = new;
            list->size++;
        }
    }

    return list->curr = new;
}

/**
 * Frees data and the node from memory.
 *
 * @param dll_node_t *node: node to free
 * @return void
 */
void dll_freeNode(dll_t *list, dll_node_t *del)
{
    assert(list);
    assert(list->freeFn);

    if (del && list->size)
    {
        if (list->head == list->tail)
            list->head = list->tail = NULL;
        else if (del == list->head)
        {
            list->head = del->next;
            list->head->prev = NULL;
        }
        else if (del == list->tail)
        {
            list->tail = del->prev;
            list->tail->next = NULL;
        }
        else
        {
            del->prev->next = del->next;
            del->next->prev = del->prev;
        }

        if (del == list->curr)
            list->curr = NULL;

        list->freeFn(del->data);
        del->prev = del->next = del->data = NULL;
        free(del);

        list->size--;
    }
}

/**
 * Deletes the node at the specific index.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param unsigned long index: index
 * @return void
 */
void dll_delete(dll_t *list, unsigned long index)
{
    dll_freeNode(list, dll_get(list, index));
}

/**
 * Deletes the first node with the specific data from the list.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @param int mode: search mode
 * @return void
 */
void dll_searchAndDelete(dll_t *list, void *data, short int mode)
{
    assert(list);
    assert(data);

    dll_node_t *found = dll_search(list, data, mode);

    if (found)
    {
        dll_freeNode(list, found);
    }
}

/**
 * Deletes the first node of the doubly linked list.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @return void
 */
void dll_popHead(dll_t *list)
{
    assert(list);

    dll_freeNode(list, list->head);
}

/**
 * Deletes the last node of the doubly linked list.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @return void
 */
void dll_popTail(dll_t *list)
{
    assert(list);

    dll_freeNode(list, list->tail);
}

/**
 * Destroys the whole list and frees it from memory.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @return void
 */
void dll_clear(dll_t *list)
{
    if (list)
    {
        dll_node_t *n = list->head;

        while (n)
        {
            dll_node_t *del = n;
            n = n->next;
            dll_freeNode(list, del);
        }
        free(list);
    }
}

/**
 * Reverses the list.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @return void
 */
void dll_reverse(dll_t *list)
{
    assert(list);

    dll_node_t *i = list->head, *j = list->tail;

    while (i != j && i != j->next)
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
 * The order of the nodes is defined through the compareFn function.
 *
 * @param dll_t *list: pointer to the doubly linked list
 * @return void
 */
void dll_sort(dll_t *list)
{
    assert(list);
    assert(list->compareFn);

    dll_node_t *i = list->head, *j, *tmp;
    while (i)
    {
        tmp = j = i;

        while (j)
        {
            if (list->compareFn(tmp->data, j->data) == 1)
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
 * @param dll_t *list: pointer to the doubly linked list
 * @return void
 */
void dll_print(dll_t *list)
{
    assert(list);
    assert(list->printFn);

    printf("--- head ---\n");

    dll_traverse(list, list->printFn);

    printf("--- tail ---\n");
}
