/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldmaterial.h - Header File

    Description: Material routines.

    v1.0 - 12/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_MATERIAL_H
#define _LD_MATERIAL_H

#include <stdio.h>
#include "ldobject.h"

class ldMaterial 
{
    public:

        char  ID[32];
        float Importance;
        bool  Nice;

        // ldMaterial > ldMaterial operator
        bool operator > (const ldMaterial &mat) const
        {
            assert(this != &mat);

            return (Importance > mat.Importance);
        }
};

typedef ldLinkList<ldMaterial> ldMatList;

// Parse "light" material in a RAD file
void ParseRAD_Light(FILE *fp, char *id, ldMatList *matlist);

// Parse "spotlight" material in a RAD file
void ParseRAD_Spotlight(FILE *fp, char *id, ldMatList *matlist);

// Parse "mirror" material in a RAD file
void ParseRAD_Mirror(FILE *fp, char *id, ldMatList *matlist);

// Parse "prism1" material in a RAD file
void ParseRAD_Prism1(FILE *fp, char *id, ldMatList *matlist);

// Parse "plastic" material in a RAD file
void ParseRAD_Plastic(FILE *fp, char *id, ldMatList *matlist);

// Parse "metal" material in a RAD file
void ParseRAD_Metal(FILE *fp, char *id, ldMatList *matlist);

// Parse "glass" material in a RAD file
void ParseRAD_Glass(FILE *fp, char *id, ldMatList *matlist);

#endif  // _LD_MATERIAL_H
