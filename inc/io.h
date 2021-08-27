/**
* \file
* \brief Input, output functions file
* \author Maslov Artem
* \version 1.0.0.0
* \date 20 August 2021
*/
#ifndef IO_H_
#define IO_H_

#include "line.h"

/// Text and background colors for console
enum ConsoleColors
{
    BLACK = 0,
    DARK_BLUE = 1,
    DARK_GREEN = 2,
    DARK_CYAN = 3,
    DARK_RED = 4,
    DARK_VIOLET = 5,
    DARK_YELLOW = 6,
    DARK_WHITE = 7,
    GREY = 8,
    BLUE = 9,
    GREEN = 10,
    CYAN = 11,
    RED = 12,
    VIOLET = 13,
    YELLOW = 14,
    WHITE = 15
};

/**
* \brief Input reading function.
*
* The function reads the following line from the input buffer.
* 
* \warning If input line bigger than buffer length, function will ignore input line ending.
* 
* \param[in]  length Maximum line length (buffer size).
* \param[in]  stream Input stream.
* 
* \param[out] buffer Input line.
* 
* \return nullptr in case of error, else pointer to readed string
*/
char* GetString(char* buffer, const int length, FILE* stream);

/**
* \brief Set color for text and background in console
*
* Full list of colors avaliable in config.h
*
* \param[in] text Text color
* \param[in] background Background color
*/
void SetColor(const int text, const int background);


/**
* \brief Outputs colored text
*
* \param[in] textColor text color
* \param[in] text Text
*/
void PutsColorText(int textColor, const char* text);

char* GetLine(FILE* stream, Line* line);

void SetRussianText();

#endif // !IO_H_
