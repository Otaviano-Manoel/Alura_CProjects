#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "functions.h"
#include "draw.h"
#include "utils.h"

char kickedWords[26];
int kickedNumbers = 0;
char wordSecret[WORD_SIZE];

int main(){
    int loser = 0;
    int win = 0;

    DrawTitle();
    InsertWordToGuessing(wordSecret);

    do
    {
        loser = IsLoser(kickedNumbers, wordSecret, kickedWords, ATTEMPTS);
        win = IsWin(kickedNumbers, wordSecret, kickedWords);

        DrawGibbet(wordSecret, kickedWords, kickedNumbers);

        DrawHangman(wordSecret, kickedWords, kickedNumbers);
        if(!loser && !win) PickPlayerDigit(&kickedWords, &kickedNumbers);
    } while (!loser && !win);

    if(loser){
        DrawLoser();
    }
    else{
        DrawWin();
    }

    AddWordInFile();
}