#include <stdio.h>
#include <Windows.h>
#include <assert.h>


#include "..\inc\text.h"
#include "..\inc\formate.h"


static void FormateStringEnding(String* string);

static void FormateStringBeginning(String* string);


void FormateStrings(Text* text)
{
    assert(text);

    for (size_t st = 0; st < text->stringsCount; st++)
    {
        FormateStringBeginning(text->strings + st);
        FormateStringEnding(text->strings + st);
    }
}

static void FormateStringBeginning(String* string)
{
    assert(string);

    char* start = string->start;
    char* end   = string->end;

    while (start <= end)
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

    char* end   = string->end;
    char* start = string->start;

    while (end >= start)
    {
        if (isspace(*end))
            string->end--;
        else
            return;
        end--;
    }
}