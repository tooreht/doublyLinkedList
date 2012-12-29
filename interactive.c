/**
 * @file   interactive.c
 * @author Marc Zimmermann (tooreht@gmail.com)
 * @date   December, 2012
 * @brief  Interactive testing of doubly linked list.
 *
 * This programm reads command lines from stdin and executes them.
 * It's purpose is to interactively test the implementation of the data structure.
 */

#include <string.h>
#include <time.h>

#include "dll.c"

DLL *list;
int *a1, *a2;

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
 * In this programm simple integers are used:
 */

/**
 * This callback function is feed with the data pointer to print the data.
 * To access the integer, the void pointer is casted to an int pointer
 * and then dereferenced.
 *
 * @param void* data
 * @return void
 */
void print_data(void *data)
{
	printf("%d\n", *(int *) data);
}

/**
 * This callback function is feed with the data pointer to free the data.
 *
 * @param void* data
 * @return void
 */
void free_data(void *data)
{
	free(data);
}

/**
 * This callback function is feed with two data pointers.
 * To access the integers, the void pointer is casted to an int pointer
 * and then dereferenced.
 *
 * @param void* first_arg
 * @param void* second_arg
 * @return int
 * 	-1: if first is greater than second
 * 	 0: if first and second are equal
 * 	 1: if first is lower than second
 */
int compare(void *first_arg, void *second_arg)
{
	int first = *(int *) first_arg;
	int second = *(int *) second_arg;

	if(first < second)
		return -1;
	else if(first == second)
		return 0;
	else
		return 1;
}

/**
 * Prints the usage options.
 *
 * @param void
 * @return void
 */
void usage(void)
{
	puts("Usage:");
	puts("");
	puts("print (p)\tprints the list");
	puts("info\t\tprints list info");
	puts("reverse\t\treverses the list");
	puts("sort\t\tsorts the list in ascending order");
	puts("delf\t\tdelete first node");
	puts("dell\t\tdelete last node");
	puts("destroy\t\tdeletes the whole list");
	puts("");
	puts("beg 1\t\tadds an integer to the beginning of the list");
	puts("end 1\t\tadds an integer to the end of the list");
	puts("find 1\t\tsearches after an integer in the list");
	puts("del 1\t\tdeletes an integer in the list");
	puts("performance 10\tdoes some performance testing with a number of elements");
	puts("");
	puts("after 1 2\tadds integer 2 after integer 1 in the list");
	puts("fill 10 20\tfills the list with integers from 10 to 20");
}

/**
 * Performs some tests with a dynamic number of elements.
 *
 * @param int elements: number of elements
 * @return void
 */
void performance(int elements)
{
	clock_t start = clock();

	int *integer;
	void *data;

	int i;
	for(i = 0; i < elements; i++)
	{
		integer = malloc(sizeof(int));
		*integer = i;
		data = integer;
		dll_add_begin(list, data);
		// dll_add_end(list, data);
		// dll_add_after(list, list->current, data);
	}

	// dll_print(list, print_data);
	// dll_sort(list, compare);
	dll_reverse(list);
	// dll_print(list, print_data);

	for(i = 0; i < elements; i++)
	{
		data = &i;
		dll_delete(list, data, compare, free_data);
		// dll_delete_first(list, free_data);
	}

	dll_print(list, print_data);

	double elapsed = ( (double)clock() - start ) / CLOCKS_PER_SEC;
	printf("Performance finished in %f s\n", elapsed);
}

/**
 * Fills the list with a specific range of integers.
 *
 * @param int beg: beginning of range
 * @param int end: end of range
 * @return void
 */
void fill(int beg, int end)
{
	if(beg > end)
		return;

	clock_t start = clock();

	int *integer;
	void *data;

	int i;
	for(i = beg; i <= end; i++)
	{
		integer = malloc(sizeof(int));
		*integer = i;
		data = integer;
		// dll_add_begin(list, data);
		dll_add_end(list, data);
		// dll_add_after(list, list->current, data);
	}

	double elapsed = ( (double)clock() - start ) / CLOCKS_PER_SEC;
	printf("Filling finished in %f s\n", elapsed);
}

