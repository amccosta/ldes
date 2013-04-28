/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldobject.cpp - Implementation File

    Description: Object class and functions.

    v1.0 - 15/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_OBJECT_CPP
#define _LD_OBJECT_CPP

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "ldobject.h"

ldObject::ldObject(int nvert, ldVector3 *vert, float imp, bool nice)
{
    BSphere    = ldSphere(nvert, vert);
    Importance = imp;
    Nice       = nice;
}

ldSphere ldObject::GetBSphere() const
{
    return BSphere;
}

float ldObject::GetRadius() const
{
    return BSphere.Radius();
}

float ldObject::GetImportance() const
{
    return Importance;
}

bool ldObject::IsNice() const
{
    return Nice;
}

uint32 ldObject::GetRayDensity(const ldVector3 &point) const
{
    float  dist = GetDistance(point);
    float  radi = BSphere.Radius();
#if 0
    float  wght = atan2(radi, dist) * 2 / PI;
#else
    float  wght;

    if (dist > 0.0)
    {
        wght = radi / dist;
        wght = wght / (wght + 1);
    } else
        wght = 1.0;
#endif

    uint32 n = uint32(Importance * wght * OBJ_SAMPLES_MAX);
    if (n < 1) return 1;
    return n;
}

float ldObject::GetDistance(const ldVector3 &point) const
{
    return point.GetDistance(BSphere.Center());
}

// Generate 'n' random directions given a 'view-point' and a 'target' sphere.
void GetRandDirs(const ldVector3 &point, const ldSphere &sphere,
                 float *array, uint32 n)
{
    ldVector3 c = sphere.Center();
    float r = sphere.Radius();
    float r2 = r + r;
    float x = c[0];
    float y = c[1];
    float z = c[2];

    srand((uint)time(NULL));

    for(uint32 i = 0; i < n; i++)
    {
        ldVector3 dir(((rand() / float(RAND_MAX) * r2) - r) + x - point[0],
                      ((rand() / float(RAND_MAX) * r2) - r) + y - point[1],
                      ((rand() / float(RAND_MAX) * r2) - r) + z - point[2]);

        dir.Normalize();

        array[i * 3    ] = dir[0];
        array[i * 3 + 1] = dir[1];
        array[i * 3 + 2] = dir[2];
    }
}

struct ObjImp
{
    ldObject *obj;
    int       dens;
};

int ObjImpCmp(const void *a, const void *b)
{
    ObjImp *aa = (ObjImp *)a;
    ObjImp *bb = (ObjImp *)b;

    if(bb->dens > aa->dens) return 1;
    if(aa->dens == bb->dens) return 0;

    return -1;
}

// Generate 'n' directions given a 'view-cone' and a list of objects
uint32 FindNewDirs(float px, float py, float pz,
                   float vx, float vy, float vz, float ap,
                   uint32 max_size, const ldObjList *nice, float *vdirs)
{
    assert(vdirs != NULL);
    assert(ap < 90.0f);

    ObjImp *vecimp = new ObjImp[nice->GetSize()];

    uint32 ndirs = 0;

    ldVector3 viewpt(px, py, pz);
    ldVector3 viewdr(vx, vy, vz);
    ldCone    cone(viewpt, viewdr, ap);

    ldObject *obj = nice->GetFirstNode();

    int i = 0;

    while(obj != NULL)
    {
        if(ap <= 0.0f || TestIntersection(obj->GetBSphere(), cone))
        {
            vecimp[i].dens = obj->GetRayDensity(viewpt);
            vecimp[i++].obj = obj;
        }

        obj = nice->GetNextNode();
    }

    int vecsize = i;

    qsort(vecimp, vecsize, sizeof(ObjImp), ObjImpCmp);

    i = 0;   

    while(ndirs < max_size && i < vecsize)
    {
        uint32 dens = vecimp[i].dens;
        if((dens + ndirs) > max_size) dens = max_size - ndirs;

#if 0
        fprintf(stderr, "obj %d: %d\n", i, dens);
#endif

        GetRandDirs(viewpt, vecimp[i++].obj->GetBSphere(),
                    &vdirs[ndirs * 3], dens);

        ndirs += dens;
    }

    delete[] vecimp;

    return ndirs;
}

#endif  // _LD_OBJECT_CPP
