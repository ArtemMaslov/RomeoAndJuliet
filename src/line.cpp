#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>

#include "..\inc\line.h"
#include "..\inc\io.h"

bool IsLineEmpty(const Line* line)
{
    assert(line);

    bool LineEmpty = true;
    Node* node = line->node;

    while (node != nullptr)
    {
        char* ptr = node->fragment;
        while (*ptr)
        {
            if (isspace(*ptr) == false)
            {
                LineEmpty = false;
                break;
            }
            ptr++;
        }
        if (LineEmpty == false)
            break;
        node = node->next;
    }

    return LineEmpty;
}

void WriteLineToFile(const Line* line, FILE* stream)
{
    assert(line);
    assert(stream);
    
    ferror(stream);

    Node* node = line->node;

    while (node != nullptr)
    {
        if (fputs(node->fragment, stream) == EOF)
        {
            puts("Ошибка записи файла, программа завершит свою работу.");
            exit(0);
        }
        node = node->next;
    }
}

void FreeMemory(Line* line)
{
    assert(line);

    Node* node = line->node;

    while (node != nullptr)
    {
        Node* ptr = node;
        node = node->next;

        free(ptr->_memory_ptr);
        free(ptr);
    }

    line->node = nullptr;
}
