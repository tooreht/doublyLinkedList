/**
 *  doublyLinkedList
 *
 *  https://github.com/tooreht/doublyLinkedList
 *
 *  @file   sample.c
 *  @author Marc Zimmermann (tooreht@gmail.com)
 *  @date   December, 2012
 *  @brief  sample usage of doublyLinkedList.
 *
 *  This programm shows sample usage of the doublyLinkedList library.
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
#include <string.h>

#include "dll.h"


/* =========================== User defined code =========================== */

/**
 * The data pointer is stored as a void pointer in each node of the list.
 * Thus three callback functions are needed to handle the generic
 * (userdefined) data structure:
 *
 * - printing the data
 * - freeing the data from memory
 * - comparing the data structures
 *
 * The function names don't matter, but the return types and parameters.
 *
 * In this programm a simple struct is used:
 */

 /* data structure */
 typedef struct
 {
    char* firstname;
    char* lastname;
    int age;
 } Person;

/**
 * This callback function is feed with the data pointer to print the data.
 * To access the integer, the void pointer is casted to an int pointer
 * and then dereferenced.
 *
 * @param void* data
 * @return void
 */
void printFn(void *data)
{
    Person *person = (Person *)data;

    puts("");
    printf("Firstname: %s\n", person->firstname);
    printf("Lastname: %s\n", person->lastname);
    printf("Age: %d\n", person->age);
    puts("");
}

/**
 * This callback function is feed with the data pointer to free the data.
 *
 * @param void* data
 * @return void
 */
void freeFn(void *data)
{
    Person *person = (Person *)data;

    free(person->firstname);
    free(person->lastname);
    free(person);
}

/**
 * This callback function is feed with two data pointers.
 * To access the integers, the void pointer is casted to an int pointer
 * and then dereferenced.
 *
 * @param void* first_arg
 * @param void* second_arg
 * @return int
 *  -1: if first is greater than second
 *   0: if first and second are equal
 *   1: if first is lower than second
 */
int compareFn(void *first_arg, void *second_arg)
{
    Person *p1 = (Person *)first_arg;
    Person *p2 = (Person *)second_arg;

    if(p1->age < p2->age)
        return -1;
    else if(p1->age == p2->age)
        return 0;
    else
        return 1;
}

Person* askPersonData()
{
    Person *person = malloc(sizeof(Person));

    size_t bytes_read;
    size_t nbytes = 8;

    char *line = malloc(nbytes + 1);

    puts("Firstname: ");
    if( (bytes_read = getline(&line, &nbytes, stdin)) != -1)
    {
        char *data = malloc(sizeof(char) * bytes_read);

        sscanf(line, "%s", data);
        person->firstname = data;
    }

    puts("Lastname: ");
    if( (bytes_read = getline(&line, &nbytes, stdin)) != -1)
    {
        char *data = malloc(sizeof(char) * bytes_read);

        sscanf(line, "%s", data);
        person->lastname = data;
    }

    puts("Age: ");
    if( (bytes_read = getline(&line, &nbytes, stdin)) != -1)
    {
        int data;

        sscanf(line, "%d", &data);
        person->age = data;
    }

    free(line);

    return person;
}

int main(int argc, char const *argv[])
{
    // creating a new list
    DLL *list = dll_create();
    dll_registerCompareFn(list, compareFn);
    dll_registerFreeFn(list, freeFn);
    dll_registerPrintFn(list, printFn);

    // ask for the number of persons to enter
    puts("How many persons do you like to enter?");
    char input[sizeof(stdin)];
    fgets(input, sizeof(stdin), stdin);

    int x;
    sscanf(input, "%d", &x);

    // ask for person data for x times
    int i;
    for(i = 0; i < x; i++)
    {
        dll_pushTail(list, askPersonData() );
    }

    // print data
    dll_print(list);
    puts("");

    // reverse the list
    puts("reverse");
    dll_reverse(list);

    // use dll iterator functions in a for loop to print the reversed list
    for(dll_head(list); dll_hasNext(list); dll_next(list))
    {
        printFn(list->curr->data);
    }


    puts("sort");
    dll_sort(list);

    // use dll iterator functions in a while loop to print the sorted list
    dll_head(list);
    while(dll_hasNext(list))
    {
        printFn(list->curr->data);
        dll_next(list);
    }

    printf("List size: %ld\n", dll_size(list));

    // empty the whole list
    dll_clear(list);


    return 0;
}
