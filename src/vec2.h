#ifndef VEC2_H
#define VEC2_H

#include "aamath.h"

typedef union _vec2
{
    struct
    {
        r32 x, y;
    };
    r32 E[2];
} vec2;

inline vec2 Vec2(r32 x, r32 y)
{
    vec2 result;

    result.x = x;
    result.y = y;

    return result;
}

//
// NOTE: Operators
//

inline vec2 operator-(const vec2 &v)
{
    vec2 result;

    result.x = -v.x;
    result.y = -v.y;

    return result;
}

inline vec2 operator+(const vec2 &a, const vec2 &b)
{
    vec2 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline vec2 operator+(const vec2 &a, const r32 &b)
{
    vec2 result;

    result.x = a.x + b;
    result.y = a.y + b;

    return result;
}

inline vec2 operator+(const r32 &b, const vec2 &a)
{
    vec2 result;

    result.x = a.x + b;
    result.y = a.y + b;

    return result;
}

inline vec2 operator-(const vec2 &a, const vec2 &b)
{
    vec2 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline vec2 operator-(const vec2 &a, const r32 &b)
{
    vec2 result;

    result.x = a.x - b;
    result.y = a.y - b;

    return result;
}

inline vec2 operator-(const r32 &b, const vec2 &a)
{
    vec2 result;

    result.x = a.x - b;
    result.y = a.y - b;

    return result;
}

inline vec2 operator*(const vec2 &a, r32 b)
{
    vec2 result;

    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}

inline vec2 operator*(r32 a, const vec2 &b)
{
    vec2 result;

    result.x = b.x * a;
    result.y = b.y * a;

    return result;
}

inline vec2 operator/(const vec2 &a, r32 b)
{
    vec2 result;

    result.x = a.x / b;
    result.y = a.y / b;

    return result;
}

inline vec2 operator/(r32 a, const vec2 &b)
{
    vec2 result;

    result.x = b.x / a;
    result.y = b.y / a;

    return result;
}


inline vec2 &operator*=(vec2 &a, const r32 &b)
{
    a = a * b;

    return a;
}

inline vec2 &operator/=(vec2 &a, const r32 &b)
{
    a = a / b;

    return a;
}

inline vec2 &operator+=(vec2 &a, const vec2 &b)
{
    a = a + b;

    return a;
}

inline vec2 &operator-=(vec2 &a, const vec2 &b)
{
    a = a - b;

    return a;
}
 
inline b32 operator==(const vec2 &a, const vec2 &b)
{
    return (AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y));
}
 
inline b32 operator!=(const vec2 &a, const vec2 &b)
{
    return !(AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y));
}

//
// NOTE: Functions
//

inline r32 DistanceSq(const vec2 &a, const vec2 &b)
{
    r32 x = b.x - a.x,
        y = b.y - a.y;

    return (x*x + y*y);
}

inline r32 Distance(const vec2 &a, const vec2 &b)
{
    return AASqrt(DistanceSq(a, b));
}

inline r32 Dot(const vec2 &a, const vec2 &b)
{
    return (a.x * b.x + a.y * b.y);
}

inline vec2 Hadamard(const vec2 &a, const vec2 &b)
{
    return Vec2(a.x * b.x, a.y * b.y);
}

inline r32 LengthSq(const vec2 &v)
{
    return Dot(v, v);
}

inline r32 Length(const vec2 &v)
{
    return AASqrt(LengthSq(v));
}

inline vec2 Normalized(const vec2 &v)
{
    vec2 result;

    Assert(v.x != 0 && v.y != 0);

    r32 oneOverLength = InvSqrt(LengthSq(v));

    result.x = v.x * oneOverLength;
    result.y = v.y * oneOverLength;

    return result;
}

inline void Normalize(vec2 &v)
{
    Assert(v.x != 0 && v.y != 0);

    r32 oneOverLength = InvSqrt(LengthSq(v));

    v.x *= oneOverLength;
    v.y *= oneOverLength;
}

inline vec2 Perpendicular(const vec2 &v)
{
    return Vec2(-v.y, v.x);
}

inline vec2 Reflect(const vec2 &v, const vec2 &n)
{
    return v - 2.0f * (Dot(v, n) * n);
}

inline vec2 Refract(const vec2 &v, const vec2 &n, r32 idx)
{
    r32 ndotv = Dot(n, v);
    r32 k = 1.0f - idx * idx * (1.0f - ndotv * ndotv);
    if (k < 0)
        return Vec2(0, 0);
    else
        return idx * v - (idx * ndotv + AASqrt(k)) * n;
}

inline b32 IsZero(const vec2 &v)
{
    return (LengthSq(v) <= EPSILON);
}

inline b32 IsUnit(const vec2 &v)
{
    return IsZero(1.0f - v.x * v.x - v.y * v.y);
}

//
// NOTE: vec2 signed int
//

union vec2s
{
    struct
    {
        s32 x, y;
    };
    s32 E[2];
};

inline vec2s Vec2s(s32 x, s32 y)
{
    vec2s result;

    result.x = x;
    result.y = y;

    return result;
}

//
// NOTE: Operators
//

inline vec2s operator-(const vec2s &v)
{
    vec2s result;

    result.x = -v.x;
    result.y = -v.y;

    return result;
}

