#ifndef _MAP_H_
#define _MAP_H_

typedef struct Map
{
    char **matriz;
    int line;
    int column;
} Map;

typedef struct Position
{
    int x;
    int y;
} Position;

void allocMap(Map *m);
void ReadMap(Map *m);
void FreeMap(Map *m);

int FindMap(Map *m, Position *p, char c);

int isValid(Map *m, int x, int y);
int isWall(Map *m, int x, int y);
int isObject(Map *m, char hero, int x, int y);
int isGhost(Map m, int x, int y);

void WalkOnMap(Map *m, int xorigin, int yorigin,
               int xdestine, int ydestine);

void CopyMap(Map *destine, Map *origin);

int CanMove(Map *m, char hero, int x, int y);

#endif