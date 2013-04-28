/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldcone.h - Header File

    Description: Acute cone class.

    v1.0 - 08/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_CONE_H
#define _LD_CONE_H

class ldCone
{
    // An acute cone is Dot(A,X-V) = |X-V| cos(T) where V is the vertex, A
    // is the unit-length direction of the axis of the cone, and T is the
    // cone angle with 0 < T < PI/2. The cone interior is defined by the
    // inequality Dot(A,X-V) >= |X-V| cos(T). Since cos(T) > 0, we can avoid
    // computing square roots. The solid cone is defined by the inequality
    // Dot(A,X-V)^2 >= Dot(X-V,X-V) cos(T)^2.

    protected:

        ldVector3   m_Vertex;
        ldVector3   m_Axis;
        float       m_Cos;      // cos(T)
        float       m_Sin;      // sin(T)

    public:

        ldCone();
        ldCone(const ldVector3 &vertex, const ldVector3 &axis, const float angle /* angle_/_2 */);

        ldVector3 &Vertex();
        const ldVector3 &Vertex() const;

        ldVector3 &Axis();
        const ldVector3 &Axis() const;

        float &CosAngle();
        const float &CosAngle() const;

        float &SinAngle();
        const float &SinAngle() const;

};

#include "ldcone.inl"

#endif  // _LD_CONE_H
