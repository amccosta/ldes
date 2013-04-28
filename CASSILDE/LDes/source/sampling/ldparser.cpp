/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldparser.cpp - Implementation File

    Description: Auxiliary parser routines.

    v1.0 - 12/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_PARSER_CPP
#define _LD_PARSER_CPP

#include <stdlib.h>
#include <math.h>

#include "ldparser.h"

// Auxiliary string for functions
static char LD_AUX_STRING[256];

// Extracts file name from full path
void GetFileNameFromFullPath(      char *fileName,
                             const char *filePath)
{
    char *chPos1 = strrchr(filePath, '/');
    char *chPos2 = strrchr(filePath, '\\');

    char  *chPos;
    uint8  index;

    if(chPos1 == NULL && chPos2 == NULL) index = 0;
    else
    {
        chPos = (chPos1 > chPos2) ? chPos1 : chPos2;
        index = uint8(chPos - filePath + 1);
    }

    char *extPos = strrchr(filePath, '.');
    uint8 extLen = (extPos == NULL) ? uint8(0) : uint8(strlen(filePath) - (extPos - filePath));
    uint8 cpyLen = uint8(strlen(&filePath[index]) - extLen);

    strncpy(fileName, &filePath[index], cpyLen);
    fileName[cpyLen] = 0;
}

// Cuts extension from fine name
void CutExtensionFromFileName(      char *fileName,
                              const char *fileNameExt)
{
    char *extPos  = strrchr(fileNameExt, '.');
    uint8 nameLen = (extPos == NULL) ? uint8(strlen(fileNameExt)) : uint8(extPos - fileNameExt);

    strncpy(fileName, fileNameExt, nameLen);
    fileName[nameLen] = 0;
}

// Gets the first token from a string
char *GetFirstToken(const char *str,
                    const char *del)
{
    if(str == NULL) return NULL;

    strcpy(LD_AUX_STRING, del);

    return strtok(const_cast<char *>(str), del);
}

// Gets the next token from a string
char *GetNextToken(const char *del)
{
    if(del != NULL) strcpy(LD_AUX_STRING, del);

    return strtok(NULL, LD_AUX_STRING);
}

// Gets a float from token
float GetFloatFromToken(const char *str)
{
    return float(atof(str));
}

// Gets an unsigned long int from token
uint32 GetUInt32FromToken(const char *str)
{
    return uint32(atol(str));
}

// Skips lines until the token is reached
void SkipLinesUntilToken(      FILE *fp,
                         const char *token)
{
    if(fp != NULL && token != NULL)
    {
        char buffer[256];

        do
        {
            if(fgets(buffer, 256, fp) == NULL) break;
        }while(strstr(buffer, token) == NULL);
    }
}

// Skips a specified number of lines
void SkipLines(      FILE  *fp,
               const uint32 nlines)
{
    if(fp != NULL)
    {
        char buffer[256];
        uint32 i = nlines;

        while(i)
        {
            if(fgets(buffer, 256, fp) == NULL) break;
            i--;
        }
    }
}

#endif  // _LD_PARSER_CPP
