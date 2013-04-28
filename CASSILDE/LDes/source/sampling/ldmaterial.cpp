/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldmaterial.cpp - Implementation File

    Description: Material routines.

    v1.0 - 12/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_MATERIAL_CPP
#define _LD_MATERIAL_CPP

#include "ldparser.h"
#include "ldmaterial.h"
#include <string.h>

#define FMAX(A,B) ((A)>(B)?(A):(B))

// Parse "light" material in a RAD file
void ParseRAD_Light(FILE *fp, char *id, ldMatList *matlist)
{
    SkipLines(fp, 3);

    ldMaterial *mat = new ldMaterial;

    strcpy(mat->ID, id);
    mat->Nice = true;
    mat->Importance = 1.0;

    matlist->AddNode(mat);
}

// Parse "spotlight" material in a RAD file
void ParseRAD_Spotlight(FILE *fp, char *id, ldMatList *matlist)
{
    SkipLines(fp, 3);

    ldMaterial *mat = new ldMaterial;

    strcpy(mat->ID, id);
    mat->Nice = true;
    mat->Importance = 1.0;

    matlist->AddNode(mat);
}

// Parse "mirror" material in a RAD file
void ParseRAD_Mirror(FILE *fp, char *id, ldMatList *matlist)
{
    SkipLines(fp, 3);

    ldMaterial *mat = new ldMaterial;

    strcpy(mat->ID, id);
    mat->Nice = true;
    mat->Importance = 1.0;

    matlist->AddNode(mat);
}

// Parse "prism1" material in a RAD file
void ParseRAD_Prism1(FILE *fp, char *id, ldMatList *matlist)
{
    SkipLines(fp, 3);

    ldMaterial *mat = new ldMaterial;

    strcpy(mat->ID, id);
    mat->Nice = true;
    mat->Importance = 1.0;

    matlist->AddNode(mat);
}

// Parse "plastic" material in a RAD file
void ParseRAD_Plastic(FILE *fp, char *id, ldMatList *matlist)
{
    char  buffer[256];
    char  seps[]  = " \t\n";

    SkipLines(fp, 2);
    fgets(buffer, 256, fp);
    GetFirstToken(buffer, seps);
    GetNextToken();
    GetNextToken();
    GetNextToken();

    float spec  = GetFloatFromToken(GetNextToken());
    float rough = GetFloatFromToken(GetNextToken());

    ldMaterial *mat = new ldMaterial;

    strcpy(mat->ID, id);
    mat->Nice = (spec > 0.035 || rough < 0.1) ? true : false;
    if (mat->Nice)
    {
        mat->Importance = FMAX((spec - 0.035) / 0.035, (0.1 - rough) / 0.1);
        if (mat->Importance > 1.0) mat->Importance = 1.0;
    } else
        mat->Importance = 0.0;

    matlist->AddNode(mat);
}

// Parse "metal" material in a RAD file
void ParseRAD_Metal(FILE *fp, char *id, ldMatList *matlist)
{
    char  buffer[256];
    char  seps[]  = " \t\n";

    SkipLines(fp, 2);
    fgets(buffer, 256, fp);
    GetFirstToken(buffer, seps);
    GetNextToken();
    GetNextToken();
    GetNextToken();

    float spec  = GetFloatFromToken(GetNextToken());
    float rough = GetFloatFromToken(GetNextToken());

    ldMaterial *mat = new ldMaterial;

    strcpy(mat->ID, id);
    mat->Nice = (spec > 0.75 || rough < 0.25) ? true : false;
    if (mat->Nice)
    {
        mat->Importance = FMAX((spec - 0.75) / 0.25, (0.25 - rough) / 0.25);
        if (mat->Importance > 1.0) mat->Importance = 1.0;
    } else
        mat->Importance = 0.0;

    matlist->AddNode(mat);
}

// Parse "glass" material in a RAD file
void ParseRAD_Glass(FILE *fp, char *id, ldMatList *matlist)
{
    SkipLines(fp, 3);

    ldMaterial *mat = new ldMaterial;

    strcpy(mat->ID, id);
    mat->Nice = true;
    mat->Importance = 1.0;

    matlist->AddNode(mat);
}

#endif  // _LD_MATERIAL_CPP
