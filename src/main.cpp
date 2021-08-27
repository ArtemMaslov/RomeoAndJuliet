#include <stdio.h>
#include <assert.h>
#include <ctype.h>

#include "..\inc\line.h"
#include "..\inc\io.h"


const char* FileName = "formate.txt";
const char* FileOutName = "formate_out.txt";

void FormateString(Line* line);

int main()
{
    SetRussianText();

    FILE* file = fopen(FileName, "r+");

    Line line = {nullptr};

    if (file)
    {
        FILE* file_out = fopen(FileOutName, "w");

        if (file_out)
        {
            while (GetLine(file, &line))
            {
                if (IsLineEmpty(&line) == false)
                {
                    FormateString(&line);
                    WriteLineToFile(&line, file_out);
                }
                FreeMemory(&line);
            }
        }
        else
            puts("Ошибка открытия файла назначения");
    }
    else
        puts("Ошибка открытия исходного файла");
}

void FormateString(Line* line)
{
    assert(line);

    Node* node = line->node;
    
    while (node != nullptr)
    {
        char* ptr = node->fragment;
        while (*ptr)
        {
            // Удаляет пробельные символы в начале строки
            if (isspace(*ptr))
                node->fragment = ptr + 1;
            else
                break;
            ptr++;
        }

        node = node->next;
    }
}