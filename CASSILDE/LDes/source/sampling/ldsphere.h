/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldsphere.h - Header File

    Description: Sphere class.

    v1.0 - 08/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_SPHERE_H
#define _LD_SPHERE_H

class ldSphere
{
    protected:

        ldVector3   m_Center;
        float       m_Radius;

    public:

        ldSphere();
        ldSphere(const ldVector3 &center, const float radius);
        ldSphere(const uint numPoints, const ldVector3 *points);

        ldVector3 &Center();
        const ldVector3 &Center() const;

        float &Radius();
        const float &Radius() const;
};

// Enclosing sphere approximation
ldSphere SmallSphere(const uint numPoints, const ldVector3 *points);

#include "ldsphere.inl"

#endif  // _LD_SPHERE_H
