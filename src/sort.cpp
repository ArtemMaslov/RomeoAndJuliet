#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "..\inc\text.h"
#include "..\inc\string.h"
#include "..\inc\sort.h"
#include "..\inc\config.h"


static int  CompareStrings(const String* s1, const String* s2, SortDirection direction);
static void PrintInt(int* ar, int left, int right);
static void SwapInt(int* ar, int index1, int index2);
static int  IntComparator(const void* element1, const void* element2);
static void QSortOnlyInt(int* ar, int left, int right);


void BubbleSortStrings(Text* text, SortDirection direction)
{
    assert(text);

    for (int st = 0; st < text->stringsCount - 1; st++)
    {
        for (int st1 = st + 1; st1 < text->stringsCount; st1++)
        {
            int result = CompareStrings(text->strings + st, text->strings + st1, direction);
            
            if (result > 0)
            {
                String temp = text->strings[st];
                text->strings[st] = text->strings[st1];
                text->strings[st1] = temp;
            }
        }
    }
}

void MemorySwap(char* data1, char* data2, size_t size)
{
    assert(data1);
    assert(data2);

    while (size > 0)
    {
        if (size >= sizeof(int64_t))
        {
            int64_t val = *((int64_t*)data1);
            *((int64_t*)data1) = *((int64_t*)data2);
            *((int64_t*)data2) = val;
            data1 += sizeof(int64_t);
            data2 += sizeof(int64_t);
            size  -= sizeof(int64_t);
        }
        else if (size >= sizeof(int32_t))
        {
            int32_t val = *((int32_t*)data1);
            *((int32_t*)data1) = *((int32_t*)data2);
            *((int32_t*)data2) = val;
            data1 += sizeof(int32_t);
            data2 += sizeof(int32_t);
            size  -= sizeof(int32_t);
        }
        else if (size >= sizeof(int16_t))
        {
            int16_t val = *((int16_t*)data1);
            *((int16_t*)data1) = *((int16_t*)data2);
            *((int16_t*)data2) = val;
            data1 += sizeof(int16_t);
            data2 += sizeof(int16_t);
            size  -= sizeof(int16_t);
        }
        else if (size >= sizeof(int8_t))
        {
            int8_t val = *((int8_t*)data1);
            *((int8_t*)data1) = *((int8_t*)data2);
            *((int8_t*)data2) = val;
            data1 += sizeof(int8_t);
            data2 += sizeof(int8_t);
            size  -= sizeof(int8_t);
        }
    }
}

