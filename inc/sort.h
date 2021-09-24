#ifndef SORT_H_
#define SORT_H_


#include "string.h"


static enum SortDirection
{
    Forward  = 1,
    Backward = -1
};


void QSortonlyIntTest();

void BubbleSortStrings(Text* text, SortDirection direction);

bool QSort(void* ar, size_t elementSize, int left, int right, int Comparator(const void* element1, const void* element2));

int ForwardStringComparator(const void* string1, const void* string2);

int BackwardStringComparator(const void* string1, const void* string2);

void MemorySwap(char* data1, char* data2, size_t size);

void BubbleSortStrings(Text* text, SortDirection direction);

#endif