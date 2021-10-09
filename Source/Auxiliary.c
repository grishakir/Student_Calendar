#pragma once
#include "../Headers/Auxiliary.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../Headers/CLine.h"
int fromCharToInt(int c)
{
    /* получает на вход символ. Возвращает значение с - <<0>> */
    return c - '0';
}

int yesOrNo()
{
/* получает ответ у пользователя ответ
 * на вопрос <<Да, или нет?>> и возвращает 1,
 * если да, и 0, если нет */
    char tmp[20];
    while (1)
    {
        printf("Y or N\n");
        gets(tmp);

        if (strlen(tmp) == 1 && (tmp[0] == 'Y' || tmp[0] == 'N'))
        {
            if (tmp[0] == 'Y')
            {
                return 1;
            }
            else if (tmp[0] == 'N')
            {
                return 0;
            }
        }

        printIncorrectInput();
    }

}

void printIncorrectInput()
{
    /* печатает на экран <<Incorrect input>> */
    printf("Incorrect input!\n");
    _NUM_OF_ERRORS++;
}

int isNum(char* string)
{
/* получает на вход строку.
 * Если в строке находится только деситичное,
 * целое, положительное число, то возвращает это число, иначе 0 */
    for (int i = 0; i < strlen(string); i++)
    {
        if (!isdigit(string[i]))
            return 0;
    }

    return (atoi(string));
}