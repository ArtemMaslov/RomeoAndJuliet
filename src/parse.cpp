#include <stdio.h>
#include <Windows.h>
#include <assert.h>

#include "..\inc\string.h"


bool ParseBuffer(char* buffer, String** strings, size_t* stringsCount)
{
    assert(buffer);
    assert(stringsCount);

    char* ptr = buffer;
    *stringsCount = 0;

    while (*ptr)
    {
        if(*ptr == '\n')
            (*stringsCount)++;
        ptr++;
    }

    *strings = (String*)calloc(*stringsCount, sizeof(String));

    if (*strings == nullptr)
    {
        puts("Ошибка выделения памяти");
        return false;
    }

    ptr = buffer;
    char* start = ptr;

    String* sptr = *strings;

    while (*ptr)
    {
        if (*ptr == '\n')
        {
            sptr->end = ptr - 1;
            sptr->start = start;

            start = ptr + 1;
            sptr++;
        }
        
        ptr++;
    }

    return true;
}