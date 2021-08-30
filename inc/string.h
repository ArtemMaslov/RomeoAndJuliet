#ifndef STRING_H_
#define STRING_H_

struct String
{
    char* start;
    char* end;
};


int CompareStrings(const String* s1, const String* s2);

#endif