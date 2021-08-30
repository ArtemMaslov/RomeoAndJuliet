#include <assert.h>

#include "..\inc\string.h"


void SortStrings(String* strings, const size_t stringsCount)
{
    assert(strings);

    for (int st = 0; st < stringsCount - 1; st++)
    {
        for (int st1 = st + 1; st1 < stringsCount; st1++)
        {
            int result = CompareStrings(strings + st, strings + st1);
            
            if (result > 0)
            {
                String temp = strings[st];
                strings[st] = strings[st1];
                strings[st1] = temp;
            }
        }
    }
}

int CompareStrings(const String* s1, const String* s2)
{
    assert(s1);
    assert(s2);

    char* start1 = s1->start;
    char* start2 = s2->start;

    char* end1 = s1->end;
    char* end2 = s2->end;

    while (start1 <= end1 && start2 <= end2)
    {
        if (*start1 > *start2)
            return 1;
        else if (*start1 < *start2)
            return -1;
        else
        {
            start1++;
            start2++;
        }
    }

    if(start1 <= end1)
        return 1;
    if(start2 <= end2)
        return -1;

    return 0;
}