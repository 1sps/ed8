/*
	05/31/2015 -st
	05/31/2015
	SPS
*/

/*
	This file has funcitons
	for the file operations
*/

#include<ncurses.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include"header8.h"

char *subGetFileName(WINDOW *ed_win)
{
	char msg1[] = "Filename: ";
	char fileNameBuffer[FNAME_LENGTH];
	char *fileName = NULL;
	int len = 0;

	clear();
	wrefresh(ed_win);
	wprintw(ed_win, "%s", msg1);
	wrefresh(ed_win);
	subOnWindow(ed_win);
	wgetstr(ed_win, fileNameBuffer);
	//noecho();
	//raw();
	subOffWindow(ed_win);
	len = strlen(fileNameBuffer);
	fileName = malloc(len*sizeof(char));
	strcpy(fileName, fileNameBuffer);
	wclear(ed_win);
	wrefresh(ed_win);
	wmove(ed_win, 0, 0);
	return fileName;
}

int subOpenFile(char *fileName, WINDOW *ed_win)
{
	int fd = open(fileName, O_RDWR | O_CREAT, 0660);
	if (fd == -1)
		wprintw(ed_win, "Error: Could not open file !\n");
	return fd;
}

LINE_NODE *subReadFile(int fd)
{
	int ln_num = 0;
	LINE_NODE *line_start = create_line_node();
	line_start->line_number = 0;
	LINE_NODE *line_current = NULL;
	LINE_NODE *line_temp = NULL;

	CHAR_NODE *char_start = create_char_node();
	CHAR_NODE *char_current = NULL;
	CHAR_NODE *char_temp = NULL;
	
	/*Local Variables*/
	int bytes_read;
	char buffer1[512];
	//char buffer2[512];
	int ch;

	register int i;
	
	line_current = line_start;
	line_current->c = char_start;
	char_current = line_current->c;
	
	/* Read from file*/
	while((bytes_read = read(fd, buffer1, BUFF_LENGTH)) > 0)
	{
			for(i=0; i<bytes_read; i++)
			{
				if(buffer1[i] != '\n')
				{
					line_current->has_data = TRUE;
					char_current->ci = buffer1[i];
					char_temp = create_char_node();
					char_current->nextc = char_temp;
					char_current = char_temp;
				}
				else if(buffer1[i] == '\n')
				{
					line_current->has_data = TRUE;
					char_current->ci = buffer1[i];
					char_current->nextc = NULL;

					/* Create next LINE_NODE */
					ln_num++;
					line_temp = create_line_node();
					line_temp->line_number = ln_num;
					line_current->next = line_temp;
					line_temp->previous = line_current;
					line_current = line_temp;
					line_current->c = create_char_node();
					char_current = line_current->c;
				}
			}
	}

	return line_start;
}

int subDisplay(LINE_NODE *first_line, WINDOW *ed_win )
{
	/*
		------
	*/
	LINE_NODE *currentLine = NULL;
	CHAR_NODE *currentChar = NULL;
	int disp = -1;

	disp = display_init(first_line, ed_win);
	if(disp == 0)
	{
		move_after_display_init(first_line, ed_win );
	}
	else
	{
	}
	wgetch(ed_win );
	return 0;
}

/* Initial (first) display */
int display_init(LINE_NODE *first_line, WINDOW *ed_win)
{
	int y, x, ymax, xmax;
	LINE_NODE *current_line = NULL;
	CHAR_NODE *current_char = NULL;

	current_line = first_line;
	current_char = current_line->c;

	getmaxyx(ed_win, ymax, xmax);

	while(current_line->has_data == TRUE)
	{
		current_char = current_line->c;
		getyx(ed_win, y, x);
		while(current_char != NULL)
		{
			/*End of screen*/
			if(y == ymax-2)
			{
				return 1;	
			}
			else
			{
				waddch(ed_win, current_char->ci);
				wrefresh(ed_win);
				current_char = current_char->nextc;
			}
		}
		current_line = current_line->next;
	}

	return 0;
}

void move_after_display_init(LINE_NODE *first_line, WINDOW *ed_win)
{
	int y, x;
	int y_count = 0;
	int y_count_inc = 0;
	LINE_NODE *currentLine = first_line;
	CHAR_NODE *currentChar = currentLine->c;
	wmove(ed_win, 0, 0);
	getyx(ed_win, y, x);
	while(currentChar->ci == ' ' || currentChar->ci == '\t')
	{
		if(currentChar->ci == ' ')
		{
			y_count++;
			x=x+1;
			wmove(ed_win, y, x);
		}
		else if(currentChar->ci == '\t')
		{
			y_count_inc = TAB_LENGTH - (y_count%TAB_LENGTH);
			y_count=y_count+y_count_inc;
			x=x+y_count_inc;
			wmove(ed_win, y, x);
		}
		currentChar = currentChar->nextc;
	}
}
//
