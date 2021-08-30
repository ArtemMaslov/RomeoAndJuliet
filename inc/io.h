#ifndef IO_H_
#define IO_H_


#include <stdio.h>

#include "string.h"


const char* FileName = "formate.txt";
const char* FileOutName = "formate_out.txt";


void SetRussianText();

bool ReadFile(char** buffer, FILE* file);

void WriteStringsToFile(const String* strings, const size_t stringsCount, FILE* file);


#endif