/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldvector3.h - Header File

    Description: 3D vector class.

    v1.0 - 08/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_VECTOR3_H
#define _LD_VECTOR3_H

// 3D vector class
class ldVector3
{
    private:

        float Data[3];      // Vector data

    public:

        // Default constructor
        ldVector3();

        // Copy constructor
        ldVector3(const ldVector3 &vector);                         // Vector to be copied

        // Constructor that sets the vector from XYZ elements
        ldVector3(const float x,                                    // X element
                  const float y,                                    // Y element
                  const float z);                                   // Z element

        // Constructor that sets the vector from an array.
        // If the array pointer is NULL the vector isn't initialized
        ldVector3(const float *array);                              // Pointer to the array

        // ldVector3 [] operator (read only)
        const float &operator [] (const int8 index) const;          // Integer index

        // ldVector3 [] operator (read-write)
        float &operator [] (const int8 index);                      // Integer index

        // Gets X
        float GetX() const;

        // Gets Y
        float GetY() const;

        // Gets Z
        float GetZ() const;

        // Low-level access to the data (read only)
        const float *GetData() const;

        // Low-level access to the data (read-write)
        float *GetData();

        // Sets the vector from XYZ elements
        ldVector3 &Set(const float x,                               // X element
                       const float y,                               // Y element
                       const float z);                              // Z element

        // Sets the vector from an array
        ldVector3 &Set(const float *array);                         // Pointer to the array

        // ldVector3 = ldVector3 operator
        ldVector3 &operator = (const ldVector3 &vector);            // Vector to be assigned

        // ldVector3 == ldVector3 operator
        bool operator == (const ldVector3 &vector) const;           // Vector to be tested

        // ldVector3 != ldVector3 operator
        bool operator != (const ldVector3 &vector) const;           // Vector to be tested

        // - ldVector3 operator
        const ldVector3 operator - () const;

        // ldVector3 += ldVector3 operator
        ldVector3 &operator += (const ldVector3 &vector);           // Vector to be added

        // ldVector3 -= ldVector3 operator
        ldVector3 &operator -= (const ldVector3 &vector);           // Vector to be subtracted

        // ldVector3 *= float operator
        ldVector3 &operator *= (const float scalar);                // Scalar to be multiplied

        // ldVector3 /= float operator
        ldVector3 &operator /= (const float scalar);                // Scalar to be divided

        // ldVector3 + ldVector3 operator
        const ldVector3 operator + (const ldVector3 &vector) const; // Vector to be added

        // ldVector3 - ldVector3 operator
        const ldVector3 operator - (const ldVector3 &vector) const; // Vector to be subtracted

        // ldVector3 * float operator
        const ldVector3 operator * (const float scalar) const;      // Scalar to be multiplied

        // ldVector3 / float operator
        const ldVector3 operator / (const float scalar) const;      // Scalar to be divided

        // float * ldVector3 friend operator
        friend const ldVector3 operator * (const float      scalar, // Scalar to be multiplied
                                           const ldVector3 &vector);// Current vector

        // float / ldVector3 friend operator
        friend const ldVector3 operator / (const float      scalar, // Scalar to be divided
                                           const ldVector3 &vector);// Current vector

        // Gets squared length
        float GetSquaredLength() const;

        // Gets length
        float GetLength() const;

        // Normalizes the vector
        ldVector3 &Normalize();

        // Gets a normalized version of the vector
        const ldVector3 GetNormalized() const;

        // Calculates the dot product between this and another vector
        float DotProduct(const ldVector3 &vector) const;            // The other vector

        // Calculates the cross product between this and another vector
        const ldVector3 CrossProduct(const ldVector3 &vector) const;// The other vector

        // Gets the squared distance between this and another point
        float GetSquaredDistance(const ldVector3 &point) const;     // The other point

        // Gets the distance between this and another point
        float GetDistance(const ldVector3 &point) const;            // The other point
};

#endif  // _LD_VECTOR3_H
