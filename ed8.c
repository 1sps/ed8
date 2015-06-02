/*
# 05/20/2015 St
# 05/31/2015
# SPS
*/
/* C program for 'Text Editor' */

/* Including required header files */
#include<ncurses.h>
#include<stdlib.h>
#include"header8.h"


/*Main begins*/
int main(int argc, char *argv[])
{
	/* If user invokes the program incorrectly */
	if(argc != 1)
	{
		printf("ed8 :: Don't pass command line arguments.");
		printf(" Please be careful and retry.\n");
		exit(1);
	}

	/*Call ed8()*/
	ed8();
	/* main() ends */
	return 0;
}

/*Editor*/
int ed8(void)
{
	/*Local Variables*/
	int fd;
	int ymax, xmax;
	CURSOR_INFO curs_info;
	char *fileName = NULL;
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
	wmove(ed_win, 0 ,0);
	  
	/*Get filename*/
	fileName = subGetFileName(ed_win);

	/*Open file*/
	fd = subOpenFile(fileName, ed_win);

	/*Read file*/
	/*And store it is the data structure*/
	firstLine = subReadFile(fd);

	/*Display*/
	curs_info = subDisplay(firstLine, ed_win);

	modeNormal(curs_info, ed_win);

	/*Free*/
	subFreeMemory(fileName);

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
