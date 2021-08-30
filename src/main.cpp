#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "..\inc\io.h"
#include "..\inc\formate.h"
#include "..\inc\parse.h"
#include "..\inc\sort.h"
#include "..\inc\string.h"

int main(int argc, char* argv[])
{
    SetRussianText();

    FILE* file = nullptr;
    FILE* file_out = nullptr;

    if(argc == 1)
        file = fopen(FileName, "r");
    else
        file = fopen(argv[1], "r");

    if (file)
    {
        if(argc == 1)
            file_out = fopen(FileOutName, "w+");
        else
            file_out = fopen(argv[2], "w+");

        if (file_out)
        {
            char* buffer = nullptr;
            String* strings = nullptr;
            size_t stringsCount = 0;

            if (ReadFile(&buffer, file) == false)
                return 1;

            if (ParseBuffer(buffer, &strings, &stringsCount) == false)
                return 1;

            FormateStrings(strings, stringsCount);

            SortStrings(strings, stringsCount);

            WriteStringsToFile(strings, stringsCount, file_out);
        }
        else
            puts("Ошибка открытия файла назначения");
    }
    else
        puts("Ошибка открытия исходного файла");
}