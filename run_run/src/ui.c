#include <stdio.h>
#include "../inc/map.h"
#include "../inc/constant.h"

char DrawWall[4][7] = {
    {"......"},
    {"......"},
    {"......"},
    {"......"}};

char DrawGhost[4][7] = {
    {" .-.  "},
    {"| OO| "},
    {"|   | "},
    {"'^^^' "}};

char DrawHero[4][7] = {
    {" .--. "},
    {"/ _.-'"},
    {"\\  '-."},
    {" '--' "}};

char DrawPill[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}};

char DrawEmpty[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}};

void Print(char draw[4][7], int i)
{
    printf("%s", draw[i]);
}

void PrintMap(Map *m)
{
    for (int i = 0; i < m->line; i++)
    {

        for (int k = 0; k < 4; k++)
        {
            for (size_t j = 0; j < m->column; j++)
            {

                switch (m->matriz[i][j])
                {
                case GHOST:
                    Print(DrawGhost, k);
                    break;
                case HERO:
                    Print(DrawHero, k);
                    break;
                case PILL:
                    Print(DrawPill, k);
                    break;
                case WALL_VERTICAL:
                case WALL_HORIZONTAL:
                    Print(DrawWall, k);
                    break;
                case EMPTY:
                    Print(DrawEmpty, k);
                    break;
                }
            }
            printf("\n");
        }
    }
}