/*
# 05/20/2015 St
# 05/31/2015
# SPS
*/
/* C program for 'Text Editor' */

/* Including required header files */
#include<ncurses.h>
#include<stdlib.h>
#include"sys/types.h"
#include"sys/stat.h"
#include"fcntl.h"
#include"header8.h"

/*Keep track which char is crusor on*/
CURSOR_INFO curs_info;
int ycount, xcount;
LINE_NODE *num1Line = NULL;

/*Main begins*/
int main(int argc, char *argv[])
{
	/* If user invokes the program incorrectly */
	if(argc != 2)
	{
		//printf("ed8 :: Don't pass command line arguments.");
		printf("ed8 :: Filename missing \n");
		printf("Syntax\n$ ./ed8 <filename>\n");
		printf("Please retry ...\n");
		exit(1);
	}

	/*Call ed8()*/
	ed8(argv[1]);
	/* main() ends */
	return 0;
}

/*Editor*/
int ed8(char *fileName)
{
	/*Local Variables*/
	int changeTo = 0;
	int fd;
	int ymax, xmax;
	LINE_NODE *firstLine = NULL;

	/*Start curses*/
	initscr();
	subInitWindow(stdscr);
	//box(stdscr, 2, 2);
	wborder(stdscr, ' ', ' ', '-', ' ', ' ', ' ', ' ', ' ' );
	wrefresh(stdscr);

	/*Create ed_win*/
	getmaxyx(stdscr, ymax, xmax);
	WINDOW *ed_win = newwin(ymax-2, xmax-2, 1 ,1);
	subInitWindow(ed_win);
	wmove(ed_win, 0 ,0);
	  
	/*Open file*/
	fd = subOpenFile(fileName, ed_win);

	/*Read file*/
	/*And store it is the data structure*/
	firstLine = subReadFile(fd);

	/*Display*/
	subDisplay(firstLine, ed_win);

	/*--------------------*/
	/*--------------------*/
	while(1)
	{
		MODE changeModeTo = modeNormal(ed_win);
		if(changeModeTo == INSERT)
		{
			modeInsert(ed_win);
			//break;
		}
		else if(changeModeTo == COMMAND)
			changeModeTo = modeCommand(ed_win);//modeCommand();
		if (changeModeTo == EXIT)
		{
			break;
		}
	}

	/*Free*/
	//subFreeMemory(fileName);
	/*Close file*/
	close(fd);

	fd = open("DUMP", O_WRONLY | O_CREAT | O_TRUNC, 0660);
	LINE_NODE *write_line = NULL;
	CHAR_NODE *write_char = NULL;
	write_line = firstLine;
	write_char = write_line->c;
	while(write_line != NULL)
	{
		write_char = write_line->c;
		while(write_char != NULL)
		{
			char ch = write_char->ci;
			char *ch_ptr = &ch;
			write(fd, ch_ptr, 1);
			write_char = write_char->nextc;
		}
		write_line = write_line->next;
	}
	close(fd);

	/*Delete windows, end curses*/
	delwin(ed_win);
	endwin();

	return 0;
}

/*Function to free the malloc'd memory*/
int subFreeMemory(char *fileName)
{
	free(fileName);
	return 0;
}

/*Function to do default initialization
  for a WINDOW
*/
void subInitWindow(WINDOW *winRef)
{
	raw();
	noecho();
	keypad(winRef, TRUE);
}

/*----------------------------*/
void subOnWindow(WINDOW *winRef)
{
	noraw();
	echo();
}

void subOffWindow(WINDOW *winRef)
{
	raw();
	noecho();
}
