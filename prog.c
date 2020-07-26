#include <ncurses.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

WINDOW *create_newwin(int height, int width, int starty, int startx);
void destroy_win(WINDOW *local_win);
void insert_char(WINDOW *win, char ch);
void insert_char_line(WINDOW *win, char ch, int spacing);


#define TEXT_OFFSET 6

int main()
{

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    refresh();

    char mesg[] = "hello there\nand hello there";

    int h, w;
    getmaxyx(stdscr, h, w);

    WINDOW *info_win;
    info_win = create_newwin(3, w, h-3, 0);
    mvwprintw(
        info_win,1,1,"%s","This shows game info"
    );
    wrefresh(info_win);


    WINDOW *play_win;
    play_win = create_newwin(h-4, w, 0, 0);

    wmove(play_win,TEXT_OFFSET,TEXT_OFFSET);
    for (int i = 0; i < strlen(mesg);i++) {
        if (mesg[i] == '\n'){
            int y, x;
            getyx(play_win, y, x);
            wmove(play_win, y+1, TEXT_OFFSET);
        } else {
            waddch(play_win, mesg[i]);
        }
    }
    wmove(play_win,TEXT_OFFSET,TEXT_OFFSET);
    wrefresh(play_win);
    refresh();

    for (int i = 0; i < strlen(mesg);i++) {
        bool done = false;
        int ch;
        while (!done) {
            if ((ch = getch()) != ERR) {
                switch (ch) {
                    case 'q':
                        done = true;
                        exit(0);
                        break;
                    case '\n':
                        if (mesg[i] == '\n') {
                            insert_char_line(play_win, ch, TEXT_OFFSET);
                            done = true;
                        }
                        break;
                    default:
                        if (mesg[i] == ch) {
                            insert_char(play_win, ch);
                            done = true;
                        }
                        break;
                }
            }
        }
        refresh();
    }
    endwin();
}


WINDOW *create_newwin(int height, int width, int starty, int startx)
{
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);
    wrefresh(local_win);
    return local_win;
}

void destroy_win(WINDOW *local_win)
{
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(local_win);
    delwin(local_win);
}


void insert_char(WINDOW *win, char ch)
{
    waddch(win, ch | A_UNDERLINE);
    wrefresh(win);
}

void insert_char_line(WINDOW *win, char ch, int spacing)
{
    int y, x;
    getyx(win, y, x);
    wmove(win, y+1, spacing);
    wrefresh(win);
}
