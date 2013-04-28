/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldobject.h - Header File

    Description: Object class and functions.

    v1.0 - 15/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_OBJECT_H
#define _LD_OBJECT_H

#define OBJ_SAMPLES_MAX 128

#include "ldlinklist.h"
#include "ldmath3d.h"

class ldObject
{
      public:

        ldSphere    BSphere;    // Bounding sphere
        float       Importance;
        bool        Nice;

    public:

        ldObject(int nvert, ldVector3 *vert, float imp, bool nice);

        ldSphere GetBSphere() const;

        float GetRadius() const;

        float GetImportance() const;

        bool IsNice() const;

        uint32 GetRayDensity(const ldVector3 &point) const;

        float GetDistance(const ldVector3 &point) const;

        // ldObject > ldObject operator
        bool operator > (const ldObject &obj) const
        {
            assert(this != &obj);

            return (Importance > obj.Importance);
        }
};

typedef ldLinkList<ldObject>   ldObjList;

// Generate 'n' randon directions given a 'view-point' and a 'target' sphere.
void GetRandDirs(const ldVector3 &point, const ldSphere &sphere, float *array, uint32 n);

// Generate 'n' directions given a 'view-cone' and a list of objects
uint32 FindNewDirs(float px, float py, float pz,
                   float vx, float vy, float vz, float ap,
                   uint32 max_size, const ldObjList *nice, float *vdirs);

#endif  // _LD_OBJECT_H
