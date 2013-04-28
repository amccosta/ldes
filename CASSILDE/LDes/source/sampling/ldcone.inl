/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldcone.inl - Inline File

    Description: Acute cone class.

    v1.0 - 08/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_CONE_INL
#define _LD_CONE_INL

inline ldCone::ldCone()
{
    // No initialization for efficiency
}

inline ldCone::ldCone(const ldVector3 &vertex, const ldVector3 &axis, const float angle)
{
    m_Vertex = vertex;
    m_Axis   = axis;

    SIN_COS_DEG(&m_Sin, &m_Cos, angle);
}

inline ldVector3 &ldCone::Vertex()
{
    return m_Vertex;
}

inline const ldVector3 &ldCone::Vertex() const
{
    return m_Vertex;
}

inline ldVector3 &ldCone::Axis()
{
    return m_Axis;
}

inline const ldVector3 &ldCone::Axis() const
{
    return m_Axis;
}

inline float &ldCone::CosAngle()
{
    return m_Cos;
}

inline const float &ldCone::CosAngle() const
{
    return m_Cos;
}

inline float &ldCone::SinAngle()
{
    return m_Sin;
}

inline const float &ldCone::SinAngle() const
{
    return m_Sin;
}

#endif  // _LD_CONE_INL
