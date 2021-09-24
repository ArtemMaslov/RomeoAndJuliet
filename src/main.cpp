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
            
            ReadText(&text, file);

            SortTextAndWriteToFile(&text, file_out);

            FreeTextStructure(&text);
        }
        else
            puts("Ошибка открытия файла назначения");
    }
    else
        puts("Ошибка открытия исходного файла");

    return 0;
}