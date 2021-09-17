#ifndef IO_H_
#define IO_H_


#include <stdio.h>

#include "string.h"


void SetRussianText();

bool ReadFile(Text* text, FILE* file);

void WriteStringsToFile(const Text* text, FILE* file);

long GetFileSize(FILE* file);


#endif