#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "..\inc\line.h"
#include "..\inc\tree.h"
#include "..\inc\io.h"

const char* FileName = "formate.txt";
const char* FileOutName = "formate_out.txt";

bool FormateLine(Line* line);
void SortAndWriteLine(Line* line, FILE* stream);
bool FormateLine(Line* line);
void FormateLineBeginning(Line* line);
bool FormateLineEnding(LineNode* node);
void WriteTreeToFile(TreeNode* node, FILE* stream);

int main()
{
    SetRussianText();

    FILE* file = fopen(FileName, "r");


    Tree tree = {nullptr};

    if (file)
    {
        FILE* file_out = fopen(FileOutName, "w+");

        if (file_out)
        {
            Line* line = (Line*)calloc(1, sizeof(Line));
            while (GetLine(file, line))
            {
                if (IsLineEmpty(line) == false)
                {
                    if (FormateLine(line) == false)
                        break;
                    if(AddItemToTree(&tree, line) == false)
                        break;
                    line = (Line*)calloc(1, sizeof(Line));
                }
                else
                    FreeLineMemory(line);
            }

            if(tree.root)
            {
                WriteTreeToFile(tree.root, file_out);

                FreeTreeMemory(tree.root);
            }
            free(line);
        }
        else
            puts("Ошибка открытия файла назначения");
    }
    else
        puts("Ошибка открытия исходного файла");
}

void FormateLineBeginning(Line* line)
{
    assert(line);

    LineNode* node = line->node;
    
    while (node != nullptr)
    {
        char* ptr = node->fragment;
        while (*ptr)
        {
            // Удаляет пробельные символы в начале строки
            if (isspace(*ptr))
                node->fragment = ptr + 1;
            else
                return;
            ptr++;
        }
        
        node = node->next;
    }

}

bool FormateLineEnding(LineNode* node)
{
    assert(node);

    if (node->next == nullptr)
    {
        for (int st = strlen(node->fragment) - 1; st >= 0; st--)
        {
            if(isspace(node->fragment[st]))
                node->fragment[st] = '\0';
            else
                return true;
        }
        return false;
    }
    else
    {
        bool result = FormateLineEnding(node->next);
        if (!result)
        {
            free(node->next->_memory_ptr);
            free(node->next);
            node->next = nullptr;

            for (int st = strlen(node->fragment) - 1; st >= 0; st--)
            {
                if(isspace(node->fragment[st]))
                    node->fragment[st] = '\0';
                else
                    return true;
            }
            return false;
        }
    }
    
    return true;
}

bool FormateLine(Line* line)
{
    assert(line);

    FormateLineBeginning(line);

    FormateLineEnding(line->node);

    // Если не сжимать строку, то сортировка не будет правильно работать. Пример:
    // 
    // Пусть значения line1 и line2 до форматирования:
    // Пусть размер fragment 10 символов + '\0'
    //
    // Line line1 = 
    // {
    //     fragment = "1234567890"
    //     next = nullptr
    // }
    //
    // Line line2 = 
    // {
    //     fragment = "   1234567"
    //     next = 
    //     {
    //         fragment = "890"
    //         next = nullptr
    //     }
    // }
    //
    // После форматирования line1 == line2 по содержимому, но без сжатия сортировка будет считать, что line1 > line2.

    return CompressLine(line);
}

void WriteTreeToFile(TreeNode* node, FILE* stream)
{
    if (node->left == nullptr && node->right == nullptr)
    {
        for (int st = 0 ; st < node->count; st++)
            WriteLineToFile(node->line, stream);
    }
    else
    {
        if (node->left)
            WriteTreeToFile(node->left, stream);
        
        for (int st = 0 ; st < node->count; st++)
            WriteLineToFile(node->line, stream);

        if (node->right)
            WriteTreeToFile(node->right, stream);
    }
}