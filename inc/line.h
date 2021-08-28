#ifndef DATA_MODEL_H_
#define DATA_MODEL_H_

const int MaxStringLength = 200;

struct LineNode
{
    char* fragment;
    char* _memory_ptr;
    LineNode* next;
};

struct Line
{
    LineNode* node;
    size_t strLen = 0;
};

char* GetLine(FILE* stream, Line* line);

bool IsLineEmpty(const Line* line);

void WriteLineToFile(Line* line, FILE* stream);

void FreeLineMemory(Line* line);

bool CompressLine(Line* line);

bool CopyLine(Line* dest, Line* src);

int CompareLines(const Line* line1, const Line* line2);

#endif