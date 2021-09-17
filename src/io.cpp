#include <stdio.h>
#include <Windows.h>
#include <assert.h>


#include "..\inc\text.h"
#include "..\inc\string.h"
#include "..\inc\io.h"


void SetRussianText()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
}

bool ReadFile(Text* text, FILE* file)
{
    assert(text);
    assert(file);

    text->bufferSize = GetFileSize(file);

    text->buffer = (char*)calloc(text->bufferSize + 1, sizeof(char));

    if (text->buffer == nullptr)
    {
        puts("Ошибка выделения памяти");
        return false;
    }

    size_t readed = fread(text->buffer, sizeof(char), text->bufferSize, file);

    if (readed != text->bufferSize)
    {
        puts("Ошибка чтения данных");
        return false;
    }

    return true;
}

void WriteStringsToFile(const Text* text, FILE* file)
{
    assert(text);
    assert(file);

    for (size_t st = 0; st < text->stringsCount; st++)
    {
        size_t count = text->strings[st].end - text->strings[st].start + 1;
        if (text->strings[st].start <= text->strings[st].end)
        {
            size_t wroteCount = fwrite(text->strings[st].start, sizeof(char), count, file);
            fputc('\n', file);

            if (wroteCount != count)
            {
                puts("Ошибка записи в файл");
                return;
            }
        }
    }
}

long GetFileSize(FILE* file)
{
    assert(file);

    fseek(file , 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    return fileSize;
}