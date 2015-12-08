#ifndef VEC4_H
#define VEC4_H

#include "aamath.h"

union v4
{
    struct
    {
        r32 x, y, z, w;
    };
    struct
    {
        r32 r, g, b, a;
    };
    v3 xyz;
    v3 rgb;
    r32 E[4];
};

//
// NOTE: Static constants
//

static const v4 VEC4_XAXIS = {1.0f, 0.0f, 0.0f, 0.0f};
static const v4 VEC4_YAXIS = {0.0f, 1.0f, 0.0f, 0.0f};
static const v4 VEC4_ZAXIS = {0.0f, 0.0f, 1.0f, 0.0f};
static const v4 VEC4_WAXIS = {0.0f, 0.0f, 0.0f, 1.0f};
static const v4 VEC4_ORIGIN = {0.0f, 0.0f, 0.0f, 0.0f};

//
// NOTE: Operators
//

inline v4 operator-(const v4 &a)
{
    v4 result;

    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    result.w = -a.w;

    return result;
}

inline v4 operator+(const v4 &a, const v4 &b)
{
    v4 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return result;
}

inline v4 operator+(const v4 &a, const r32 &b)
{
    v4 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;
    result.w = a.w + b;

    return result;
}

inline v4 operator+(const r32 &b, const v4 &a)
{
    v4 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;
    result.w = a.w + b;

    return result;
}

inline v4 operator-(const v4 &a, const v4 &b)
{
    v4 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return result;
}

inline v4 operator-(const v4 &a, const r32 &b)
{
    v4 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;
    result.w = a.w - b;

    return result;
}

inline v4 operator-(const r32 &b, const v4 &a)
{
    v4 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;
    result.w = a.w - b;

    return result;
}

inline v4 operator*(const v4 &a, r32 b)
{
    v4 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;

    return result;
}

inline v4 operator*(r32 a, const v4 &b)
{
    v4 result = b * a;

    return result;
}

inline v4 operator/(const v4 &a, r32 b)
{
    v4 result;

    r32 oneOverB = 1.0f / b;

    result.x = a.x * oneOverB;
    result.y = a.y * oneOverB;
    result.z = a.z * oneOverB;
    result.w = a.w * oneOverB;

    return result;
}

inline v4 operator/(r32 a, const v4 &b)
{
    v4 result;

    r32 oneOverA = 1.0f / a;

    result.x = b.x * oneOverA;
    result.y = b.y * oneOverA;
    result.z = b.z * oneOverA;
    result.w = b.w * oneOverA;

    return result;
}


inline v4 &operator*=(v4 &a, const r32 &b)
{
    a = a * b;

    return a;
}

inline v4 &operator/=(v4 &a, const r32 &b)
{
    a = a / b;

    return a;
}

inline v4 &operator+=(v4 &a, const v4 &b)
{
    a = a + b;

    return a;
}

inline v4 &operator+=(v4 &a, const r32 &b)
{
    a = a + b;

    return a;
}

inline v4 &operator-=(v4 &a, const v4 &b)
{
    a = a - b;

    return a;
}

inline v4 &operator-=(v4 &a, const r32 &b)
{
    a = a - b;

    return a;
}
 
inline b32 operator==(const v4 &a, const v4 &b)
{
    return (AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y)
            && AreEqual(a.z, b.z)
            && AreEqual(a.w, b.w));
}
 
inline b32 operator!=(const v4 &a, const v4 &b)
{
    return !(AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y)
            && AreEqual(a.z, b.z)
            && AreEqual(a.w, b.w));
}

//
// NOTE: Functions
//

inline v4 Cross(const v4 &a, const v4 &b)
{
    v4 result = {a.y * b.z + a.z * b.y,
                 a.z * b.x + a.x * b.z,
                 a.x * b.y + b.x * a.y,
                 a.w}; // set to 0 or use a/b?

    return result;
}

inline r32 DistanceSq(const v4 &a, const v4 &b)
{
    r32 x = b.x - a.x,
        y = b.y - a.y,
        z = b.z - a.z;

    return (x*x + y*y + z*z);
}

inline r32 Distance(const v4 &a, const v4 &b)
{
    return AASqrt(DistanceSq(a, b));
}

inline r32 Dot(const v4 &a, const v4 &b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline v4 Hadamard(const v4 &a, const v4 &b)
{
    return {a.x * b.x, a.y * b.y, a.z * b.z, a.w * a.w};
}

inline r32 LengthSq(const v4 &a)
{
    return Dot(a, a);
}

inline r32 Length(const v4 &a)
{
    return AASqrt(LengthSq(a));
}

inline void Normalize(v4 &a)
{
    r32 oneOverLength = InvSqrt(LengthSq(a));

    a.x *= oneOverLength;
    a.y *= oneOverLength;
    a.z *= oneOverLength;
}

inline v4 Reflect(const v4 &v, const v4 &n)
{
    return v - 2.0f * (Dot(v, n) * n);
}

inline v4 Refract(const v4 &v, const v4 &n, r32 idx)
{
    r32 ndotv = Dot(n, v);
    r32 k = 1.0f - idx * idx * (1.0f - ndotv * ndotv);
    if (k < 0.0f)
        return {0.0f, 0.0f};
    else
        return idx * v - (idx * ndotv + AASqrt(k)) * n;
}

// A . (B x C)
inline r32 TripleScal(const v4 &a, const v4 &b, const v4 &c)
{
    return Dot(a, Cross(b, c));
}

// (B x C) x A
inline v4 TripleVec(const v4 &a, const v4 &b, const v4 &c)
{
    return Cross(a, Cross(b, c));
}

inline b32 IsZero(const v4 &v)
{
    return (LengthSq(v) <= EPSILON);
}

inline b32 IsUnit(const v4 &v)
{
    return IsZero(1.0f - v.x * v.x - v.y * v.y - v.z * v.z);
}

#endif

