#ifndef Draw
#define Draw
#include <stdio.h>
#include "utils.h"

void DrawTitle(){
    printf("************************************\n");
    printf("*             HATMAN GAME          *\n");
    printf("************************************\n");
    printf("\n\n");
}

void DrawHangman(char* wordSecret, char* kickedWords, int kickedNumbers){
    printf("\n");
    for (size_t i = 0; i < strlen(wordSecret); i++)
    {
        if(IsKickedLetter(kickedWords, kickedNumbers, wordSecret[i])){
            printf(" %c ", wordSecret[i]);
        }
        else{
            printf(" _ ");  
        }
    }
    printf("\n\n");
}

void DrawGibbet(char* wordSecret, char* kickedWords, int* kickedNumbers){
    int errors = NumberErrors(kickedNumbers, wordSecret, kickedWords);

    int head = errors >= 1;
    int body = errors >= 2;
    int armLeft = errors >= 3;
    int armRight = errors >= 4;
    int legLeft = errors >= 5;
    int legRight = errors >= 6;

    printf(" _________    \n");
    printf(" |/      |    \n");
    printf(" |      %c%c%c   \n", (head ? '(': ' '), (head ? '_': ' '), (head ? ')': ' '));
    printf(" |      %c%c%c  \n", (armLeft ? '\\' : ' '), (body? '|' : ' '), (armRight ? '/': ' '));
    printf(" |       %c    \n", (body? '|' : ' '));
    printf(" |      %c %c  \n", (legLeft ? '/' : ' '), (legRight ? '\\' : ' '));
    printf(" |            \n");
    printf("_|___         \n");
}

void DrawLoser(){
    printf("\n");
    printf("You Lose!!!");
    printf("\n");
    printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");
    printf("\n");
};

void DrawWin(){
    printf("\n");
    printf("Congratulations, you win!!!");
    printf("\n");
    printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n");
    printf("\n");
}

#endif