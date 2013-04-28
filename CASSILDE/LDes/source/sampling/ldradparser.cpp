/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldradparser.cpp - Implementation File

    Description: RAD parser routines.

    v1.0 - 12/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation

    v1.1 - 15/03/2002 by Pedro Cruz (pedromcruz@hotmail.com)
         - Added the sphere to the parser
*/

#ifndef _LD_RAD_PARSER_CPP
#define _LD_RAD_PARSER_CPP

#include "ldparser.h"
#include "ldradparser.h"

// Parses a RAD file
bool ParseRADFile(const char      *pathFileName,
                        ldMatList *matlist,
                        ldObjList *objlist)
{
    FILE *fp = fopen(pathFileName, "rt");
    if(fp == NULL) return false;

    char  buffer[256];
    char  seps[]  = " \t\n";
    char  modifier[32];
    char  type[32];
    char  identifier[32];
    char *str;

    ldVector3 *varray     = NULL;
    uint32     vsize      = 0;
    uint32     nvert      = 0;
    float      importance = 0.0f;
    bool       nice       = false;

    while(!feof(fp))
    {
        if(fgets(buffer, 256, fp) == NULL) break;

        if(buffer[0] == '#') continue;      // Comment

        str = GetFirstToken(buffer, seps);

        if(str == NULL) continue;          // Empty line

        strcpy(modifier,   str);
        strcpy(type,       GetNextToken());
        strcpy(identifier, GetNextToken());

        if(!strcmp(modifier, "void"))
        {
                 if(!strcmp(type, "light"     )) ParseRAD_Light    (fp, identifier, matlist);
            else if(!strcmp(type, "illum"     )) SkipLines         (fp, 3);
            else if(!strcmp(type, "glow"      )) SkipLines         (fp, 3);
            else if(!strcmp(type, "spotlight" )) ParseRAD_Spotlight(fp, identifier, matlist);
            else if(!strcmp(type, "mirror"    )) ParseRAD_Mirror   (fp, identifier, matlist);
            else if(!strcmp(type, "prism1"    )) ParseRAD_Prism1   (fp, identifier, matlist);
            else if(!strcmp(type, "prism2"    )) SkipLines         (fp, 3);
            else if(!strcmp(type, "mist"      )) SkipLines         (fp, 3);
            else if(!strcmp(type, "plastic"   )) ParseRAD_Plastic  (fp, identifier, matlist);
            else if(!strcmp(type, "metal"     )) ParseRAD_Metal    (fp, identifier, matlist);
            else if(!strcmp(type, "trans"     )) SkipLines         (fp, 3);
            else if(!strcmp(type, "plastic2"  )) SkipLines         (fp, 3);
            else if(!strcmp(type, "metal2"    )) SkipLines         (fp, 3);
            else if(!strcmp(type, "trans2"    )) SkipLines         (fp, 3);
            else if(!strcmp(type, "dielectric")) SkipLines         (fp, 3);
            else if(!strcmp(type, "interface" )) SkipLines         (fp, 3);
            else if(!strcmp(type, "glass"     )) ParseRAD_Glass    (fp, identifier, matlist);
            else if(!strcmp(type, "plasfunc"  )) SkipLines         (fp, 3);
            else if(!strcmp(type, "metfunc"   )) SkipLines         (fp, 3);
            else if(!strcmp(type, "transfunc" )) SkipLines         (fp, 3);
        }
        else
        {
            if(!strcmp(type, "source"))
            {
                SkipLines(fp, 3);
            }
            else if(!strcmp(type, "sphere"))
            {
                uint32 index = 0;
                bool   found = false;

                ldMaterial *mat = matlist->GetFirstNode();

                while(!found && mat != NULL)
                {
                    if(!strcmp(mat->ID, modifier)) found = true;
                    else mat = matlist->GetNextNode();
                }

                if(found && mat->Nice)
                {
                    nice = true;
                    if(mat->Importance > importance)
                        importance = mat->Importance;
                }

                SkipLines(fp, 2);
                fgets(buffer, 256, fp);

                GetFirstToken(buffer, seps);

                float  x, y, z, r;
                varray = new ldVector3[8];

                x = GetFloatFromToken(GetNextToken());
                y = GetFloatFromToken(GetNextToken());
                z = GetFloatFromToken(GetNextToken());
                r = GetFloatFromToken(GetNextToken());

                varray[0].Set(x+r, y+r, z+r);
                varray[1].Set(x+r, y+r, z-r);
                varray[2].Set(x+r, y-r, z+r);
                varray[3].Set(x+r, y-r, z-r);
                varray[4].Set(x-r, y+r, z+r);
                varray[5].Set(x-r, y+r, z-r);
                varray[6].Set(x-r, y-r, z+r);
                varray[7].Set(x-r, y-r, z-r);

                nvert = 8;
            }
            else if(!strcmp(type, "bubble"))
            {
                SkipLines(fp, 3);
            }
            else if(!strcmp(type, "polygon"))
            {
                uint32 index = 0;
                bool   found = false;

                ldMaterial *mat = matlist->GetFirstNode();

                while(!found && mat != NULL)
                {
                    if(!strcmp(mat->ID, modifier)) found = true;
                    else mat = matlist->GetNextNode();
                }

                if(found && mat->Nice)
                {
                    nice = true;
                    if(mat->Importance > importance)
                        importance = mat->Importance;
                }

                SkipLines(fp, 2);
                fgets(buffer, 256, fp);

                // Vertices in polygon
                uint32 n = GetUInt32FromToken(GetFirstToken(buffer, seps)) / 3;

                if(varray == NULL)
                {
                    vsize = n + 64;
                    varray = new ldVector3[vsize];
                }
                else if(vsize < nvert + n)
                {
                    ldVector3 *tarray = new ldVector3[vsize + n + 64];

                    memcpy(tarray, varray, nvert * sizeof(ldVector3));

                    delete[] varray;

                    varray = tarray;
                    vsize += (n + 64);
                }

                float  x, y, z;
                uint32 i = nvert;

                str = GetNextToken();
                if(str != NULL)
                {
                    x = GetFloatFromToken(str);
                    y = GetFloatFromToken(GetNextToken());
                    z = GetFloatFromToken(GetNextToken());
                    varray[nvert].Set(x, y, z);

                    i++;
                }

                while(i < (nvert + n))
                {
                    fgets(buffer, 256, fp);
                    x = GetFloatFromToken(GetFirstToken(buffer, seps));
                    y = GetFloatFromToken(GetNextToken());
                    z = GetFloatFromToken(GetNextToken());
                    varray[i++].Set(x, y, z);
                }

                nvert += n;
            }
            else if(!strcmp(type, "cone"))
            {
            }
            else if(!strcmp(type, "cup"))
            {
            }
            else if(!strcmp(type, "cylinder"))
            {
            }
            else if(!strcmp(type, "tube"))
            {
            }
            else if(!strcmp(type, "ring"))
            {
            }
            else if(!strcmp(type, "instance"))
            {
            }
        }
    }

    fclose(fp);

    if(nvert)
    {
        ldObject *obj = new ldObject(nvert, varray, importance, nice);

        objlist->AddNode(obj);

        delete[] varray;
    }

    return true;
}

#endif  // _LD_RAD_PARSER_CPP