/**
 * Extracts the commands out of a line and executes them.
 *
 * @param char *line: char pointer to the line
 * @param size_t *nbytes: numbers of allocated charbytes
 * @return void
 */
void parse_line(char *line, size_t *nbytes)
{
	//printf("nbytes: %ld %s\n", *nbytes, line);

	// if(command[*nbytes-1] == '\n')
	// 	command[*nbytes-1] = '\0';

	if(!list)
		list = dll_create();

	char command[10];
	void *arg1, *arg2;
	
	a1 = malloc(sizeof(int));
	a2 = malloc(sizeof(int));

	int nargs = sscanf(line, "%s %d %d", command, a1, a2);
	
	arg1 = a1;
	arg2 = a2;

	// printf("%d %s %d %d\n", nargs, command, *a1, *a2);

	switch(nargs)
	{
		case 1:
			if(!strcmp(command, "print") || !strcmp(command, "p"))
			{
				dll_print(list, print_data);
			}
			else if(!strcmp(command, "info"))
			{
				printf("head\t %p %d\n", list->head, list->head ? *(int*)list->head->data : -1);
				printf("tail\t %p %d\n", list->tail, list->tail ? *(int*)list->tail->data : -1);
				printf("curr\t %p %d\n", list->curr, list->curr ? *(int*)list->curr->data : -1);
				printf("size\t %d\n", list->size);
			}
			else if(!strcmp(command, "reverse"))
			{
				dll_reverse(list);
			}
			else if(!strcmp(command, "sort"))
			{
				dll_sort(list, compare);
			}
			else if(!strcmp(command, "delf"))
			{
				dll_delete_first(list, free_data);
			}
			else if(!strcmp(command, "dell"))
			{
				dll_delete_last(list, free_data);
			}
			else if(!strcmp(command, "destroy"))
			{
				dll_destroy(list, free_data);
				list = NULL;
			}
			else
			{
				usage();
			}
			break;
		case 2:
			if(!strcmp(command, "beg"))
			{
				dll_add_begin(list, arg1);
			}
			else if(!strcmp(command, "end"))
			{
				dll_add_end(list, arg1);
			}
			else if(!strcmp(command, "find"))
			{
				Node *found = dll_search(list, arg1, compare);
				if(found)
					print_data(found->data);
				else
					printf("Node with data %d couldn't be found\n", *a1);
			}
			else if(!strcmp(command, "del"))
			{
				dll_delete(list, arg1, compare, free_data);
			}
			else if(!strcmp(command, "performance"))
			{
				performance(*a1);
			}
			else
			{
				usage();
			}
			break;
		case 3:
			if(!strcmp(command, "after"))
			{
				if(list->head)
				{
					Node *n = dll_search(list, arg1, compare);
					list->curr = dll_add_after(list, n, arg2);
				}
				else
				{
					list->head = dll_add_begin(list, arg2);
				}
			}
			else if(!strcmp(command, "fill"))
			{
				fill(*a1, *a2);
			}
			else
			{
				usage();
			}
			break;
		default:
			usage();
	}
}

/**
 * Main:
 * Reads each line from stdin which is not an EOF.
 * Frees the allocated memory.
 *
 * @param int argc: number of arguments
 * @param char const *argv[]: pointer to arguments
 * @return int: success
 */
int main(int argc, char const *argv[])
{
	size_t bytes_read;
	size_t nbytes = 8;

	char *line = (char *) malloc(nbytes + 1);

	puts("Enter a command:");

	while( (bytes_read = getline(&line, &nbytes, stdin)) != -1)
	{
		parse_line(line, &bytes_read);
	}

	free(line);

	free(a1);
	free(a2);

	dll_destroy(list, free_data);

	return 0;
}