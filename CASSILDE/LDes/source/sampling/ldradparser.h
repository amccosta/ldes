/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldradparser.h - Header File

    Description: RAD parser routines.

    v1.0 - 12/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation

    v1.1 - 15/03/2002 by Pedro Cruz (pedromcruz@hotmail.com)
         - Added the sphere to the parser
*/

#ifndef _LD_RAD_PARSER_H
#define _LD_RAD_PARSER_H

#include "ldobject.h"
#include "ldmaterial.h"

// Parses a RAD file
bool ParseRADFile(const char      *pathFileName,        // File path and name
                        ldMatList *matlist,             // Material list
                        ldObjList *objlist);            // Object list

#endif  // _LD_RAD_PARSER_H
