#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../inc/ia.h"
#include "../inc/constant.h"
#include "../inc/map.h"

Node *CreateNode()
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->g_score = 10000;
    node->h_score = 10000;
    node->f_score = 10000;
    node->position.x = -1;
    node->position.y = -1;
    node->parent = NULL;
    return node;
}

void RemoveElement(int index, Node *list[], int *listSize)
{
    if (index < 0 || index >= (*listSize))
        return;

    for (int i = index; i < *listSize - 1; i++)
    {
        list[i] = list[i + 1];
    }
    list[(*listSize) - 1] = NULL;
    (*listSize)--;
}
void AddElement(Node *list[], Node *elementToAdd, int *listSize)
{
    list[(*listSize)] = elementToAdd;
    (*listSize)++;
}

Node FilterBestMove(Node *current)
{
    Node best = *current;

    if (best.parent == NULL)
    {
        return best;
    }

    Node passMove = best;
    while (best.parent != NULL)
    {
        passMove = best;
        best = *best.parent;
    }
    return passMove;
}

Node GetBestMove(Map m, Position start, Position goal)
{
    int lenght = m.line * m.column;

    Node *openList[lenght];
    int openListSize = 0;
    Node *closedList[lenght];
    int closedListSize = 0;

    Node *startNode = CreateNode();
    startNode->position.x = start.x;
    startNode->position.y = start.y;
    startNode->f_score = 0;
    startNode->h_score = 0;
    startNode->g_score = 0;

    AddElement(openList, startNode, &openListSize);

    int options[4][2] = {
        {-1, 0}, // UP
        {1, 0},  // DOWN
        {0, 1},  // RIGHT
        {0, -1}, // LEFT
    };

    while (openListSize > 0)
    {
        Node *currentNode = CreateNode();
        int index = 0;

        for (int i = 0; i < openListSize; i++)
        {
            if (openList[i] == NULL)
                continue;
            if (openList[i]->f_score < currentNode->f_score)
            {
                currentNode = openList[i];
                index = i;
            }
        }

        RemoveElement(index, openList, &openListSize);

        for (int i = 0; i < 4; i++)
        {
            int x = currentNode->position.x + options[i][0];
            int y = currentNode->position.y + options[i][1];

            Node *next = CreateNode();
            next->position.x = x;
            next->position.y = y;
            next->parent = currentNode;
            next->parent->position.x = currentNode->position.x;
            next->parent->position.y = currentNode->position.y;

            if (m.matriz[x][y] == HERO)
            {
                Node bestMove = FilterBestMove(next);
                FreeMemoryToNode(openList, openListSize);
                FreeMemoryToNode(closedList, closedListSize);
                return bestMove;
            }

            if (!CanMove(&m, GHOST, x, y))
                continue;

            next->g_score = currentNode->g_score + 1;
            next->h_score = abs(x - goal.x) + abs(y - goal.y);
            next->f_score = next->g_score + next->h_score;

            bool skip = false;

            for (int j = 0; j < openListSize; j++)
            {
                if (openList[j] == NULL)
                    continue;

                if (openList[j]->position.x == next->position.x &&
                    openList[j]->position.y == next->position.y)
                {
                    if (openList[j]->f_score <= next->f_score)
                    {
                        skip = true;
                        break;
                    }
                }
            }

            for (int j = 0; j < closedListSize; j++)
            {
                if (closedList[j] == NULL)
                    continue;
                if (closedList[j]->position.x == next->position.x &&
                    closedList[j]->position.y == next->position.y)
                {
                    if (closedList[j]->f_score <= next->f_score)
                    {
                        skip = true;
                        break;
                    }
                }
            }

            if (!skip)
            {
                AddElement(openList, next, &openListSize);
            }
        }

        AddElement(closedList, currentNode, &closedListSize);
    }

    FreeMemoryToNode(openList, openListSize);

    FreeMemoryToNode(closedList, closedListSize);

    Node goalFound;
    goalFound.f_score = -1;
    return goalFound;
}

void FreeMemoryToNode(Node *list[], int listSize)
{
    for (int i = 0; i < listSize; i++)
    {
        if (list[i])
        {
            free(list[i]);
        }
    }
}