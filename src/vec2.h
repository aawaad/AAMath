#ifndef VEC2_H
#define VEC2_H

#include "aamath.h"

union v2
{
    struct
    {
        r32 x, y;
    };
    r32 E[2];
};

//
// NOTE: Operators
//

inline v2 operator-(const v2 &v)
{
    v2 result;

    result.x = -v.x;
    result.y = -v.y;

    return result;
}

inline v2 operator+(const v2 &a, const v2 &b)
{
    v2 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline v2 operator+(const v2 &a, const r32 &b)
{
    v2 result;

    result.x = a.x + b;
    result.y = a.y + b;

    return result;
}

inline v2 operator+(const r32 &b, const v2 &a)
{
    v2 result;

    result.x = a.x + b;
    result.y = a.y + b;

    return result;
}

inline v2 operator-(const v2 &a, const v2 &b)
{
    v2 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline v2 operator-(const v2 &a, const r32 &b)
{
    v2 result;

    result.x = a.x - b;
    result.y = a.y - b;

    return result;
}

inline v2 operator-(const r32 &b, const v2 &a)
{
    v2 result;

    result.x = a.x - b;
    result.y = a.y - b;

    return result;
}

inline v2 operator*(const v2 &a, r32 b)
{
    v2 result;

    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}

inline v2 operator*(r32 a, const v2 &b)
{
    v2 result;

    result.x = b.x * a;
    result.y = b.y * a;

    return result;
}

inline v2 operator/(const v2 &a, r32 b)
{
    v2 result;

    result.x = a.x / b;
    result.y = a.y / b;

    return result;
}

inline v2 operator/(r32 a, const v2 &b)
{
    v2 result;

    result.x = b.x / a;
    result.y = b.y / a;

    return result;
}


inline v2 &operator*=(v2 &a, const r32 &b)
{
    a = a * b;

    return a;
}

inline v2 &operator/=(v2 &a, const r32 &b)
{
    a = a / b;

    return a;
}

inline v2 &operator+=(v2 &a, const v2 &b)
{
    a = a + b;

    return a;
}

inline v2 &operator-=(v2 &a, const v2 &b)
{
    a = a - b;

    return a;
}
 
inline b32 operator==(const v2 &a, const v2 &b)
{
    return (AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y));
}
 
inline b32 operator!=(const v2 &a, const v2 &b)
{
    return !(AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y));
}

//
// NOTE: Functions
//

inline r32 DistanceSq(const v2 &a, const v2 &b)
{
    r32 x = b.x - a.x,
        y = b.y - a.y;

    return (x*x + y*y);
}

inline r32 Distance(const v2 &a, const v2 &b)
{
    return AASqrt(DistanceSq(a, b));
}

inline r32 Dot(const v2 &a, const v2 &b)
{
    return (a.x * b.x + a.y * b.y);
}

inline v2 Hadamard(const v2 &a, const v2 &b)
{
    return {a.x * b.x, a.y * b.y};
}

inline r32 LengthSq(const v2 &v)
{
    return Dot(v, v);
}

inline r32 Length(const v2 &v)
{
    return AASqrt(LengthSq(v));
}

inline void Normalize(v2 &v)
{
    r32 oneOverLength = InvSqrt(LengthSq(v));

    v.x *= oneOverLength;
    v.y *= oneOverLength;
}

inline v2 Perpendicular(const v2 &v)
{
    return {-v.y, v.x};
}

inline v2 Reflect(const v2 &v, const v2 &n)
{
    return v - 2.0f * (Dot(v, n) * n);
}

inline v2 Refract(const v2 &v, const v2 &n, r32 idx)
{
    r32 ndotv = Dot(n, v);
    r32 k = 1.0f - idx * idx * (1.0f - ndotv * ndotv);
    if (k < 0)
        return {0, 0};
    else
        return idx * v - (idx * ndotv + AASqrt(k)) * n;
}

inline b32 IsZero(const v2 &v)
{
    return (LengthSq(v) <= EPSILON);
}

inline b32 IsUnit(const v2 &v)
{
    return IsZero(1.0f - v.x * v.x - v.y * v.y);
}

#endif

