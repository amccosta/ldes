/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldmath.inl - Inline File

    Description: Standard math routines.

    v1.0 - 08/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_MATH_INL
#define _LD_MATH_INL

// Defines EPSILON
static float EPSILON = 0.00001f;

// Tests if argument is zero (+/- epsilon)
inline bool IS_ZERO(const float n)
{
    return (n >= -EPSILON && n <= EPSILON);
}

// Returns inverse of argument
inline float INV(const float n)
{
    assert(n != 0.0f);

    return (1.0f / n);
}

// Radians to degrees convertion
inline float RAD2DEG(const float r)
{
    return (r * 180.0f / PI);
}

// Degrees to radians convertion
inline float DEG2RAD(const float d)
{
    return (d * PI / 180.0f);
}

// Returns remainder of division
inline float MOD(const float a,
                 const float b)
{
    assert(b != 0.0f);

    int32 n = int32(a / b);
    float m = a - (n * b);

    return (m < 0.0f) ? (m + b) : m;
}

// Returns floor of argument
inline float FLOOR(const float n)
{
    int32 in = int32(n);

    return float(in - ((n < 0.0f) && (n != float(in))));
}

// Returns ceiling of argument
inline float CEIL(const float n)
{
    int32 in = int32(n);

    return float(in + ((n > 0.0f) && (n != float(in))));
}

// Rounds argument to the closest integer
inline int32 ROUND(const float n)
{
    return int32(n + 0.5f);
}

// Clamp argument to a specific range [minimum, maximum]
template<class Type>
inline Type CLAMP(const Type num,
                  const Type min,
                  const Type max)
{
    return (min > num) ? min : (max > num) ? num : max;
}

// Assures that the arguments are in minimum - maximum order
template<class Type>
inline void MIN_MAX(Type &min,
                    Type &max)
{
    if(min > max)
    {
        Type swp = min;
             min = max;
             max = swp;
    }
}

// Returns minimum of two arguments
template<class Type>
inline Type MIN2(const Type a,
                 const Type b)
{
    return ((a < b) ? a : b);
}

// Returns maximum of two arguments
template<class Type>
inline Type MAX2(const Type a,
                 const Type b)
{
    return ((b > a) ? b : a);
}

// Returns maximum of three arguments
template<class Type>
inline Type MAX3(const Type a,
                 const Type b,
                 const Type c)
{
    return MAX2(MAX2(a, b), c);
}

// Returns absolute value of argument
inline float ABS(const float n)
{
    return ((n < 0.000000f) ? -n : n);
}

// Gets the closest integer log2 of a number
inline uint8 ILOG2(const uint32 n)
{
    uint8  lo;
    uint8  hi   = 32;
    uint32 mask = uint32(1<<31);

    while(mask)     // Get integer log2 of 'n' (high bit)
    {
        if(n & mask) break;
        mask>>=1;
        hi--;
    }

    if(hi)          // Get the closest log2 number
    {
        lo = hi - 1;

        if(((1<<hi) - n) <= (n - (1<<lo))) return hi;
        else return lo;
    }
    else return 0;
}

// Returns squared argument
inline float SQR(const float n)
{
    return (n * n);
}

// Returns square root of argument
inline float SQRT(const float n)
{
    return float(sqrt(n));
}

// Returns inverse square root of argument
inline float INV_SQRT(const float n)
{
    return INV(SQRT(n));
}

// Returns the sine of an angle expressed radians
inline float SIN_RAD(const float r)
{
    return float(sin(r));
}

// Returns the sine of an angle expressed degrees
inline float SIN_DEG(const float d)
{
    return SIN_RAD(DEG2RAD(d));
}

// Returns the cosine of an angle expressed radians
inline float COS_RAD(const float r)
{
    return float(cos(r));
}

// Returns the cosine of an angle expressed degrees
inline float COS_DEG(const float d)
{
    return COS_RAD(DEG2RAD(d));
}

// Returns the tangent of an angle expressed radians
inline float TAN_RAD(const float r)
{
    return float(tan(r));
}

// Returns the tangent of an angle expressed degrees
inline float TAN_DEG(const float d)
{
    return TAN_RAD(DEG2RAD(d));
}

// Returns the arctangent of an angle expressed radians
inline float ATAN_RAD(const float r)
{
    return float(atan(r));
}

// Returns the arctangent of an angle expressed degrees
inline float ATAN_DEG(const float d)
{
    return ATAN_RAD(DEG2RAD(d));
}

// Gets the sine and cosine of an angle expressed in radians
inline void SIN_COS_RAD(      float *s,
                              float *c,
                        const float  r)
{
    *s = SIN_RAD(r);
    *c = COS_RAD(r);
}

// Gets the sine and cosine of an angle expressed in degrees
inline void SIN_COS_DEG(      float *s,
                              float *c,
                        const float  d)
{
    const float r = DEG2RAD(d);

    *s = SIN_RAD(r);
    *c = COS_RAD(r);
}

#endif  // _LD_MATH_INL
