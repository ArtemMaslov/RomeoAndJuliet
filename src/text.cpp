#include <stdlib.h>
#include <assert.h>


#include "..\inc\text.h"
#include "..\inc\io.h"
#include "..\inc\formate.h"
#include "..\inc\parse.h"
#include "..\inc\sort.h"
#include "..\inc\string.h"


int ReadText(Text* text, FILE* input)
{
    assert(text);
    assert(input);

    FreeTextStructure(text);
    text->stringsCount = text->nullStringsCount = text->bufferSize = 0;

    if (ReadFile(text, input) == false)
        return 1;

    if (ParseBuffer(text) == false)
        return 1;

    FormateStrings(text);
}

void SortTextAndWriteToFile(Text* text, FILE* output)
{
    assert(text);
    assert(output);

    qsort(text->strings, text->stringsCount, sizeof(text->strings[0]), ForwardStringComparator);

    WriteStringsToFile(text, output);

    WriteSeparatorLinesToFile(output);
            
    QSort(text->strings, sizeof(text->strings[0]), 0, text->stringsCount-1, BackwardStringComparator);
    
    WriteStringsToFile(text, output);
    
    WriteSeparatorLinesToFile(output);
    
    fwrite(text->buffer, sizeof(char), text->bufferSize, output);
            
    WriteSeparatorLinesToFile(output);

}

void FreeTextStructure(Text* text)
{
    assert(text);

    if(text->strings)
        free(text->strings);
    if(text->buffer)
        free(text->buffer);
}