bool QSort(void* ar, size_t elementSize, int left, int right, int Comparator(const void* element1, const void* element2))
{
    assert(ar);

    int pivotIndex      = (left+right)/2;
    int pivotIndexLeft  = pivotIndex - 1;
    int pivotIndexRight = pivotIndex + 1;

    char* pivot = (char*)calloc(1, elementSize);
    if(pivot == nullptr)
        return false;

    pivot = (char*)memcpy(pivot, (char*)ar + pivotIndex * elementSize, elementSize);
    if(pivot == nullptr)
        return false;

    int leftIndex  = left;
    int rightIndex = right;
    
    //PrintInt((int*)(ar), left, right);

    while (leftIndex <= pivotIndexLeft && rightIndex >= pivotIndexRight)
    {
        while (Comparator((char*)ar + leftIndex * elementSize, pivot) < 0)
            leftIndex++;

        if (leftIndex > pivotIndexLeft)
            break;
        
        if(Comparator((char*)ar + leftIndex * elementSize, pivot) == 0)
        {
            MemorySwap((char*)ar + leftIndex * elementSize, (char*)ar + pivotIndexLeft * elementSize, elementSize);
            //PrintInt((int*)(ar), left, right);
            pivotIndexLeft--;
            if (pivotIndexLeft <= 0)
                break;
            continue;
        }
        
        while (Comparator((char*)ar + rightIndex * elementSize, pivot) > 0)
            rightIndex--;
        
        if (rightIndex < pivotIndexRight)
            break;

        if (Comparator((char*)ar + rightIndex * elementSize, pivot) == 0)
        {
            MemorySwap((char*)ar + rightIndex * elementSize, (char*)ar + pivotIndexRight * elementSize, elementSize);
            //PrintInt((int*)(ar), left, right);
            pivotIndexRight++;
            if (pivotIndexRight >= right)
                break;
            continue;
        }
        
        MemorySwap((char*)ar + leftIndex * elementSize, (char*)ar + rightIndex * elementSize, elementSize);
        //PrintInt((int*)(ar), left, right);
        leftIndex++;
        rightIndex--;
    }

    while (leftIndex <= pivotIndexLeft)
    {
        if (Comparator((char*)ar + leftIndex * elementSize, pivot) == 0)
        {
            MemorySwap((char*)ar + leftIndex * elementSize, (char*)ar + pivotIndexLeft * elementSize, elementSize);
            //PrintInt((int*)(ar), left, right);
            pivotIndexLeft--;
        }
        if (Comparator((char*)ar + leftIndex * elementSize, pivot) > 0)
        {
            pivotIndexRight--;
            MemorySwap((char*)ar + leftIndex * elementSize, (char*)ar + pivotIndexRight * elementSize, elementSize);
            //PrintInt((int*)(ar), left, right);
            continue;
        }
        leftIndex++;
    }

    while (pivotIndexRight <= rightIndex)
    {
        if (Comparator((char*)ar + rightIndex * elementSize, pivot) == 0)
        {
            MemorySwap((char*)ar + rightIndex * elementSize, (char*)ar + pivotIndexRight * elementSize, elementSize);
            //PrintInt((int*)(ar), left, right);
            pivotIndexRight++;
        }
        if (Comparator((char*)ar + rightIndex * elementSize, pivot) < 0)
        {
            pivotIndexLeft++;
            MemorySwap((char*)ar + rightIndex * elementSize, (char*)ar + pivotIndexLeft * elementSize, elementSize);
            //PrintInt((int*)(ar), left, right);
            continue;
        }
        rightIndex--;
    }

    free(pivot);

    bool result = true;
    if (left < pivotIndexLeft)
        result = QSort(ar, elementSize, left, pivotIndexLeft, Comparator);
    if (pivotIndexRight < right && result)
        result = QSort(ar, elementSize, pivotIndexRight, right, Comparator);
    return result;
}

int  ForwardStringComparator(const void* string1, const void* string2)
{
    assert(string1);
    assert(string2);

    return CompareStrings((String*)string1, (String*)string2, Forward);
}

int  BackwardStringComparator(const void* string1, const void* string2)
{
    assert(string1);
    assert(string2);

    return CompareStrings((String*)string1, (String*)string2, Backward);
}

static int CompareStrings(const String* s1, const String* s2, SortDirection direction)
{
    assert(s1);
    assert(s2);

    char* start1 = s1->start;
    char* start2 = s2->start;

    char* end1   = s1->end;
    char* end2   = s2->end;

    if(direction == Forward)
    {

#ifdef SKIP_NOT_ALPHA_SYMVOLS
        while (start1 <= end1 && !isalpha(*start1))
            start1++;

        while (start2 <= end2 && !isalpha(*start2))
            start2++;
#endif // SKIP_NOT_ALPHA_SYMVOLS

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
    }
    else
    {
        
#ifdef SKIP_NOT_ALPHA_SYMVOLS
        while (start1 <= end1 && !isalpha(*end1))
            end1--;

        while (start2 <= end2 && !isalpha(*end2))
            end2--;
#endif // SKIP_NOT_ALPHA_SYMVOLS

        while (start1 <= end1 && start2 <= end2)
        {
            if (*end1 > *end2)
                return 1;
            else if (*end1 < *end2)
                return -1;
            else
            {
                end1--;
                end2--;
            }
        }
    }

    if(start1 <= end1)
        return 1;
    if(start2 <= end2)
        return -1;

    return 0;
}

//***\\---//***\\-------------//***\\---//***//
//***\\---//***\\-------------//***\\---//***//
//***\\---//***\\-QSort_Tests-//***\\---//***//
//***\\---//***\\-------------//***\\---//***//
//***\\---//***\\-------------//***\\---//***//

static void SwapInt(int* ar, int index1, int index2)
{
    assert(ar);

    int temp = ar[index1];
    ar[index1] = ar[index2];
    ar[index2] = temp;
}

static void PrintInt(int* ar, int left, int right)
{
    assert(ar);

    for (int st = left; st <= right; st++)
        printf("%2d ", ar[st]);
    puts("");
}

