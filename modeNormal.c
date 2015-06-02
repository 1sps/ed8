/*
# 05/31/2015 -St
# 05/31/2015
*/

/*This file has functions for Normal mode*/

/* Include header files */
#include<ncurses.h>
#include"header8.h"

/* Function definition of editor() */
void modeNormal(WINDOW *ed_win)
{
	/*Function local variables*/
	LINE_NODE *line_start = NULL;
	LINE_NODE *current = NULL;

	{
		//line_start = read_file(file1);

		//display(line_start, ed_win);

		wrefresh(ed_win);
	}
}
