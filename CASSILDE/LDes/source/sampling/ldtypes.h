/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldtypes.h - Header File

    Description: Basic types definitions.

    v1.0 - 04/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_TYPES_H
#define _LD_TYPES_H

#if defined (_MSC_VER)                  // Compiling on MS Visual C++

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from MS Windows headers
#include <windows.h>                    // Include master include file for MS Windows applications
//#include <crtdbg.h>

#if (_MSC_VER <= 1200)                  // Compiling on MS Visual C++ (version 6.0 or prior)

#define for if(false) {} else for       // Fancy trick to fix the scope of variables defined in for loops

#endif  // (_MSC_VER <= 1200)
#endif  // (_MSC_VER)

// Basic types
typedef signed   char       int8;       // Signed 8 bit integer
typedef unsigned char       uint8;      // Unsigned 8 bit integer
typedef signed   short      int16;      // Signed 16 bit integer
typedef unsigned short      uint16;     // Unsigned 16 bit integer
typedef signed   long       int32;      // Signed 32 bit integer
typedef unsigned long       uint32;     // Unsigned 32 bit integer
typedef unsigned int        uint;       // Unsigned default integer

#endif  // _LD_TYPES_H
