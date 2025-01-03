#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "./inc/main.h"
#include "./inc/map.h"
#include "./inc/ui.h"
#include "./inc/constant.h"
#include "./inc/ia.h"

Map m;

Position hero;
int pills = 0;
int result;

int EndGame()
{
    Position pos;

    int lose = !FindMap(&m, &pos, HERO);
    int win = !FindMap(&m, &pos, GHOST);

    result = win ? 1 : 0;

    return win || lose;
}

int isDirection(char direction)
{
    return direction == LEFT ||
           direction == UP ||
           direction == DOWN ||
           direction == RIGHT;
}

void Move(char direction)
{

    int nextx = hero.x;
    int nexty = hero.y;

    switch (direction)
    {
    case LEFT:
        nexty--;
        break;
    case UP:
        nextx--;
        break;
    case DOWN:
        nextx++;
        break;
    case RIGHT:
        nexty++;
        break;
    }

    if (!CanMove(&m, HERO, nextx, nexty))
        return;

    if (isObject(&m, PILL, nextx, nexty))
    {
        pills++;
    }
    else if (isGhost(m, nextx, nexty))
    {
        m.matriz[hero.x][hero.y] = EMPTY;
        return;
    }

    WalkOnMap(&m, hero.x, hero.y, nextx, nexty);
    hero.x = nextx;
    hero.y = nexty;
}

int MoveRandom(int xCurrent, int yCurrent,
               int *xdestine, int *ydestine)
{
    int options[4][2] = {
        {xCurrent, yCurrent + 1},
        {xCurrent + 1, yCurrent},
        {xCurrent, yCurrent - 1},
        {xCurrent - 1, yCurrent}};

    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        int position = rand() % 4;

        if (CanMove(&m, GHOST, options[position][0], options[position][1]))
        {
            *xdestine = options[position][0];
            *ydestine = options[position][1];
            return 1;
        }
    }

    return 0;
}

void Ghosts()
{
    Map copy;

    CopyMap(&copy, &m);

    for (int i = 0; i < copy.line; i++)
    {
        for (int j = 0; j < copy.column; j++)
        {
            if (copy.matriz[i][j] == GHOST)
            {
                srand(time(NULL));
                int percent = rand() % 100;
                int newx, newy;

                if (percent < 20)
                {
                    MoveRandom(i, j, &newx, &newy);
                }
                else
                {
                    Node n = GetBestMove(m, (Position){i, j}, hero);

                    if (n.f_score == -1)
                    {
                        newx = -1;
                        newy = -1;
                    }
                    newx = n.position.x;
                    newy = n.position.y;
                }

                if (newx == -1 || newy == -1)
                {
                    continue;
                }
                WalkOnMap(&m, i, j, newx, newy);
            }
        }
    }

    FreeMap(&copy);
}

void ExplosionPillInDirection(int x, int y, int somex, int somey, int qtd)
{
    if (qtd == 0)
        return;

    int newx = x + somex;
    int newy = y + somey;

    if (!isValid(&m, newx, newy))
        return;
    if (isWall(&m, newx, newy))
        return;

    m.matriz[newx][newy] = EMPTY;
    ExplosionPillInDirection(newx, newy, somex, somey, qtd--);
}

void ExplosionPill()
{
    if (pills == 0)
        return;

    ExplosionPillInDirection(hero.x, hero.y, 0, 1, 2);
    ExplosionPillInDirection(hero.x, hero.y, 0, -1, 2);
    ExplosionPillInDirection(hero.x, hero.y, 1, 0, 2);
    ExplosionPillInDirection(hero.x, hero.y, -1, 0, 2);
    pills--;
}

int main()
{

    ReadMap(&m);
    FindMap(&m, &hero, HERO);

    while (!EndGame())
    {
        printf("Pill: %d\n", pills);
        PrintMap(&m);

        char key;
        scanf(" %c", &key);

        if (isDirection(key))
            Move(key);
        if (key == BOMB)
            ExplosionPill();

        Ghosts();
    }

    printf("Pill: %d\n", pills);
    PrintMap(&m);

    FreeMap(&m);

    if (result)
    {
        printf("You Win!\n");
    }
    else
    {
        printf("Game Over!\n");
    }

    char key;
    scanf(" %c", &key);
}