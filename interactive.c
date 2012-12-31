/**
 *  doublyLinkedList
 *
 *	@file   interactive.c
 *	@author Marc Zimmermann (tooreht@gmail.com)
 *	@date   December, 2012
 *	@brief  Interactive testing of doubly linked list.
 *
 *	This programm reads command lines from stdin and executes them.
 *	It's purpose is to interactively test the implementation of the data structure.
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

#include <string.h>
#include <time.h>

#include "dll.c"

DLL *list;
int *d1, *d2;

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
	puts("print (p)\tprint the list");
	puts("info\t\tprint list info");
	puts("reverse\t\treverse the list");
	puts("sort\t\tsort the list in ascending order");
	puts("delf\t\tdelete the first node");
	puts("dell\t\tdelete the last node");
	puts("destroy\t\tdelete the whole list");
	puts("");
	puts("beg 1\t\tadd an integer to the beginning of the list");
	puts("end 1\t\tadds an integer to the end of the list");
	puts("find 1\t\tsearche after an integer in the list");
	puts("del 1\t\tdelete an integer in the list");
	puts("performance 10\tdo some performance testing with a number of elements");
	puts("");
	puts("after 1 2\tadd integer 2 after integer 1 in the list");
	puts("fill 10 20\tfill the list with integers from 10 to 20");
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
 * Read from a file and print line by line.
 *
 * @param const char *file: file name
 * @return void
 */
void read_file(const char *file)
{
	FILE *fp; /* declare the file pointer */
	fp = fopen(file, "rt"); /* open the file for reading */

	if(fp == NULL)
	{
		printf("Cannot open file '%s'\n", file);
		exit(1);
	}

	size_t bytes_read;
	size_t nbytes = 8;

	char *line = (char *) malloc(nbytes + 1);

	while( (bytes_read = getline(&line, &nbytes, fp)) != -1)
	{
		printf("%s", line);
	}

	fclose(fp);  /* close the file prior to exiting the routine */
}

/**
 * Shows programm warranty information.
 *
 * @param void
 * @return void
 */
void show_warranty(void)
{
	puts("15. Disclaimer of Warranty.");
	puts("");
	puts("THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY");
	puts("APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT");
	puts("HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY");
	puts("OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,");
	puts("THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR");
	puts("PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM");
	puts("IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF");
	puts("ALL NECESSARY SERVICING, REPAIR OR CORRECTION.");
}

/**
 * Shows programm conditions.
 *
 * @param void
 * @return void
 */
void show_conditions(void)
{
	read_file("LICENSE.md");
}

/**
 * Executes gpl commands.
 *
 * @param int nargs: number of arguments
 * @param char *command: pointer to command string
 * @param char option: option
 * @return void
 */
void execute_gpl(int nargs, char *command, char option)
{
	switch(nargs)
	{
		case 2:
			if(!strcmp(command, "show"))
			{
				if(option == 'w')
					show_warranty();
				else if(option == 'c')
					show_conditions();
			}
		break;
	}
}

/**
 * Executes dll commands.
 *
 * @param int nargs: number of arguments
 * @param char *command: pointer to command string
 * @param int arg1: argument one
 * @param int arg2: argument two
 * @return void
 */
void execute_dll(int nargs, char *command, int arg1, int arg2)
{
	d1 = malloc(sizeof(int));
	d2 = malloc(sizeof(int));

	*d1 = arg1;
	*d2 = arg2;

	void *a1, *a2;

	a1 = d1;
	a2 = d2;

	if(!list)
		list = dll_create();

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
			else if(!strcmp(command, "show"))
			{
				// do absolutely nothing
			}
			else
			{
				usage();
			}
			break;
		case 2:
			if(!strcmp(command, "beg"))
			{
				dll_add_begin(list, a1);
			}
			else if(!strcmp(command, "end"))
			{
				dll_add_end(list, a1);
			}
			else if(!strcmp(command, "find"))
			{
				Node *found = dll_search(list, a1, compare);
				if(found)
					print_data(found->data);
				else
					printf("Node with data %d couldn't be found\n", arg1);
			}
			else if(!strcmp(command, "del"))
			{
				dll_delete(list, a1, compare, free_data);
			}
			else if(!strcmp(command, "performance"))
			{
				performance(arg1);
			}
			else if(!strcmp(command, "show"))
			{
				char option = (int) arg1;
				if(option == 'w')
					show_warranty();
				else if(option == 'c')
					show_conditions();
			}
			else
			{
				usage();
			}
			break;
		case 3:
			if(!strcmp(command, "after"))
			{
				Node *n = dll_search(list, a1, compare);
				if(n)
					list->curr = dll_add_after(list, n, a2);
				else
					printf("Node with data %d couldn't be found\n", arg1);
			}
			else if(!strcmp(command, "fill"))
			{
				fill(arg1, arg2);
			}
			else
			{
				usage();
			}
			break;
		default: usage();
	}
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
	int nargs;
	char command[*nbytes], c;

	int a1 = 0, a2 = 0;

	nargs = sscanf(line, "%s %d %d", command, &a1, &a2);

	execute_dll(nargs, command, a1, a2);

	nargs = sscanf(line, "%s %c", command, &c);

	execute_gpl(nargs, command, c);
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

	puts("---------- doublyLinkedList  Copyright (C) 2012  Marc Zimmermann ----------");
	puts("This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.");
	puts("This is free software, and you are welcome to redistribute it");
	puts("under certain conditions; type `show c' for details.");
	puts("");
	puts("Enter a command:");

	while( (bytes_read = getline(&line, &nbytes, stdin)) != -1)
	{
		parse_line(line, &bytes_read);
	}

	free(d1);
	free(d2);

	free(line);

	dll_destroy(list, free_data);

	return 0;
}