/*
# 06/02/2015
# 06/02/2015
# SPS
*/

/*This file has functions for navigation*/

#include<ncurses.h>
#include"header8.h"

/*modeNormal will call this function*/
void navigate(char ch, WINDOW *ed_win)
{
	if(ch == 'h')
		navigateH(ed_win);
	else if(ch == 'j')
		navigateJ(ed_win);
	else if(ch == 'k')
		navigateK(ed_win);
	else if(ch == 'l')
		navigateL(ed_win);
}

void navigateH(WINDOW *ed_win)
{
	int y, x;
	/*getyx(ed_win, y, x);
	wmove(ed_win, 30, 0);
	wrefresh(ed_win);
	wprintw(ed_win, "H ENTERED");
	wrefresh(ed_win);
	wmove(ed_win, y, x);
	*/
	int x_count_dec = 0;
	//xcount++;
	if((curs_info.cursor_char->previousc != NULL))
	{
		if(curs_info.cursor_char->previousc->ci != '\t')
		{
			xcount--;
			getyx(ed_win, y, x);
			wmove(ed_win, y, x-1);
			wrefresh(ed_win);
			curs_info.cursor_char = curs_info.cursor_char->previousc;
		}
		else if(curs_info.cursor_char->previousc->ci == '\t')
		{
			getyx(ed_win, y, x);
			LINE_NODE *ltemp = curs_info.cursor_line;
			CHAR_NODE *ctemp = ltemp->c;
			CHAR_NODE *current = ctemp;
			int count = 0;
			while(current != curs_info.cursor_char->previousc)
			{
				if(current->ci != '\t')
					count++;
				if(current->ci == '\t')
					count = count + (TAB_LENGTH - (count%TAB_LENGTH));

				current = current->nextc;
			}

			xcount = count;
			wmove(ed_win, y, xcount);
			wrefresh(ed_win);
			curs_info.cursor_char = curs_info.cursor_char->previousc;
			/*
			getyx(ed_win, y, x);
			x_count_dec = (xcount%TAB_LENGTH);
			xcount=xcount+x_count_inc;
			x = x + x_count_inc;
			wmove(ed_win, y, x);
			curs_info.cursor_char = curs_info.cursor_char->nextc;
			*/
		}
	}
}

void navigateJ(WINDOW *ed_win)
{
	if(curs_info.cursor_line->next != NULL)
	{
		int y, x;
		getyx(ed_win, y, x);
		wmove(ed_win, y+1, 0);
		wrefresh(ed_win);
		xcount = 0;
		curs_info.cursor_line = curs_info.cursor_line->next;
		curs_info.cursor_char = curs_info.cursor_line->c;
		CHAR_NODE *currentChar = curs_info.cursor_line->c;
		while(currentChar->ci == ' ' || currentChar->ci == '\t' || currentChar->ci == '\n')
		{
			if(currentChar->ci == ' ')
			{
				
				getyx(ed_win, y, x);
				xcount++;
				x=x+1;
				wmove(ed_win, y, x);
				wrefresh(ed_win);
			}
			else if(currentChar->ci == '\t')
			{
				getyx(ed_win, y, x);
				int x_count_inc = 0;
				x_count_inc = TAB_LENGTH - (xcount%TAB_LENGTH);
				xcount=xcount+x_count_inc;
				x=x+x_count_inc;
				wmove(ed_win, y, x);
				wrefresh(ed_win);
			}
			else if(currentChar->ci == '\n')
			{
				getyx(ed_win, y, x);
				curs_info.cursor_line = curs_info.cursor_line;
				curs_info.cursor_char = curs_info.cursor_line->c;
				wmove(ed_win, y, 0);
				wrefresh(ed_win);
				xcount = 0;
				break;
			}
			currentChar = currentChar->nextc;
			curs_info.cursor_char = currentChar;
		}
	}
}
void navigateK(WINDOW *ed_win)
{
	if(curs_info.cursor_line->previous != NULL)
	{
		int y, x;
		getyx(ed_win, y, x);
		wmove(ed_win, y-1, 0);
		wrefresh(ed_win);
		xcount = 0;
		curs_info.cursor_line = curs_info.cursor_line->previous;
		curs_info.cursor_char = curs_info.cursor_line->c;
		CHAR_NODE *currentChar = curs_info.cursor_line->c;
		while(currentChar->ci == ' ' || currentChar->ci == '\t' || currentChar->ci == '\n')
		{
			if(currentChar->ci == ' ')
			{
				
				getyx(ed_win, y, x);
				xcount++;
				x=x+1;
				wmove(ed_win, y, x);
				wrefresh(ed_win);
			}
			else if(currentChar->ci == '\t')
			{
				getyx(ed_win, y, x);
				int x_count_inc = 0;
				x_count_inc = TAB_LENGTH - (xcount%TAB_LENGTH);
				xcount=xcount+x_count_inc;
				x=x+x_count_inc;
				wmove(ed_win, y, x);
			}
			else if(currentChar->ci == '\n')
			{
				getyx(ed_win, y, x);
				curs_info.cursor_line = curs_info.cursor_line;
				curs_info.cursor_char = curs_info.cursor_line->c;
				wmove(ed_win, y, 0);
				wrefresh(ed_win);
				xcount = 0;
				break;
			}
			currentChar = currentChar->nextc;
			curs_info.cursor_char = currentChar;
		}
	}
}
void navigateL(WINDOW *ed_win)
{
	int y, x;
	int x_count_inc = 0;
	//xcount++;
	if((curs_info.cursor_char->nextc != NULL) && (curs_info.cursor_char->nextc->ci !='\n'))
	{
		if(curs_info.cursor_char->ci != '\t')
		{
			xcount++;
			getyx(ed_win, y, x);
			wmove(ed_win, y, xcount);
			wrefresh(ed_win);
			curs_info.cursor_char = curs_info.cursor_char->nextc;
		}
		else if(curs_info.cursor_char->ci == '\t')
		{
			//xcount++;
			getyx(ed_win, y, x);
			x_count_inc = TAB_LENGTH - (xcount%TAB_LENGTH);
			xcount=xcount+x_count_inc;
			//x = x + x_count_inc;
			wmove(ed_win, y, xcount);
			curs_info.cursor_char = curs_info.cursor_char->nextc;
		}
	}
	
}
