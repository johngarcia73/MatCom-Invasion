#include"menu.h"
#include"ncurses.h"

void mainMenu()
{
    options[0].x = largoMapa/4;
    options[0].y = anchoMapa/2;
    options[1].x = options[0].x;
    options[1].y = options[0].y + 3;

    clear();
    drawTitle();
    drawOptions();
    drawPointer();

    select2();
}

void select2()
{
    int key;
    while(1)
    {
        key = getch();
        erasePointer();

        switch (key)
        {
            case KEY_UP:
                if(option <= 0) break;
                option--;
                break;
            case KEY_DOWN:    
                if(option >= optionsNumber - 1) break;
                option++;
                break;
            case 32:
                if(option == 0)
                {
                    clear();
                    game();
                }
                if(option == 1) exit(0);
                break;        
            default:
                break;    
        }
        drawPointer();
    }
}

void drawOptions()
{
    attron(COLOR_PAIR(5));
    mvprintw(options[0].y, options[0].x, "New Game");
    mvprintw(options[1].y, options[0].x, "Exit");
    attroff(COLOR_PAIR(5));
    refresh();
}

void erasePointer()
{
    attron(COLOR_PAIR(5));
    mvprintw(options[option].y, options[option].x -2, "  ");
    attroff(COLOR_PAIR(5));
    refresh();
}

void drawPointer()
{
    attron(COLOR_PAIR(5));
    mvprintw(options[option].y, options[option].x -2, "->");
    attroff(COLOR_PAIR(5));
    refresh();
}

void drawTitle()
{
    attron(COLOR_PAIR(6));
    mvprintw(2, largoMapa/2 - 7, "MATCOM INVASION");
    attroff(COLOR_PAIR(6));
    refresh();
}