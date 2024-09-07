#include"menu.h"
#include<string.h>


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
    if(option == 1)
    {
        endwin();
        exit(0);
    } 
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
    //mvprintw(2, largoMapa/2 - 7, "MATCOM INVASION");
    char *text = "MATCOM INVASION";
    draw_text(5, 5, text);
    attroff(COLOR_PAIR(6));
    refresh();
    pthread_mutex_unlock(&lock);

}

        //  Drawing the Title

void draw_char(int y, int x, char ch) {
    switch (ch) {
        case 'M':
            mvprintw(y, x, "###   ###");
            mvprintw(y+1, x, "#### ####");
            mvprintw(y+2, x, "## ### ##");
            mvprintw(y+3, x, "##  #  ##");
            mvprintw(y+4, x, "##     ##");
            break;
        case 'A':
            mvprintw(y, x, "  ###  ");
            mvprintw(y+1, x, " ##### ");
            mvprintw(y+2, x, "##   ##");
            mvprintw(y+3, x, "#######");
            mvprintw(y+4, x, "##   ##");
            break;
        case 'T':
            mvprintw(y, x, "#######");
            mvprintw(y+1, x, "   ##   ");
            mvprintw(y+2, x, "   ##   ");
            mvprintw(y+3, x, "   ##   ");
            mvprintw(y+4, x, "   ##   ");
            break;
        case 'C':
            mvprintw(y, x, " #####");
            mvprintw(y+1, x, "##    ");
            mvprintw(y+2, x, "##    ");
            mvprintw(y+3, x, "##    ");
            mvprintw(y+4, x, " #####");
            break;
        case 'O':
            mvprintw(y, x, " ##### ");
            mvprintw(y+1, x, "##   ##");
            mvprintw(y+2, x, "##   ##");
            mvprintw(y+3, x, "##   ##");
            mvprintw(y+4, x, " ##### ");
            break;
        case 'I':
            mvprintw(y, x, "#####");
            mvprintw(y+1, x, "  ## ");
            mvprintw(y+2, x, "  ## ");
            mvprintw(y+3, x, "  ## ");
            mvprintw(y+4, x, "#####");
            break;
        case 'N':
            mvprintw(y, x, "##   ##");
            mvprintw(y+1, x, "###  ##");
            mvprintw(y+2, x, "## # ##");
            mvprintw(y+3, x, "##  ###");
            mvprintw(y+4, x, "##   ##");
            break;
        case 'V':
            mvprintw(y, x, "##     ##");
            mvprintw(y+1, x, "##     ##");
            mvprintw(y+2, x, " ##   ## ");
            mvprintw(y+3, x, "  ## ##  ");
            mvprintw(y+4, x, "   ###   ");
            break;
        case 'S':
            mvprintw(y, x, " #####");
            mvprintw(y+1, x, "##    ");
            mvprintw(y+2, x, " #####");
            mvprintw(y+3, x, "    ##");
            mvprintw(y+4, x, "##### ");
            break;
        case 'W':
            mvprintw(y, x, "# #  #");
            mvprintw(y+1, x, "# #  #");
            mvprintw(y+2, x, "# #  #");
            mvprintw(y+3, x, "# #  #");
            mvprintw(y+4, x, " #####");
            break;
        case 'U':
            mvprintw(y, x, "##  ##");
            mvprintw(y+1, x, "##  ##");
            mvprintw(y+2, x, "##  ##");
            mvprintw(y+3, x, "######");
            mvprintw(y+4, x, " #### ");
            break;

        case 'Y':
            mvprintw(y, x, "##  ##");
            mvprintw(y+1, x, " ## ## ");
            mvprintw(y+2, x, "  ## ");
            mvprintw(y+3, x, "  ##  ");
            mvprintw(y+4, x, "  ##  ");
            break;

        default:
            break;
    }
}

void draw_text(int start_y, int start_x, const char *text) {
    int spacing = 2; // Espacio entre letras

    for (int i = 0; i < strlen(text); ++i) {
        if (text[i] != ' ') {
            draw_char(start_y, start_x + i * (9 + spacing), text[i]);
        }
    }
}

void winnerScreen()
{
    clear();
    
    attron(COLOR_PAIR(6));
    char *text = "YOU WIN";
    draw_text(10, 10, text);
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(5));
    mvprintw(30, 10, "Press spacebar to go back to menu...");
    attroff(COLOR_PAIR(5));
    refresh();

    int key;

    while(1)
    {
        key = getch();
        
        pthread_mutex_unlock(&lock);
        
        if(key == 32) break;
    }
}