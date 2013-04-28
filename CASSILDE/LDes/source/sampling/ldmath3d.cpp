/*
    CASSILDE - Computer Assisted Lighting Design

    File:   ldmath3d.cpp - Implementation File

    Description: 3D math classes header and functions.

    v1.0 - 08/03/2002 by Helder Parracho (hparracho@hotmail.com)
         - Initial implementation
*/

#ifndef _LD_MATH_3D_CPP
#define _LD_MATH_3D_CPP

#include "ldmath3d.h"

// Tests intersection between a sphere and an acute cone
bool TestIntersection(const ldSphere &sphere, const ldCone &cone)
{
    // Test if cone vertex is in sphere
    ldVector3 diff = sphere.Center() - cone.Vertex();
    float     RSqr = sphere.Radius() * sphere.Radius();
    float     LSqr = diff.GetSquaredLength();

    if(LSqr <= RSqr) return true;

    // Test if sphere center is in cone
    float dot    = diff.DotProduct(cone.Axis());
    float dotSqr = dot * dot;
    float cosSqr = cone.CosAngle() * cone.CosAngle();

    if(dotSqr >= LSqr * cosSqr && dot > 0.0f)
    {
        // Sphere center is inside cone, so sphere and cone intersect.
        return true;
    }

    // Sphere center is outside cone. Problem now reduces to looking for
    // an intersection between circle and ray in the plane containing
    // cone vertex and spanned by cone axis and vector from vertex to
    // sphere center.

    // Ray is t*D+V (t >= 0) where |D| = 1 and dot(A,D) = cos(angle).
    // Also, D = e*A+f*(C-V). Plugging ray equation into sphere equation
    // yields R^2 = |t*D+V-C|^2, so the quadratic for intersections is
    // t^2 - 2*dot(D,C-V)*t + |C-V|^2 - R^2 = 0. An intersection occurs
    // if and only if the discriminant is nonnegative. This test becomes
    //
    //     dot(D,C-V)^2 >= dot(C-V,C-V) - R^2
    //
    // Note that if the right-hand side is nonpositive, then the inequality
    // is true (the sphere contains V). I have already ruled this out in
    // the first block of code in this function.

    float ULen  = SQRT(ABS(LSqr - dotSqr));
    float test  = cone.CosAngle() * dot + cone.SinAngle() * ULen;
    float discr = test * test - LSqr + RSqr;

    return (discr >= 0.0f && test >= 0.0f);
}

// If an intersection occurs, the point of intersection closest to the cone vertex is returned.
bool FindIntersection(const ldSphere &sphere, const ldCone &cone, ldVector3 &closest)
{
    // Test if cone vertex is in sphere
    ldVector3 diff = sphere.Center() - cone.Vertex();
    float     RSqr = sphere.Radius() * sphere.Radius();
    float     LSqr = diff.GetSquaredLength();

    if(LSqr <= RSqr) return true;

    // Test if sphere center is in cone
    float dot    = diff.DotProduct(cone.Axis());
    float dotSqr = dot * dot;
    float cosSqr = cone.CosAngle() * cone.CosAngle();

    if(dotSqr >= LSqr * cosSqr && dot > 0.0f)
    {
        // Sphere center is inside cone, so sphere and cone intersect.
        return true;
    }

    // Sphere center is outside cone. Problem now reduces to looking for
    // an intersection between circle and ray in the plane containing
    // cone vertex and spanned by cone axis and vector from vertex to
    // sphere center.

    // Ray is t*D+V (t >= 0) where |D| = 1 and dot(A,D) = cos(angle).
    // Also, D = e*A+f*(C-V). Plugging ray equation into sphere equation
    // yields R^2 = |t*D+V-C|^2, so the quadratic for intersections is
    // t^2 - 2*dot(D,C-V)*t + |C-V|^2 - R^2 = 0. An intersection occurs
    // if and only if the discriminant is nonnegative. This test becomes
    //
    //     dot(D,C-V)^2 >= dot(C-V,C-V) - R^2
    //
    // Note that if the right-hand side is nonpositive, then the inequality
    // is true (the sphere contains V). I have already ruled this out in
    // the first block of code in this function.

    float ULen  = SQRT(ABS(LSqr - dotSqr));
    float test  = cone.CosAngle() * dot + cone.SinAngle() * ULen;
    float discr = test * test - LSqr + RSqr;

    if(discr >= 0.0f && test >= 0.0f)
    {
        // Compute point of intersection closest to vertex V
        float     T   = test - SQRT(discr);
        ldVector3 B   = diff - dot * cone.Axis();
        float     tmp = cone.SinAngle() / ULen;

        closest = T * (cone.CosAngle() * cone.Axis() + tmp * B);

        return true;
    }

    return false;
}

#endif  // _LD_MATH_3D_CPP
