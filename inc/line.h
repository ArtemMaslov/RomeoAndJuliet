#ifndef DATA_MODEL_H_
#define DATA_MODEL_H_

const int MaxStringLength = 200;

struct Node
{
    char* fragment;
    char* _memory_ptr;
    Node* next;
};

struct Line
{
    Node* node;
};


bool IsLineEmpty(const Line* line);

void WriteLineToFile(const Line* line, FILE* stream);

void FreeMemory(Line* line);

#endif