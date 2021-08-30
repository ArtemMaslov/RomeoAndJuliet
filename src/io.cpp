#include <stdio.h>
#include <Windows.h>
#include <assert.h>

#include "..\inc\string.h"


void SetRussianText()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

bool ReadFile(char** buffer, FILE* file)
{
    assert(file);

    ferror(file);

    fseek(file , 0 , SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    *buffer = (char*)calloc(fileSize, sizeof(char));

    if (*buffer == nullptr)
    {
        puts("Ошибка выделения памяти");
        return false;
    }

    size_t readed = fread(*buffer, sizeof(char), fileSize, file);

    /*if (readed != fileSize)
    {
        puts("Ошибка чтения данных");
        return false;
    }*/

    return true;
}

void WriteStringsToFile(const String* strings, const size_t stringsCount, FILE* file)
{
    assert(strings);
    assert(file);
    
    ferror(file);

    for (int st = 0; st < stringsCount; st++)
    {
        size_t count = strings[st].end - strings[st].start + 1;
        if (strings[st].start <= strings[st].end)
        {
            size_t wroteCount = fwrite(strings[st].start, sizeof(char), count, file);
            fputc('\n', file);

            if (wroteCount != count)
            {
                puts("Ошибка записи в файл");
                return;
            }
        }
    }
}