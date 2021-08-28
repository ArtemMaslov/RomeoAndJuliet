#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <Windows.h>
#include <cmath>

#include "..\inc\io.h"
#include "..\inc\line.h"
#include <Windows.h>

char* GetString(char* buffer, const int length, FILE* stream)
{
    assert(buffer);
    assert(stream);

    ferror(stream);

    char* result = nullptr;
    char* index  = nullptr;

    result = fgets(buffer, length, stream);

    if (result)
    {
        if (strcmp(buffer, "\n") == 0)//Empty string, program must be closed
            return nullptr;

        index = strchr(buffer, '\n');

        if (index)
            *index = '\0';
        else
        {
            SetColor(RED, BLACK);
            puts("\nEntered string is too big, part of it will be ignored. Correctly readed:");
            printf("\"%s\"\n\n", buffer);
            SetColor(WHITE, BLACK);

            while (getchar() != '\n')
                continue;
        }
    }
    return result;
}

void SetColor(const int text, const int background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, ((background & 0xf) << 4) | (text & 0xf));
}

void PutsColorText(int textColor, const char* text)
{
    assert(text);

    SetColor(textColor, BLACK);
    puts(text);
    SetColor(WHITE, BLACK);
}

void SetRussianText()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}