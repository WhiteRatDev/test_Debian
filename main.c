#include <ncurses.h>
#include <stdlib.h>

void draw_menu(WINDOW *menu_win, int highlight);

int main() {
    int highlight = 1;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak(); // Линейная буферизация отключена
    curs_set(0); // Скрыть курсор

    WINDOW *menu_win = newwin(10, 40, 4, 4);
    keypad(menu_win, TRUE);

    mvprintw(0, 0, "Welcome to TWEAKOS Remote Interface (Debian ARM64)");
    mvprintw(1, 0, "Use arrow keys to go up and down, Press enter to select");
    refresh();

    while(1) {
        draw_menu(menu_win, highlight);
        c = wgetch(menu_win);
        switch(c) {
            case KEY_UP:
                if(highlight == 1) highlight = 4; else --highlight;
                break;
            case KEY_DOWN:
                if(highlight == 4) highlight = 1; else ++highlight;
                break;
            case 10: // Enter
                choice = highlight;
                break;
            default:
                break;
        }
        if(choice != 0) break; 
    }

    clear();
    mvprintw(0, 0, "You chose option %d. System is processing...", choice);
    refresh();
    getch();
    endwin();

    return 0;
}

void draw_menu(WINDOW *menu_win, int highlight) {
    int x, y, i;
    char *choices[] = {
        "1. Check System Load (top)",
        "2. List Files (ls -la)",
        "3. Network Status",
        "4. Exit"
    };

    x = 2; y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < 4; i++) {
        if(highlight == i + 1) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
        y++;
    }
    wrefresh(menu_win);
}
