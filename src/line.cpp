#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "..\inc\line.h"
#include "..\inc\io.h"

#define CHECK_MEMORY(ptr, line, copy)   if (ptr == nullptr)\
                                        {\
                                            puts("Ошибка выделения памяти");\
                                            if (line)\
                                                FreeLineMemory(line);\
                                            if (copy)\
                                                FreeLineMemory(copy);\
                                            return false;\
                                        }

char* GetLine(FILE* stream, Line* line)
{
    assert(stream);
    assert(line);
    
    ferror(stream);
    
    char* result = nullptr;
    char* index  = nullptr;

    line->strLen = 0;
    line->node = (LineNode*)calloc(1, sizeof(LineNode));
    line->node->next = nullptr;

    LineNode* currentNode = line->node;

    do
    {
        if (currentNode == nullptr)
        {
            puts("Ошибка выделения памяти");
            FreeLineMemory(line);
            return nullptr;
        }

        currentNode->fragment = (char*)calloc(MaxStringLength, sizeof(char));
        currentNode->_memory_ptr = currentNode->fragment;

        if (currentNode->fragment == nullptr)
        {
            puts("Ошибка выделения памяти");
            FreeLineMemory(line);
            return nullptr;
        }

        result = fgets(currentNode->fragment, MaxStringLength, stream);

        if (result)
        {
            line->strLen += strlen(currentNode->fragment);
            index = strchr(currentNode->fragment, '\n');
            if (index == nullptr)
            {
                currentNode->next = (LineNode*)calloc(1, sizeof(LineNode));
                currentNode = currentNode->next;
            }
            else
                *index = '\0';
        }
    }
    while (index == nullptr && result);

    return result;
}

bool IsLineEmpty(const Line* line)
{
    assert(line);

    bool LineEmpty = true;
    LineNode* node = line->node;

    while (node)
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

void WriteLineToFile(Line* line, FILE* stream)
{
    assert(line);
    assert(stream);
    
    ferror(stream);

    LineNode* node = line->node;

    while (node)
    {
        if (fputs(node->fragment, stream) == EOF)
        {
            puts("Ошибка записи файла, программа завершит свою работу.");
            FreeLineMemory(line);
            exit(0);
        }
        node = node->next;
    }
    fputc('\n', stream);
}

void FreeLineMemory(Line* line)
{
    assert(line);

    LineNode* node = line->node;

    while (node)
    {
        LineNode* ptr = node;
        node = node->next;

        free(ptr->_memory_ptr);
        free(ptr);
    }

    line->node = nullptr;
}

bool CompressLine(Line* line)
{
    Line copy = {nullptr, 0};

    CopyLine(&copy, line);

    FreeLineMemory(line);

    LineNode* src  = copy.node;
    LineNode** dest = &(line->node);
    
    *dest = (LineNode*)calloc(1, sizeof(LineNode));

    //CHECK_MEMORY(dest, line, &copy)
    if (dest == nullptr)
    {
        puts("Ошибка выделения памяти");
        if (line)
            FreeLineMemory(line);
        FreeLineMemory(&copy);
        return false;
    }

    (*dest)->fragment = (char*)calloc(MaxStringLength, sizeof(char));
    (*dest)->_memory_ptr = (*dest)->fragment;
    
    if ((*dest)->fragment == nullptr)
    {
        puts("Ошибка выделения памяти");
        if (line)
            FreeLineMemory(line);
        FreeLineMemory(&copy);
        return false;
    }
    //CHECK_MEMORY((*dest)->fragment, line, &copy)

    size_t srcCopied = 0;
    char* ptr = src->fragment;

    while (src)
    {
        size_t destLength = strlen((*dest)->fragment);
        size_t srcLength  = strlen(src->fragment);

        if (destLength + 1 == MaxStringLength)
        {
            (*dest)->next = (LineNode*)calloc(1, sizeof(LineNode));
            dest       = &((*dest)->next);
            
            if (dest == nullptr)
            {
                puts("Ошибка выделения памяти");
                if (line)
                    FreeLineMemory(line);
                FreeLineMemory(&copy);
                return false;
            }
            //CHECK_MEMORY(dest, line, &copy)

            (*dest)->fragment    = (char*)calloc(MaxStringLength, sizeof(char));
            (*dest)->_memory_ptr = (*dest)->fragment;
            
            if ((*dest)->fragment == nullptr)
            {
                puts("Ошибка выделения памяти");
                if (line)
                    FreeLineMemory(line);
                FreeLineMemory(&copy);
                return false;
            }
            //CHECK_MEMORY((*dest)->fragment, line, &copy)

            destLength = 0;
        }

        strncat((*dest)->fragment, ptr, MaxStringLength - destLength - 1);
        size_t newDestLength = strlen((*dest)->fragment);
        srcCopied += newDestLength - destLength;
        ptr += newDestLength - destLength;
        
        assert(srcCopied<=srcLength);

        if (srcCopied == srcLength)
        {
            src = src->next;
            if(src)
                ptr = src->fragment;
            srcCopied = 0;
        }
    }

    return true;
}

bool CopyLine(Line* dest_line, Line* src_line)
{
    dest_line->strLen = src_line->strLen;

    LineNode* src  = src_line->node;
    LineNode** dest = &(dest_line->node);
    
    while (src)
    {
        *dest = (LineNode*)calloc(1, sizeof(LineNode));
        CHECK_MEMORY((*dest), dest_line, nullptr)
            
        (*dest)->fragment = (char*)calloc(MaxStringLength, sizeof(char));
        (*dest)->_memory_ptr = (*dest)->fragment;
        
        CHECK_MEMORY((*dest)->fragment, dest_line, nullptr)

        strncpy((*dest)->fragment, src->fragment, MaxStringLength - 1);

        src  = src->next;
        dest = &((*dest)->next);
    }

    return true;
}

int CompareLines(const Line* line1, const Line* line2)
{
    assert(line1);
    assert(line2);

    LineNode* node1 = line1->node;
    LineNode* node2 = line2->node;

    while (node1 && node2)
    {
        int result = strcmp(node1->fragment, node2->fragment);

        if (result)
            return result;
        else
        {
            node1 = node1->next;
            node2 = node2->next;
        }
    }
    
    if (node1 != nullptr)
        return 1;
    else if (node2 != nullptr)
        return -1;
    else
        return 0;
}