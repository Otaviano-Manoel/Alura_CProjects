#ifndef Utils
#define Utils
#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

void PickPlayerDigit(char* kickedWords, int* kickedNumbers){
    char answer;
    printf("Insert a word: ");
    scanf(" %c", &answer);

    kickedWords[(*kickedNumbers)] = toupper(answer);
    (*kickedNumbers)++;
}

int IsKickedLetter(char* kickedWords, int kickedNumbers, char letter){
    int found = 0;
    for (size_t j = 0; j < kickedNumbers; j++)
    {
        if(kickedWords[j] == letter){
            found = 1;
            break;;
        }
    }
    return found;
}

void InsertWordToGuessing(char* wordSecret){
    FILE* f = fopen("words.txt", "r");

     if (f == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    int numberWords;
    fscanf(f, "%d", &numberWords);

    srand(time(0));
    int random = rand() % numberWords;

    for (size_t i = 0; i <= random; i++)
    {
        fscanf(f, "%s", wordSecret);
    }

    if (strlen(wordSecret) == 0) {
        printf("Nenhuma palavra foi lida!\n");
    }

    for (size_t i = 0; i < strlen(wordSecret); i++)
    {
        wordSecret[i] = toupper(wordSecret[i]);
    }

    fclose(f);
}

int NumberErrors(int kickedNumbers, char* wordSecret, char* kickedWords){
    int errors = 0;
    for (size_t i = 0; i < kickedNumbers; i++)
    {
        int exists = 0;
        for (size_t j = 0; j < strlen(wordSecret); j++)
        {
                if(wordSecret[j] == kickedWords[i]){
                    exists = 1;
                    break;
                }
        }

        if(!exists) errors++; 
    }
    return errors;
}

int IsLoser(int kickedNumbers, char* wordSecret, char* kickedWords, int maxNumberError){

    if(NumberErrors(kickedNumbers, wordSecret, kickedWords) >= maxNumberError) return 1;
    return 0;
}

int IsWin(int kickedNumbers,char* wordSecret,char* kickedWords){
    for (size_t i = 0; i < strlen(wordSecret); i++)
    {
        if(!IsKickedLetter(kickedWords, kickedNumbers, wordSecret[i])) return 0;
    }
    return 1;
}

void AddWordInFile(){

    printf("Do you want to add a word to the game?(Y\\N)");

    char answer;
    scanf(" %c", &answer);

    if(toupper(answer) == 'Y'){

        printf("Write your word");
        char newWord[50];
        scanf("%s", &newWord);

        FILE* f;

        f = fopen("words.txt", "r+");

        if (f == NULL) {
            printf("Erro ao abrir o arquivo!\n");
            exit(1);
        }   

        int numberWords;
        fscanf(f, "%d", &numberWords);
        numberWords++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", numberWords);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", newWord);

        fclose(f);
    }
}

#endif