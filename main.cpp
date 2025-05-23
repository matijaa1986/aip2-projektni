#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ispisPloce(char ploca[10][10], int ispisBroda)
{
    printf("  1  2  3  4  5  6  7  8  9  10\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%2d", i + 1);
        for (int j = 0; j < 10; j++)
        {
            if (ploca[i][j] == 'V')
                printf("🌊 ");
            else if (ploca[i][j] == 'B' && ispisBroda == 1)
                printf("🚢 ");
            else if (ploca[i][j] == 'B' && ispisBroda == 0)
                printf("🌊 ");
            else if (ploca[i][j] == 'H')
                printf("💥 ");
            else if (ploca[i][j] == 'X')
                printf("❌ ");
        }
        printf("\n");
    }
}