static void QSortOnlyInt(int* ar, int left, int right)
{
    assert(ar);

    int pivotIndex = (left+right)/2;
    int pivotIndexLeft = pivotIndex - 1;
    int pivotIndexRight = pivotIndex + 1;
    int pivot = ar[pivotIndex];

    int leftIndex  = left;
    int rightIndex = right;

    //puts("Исходные данные:");
    //PrintInt(ar, left, right);

    while (leftIndex <= pivotIndexLeft && rightIndex >= pivotIndexRight)
    {
        while (ar[leftIndex] < pivot)
            leftIndex++;

        if (leftIndex > pivotIndexLeft)
            break;

        if (ar[leftIndex] == pivot)
        {
            SwapInt(ar, leftIndex, pivotIndexLeft);
            //puts("ar[leftIndex] == pivot:");
            //PrintInt(ar, left, right);
            pivotIndexLeft--;
            if (pivotIndexLeft <= 0)
                break;
            continue;
        }
        
        while (ar[rightIndex] > pivot)
            rightIndex--;
        
        if (rightIndex < pivotIndexRight)
            break;

        if (ar[rightIndex] == pivot)
        {
            SwapInt(ar, rightIndex, pivotIndexRight);
            //puts("ar[rightIndex] == pivot:");
            //PrintInt(ar, left, right);
            pivotIndexRight++;
            if (pivotIndexRight >= right)
                break;
            continue;
        }
        
        SwapInt(ar, leftIndex, rightIndex);
        //puts("Standart swap:");
        //PrintInt(ar, left, right);
        leftIndex++;
        rightIndex--;
    }

    while (leftIndex <= pivotIndexLeft)
    {
        if (ar[leftIndex] == pivot)
        {
            SwapInt(ar, leftIndex, pivotIndexLeft);
           // PrintInt(ar, left, right);
            pivotIndexLeft--;
        }
        if (ar[leftIndex] > pivot)
        {
            SwapInt(ar, leftIndex, --pivotIndexRight);
            //PrintInt(ar, left, right);
            continue;
        }
        leftIndex++;
    }
    
    while (pivotIndexRight <= rightIndex)
    {
        if (ar[rightIndex] == pivot)
        {
            SwapInt(ar, rightIndex, pivotIndexRight);
            //PrintInt(ar, left, right);
            pivotIndexRight++;
        }
        if (ar[rightIndex] < pivot)
        {
            SwapInt(ar, rightIndex, ++pivotIndexLeft);
            //PrintInt(ar, left, right);
            continue;
        }
        rightIndex--;
    }
    if (left < pivotIndexLeft)
        QSortOnlyInt(ar, left, pivotIndexLeft);
    if (pivotIndexRight < right)
        QSortOnlyInt(ar, pivotIndexRight, right);
}

void QSortonlyIntTest()
{
    int tests[][40] = 
    {
        {30, 2, 1, 4, 2, 3, 7, 10, 12, 16, 21, 28, 13, 15, 4, 7, 54, 7, 23, 8, 34, 87, 4, 1, 54, 6, 1 ,4 ,3 ,3},
        {1},
        {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
        {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
        {0,0,0,0,0,0},
        {6, 3, 56, 3, 5, 12, 01, 3, 1, 3, 5 ,1 ,23 , 2, 2, 2, 24, 0 ,5 ,43 ,},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {-10, 12, 124, 624, 6, 23, 654, 23, 5, 23, 654, 12, 3},
        {1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
        {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8,},
        {-1, -2, -3, 54, 2, 1, 13, 53, 23, 5, 1, 2, 3, 4, 5, 3, 2, 1, 4 ,5, 6, 7, 0, -1, -1, -2, -3, -4, -5, -4, -4, -4, -5,-6},
    };

    for (int st = 0; st < sizeof(tests) / sizeof(tests[0]); st++)
    {
            if(QSort((char*)tests[st], sizeof(int),  0, sizeof(tests[st]) / sizeof(int)-1, IntComparator) ==false)
                puts("Error");
        
            //QSort1(tests[st], 0, sizeof(tests[st]) / sizeof(int)-1);
            PrintInt(tests[st], 0, sizeof(tests[st]) / sizeof(int) -1);
        puts("");
    }
}

static int IntComparator(const void* element1, const void* element2)
{
    assert(element1);
    assert(element2);

    int val1 = *((int*)element1);
    int val2 = *((int*)element2);

    if (val1 == val2)
        return 0;
    else if (val1 > val2)
        return 1;
    else
        return -1;
}