inline vec2s operator+(const vec2s &a, const vec2s &b)
{
    vec2s result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline vec2s operator+(const vec2s &a, const s32 &b)
{
    vec2s result;

    result.x = a.x + b;
    result.y = a.y + b;

    return result;
}

inline vec2s operator+(const s32 &b, const vec2s &a)
{
    vec2s result;

    result.x = a.x + b;
    result.y = a.y + b;

    return result;
}

inline vec2s operator-(const vec2s &a, const vec2s &b)
{
    vec2s result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline vec2s operator-(const vec2s &a, const s32 &b)
{
    vec2s result;

    result.x = a.x - b;
    result.y = a.y - b;

    return result;
}

inline vec2s operator-(const s32 &b, const vec2s &a)
{
    vec2s result;

    result.x = a.x - b;
    result.y = a.y - b;

    return result;
}

inline vec2s operator*(const vec2s &a, s32 b)
{
    vec2s result;

    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}

inline vec2s operator*(s32 a, const vec2s &b)
{
    vec2s result;

    result.x = b.x * a;
    result.y = b.y * a;

    return result;
}

inline vec2s operator/(const vec2s &a, s32 b)
{
    vec2s result;

    result.x = a.x / b;
    result.y = a.y / b;

    return result;
}

inline vec2s operator/(s32 a, const vec2s &b)
{
    vec2s result;

    result.x = b.x / a;
    result.y = b.y / a;

    return result;
}


inline vec2s &operator*=(vec2s &a, const s32 &b)
{
    a = a * b;

    return a;
}

inline vec2s &operator/=(vec2s &a, const s32 &b)
{
    a = a / b;

    return a;
}

inline vec2s &operator+=(vec2s &a, const vec2s &b)
{
    a = a + b;

    return a;
}

inline vec2s &operator-=(vec2s &a, const vec2s &b)
{
    a = a - b;

    return a;
}
 
inline b32 operator==(const vec2s &a, const vec2s &b)
{
    return ((a.x == b.x) && (a.y == b.y));
}
 
inline b32 operator!=(const vec2s &a, const vec2s &b)
{
    return !((a.x == b.x) && (a.y == b.y));
}

//
// NOTE: Functions
//

inline s32 DistanceSq(const vec2s &a, const vec2s &b)
{
    s32 x = b.x - a.x,
        y = b.y - a.y;

    return (x*x + y*y);
}

inline r32 Distance(const vec2s &a, const vec2s &b)
{
    return AASqrt((r32)DistanceSq(a, b));
}

inline s32 Dot(const vec2s &a, const vec2s &b)
{
    return (a.x * b.x + a.y * b.y);
}

inline vec2s Hadamard(const vec2s &a, const vec2s &b)
{
    return Vec2s(a.x * b.x, a.y * b.y);
}

inline s32 LengthSq(const vec2s &v)
{
    return Dot(v, v);
}

inline r32 Length(const vec2s &v)
{
    return AASqrt((r32)LengthSq(v));
}

inline vec2s Perpendicular(const vec2s &v)
{
    return Vec2s(-v.y, v.x);
}

inline b32 IsZero(const vec2s &v)
{
    return (v.x == 0 && v.y == 0);
}

//
// NOTE: vec2 unsigned int
//

union vec2u
{
    struct
    {
        u32 x, y;
    };
    u32 E[2];
};

inline vec2u Vec2u(u32 x, u32 y)
{
    vec2u result;

    result.x = x;
    result.y = y;

    return result;
}

//
// NOTE: Operators
//

inline vec2u operator+(const vec2u &a, const vec2u &b)
{
    vec2u result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline vec2u operator+(const vec2u &a, const u32 &b)
{
    vec2u result;

    result.x = a.x + b;
    result.y = a.y + b;

    return result;
}

inline vec2u operator+(const u32 &b, const vec2u &a)
{
    vec2u result;

    result.x = a.x + b;
    result.y = a.y + b;

    return result;
}

inline vec2u operator-(const vec2u &a, const vec2u &b)
{
    vec2u result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline vec2u operator-(const vec2u &a, const u32 &b)
{
    vec2u result;

    result.x = a.x - b;
    result.y = a.y - b;

    return result;
}

inline vec2u operator-(const u32 &b, const vec2u &a)
{
    vec2u result;

    result.x = a.x - b;
    result.y = a.y - b;

    return result;
}

inline vec2u operator*(const vec2u &a, u32 b)
{
    vec2u result;

    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}

inline vec2u operator*(u32 a, const vec2u &b)
{
    vec2u result;

    result.x = b.x * a;
    result.y = b.y * a;

    return result;
}

inline vec2u operator/(const vec2u &a, u32 b)
{
    vec2u result;

    result.x = a.x / b;
    result.y = a.y / b;

    return result;
}

inline vec2u operator/(u32 a, const vec2u &b)
{
    vec2u result;

    result.x = b.x / a;
    result.y = b.y / a;

    return result;
}


inline vec2u &operator*=(vec2u &a, const u32 &b)
{
    a = a * b;

    return a;
}

inline vec2u &operator/=(vec2u &a, const u32 &b)
{
    a = a / b;

    return a;
}

inline vec2u &operator+=(vec2u &a, const vec2u &b)
{
    a = a + b;

    return a;
}

inline vec2u &operator-=(vec2u &a, const vec2u &b)
{
    a = a - b;

    return a;
}
 
inline b32 operator==(const vec2u &a, const vec2u &b)
{
    return ((a.x == b.x) && (a.y == b.y));
}
 
inline b32 operator!=(const vec2u &a, const vec2u &b)
{
    return !((a.x == b.x) && (a.y == b.y));
}

//
// NOTE: Functions
//

inline u32 Dot(const vec2u &a, const vec2u &b)
{
    return (a.x * b.x + a.y * b.y);
}

inline vec2u Hadamard(const vec2u &a, const vec2u &b)
{
    return Vec2u(a.x * b.x, a.y * b.y);
}

inline b32 IsZero(const vec2u &v)
{
    return (v.x == 0 && v.y == 0);
}

#endif

