#ifndef IA_H
#define IA_H

#include "map.h"

// Definição de struct Node
typedef struct Node
{
    Position position;
    int g_score, h_score, f_score;
    struct Node *parent;
} Node;

Node *createNode();
void RemoveElement(int index, Node *list[], int *listSize);
void AddElement(Node *list[], Node *elementToAdd, int *listSize);
Node GetBestMove(Map m, Position start, Position goal);
void FreeMemoryToNode(Node *list[], int listSize);
Node FilterBestMove(Node *current);

#endif // IA_H