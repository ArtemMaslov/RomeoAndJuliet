#include <stdio.h>
#include <Windows.h>
#include <assert.h>


#include "..\inc\text.h"
#include "..\inc\string.h"


bool ParseBuffer(Text* text)
{
    assert(text);

    char* ptr = text->buffer;
    bool  nullString = true;

    while (*ptr)
    {
        if (*ptr == '\n')
        {
            if (nullString)
                text->nullStringsCount++;
            else
                text->stringsCount++;

            nullString = true;
        }
        else if (isspace(*ptr) == 0)
        {
            nullString = false;
        }
        ptr++;
    }

    text->strings = (String*)calloc(text->stringsCount, sizeof(String));

    if (text->strings == nullptr)
    {
        puts("Ошибка выделения памяти");
        return false;
    }

    ptr = text->buffer;
    char* start = ptr;

    String* sptr = text->strings;
    nullString = true;

    while (*ptr)
    {
        if (*ptr == '\n')
        {
            if (nullString == 0)
            {
                sptr->end   = ptr - 1;
                sptr->start = start;

                start = ptr + 1;
                sptr++;
            }

            nullString = true;
        }
        else if (isspace(*ptr) == 0)
        {
            nullString = false;
        }
        
        ptr++;
    }

    return true;
}