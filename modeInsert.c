/*
# 06/01/2015 -St
# 06/01/2015
# SPS
*/

/*This file has functions for insert mode*/
/*
	REMEMBER
	--------

	What we need ?
	-> curs_info
	-> xcount
*/
#include<ncurses.h>
#include"header8.h"

MODE modeInsert(WINDOW *ed_win)
{
	MODE changeModeTo = PHONY;
	int y, x;

	getyx(ed_win, y, x);
	echo();
	while(1)
	{
		int ch = wgetch(ed_win);
		if(ch == KEY_F(2))
		{
			noecho();
			changeModeTo = NORMAL;
			return changeModeTo;
		}
		else
		{
			CHAR_NODE *temp = create_char_node();
			temp->ci = ch;
			if(curs_info.cursor_char->previousc == NULL)
			{
				curs_info.cursor_line->c = temp;
			}
			else if(curs_info.cursor_char->previousc != NULL)
			{
				curs_info.cursor_char->previousc->nextc = temp;
				temp->previousc = curs_info.cursor_char->previousc;
			}
			temp->nextc = curs_info.cursor_char;
			curs_info.cursor_char->previousc = temp;

			getyx(ed_win, y, x);
			wmove(ed_win, y, 0);
			wclrtoeol(ed_win);
			temp = curs_info.cursor_line->c;
			while((temp != NULL) && (temp->ci != '\n'))
			{
				waddch(ed_win, temp->ci);
				temp = temp->nextc;
			}
			wmove(ed_win, y, x);
			wrefresh(ed_win);
		}
	}
	/*Unreachable code*/
	return changeModeTo;
}
