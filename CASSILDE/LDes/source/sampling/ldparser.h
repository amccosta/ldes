/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldparser.h - Header File

    Description: Auxiliary parser routines.

    v1.0 - 12/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_PARSER_H
#define _LD_PARSER_H

#include <stdio.h>
#include <string.h>
#include "ldtypes.h"

// Extracts file name from full path
void GetFileNameFromFullPath(      char *,              // File name (without extension)
                             const char *);             // Path to extract name

// Cuts extension from fine name
void CutExtensionFromFileName(      char *,             // File name with extension removed
                              const char *);            // File name

// Gets the first token from a string
char *GetFirstToken(const char *,                       // String containing token(s)
                    const char *);                      // String of delimiter characters

// Gets the next token from a string
char *GetNextToken(const char * = NULL);                // String of delimiter characters

// Gets a float from token
float GetFloatFromToken(const char *);                  // String containing token

// Gets an unsigned long int from token
uint32 GetUInt32FromToken(const char *);                // String containing token

// Skips lines until the token is reached
void SkipLinesUntilToken(      FILE *,                  // File pointer
                         const char *);                 // Token to be found

// Skips a specified number of lines
void SkipLines(      FILE *,                            // File pointer
               const uint32);                           // Number of lines to skip

#endif  // _LD_PARSER_H
