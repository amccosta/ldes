/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldvector3.inl - Inline File

    Description: 3D vector class.

    v1.0 - 08/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_VECTOR3_INL
#define _LD_VECTOR3_INL

#define X 0
#define Y 1
#define Z 2

#ifndef NULL
#define NULL 0
#endif

// Default constructor
inline ldVector3::ldVector3()
{
    Data[X] = Data[Y] = Data[Z] = 0.0f;
}

// Copy constructor
inline ldVector3::ldVector3(const ldVector3 &vector)
{
    Data[X] = vector.Data[X];
    Data[Y] = vector.Data[Y];
    Data[Z] = vector.Data[Z];
}

// Constructor that sets the vector from XYZ elements
inline ldVector3::ldVector3(const float x,
                            const float y,
                            const float z)
{
    Data[X] = x;
    Data[Y] = y;
    Data[Z] = z;
}

// Constructor that sets the vector from an array.
// If the array pointer is NULL the vector isn't initialized
inline ldVector3::ldVector3(const float *array)
{
    if(array != NULL)
    {
        Data[X] = array[X];
        Data[Y] = array[Y];
        Data[Z] = array[Z];
    }
}

// ldVector3 [] operator (read only)
inline const float &ldVector3::operator [] (const int8 index) const
{
    assert(index >= 0 && index <= 2);

    return Data[index];
}

// ldVector3 [] operator (read-write)
inline float &ldVector3::operator [] (const int8 index)
{
    assert(index >= 0 && index <= 2);

    return Data[index];
}

// Gets X
inline float ldVector3::GetX() const
{
    return Data[X];
}

// Gets Y
inline float ldVector3::GetY() const
{
    return Data[Y];
}

// Gets Z
inline float ldVector3::GetZ() const
{
    return Data[Z];
}

// Low-level access to the data (read only)
inline const float *ldVector3::GetData() const
{
    return Data;
}

// Low-level access to the data (read-write)
inline float *ldVector3::GetData()
{
    return Data;
}

// Sets the vector from XYZ elements
inline ldVector3 &ldVector3::Set(const float x,
                                 const float y,
                                 const float z)
{
    Data[X] = x;
    Data[Y] = y;
    Data[Z] = z;

    return (*this);
}

// Sets the vector from XYZ elements
inline ldVector3 &ldVector3::Set(const float *array)
{
    assert(array != NULL);

    Data[X] = array[X];
    Data[Y] = array[Y];
    Data[Z] = array[Z];

    return (*this);
}

// ldVector3 = ldVector3 operator
inline ldVector3 &ldVector3::operator = (const ldVector3 &vector)
{
    assert(this != &vector);

    Data[X] = vector.Data[X];
    Data[Y] = vector.Data[Y];
    Data[Z] = vector.Data[Z];

    return (*this);
}

// ldVector3 == ldVector3 operator
inline bool ldVector3::operator == (const ldVector3 &vector) const
{
    assert(this != &vector);

    return (Data[X] == vector.Data[X] &&
            Data[Y] == vector.Data[Y] &&
            Data[Z] == vector.Data[Z]);
}

// ldVector3 != ldVector3 operator
inline bool ldVector3::operator != (const ldVector3 &vector) const
{
    return (!(*this == vector));
}

// - ldVector3 operator
inline const ldVector3 ldVector3::operator - () const
{
    return ldVector3(-Data[X], -Data[Y], -Data[Z]);
}

// ldVector3 += ldVector3 operator
inline ldVector3 &ldVector3::operator += (const ldVector3 &vector)
{
    Data[X] += vector.Data[X];
    Data[Y] += vector.Data[Y];
    Data[Z] += vector.Data[Z];

    return (*this);
}

// ldVector3 -= ldVector3 operator
inline ldVector3 &ldVector3::operator -= (const ldVector3 &vector)
{
    Data[X] -= vector.Data[X];
    Data[Y] -= vector.Data[Y];
    Data[Z] -= vector.Data[Z];

    return (*this);
}

// ldVector3 *= float operator
inline ldVector3 &ldVector3::operator *= (const float scalar)
{
    Data[X] *= scalar;
    Data[Y] *= scalar;
    Data[Z] *= scalar;

    return (*this);
}

// ldVector3 /= float operator
inline ldVector3 &ldVector3::operator /= (const float scalar)
{
    assert(scalar != 0.0f);

    Data[X] /= scalar;
    Data[Y] /= scalar;
    Data[Z] /= scalar;

    return *this;
}

// ldVector3 + ldVector3 operator
inline const ldVector3 ldVector3::operator + (const ldVector3 &vector) const
{
    return ldVector3(*this) += vector;
}

// ldVector3 - ldVector3 operator
inline const ldVector3 ldVector3::operator - (const ldVector3 &vector) const
{
    return ldVector3(*this) -= vector;
}

// ldVector3 * float operator
inline const ldVector3 ldVector3::operator * (const float scalar) const
{
    return ldVector3(*this) *= scalar;
}

// ldVector3 / float operator
inline const ldVector3 ldVector3::operator / (const float scalar) const
{
    return ldVector3(*this) /= scalar;
}

// float * ldVector3 friend operator
inline const ldVector3 operator * (const float      scalar,
                                   const ldVector3 &vector)
{
    return ldVector3(vector) *= scalar;
}

// float / ldVector3 friend operator
inline const ldVector3 operator / (const float      scalar,
                                   const ldVector3 &vector)
{
    return ldVector3(vector) /= scalar;
}

// Gets squared length
inline float ldVector3::GetSquaredLength() const
{
    return (Data[X] * Data[X] + Data[Y] * Data[Y] + Data[Z] * Data[Z]);
}

// Gets length
inline float ldVector3::GetLength() const
{
    return SQRT(GetSquaredLength());
}

// Normalizes the vector
inline ldVector3 &ldVector3::Normalize()
{
    (*this) /= GetLength();

    return (*this);
}

// Gets a normalized version of the vector
inline const ldVector3 ldVector3::GetNormalized() const
{
    return ldVector3(*this).Normalize();
}

// Calculates the dot product between this and another vector
inline float ldVector3::DotProduct(const ldVector3 &vector) const
{
    return (Data[X] * vector.Data[X] + 
            Data[Y] * vector.Data[Y] +
            Data[Z] * vector.Data[Z]);
}

// Calculates the cross product between this and another vector
inline const ldVector3 ldVector3::CrossProduct(const ldVector3 &vector) const
{
    return ldVector3(Data[Y] * vector.Data[Z] - Data[Z] * vector.Data[Y],
                     Data[Z] * vector.Data[X] - Data[X] * vector.Data[Z],
                     Data[X] * vector.Data[Y] - Data[Y] * vector.Data[X]);
}

// Gets the squared distance between this and another point
inline float ldVector3::GetSquaredDistance(const ldVector3 &point) const
{
    return (SQR(Data[X] - point.Data[X]) +
            SQR(Data[Y] - point.Data[Y]) +
            SQR(Data[Z] - point.Data[Z]));
}

// Gets the distance between this and another point
inline float ldVector3::GetDistance(const ldVector3 &point) const
{
    return SQRT(GetSquaredDistance(point));
}

#undef X
#undef Y
#undef Z

#endif  // _LD_VECTOR3_INL
