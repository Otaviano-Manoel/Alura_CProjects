#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    // Inicialize variables
    int second = time(0);
    srand(second);

    int numberSecret = rand() % 100;

    int attempts = 0;

    int kick;

    int nivel;

    double points = 1000;

    // Init Game
    printf("\n\n");
    printf("          P  /_\\  P                              \n");
    printf("         /_\\_|_|_/_\\                            \n");
    printf("     n_n | ||. .|| | n_n          Welcome to      \n");
    printf("     |_|_|nnnn nnnn|_|_|      the Guessing Game!  \n");
    printf("    |" "  |  |_|  |"  " |                         \n");
    printf("    |_____| ' _ ' |_____|                         \n");
    printf("          \\__|_|__/                              \n");
    printf("\n\n");

    // Select level the game.
    printf("What is your game level?\n");
    printf("Easy (1) | Medium (2) | Difficult (3).\n");
    scanf("%d", &nivel);

    switch (nivel)
    {
    case 2:
        numberSecret = numberSecret * 10;
        printf("Your guessing range is 0 - 1000");
        break;
    case 3:
        numberSecret = numberSecret * 100;
        printf("Your guessing range is 0 - 10.000");
        break;
    default:
        printf("Your guessing range is 0 - 100");
        break;
    }

    // Run loop to game.
    do
    {
        printf("\nWhat's your number: ");

        scanf("%d", &kick);

        if (kick < 0)
        {
            printf("Cannot be negative.\n");
            continue;
        }

        int right = (kick == numberSecret);

        int bigger = kick > numberSecret;

        if (right)
        {
            printf("\n\n");
            printf("             OOOOOOOOOOO               \n");
            printf("         OOOOOOOOOOOOOOOOOOO           \n");
            printf("      OOOOOO  OOOOOOOOO  OOOOOO        \n");
            printf("    OOOOOO      OOOOO      OOOOOO      \n");
            printf("  OOOOOOOO  #   OOOOO  #   OOOOOOOO    \n");
            printf(" OOOOOOOOOO    OOOOOOO    OOOOOOOOOO   \n");
            printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO  \n");
            printf("OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO  \n");
            printf("OOOO  OOOOOOOOOOOOOOOOOOOOOOOOO  OOOO  \n");
            printf(" OOOO  OOOOOOOOOOOOOOOOOOOOOOO  OOOO   \n");
            printf("  OOOO   OOOOOOOOOOOOOOOOOOOO  OOOO    \n");
            printf("    OOOOO   OOOOOOOOOOOOOOO   OOOO     \n");
            printf("      OOOOOO   OOOOOOOOO   OOOOOO      \n");
            printf("         OOOOOO         OOOOOO         \n");
            printf("             OOOOOOOOOOOO              \n");
            printf("\n\n");

            printf("You Win!!! \n");
        }
        else if (bigger)
        {
            printf("The number is smaller.\n");
        }
        else
        {
            printf("The number is bigger.\n");
        }

        double pointLess = (abs)(kick - numberSecret) / (double)2;
        points = points - pointLess;

        if (points <= 0)
        {
            points = 0;
            printf("\n\n");
            printf("       \\|/ ____ \\|/    \n");
            printf("        @~/ ,. \\~@      \n");
            printf("       /_( \\__/ )_\\    \n");
            printf("          \\__U_/        \n");
            printf("\n\n");

            printf("You Lose.\n");
            break;
        }

        attempts++;
        printf("Number of attempts: %d \n", attempts);
    } while (numberSecret != kick);

    printf("\nPoints: %.1f", points);
    printf("The number was: %d", numberSecret);

    return 0;
}