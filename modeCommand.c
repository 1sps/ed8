/*
# 06/01/2015 -St
# 06/01/2015
# SPS
*/

/*This file has functions for insert mode*/

#include<ncurses.h>
#include"header8.h"

MODE modeCommand(WINDOW *ed_win)
{
	MODE changeModeTo = PHONY;
	char choice[25];
	int y, x, ymax, xmax;
	getyx(ed_win, y, x);
	getmaxyx(ed_win, ymax, xmax);
	wmove(ed_win, ymax-1, 0);
	waddch(ed_win, ':');
	wrefresh(ed_win);
	subOnWindow(ed_win);
	wgetstr(ed_win, choice);
	subOffWindow(ed_win);
	wmove(ed_win, ymax-1, 0);
	wclrtoeol(ed_win);
	wmove(ed_win, y, x);
	wrefresh(ed_win);
	if(strcmp(choice, "q") == 0)
	{
		changeModeTo = EXIT;
		return changeModeTo;
	}
	return changeModeTo;
}
