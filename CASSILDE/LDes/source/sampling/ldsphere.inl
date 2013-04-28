/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldsphere.inl - Inline File

    Description: Sphere class.

    v1.0 - 08/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_SPHERE_INL
#define _LD_SPHERE_INL

inline ldSphere::ldSphere()
{
    // No initialization for efficiency
}

inline ldSphere::ldSphere(const ldVector3 &center, const float radius)
{
    m_Center = center;
    m_Radius = radius;
}

inline ldSphere::ldSphere(const uint numPoints, const ldVector3 *points)
{
    (*this) = SmallSphere(numPoints, points);
}

inline ldVector3 &ldSphere::Center()
{
    return m_Center;
}

inline const ldVector3 &ldSphere::Center() const
{
    return m_Center;
}

inline float &ldSphere::Radius()
{
    return m_Radius;
}

inline const float &ldSphere::Radius() const
{
    return m_Radius;
}

#endif  // _LD_SPHERE_INL
