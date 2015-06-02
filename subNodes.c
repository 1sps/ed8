/*
	05/23/2015 -st
	05/23/2015
	SPS
*/

/*
# This file defines the functions which create LINE_NODE and CHAR_NODE
*/

/* Include header files */
#include<ncurses.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include"header8.h"

/* Function to create a new LINE_NODE */
/* Returns the pointer to newly created LINE_NODE */
LINE_NODE *create_line_node(void)
{
	LINE_NODE *node_ptr = malloc(sizeof(LINE_NODE));
	node_ptr->next = NULL;
	node_ptr->previous = NULL;
	int line_number = -1;
	node_ptr->has_data = FALSE;
	node_ptr->num_bytes = 0;
	return node_ptr;
}

/* Function to create a new CHAR_NODE */
/* Returns the pointer to newly created CHAR_NODE*/
CHAR_NODE *create_char_node(void)
{
	CHAR_NODE *char_node_ptr = malloc(sizeof(CHAR_NODE));
	char_node_ptr->nextc = NULL;
	char_node_ptr->previousc = NULL;
	return char_node_ptr;
}
