#ifndef _MAIN_H_
#define _MAIN_H_

int EndGame();
void Move(char direction);

int isDirection(char direction);
void Ghosts();
void ExplosionPill();
void ExplosionPillInDirection(int x, int y, int somex, int somey, int qtd);

int WhereDoesTheGhostGo(int xCurrent, int yCurrent,
                        int *xdestine, int *ydestine);

#endif