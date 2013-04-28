/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldmath3d.h - Header File

    Description: 3D math classes header and functions.

    v1.0 - 08/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_MATH_3D_H
#define _LD_MATH_3D_H

#include <assert.h>
#include <math.h>

#include "ldmath.h"

#include "ldvector3.h"
#include "ldvector3.inl"

#include "ldcone.h"
#include "ldsphere.h"

bool TestIntersection(const ldSphere &sphere, const ldCone &cone);

// If an intersection occurs, the point of intersection closest to the cone vertex is returned.
bool FindIntersection(const ldSphere &sphere, const ldCone &cone, ldVector3 &closest);

#endif  // _LD_MATH_3D_H
