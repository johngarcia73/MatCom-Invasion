#include"map.h"

void draw()   //Draws the map and its elements.
{
    printf("\n");

    for (int i = 0; i < anchoMapa; i++)
    {
        printf("\t");
        for (int j = 0; j < largoMapa; j++)
        {   
            
            printf("%c", map[i][j]);
            printf("   ");
        }
        printf("\n\n");
    }
    printf("\n");
}

int* positionGen(int number)
{
    int *positions = malloc(number * sizeof(int));
    srand((unsigned int)time(NULL));

    for (int i = 0; i < number; i++)
    {
        positions[i] = rand() % 9;
    }

    return positions;
}

void cleanPosition(int x, int y)
{
    attron(COLOR_PAIR(3));
    mvaddch(y, x, ' ');
    attroff(COLOR_PAIR(3));
    refresh();
}
