#ifndef AAMATH_H
#define AAMATH_H

#include "aatypes.h"
#include <math.h>

#define EPSILON 1.0e-6f
#define TWOPI   6.2831853071795864769252867665590f
#define TAU     6.2831853071795864769252867665590f

#undef AAMATH_APPROXIMATE

union intfloat
{
    r32 f;
    u32 u;
};

// see https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Approximations_that_depend_on_the_floating_point_representation
inline r32 Sqrt(r32 x)
{
#if defined(AAMATH_APPROXIMATE)
    intfloat y = {x};
    y.u -= 1 << 23;
    y.u >>= 1;
    y.u += 1 << 29;
    return y.f;
#else
    return sqrtf(x);
#endif
}

// see http://rrrola.wz.cz/inv_sqrt.html - improved fast inv sqrt
inline r32 InvSqrt(r32 x)
{
#if defined(AAMATH_APPROXIMATE)
    intfloat y = {x};
    y.u = 0x5F1FFFF9ul - (y.u >> 1);
    return 0.703952253f * y.f * (2.38924456f - x * y.f * y.f);

//    r32 halfx = 0.5f * x;
//    int i = *(int*)&x;
//    i = 0x5f3759df - (i >> 1);
//    x = *(r32*)&i;
//    x = x * (1.5f - halfx * x * x);
//    return x;

#else
    return 1.0f / sqrtf(x);
#endif
}

// check if two floats are relatively equal
inline b32 IsEqual(r32 a, r32 b, r32 epsilon = EPSILON)
{
    return fabs(a - b) <= epsilon * (fabs(a) + fabs(b) + 1.0f);
}

// check if float is within epsilon of zero
inline b32 IsZero(r32 x, r32 epsilon = EPSILON)
{
    return fabs(x) <= epsilon;
}

#endif

