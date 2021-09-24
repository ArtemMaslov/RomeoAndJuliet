
#ifndef _TEXT_H_
#define _TEXT_H_


#include <stdio.h>
#include "string.h"


struct Text
{
    char*   buffer;
    long    bufferSize;
    String* strings;
    size_t  stringsCount;
    size_t  nullStringsCount;
};

void FreeTextStructure(Text* text);

int ReadText(Text* text, FILE* input);

void SortTextAndWriteToFile(Text* text, FILE* output);

#endif // !_TEXT_H_
