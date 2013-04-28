/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldmath.h - Header File

    Description: Standard math routines.

    v1.0 - 08/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_MATH_H
#define _LD_MATH_H

#include <math.h>

#include "ldtypes.h"

// Defines PI
const float PI = 3.14159265358979323846f;

// Tests if argument is zero (+/- epsilon)
bool IS_ZERO(const float n);                // Value to be tested

// Returns inverse of argument
float INV(const float n);                   // Value to be inverted

// Radians to degrees convertion
float RAD2DEG(const float r);               // Angle in radians

// Degrees to radians convertion
float DEG2RAD(const float d);               // Angle in degrees

// Returns remainder of division
float MOD(const float a,                    // Numerator
          const float b);                   // Denominator

// Returns floor of argument
float FLOOR(const float n);                 // Value to get the floor

// Returns ceiling of argument
float CEIL(const float n);                  // Value to get the ceiling

// Rounds argument to the closest integer
int32 ROUND(const float n);                 // Value to round

// Clamp argument to a specific range [minimum, maximum]
template<class Type>
Type CLAMP(const Type num,                  // Value to clamp
           const Type min,                  // Minimum limit
           const Type max);                 // Maximum limit

// Assures that the arguments are in minimum - maximum order
template<class Type>
void MIN_MAX(Type &min,                     // 1st value to be tested and returned minimum
             Type &max);                    // 2nd value to be tested and returned maximum

// Returns minimum of two arguments
template<class Type>
Type MIN2(const Type a,                     // 1st value to be tested
          const Type b);                    // 2nd value to be tested

// Returns maximum of two arguments
template<class Type>
Type MAX2(const Type a,                     // 1st value to be tested
          const Type b);                    // 2nd value to be tested

// Returns maximum of three arguments
template<class Type>
Type MAX3(const Type a,                     // 1st value to be tested
          const Type b,                     // 2nd value to be tested
          const Type c);                    // 3rd value to be tested

// Returns absolute value of argument
float ABS(const float n);                   // Value to get absolute

// Gets the closest integer log2 of a number
uint8 ILOG2(const uint32 n);                // Value to get log2

// Returns squared argument
float SQR(const float n);                   // Value to get square

// Returns square root of argument
float SQRT(const float n);                  // Value to get square root

// Returns inverse square root of argument
float INV_SQRT(const float n);              // Value to get inverse of square root

// Returns the sine of an angle expressed in radians
float SIN_RAD(const float r);               // Angle in radians

// Returns the sine of an angle expressed in degrees
float SIN_DEG(const float d);               // Angle in degrees

// Returns the cosine of an angle expressed in radians
float COS_RAD(const float r);               // Angle in radians

// Returns the cosine of an angle expressed in degrees
float COS_DEG(const float d);               // Angle in degrees

// Returns the tangent of an angle expressed in radians
float TAN_RAD(const float r);               // Angle in radians

// Returns the tangent of an angle expressed in degrees
float TAN_DEG(const float d);               // Angle in degrees

// Returns the arctangent of an angle expressed in radians
float ATAN_RAD(const float r);              // Angle in radians

// Returns the arctangent of an angle expressed in degrees
float ATAN_DEG(const float d);              // Angle in degrees

// Gets the sine and cosine of an angle expressed in radians
void SIN_COS_RAD(      float *s,            // Returned sine of angle
                       float *c,            // Returned cosine of angle
                 const float  r);           // Angle in radians

// Gets the sine and cosine of an angle expressed in degrees
void SIN_COS_DEG(      float *s,            // Returned sine of angle
                       float *c,            // Returned cosine of angle
                 const float  d);           // Angle in degrees

#include "ldmath.inl"

#endif  // _LD_MATH_H
