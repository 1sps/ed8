/*
# Header file
# This file contains:
1. Constants
2. typedefs
3. Function prototype declarations
4. Other #define 
*/

/*
# 05/22/2015 -st
# 05/23/2015
# SPS
*/

#ifndef INCLUDE_HEADER
	#define INCLUDE_HEADER

	/* Constants */
	#define ONE 1
	#define BUFF_LENGTH 512
	#define FNAME_LENGTH 25
	#define TAB_LENGTH 8

	/* Declaring the structure of the node */
	/* This holds each line */
	/* The file is a linked list of lines*/
	typedef struct line_node
	{
		struct char_node *c;
		struct line_node *next;
		struct line_node *previous;
		int line_number;
		bool has_data;
		int num_bytes;
	}LINE_NODE;

	/* A character node */
	/* Structure of each character of each line */
	/* Each line is a linked list of chars*/
	typedef struct char_node
	{
		char ci;
		struct char_node *nextc;
		struct char_node *previousc;
	}CHAR_NODE;
	
	/*Struct LINE_NODE and CHAR_NODE*/
	typedef struct cursor_info
	{
		LINE_NODE *cursor_line;
		CHAR_NODE *cursor_char;
	}CURSOR_INFO;

	/* Function prototype declarations*/
	int modeNormal(WINDOW *);
	CHAR_NODE *create_char_node(void);
	LINE_NODE *create_line_node(void);
	LINE_NODE *subReadFile(int);
	void subDisplay(LINE_NODE *, WINDOW *);
	int display_init(LINE_NODE *, WINDOW *);
	LINE_NODE *next_line(LINE_NODE *);
	LINE_NODE *previous_line(LINE_NODE *);
	LINE_NODE *next_page(LINE_NODE *);
	char *subGetFileName(WINDOW *);
	int subOpenFile(char *, WINDOW *);
	int ed8(char *);
	int subFreeMemory(char *);
	void subInitWindow(WINDOW *);
	void subOnWindow(WINDOW *);
	void subOffWindow(WINDOW *);
	void move_after_display_init(LINE_NODE *, WINDOW *);
	int modeInsert(WINDOW *);
	int modeCommand(WINDOW *);
	
	extern CURSOR_INFO curs_info;

#endif
