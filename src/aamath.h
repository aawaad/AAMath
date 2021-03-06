#ifndef AAMATH_H
#define AAMATH_H

#include <float.h>
#include <limits.h>
#include <math.h>
#include "aatypes.h"

namespace aam
{

#define EPSILON         1.0e-6f
#define PI              3.14159265358979323846264338327950288f
#define PIOVERTWO       1.57079632679489661923132169163975144f
#define PIOVERFOUR      0.78539816339744828f
#define TWOPI           6.28318530717958647692528676655900576f
#define TAU             6.28318530717958647692528676655900576f
#define ONEOVERPI       0.318309886183790671537767526745028724f;
#define ONEOVERTWOPI    0.159154943091895335768883763372514362f;
#define ONEOVERTAU      0.159154943091895335768883763372514362f;

#undef AAMATH_APPROXIMATE

#ifdef AAMATH_DEBUG
#define AAM_Assert(x) if(!(x)) {*(int *)0 = 0;}
#else
#define AAM_Assert(x)
#endif

union intfloat
{
    r32 f;
    u32 u;
};

// NOTE: see https://en.wikipedia.org/wiki/Methods_of_computing_square_roots#Approximations_that_depend_on_the_floating_point_representation
inline r32 AASqrt(r32 x)
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

// NOTE: see http://rrrola.wz.cz/inv_sqrt.html - improved fast inv sqrt
inline r32 InvSqrt(r32 x)
{
#if defined(AAMATH_APPROXIMATE)
    intfloat y = {x};
    y.u = 0x5F1FFFF9ul - (y.u >> 1);
    return 0.703952253f * y.f * (2.38924456f - x * y.f * y.f);
#else
    return 1.0f / sqrtf(x);
#endif
}

// NOTE: check if two floats are relatively equal
inline b32 AreEqual(r32 a, r32 b, r32 epsilon = EPSILON)
{
    return fabs(a - b) <= epsilon * (fabs(a) + fabs(b) + 1.0f);
}

// NOTE: check if float is within epsilon of zero
inline b32 IsZero(r32 x, r32 epsilon = EPSILON)
{
    return fabs(x) <= epsilon;
}

inline void SinCos(r32 angle, r32 &a, r32 &b)
{
    a = sinf(angle);
    b = cosf(angle);
}

inline r32 Clamp(r32 x, r32 min, r32 max)
{
    r32 result = x;
    AAM_Assert(min < max);

    if(x < min)
        result = min;
    else if(x > max)
        result = max;

    return result;
}

inline r32 Clamp01(r32 x)
{
    return Clamp(x, 0.0f, 1.0f);
}

inline b32 IsNaN(r32 x)
{
    //return !(x == x);
    return ((*(u32*)&x) & 0x7fffffff) > 0x7f800000;
}

inline r32 Lerp(r32 t, r32 a, r32 b)
{
    return (1 - t) * a + t * b;
}

inline r32 Min(r32 a, r32 b)
{
    return (a < b) ? a : b;
}

inline r32 Max(r32 a, r32 b)
{
    return (a > b) ? a : b;
}

} // NOTE: Namespace

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "mat4.h"
#include "quat.h"
#include "collision.h"

#endif

