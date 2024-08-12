#include"menu.h"

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
        
        pthread_mutex_unlock(&lock);
        

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
            default:
                break;    
        }
        if(key == 32) break;
        drawPointer();
        refresh();
        napms(50);
    }

    if(option == 0)
    {
        game();
    }
    if(option == 1) exit(0);
}

void drawOptions()
{
    pthread_mutex_lock(&lock);
    
    attron(COLOR_PAIR(5));
    mvprintw(options[0].y, options[0].x, "New Game");
    mvprintw(options[1].y, options[0].x, "Exit");
    attroff(COLOR_PAIR(5));
    refresh();

    pthread_mutex_unlock(&lock);

}

void erasePointer()
{
    pthread_mutex_lock(&lock);

    attron(COLOR_PAIR(5));
    mvprintw(options[option].y, options[option].x -2, "  ");
    attroff(COLOR_PAIR(5));
    refresh();
    pthread_mutex_unlock(&lock);

}

void drawPointer()
{
    pthread_mutex_lock(&lock);

    attron(COLOR_PAIR(5));
    mvprintw(options[option].y, options[option].x -2, "->");
    attroff(COLOR_PAIR(5));
    refresh();
    pthread_mutex_unlock(&lock);

}

void drawTitle()
{
    pthread_mutex_lock(&lock);

    attron(COLOR_PAIR(6));
    mvprintw(2, largoMapa/2 - 7, "MATCOM INVASION");
    attroff(COLOR_PAIR(6));
    refresh();
    pthread_mutex_unlock(&lock);

}