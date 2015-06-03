/*
# 05/31/2015 -St
# 05/31/2015
*/

/*This file has functions for Normal mode*/

/* Include header files */
#include<ncurses.h>
#include"header8.h"

/* Function definition of editor() */
MODE modeNormal(WINDOW *ed_win)
{
	/*Function local variables*/
	LINE_NODE *line_start = NULL;
	LINE_NODE *current = NULL;
	MODE changeModeTo = PHONY;
	char ch = 0;

	{
		wrefresh(ed_win);
		//wgetch(ed_win);
		/*Look for nav(hjkl), mode(i), or command(:) in an inf loop*/
		/*call appropriate functions*/
		while(1)
		{
			ch = wgetch(ed_win);
			/*if(ch == 'j')
			{
				jAtNormalMode();
			}*/
			if(ch == 'i')
			{

				changeModeTo = INSERT;
				return changeModeTo;
			}
			else if(ch == ':') 
			{
				changeModeTo = COMMAND;
				return changeModeTo;
			}
		}
	}
	return changeModeTo;
}
