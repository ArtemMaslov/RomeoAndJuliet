#include <stdio.h>
#include <Windows.h>
#include <assert.h>

#include "..\inc\formate.h"


static void FormateStringEnding(String* string);


static void FormateStringBeginning(String* string);


void FormateStrings(String* strings, const size_t stringsCount)
{
    assert(strings);

    for (size_t st = 0; st < stringsCount; st++)
    {
        FormateStringBeginning(strings + st);
        FormateStringEnding(strings + st);
    }
}

static void FormateStringBeginning(String* string)
{
    assert(string);

    char* start = string->start;

    while (start <= string->end)
    {
        if (isspace(*start))
            string->start++;
        else
            return;
        start++;
    }
}

static void FormateStringEnding(String* string)
{
    assert(string);

    char* end = string->end;

    while (end >= string->start)
    {
        if (isspace(*end))
            string->end--;
        else
            return;
        end--;
    }
}