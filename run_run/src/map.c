#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/map.h"
#include "../inc/constant.h"

void ReadMap(Map *m)
{
    FILE *f;
    f = fopen("map.txt", "r");
    if (f == 0)
    {
        printf("Error reading map");
        exit(1);
    }

    fscanf(f, "%d %d", &(m->line), &(m->column));
    allocMap(m);

    for (int i = 0; i < m->line; i++)
    {
        fscanf(f, "%s", m->matriz[i]);
    }

    fclose(f);
}

void allocMap(Map *m)
{
    m->matriz = malloc(sizeof(char *) * m->line);

    for (int i = 0; i < m->line; i++)
    {
        m->matriz[i] = malloc((sizeof(char)) * m->column + 1);
    }
}

void CopyMap(Map *destine, Map *origin)
{
    destine->line = origin->line;
    destine->column = origin->column;
    allocMap(destine);
    for (int i = 0; i < origin->line; i++)
    {
        strcpy(destine->matriz[i], origin->matriz[i]);
    }
}

void FreeMap(Map *m)
{
    for (int i = 0; i < m->line; i++)
    {
        free(m->matriz[i]);
    }

    free(m->matriz);
}

int FindMap(Map *m, Position *p, char c)
{

    for (int i = 0; i < m->line; i++)
    {
        for (int j = 0; j < m->column; j++)
        {
            if (m->matriz[i][j] == c)
            {
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }

    return 0;
}

int CanMove(Map *m, char hero, int x, int y)
{
    return isValid(m, x, y) &&
           !isWall(m, x, y) &&
           !isObject(m, hero, x, y) &&
           !isGhost(*m, x, y);
}

int isValid(Map *m, int x, int y)
{
    if (x >= m->line)
        return 0;
    if (y >= m->column)
        return 0;

    return 1;
}

int isObject(Map *m, char obj, int x, int y)
{
    return m->matriz[x][y] == obj;
}
int isGhost(Map m, int x, int y)
{
    return m.matriz[x][y] == GHOST;
}

int isWall(Map *m, int x, int y)
{
    return m->matriz[x][y] == WALL_VERTICAL ||
           m->matriz[x][y] == WALL_HORIZONTAL;
}

void WalkOnMap(Map *m, int xorigin, int yorigin,
               int xdestine, int ydestine)
{
    char hero = m->matriz[xorigin][yorigin];
    m->matriz[xdestine][ydestine] = hero;
    m->matriz[xorigin][yorigin] = EMPTY;
}