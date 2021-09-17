#include <assert.h>
#include <stdio.h>


#include "..\inc\text.h"
#include "..\inc\string.h"


static int CompareStrings(const String* s1, const String* s2);

void SortStrings(Text* text)
{
    assert(text);

    for (int st = 0; st < text->stringsCount - 1; st++)
    {
        for (int st1 = st + 1; st1 < text->stringsCount; st1++)
        {
            int result = CompareStrings(text->strings + st, text->strings + st1);
            
            if (result > 0)
            {
                String temp = text->strings[st];
                text->strings[st] = text->strings[st1];
                text->strings[st1] = temp;
            }
        }
    }
}

void SortArray(void* ar, size_t arType, int arSize, int cmpFunction(void* el1, void* el2))
{

}

void SwapInt(int* ar, int index1, int index2)
{
    int temp = ar[index1];
    ar[index1] = ar[index2];
    ar[index2] = temp;
}

void QSort(int* ar, int left, int right)
{
    for (int st = left; st <= right; st++)
    {
        printf("%d ", ar[st]);
    }
    puts("");

    int pivotIndex = (left+right)/2;
    int pivot = ar[pivotIndex];

    int leftIndex  = left;
    int rightIndex = right;

    while (leftIndex <= rightIndex)
    {
        while (ar[leftIndex] < pivot)
            leftIndex++;
        
        while (ar[rightIndex] > pivot)
            rightIndex--;

        if (leftIndex <= rightIndex)
        {
            SwapInt(ar, leftIndex++, rightIndex--);
            leftIndex++;
            rightIndex--;
        }
    }

    if (left < rightIndex)
        QSort(ar, left, rightIndex);
    if (leftIndex < right)
        QSort(ar, leftIndex, right);
}

void QSortTest()
{
    int tests[][30] = 
    {
        {30, 2, 1, 4, 2, 3, 7, 10, 12, 16, 21, 28, 13, 15, 4, 7, 54, 7, 23, 8, 34, 87, 4, 1, 54, 6, 1 ,4 ,3 ,3},
        {1},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        {0,0,0,0,0,0},
    };

    for (int st = 0; st < sizeof(tests) / sizeof(tests[0]); st++)
    {
        for (int st1 = 0; st1 < sizeof(tests[0]) / sizeof(int); st1++)
        {
            QSort(tests[st], 0, sizeof(tests[st]) / sizeof(int)-1);
            printf("%d ", tests[st][st1]);
        }
        puts("\n");
    }
}

static int CompareStrings(const String* s1, const String* s2)
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