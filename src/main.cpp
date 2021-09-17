#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


#include "..\inc\text.h"
#include "..\inc\io.h"
#include "..\inc\formate.h"
#include "..\inc\parse.h"
#include "..\inc\sort.h"
#include "..\inc\string.h"


const char* FileName    = "formate.txt";
const char* FileOutName = "formate_out.txt";


int main(int argc, char* argv[])
{
    SetRussianText();
    QSortTest();
    return 0;
    FILE* file     = nullptr;
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
            Text text = {};
            text.buffer  = nullptr;
            text.strings = nullptr;
            text.stringsCount = text.nullStringsCount = text.bufferSize = 0;

            if (ReadFile(&text, file) == false)
                return 1;

            if (ParseBuffer(&text) == false)
                return 1;

            FormateStrings(&text);

            SortStrings(&text);

            WriteStringsToFile(&text, file_out);
        }
        else
            puts("Ошибка открытия файла назначения");
    }
    else
        puts("Ошибка открытия исходного файла");

    return 0;
}