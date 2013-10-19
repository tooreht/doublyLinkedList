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
 static Node* dll_createNode(void *data);
 static Node* dll_addFirstNode(DLL *list, void *data);
 static void dll_freeNode(DLL *list, Node *del);

/**
 * Creates a new doubly linked list.
 *
 * @param void
 * @return DLL*: pointer of new doubly linked list
 */
 DLL* dll_create(void)
 {
    DLL *new = malloc(sizeof(DLL));

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
 * Creates a cloned doubly linked list.
 *
 * @param void
 * @return DLL*: pointer of cloned doubly linked list
 */
 DLL* dll_clone(DLL *list)
 {
    DLL *clone = malloc(sizeof(DLL));
    if (clone)
    {
        clone->head = list->head;
        clone->tail = list->tail;
        clone->curr = list->curr;
        clone->size = list->size;
        clone->compareFn = list->compareFn;
        clone->freeFn = list->freeFn;
        clone->printFn = list->printFn;

        Node *n = list->head;
        while(n->next)
        {
            Node *new = malloc(sizeof(Node));
            if (new) {
                new->data = n->data;
                new->prev = n->prev;
                new->next = n->next;
                n = n->next;
            }
            else
            {
                puts("ERROR: Out of memory");
            }
        }
    }
    else
    {
        puts("ERROR: Out of memory");
    }

    return clone;   
 }

/**
 * Registers compareFn callback function on the list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param int (*compareFn)(void*, void*): callback function compareFn
 * @return void
 */
 void dll_registerCompareFn(DLL *list, int (*compareFn)(void*, void*) )
 {
    assert(list);
    assert(compareFn);

    list->compareFn = compareFn;
}

/**
 * Registers freeFn callback function on the list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param int (*compareFn)(void*, void*): callback function compareFn
 * @return void
 */
 void dll_registerFreeFn(DLL *list, void (*freeFn)(void*) )
 {
    assert(list);
    assert(freeFn);

    list->freeFn = freeFn;
}

/**
 * Registers printFn callback function on the list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param int (*compareFn)(void*, void*): callback function compareFn
 * @return void
 */
 void dll_registerPrintFn(DLL *list, void (*printFn)(void*) )
 {
    assert(list);
    assert(printFn);

    list->printFn = printFn;
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
 short int dll_hasNext(DLL *list)
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
 * @param DLL *list: pointer to the doubly linked list
 * @return int: has previous
 */
 short int dll_hasPrev(DLL *list)
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
 * @param DLL *list: pointer to the doubly linked list
 * @param void (*callback)(void*): callback function
 * @return void
 */
 void dll_traverse(DLL *list, void (*callback)(void*) )
 {
    assert(list);
    assert(callback);

    Node *n = list->head;

    while (n)
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
 short int dll_contains(DLL *list, Node *node)
 {
    assert(list);

    if (node && list->size)
    {
        Node *n = list->head;

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
 * @param DLL *list: pointer to the doubly linked list
 * @param unsigned long index: index
 * @return Node*: pointer to the pushed node
 */
 Node* dll_get(DLL *list, unsigned long index)
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
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the found node
 */
 Node* dll_searchHeadToTail(DLL *list, void *data)
 {
    assert(list);
    assert(list->compareFn);
    assert(data);

    Node *n = list->head;

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
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the found node
 */
 Node* dll_searchTailToHead(DLL *list, void *data)
 {
    assert(list);
    assert(list->compareFn);
    assert(data);

    Node *n = list->tail;

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
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @return Node*: pointer to the found node
 */
 Node* dll_searchHeadAndTail(DLL *list, void *data)
 {
    assert(list);
    assert(list->compareFn);
    assert(data);

    Node *i = list->head, *j = list->tail;

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
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @param int mode: search mode
 * @return Node*: pointer to the found node
 */
 Node* dll_search(DLL *list, void *data, short int mode)
 {
    assert(list);
    assert(data);

    Node *search = NULL;

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
 * Sets the node at the index to a specific value.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param unsigned long index: index
 * @param void *data: data pointer
 * @return Node*: pointer to the pushed node
za */
 Node* dll_set(DLL *list, unsigned long index, void *data)
 {
    list->curr = dll_get(list, index);
    list->curr->data = data;

    return list->curr;
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

    if (list->head)
    {
        Node *new = dll_createNode(data);

        if (new)
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

    if (list->tail)
    {
        Node *new = dll_createNode(data);

        if (new)
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
 * @param Node *node: node to free
 * @return void
 */
 void dll_freeNode(DLL *list, Node *del)
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
 * @param DLL *list: pointer to the doubly linked list
 * @param unsigned long index: index
 * @return void
 */
 void dll_delete(DLL *list, unsigned long index)
 {
    dll_freeNode(list, dll_get(list, index));
}

/**
 * Deletes the first node with the specific data from the list.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @param void *data: data pointer
 * @param int mode: search mode
 * @return void
 */
 void dll_searchAndDelete(DLL *list, void *data, short int mode)
 {
    assert(list);
    assert(data);

    Node *found = dll_search(list, data, mode);

    if (found)
    {
        dll_freeNode(list, found);
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

    dll_freeNode(list, list->head);
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

    dll_freeNode(list, list->tail);
}

/**
 * Destroys the whole list and frees it from memory.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
 void dll_clear(DLL *list)
 {
    if (list)
    {
        Node *n = list->head;

        while (n)
        {
            Node *del = n;
            n = n->next;
            dll_freeNode(list, del);
        }
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
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
 void dll_insertionSort(DLL *list)
 {
    assert(list);
    assert(list->compareFn);

    Node *i = list->head, *j, *tmp;
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

// /**
//  * Sorts the list with the merge sort algorithm.
//  *
//  * The order of the nodes is defined through the compareFn function.
//  *
//  * @param DLL *list: pointer to the doubly linked list
//  * @return void
//  */
//  Node* dll_mergeSort(DLL *list, Node *first)
//  {
//     if (first == NULL || first->next == NULL)
//         return first;

//     Node *second = dll_split(first);

//     first = dll_mergeSort(list, first);
//     second = dll_mergeSort(list, second);

//     return dll_merge(list, first, second);
// }

// /**
//  * Splits the list.
//  *
//  * The order of the nodes is defined through the compareFn function.
//  *
//  * @param DLL *list: pointer to the doubly linked list
//  * @return void
//  */
//  Node* dll_split(Node *first)
//  {
//     if (first == NULL || first->next == NULL)
//         return NULL;

//     Node *second = first->next;
//     first->next = second->next;
//     second->next = dll_split(second->next);

//     return second;
// }

// *
//  * Merges the list.
//  *
//  * The order of the nodes is defined through the compareFn function.
//  *
//  * @param DLL *list: pointer to the doubly linked list
//  * @return void
 
//  Node* dll_merge(DLL *list, Node *first, Node *second)
//  {
//     if (first == NULL)
//         return second;
//     if (second == NULL)
//         return list->tail = first; // preserve tail

//     if (list->compareFn(first->data, second->data) == -1)
//     {
//         first->next = dll_merge(list, first->next, second);
//         first->next->prev = first;
//         first->prev = NULL;

//         return first;
//     } else {
//         second->next = dll_merge(list, first, second->next);
//         second->next->prev = second;
//         second->prev = NULL;

//         return second;
//     }
// }

// /**
//  * Sorts the list.
//  *
//  * The order of the nodes is defined through the compareFn function.
//  *
//  * @param DLL *list: pointer to the doubly linked list
//  * @return void
//  */
//  void dll_sort(DLL *list)
//  {
//     assert(list);

//     list->head = dll_mergeSort(list, list->head);
// }

/**
 * Sorts the list with the merge sort algorithm.
 *
 * The order of the nodes is defined through the compareFn function.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
 DLL* dll_mergeSort(DLL *first)
 {
    if (first->head == first->tail)
        return first;

    DLL *second = dll_clone(first);
    unsigned long size = first->size / 2;
    second->head = dll_get(first, size);
    // second->size = first->size - size;
    // second->printFn(second->head->prev->data);
    first->tail = second->head->prev;
    first->tail->next = NULL;
    // first->size = size;
    first->size = second->size = 1;

    // Node *tmp = second->head;
    // while(tmp)
    // {
    //     first->printFn(tmp->data);
    //     tmp = tmp->next;
    // }

    // dll_print(second);
    // printf("%ld\n", second->size);
    // dll_print(first);
    // printf("%ld\n", first->size);

    DLL *a = dll_mergeSort(first);
    DLL *b = dll_mergeSort(second);

    first->head = dll_merge(first, a->head, b->head);

    return first;
}

/*
 * Merges the list.
 *
 * The order of the nodes is defined through the compareFn function.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
Node* dll_merge(DLL *list, Node *a, Node *b)
{
    Node *dummyHead = malloc(sizeof(Node));
    Node *curr = dummyHead;

    while (a && b)
    {
        if (list->compareFn(a->data, b->data) == -1)
        {
            curr->next = a;
            a = a->next;
        }
        else
        {
            curr->next = b;
            b = b->next;
        }
        curr = curr->next;
    }
    curr->next = (a == NULL) ? b : a;
    return dummyHead->next;
}

/*
 * Merges the list.
 *
 * The order of the nodes is defined through the compareFn function.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
//  Node* dll_merge(DLL *list, Node *first, Node *second)
//  {
//     if (first == NULL)
//         return second;
//     if (second == NULL)
//         return first;

//     if (list->compareFn(first->data, second->data) == -1)
//     {
//         first->next = dll_merge(list, first->next, second);
//         first->next->prev = first;
//         first->prev = NULL;

//         return first;
//     }
//     else
//     {
//         second->next = dll_merge(list, first, second->next);
//         second->next->prev = second;
//         second->prev = NULL;

//         return second;
//     }
// }

/**
 * Sorts the list.
 *
 * The order of the nodes is defined through the compareFn function.
 *
 * @param DLL *list: pointer to the doubly linked list
 * @return void
 */
 void dll_sort(DLL *list)
 {
    assert(list);

    unsigned long size = list->size;
    list = dll_mergeSort(list);
    list->size = size;
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
    assert(list->printFn);

    printf("--- head ---\n");

    dll_traverse(list, list->printFn);

    printf("--- tail ---\n");
}
