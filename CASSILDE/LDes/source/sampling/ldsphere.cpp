/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldsphere.cpp - Implementation File

    Description: Sphere class.

    v1.0 - 08/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_SPHERE_CPP
#define _LD_SPHERE_CPP

#include "ldmath3d.h"

// Enclosing sphere approximation
ldSphere SmallSphere(const uint numPoints, const ldVector3 *points)
{
    assert(numPoints > 0);
    assert(points != NULL);

    ldVector3 center;
    float     radius = -1.0f;

    for(uint i = 0; i < numPoints; i++) center += points[i];

    center /= float(numPoints);

    for(uint i = 0; i < numPoints; i++)
    {
        float d2 = center.GetSquaredDistance(points[i]);

        if(d2 > radius) radius = d2;
    }

    radius = SQRT(radius) + EPSILON;

    return ldSphere(center, radius);
}

#endif  // _LD_SPHERE_CPP
