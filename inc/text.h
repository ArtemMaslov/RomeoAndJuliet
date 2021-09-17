
#ifndef _TEXT_H_
#define _TEXT_H_


#include "string.h"


struct Text
{
    char*   buffer;
    long    bufferSize;
    String* strings;
    size_t  stringsCount;
    size_t  nullStringsCount;
};


#endif // !_TEXT_H_
