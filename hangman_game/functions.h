#ifndef Functions
#define Functions

#define WORD_SIZE 50
#define ATTEMPTS 6

//Utils.h
void PickPlayerDigit(char* kickedWords, int* kickedNumbers);
int IsKickedLetter(char* kickedWords, int kickedNumbers, char letter);
void InsertWordToGuessing(char* wordSecret);
int IsLoser(int kickedNumbers, char* wordSecret, char* kickedWords, int maxNumberError);
int IsWin(int kickedNumbers,char* wordSecret,char* kickedWords);
int NumberErrors(int kickedNumbers, char* wordSecret, char* kickedWords);

void AddWordInFile();

// Draw.h
void DrawTitle();
void DrawHangman(char* wordSecret, char* kickedWords, int kickedNumbers);
void DrawLoser();
void DrawWin();
#endif