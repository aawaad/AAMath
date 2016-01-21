#ifndef VEC3_H
#define VEC3_H

#include "aamath.h"

namespace aam
{

typedef union _vec3
{
    struct
    {
        r32 x, y, z;
    };
    struct
    {
        r32 u, v, w;
    };
    struct
    {
        r32 r, g , b;
    };
    r32 E[3];
} vec3;

inline vec3 Vec3(r32 x, r32 y, r32 z)
{
    vec3 result;

    result.x = x;
    result.y = y;
    result.z = z;

    return result;
}

//
// NOTE: Static constants
//

static const vec3 VEC3_XAXIS = {1.0f, 0, 0};
static const vec3 VEC3_YAXIS = {0, 1.0f, 0};
static const vec3 VEC3_ZAXIS = {0, 0, 1.0f};
static const vec3 VEC3_ORIGIN = {0, 0, 0};
static const vec3 VEC3_ZERO = {0, 0, 0};

//
// NOTE: Operators
//

inline vec3 operator-(const vec3 &v)
{
    vec3 result;

    result.x = -v.x;
    result.y = -v.y;
    result.z = -v.z;

    return result;
}

inline vec3 operator+(const vec3 &a, const vec3 &b)
{
    vec3 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline vec3 operator+(const vec3 &a, const r32 &b)
{
    vec3 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;

    return result;
}

inline vec3 operator+(const r32 &b, const vec3 &a)
{
    vec3 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;

    return result;
}

inline vec3 operator-(const vec3 &a, const vec3 &b)
{
    vec3 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline vec3 operator-(const vec3 &a, const r32 &b)
{
    vec3 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;

    return result;
}

inline vec3 operator-(const r32 &b, const vec3 &a)
{
    vec3 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;

    return result;
}

inline vec3 operator*(const vec3 &a, r32 b)
{
    vec3 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}

inline vec3 operator*(r32 a, const vec3 &b)
{
    vec3 result = b * a;

    return result;
}

inline vec3 operator/(const vec3 &a, r32 b)
{
    vec3 result;

    r32 oneOverB = 1.0f / b;

    result.x = a.x * oneOverB;
    result.y = a.y * oneOverB;
    result.z = a.z * oneOverB;

    return result;
}

inline vec3 operator/(r32 a, const vec3 &b)
{
    vec3 result;

    r32 oneOverA = 1.0f / a;

    result.x = b.x * oneOverA;
    result.y = b.y * oneOverA;
    result.z = b.z * oneOverA;

    return result;
}


inline vec3 &operator*=(vec3 &a, const r32 &b)
{
    a = a * b;

    return a;
}

inline vec3 &operator/=(vec3 &a, const r32 &b)
{
    a = a / b;

    return a;
}

inline vec3 &operator+=(vec3 &a, const vec3 &b)
{
    a = a + b;

    return a;
}

inline vec3 &operator+=(vec3 &a, const r32 &b)
{
    a = a + b;

    return a;
}

inline vec3 &operator-=(vec3 &a, const vec3 &b)
{
    a = a - b;

    return a;
}

inline vec3 &operator-=(vec3 &a, const r32 &b)
{
    a = a - b;

    return a;
}
 
inline b32 operator==(const vec3 &a, const vec3 &b)
{
    return (AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y)
            && AreEqual(a.z, b.z));
}
 
inline b32 operator!=(const vec3 &a, const vec3 &b)
{
    return !(AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y)
            && AreEqual(a.z, b.z));
}

//
// NOTE: Functions
//

inline vec3 Cross(const vec3 &a, const vec3 &b)
{
    vec3 result = Vec3(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - b.x * a.y);

    return result;
}

inline r32 DistanceSq(const vec3 &a, const vec3 &b)
{
    r32 x = b.x - a.x,
        y = b.y - a.y,
        z = b.z - a.z;

    return (x*x + y*y + z*z);
}

inline r32 Distance(const vec3 &a, const vec3 &b)
{
    return AASqrt(DistanceSq(a, b));
}

inline r32 Dot(const vec3 &a, const vec3 &b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline vec3 Hadamard(const vec3 &a, const vec3 &b)
{
    return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline r32 LengthSq(const vec3 &v)
{
    return Dot(v, v);
}

inline r32 Length(const vec3 &v)
{
    return AASqrt(LengthSq(v));
}

inline vec3 Normalized(const vec3 &v)
{
    vec3 result;

    Assert(v.x != 0 && v.y != 0 && v.z != 0);

    r32 oneOverLength = InvSqrt(LengthSq(v));

    result.x = v.x * oneOverLength;
    result.y = v.y * oneOverLength;
    result.z = v.z * oneOverLength;

    return result;
}

inline void Normalize(vec3 &v)
{
    Assert(v.x != 0 && v.y != 0 && v.z != 0);

    r32 oneOverLength = InvSqrt(LengthSq(v));

    v *= oneOverLength;
}

inline vec3 Reflect(const vec3 &v, const vec3 &n)
{
    return v - 2.0f * (Dot(v, n) * n);
}

inline vec3 Refract(const vec3 &v, const vec3 &n, r32 idx)
{
    r32 ndotv = Dot(n, v);
    r32 k = 1.0f - idx * idx * (1.0f - ndotv * ndotv);
    if (k < 0)
        return Vec3(0, 0, 0);
    else
        return idx * v - (idx * ndotv + AASqrt(k)) * n;
}

// NOTE: A . (B x C)
inline r32 TripleScal(const vec3 &a, const vec3 &b, const vec3 &c)
{
    return Dot(a, Cross(b, c));
}

// NOTE: (B x C) x A
inline vec3 TripleVec(const vec3 &a, const vec3 &b, const vec3 &c)
{
    return Cross(a, Cross(b, c));
}

inline b32 IsZero(const vec3 &v)
{
    return (LengthSq(v) <= EPSILON);
}

inline b32 IsUnit(const vec3 &v)
{
    return IsZero(1.0f - v.x * v.x - v.y * v.y - v.z * v.z);
}

//
// NOTE: vec3 signed int
//

union vec3s
{
    struct
    {
        s32 x, y, z;
    };
    struct
    {
        s32 u, v, w;
    };
    struct
    {
        s32 r, g , b;
    };
    s32 E[3];
};

inline vec3s Vec3s(s32 x, s32 y, s32 z)
{
    vec3s result;

    result.x = x;
    result.y = y;
    result.z = z;

    return result;
}

//
// NOTE: Static constants
//

static const vec3s VEC3S_XAXIS = {1, 0, 0};
static const vec3s VEC3S_YAXIS = {0, 1, 0};
static const vec3s VEC3S_ZAXIS = {0, 0, 1};
static const vec3s VEC3S_ORIGIN = {0, 0, 0};

//
// NOTE: Operators
//

inline vec3s operator-(const vec3s &v)
{
    vec3s result;

    result.x = -v.x;
    result.y = -v.y;
    result.z = -v.z;

    return result;
}

inline vec3s operator+(const vec3s &a, const vec3s &b)
{
    vec3s result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline vec3s operator+(const vec3s &a, const s32 &b)
{
    vec3s result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;

    return result;
}

inline vec3s operator+(const s32 &b, const vec3s &a)
{
    vec3s result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;

    return result;
}

inline vec3s operator-(const vec3s &a, const vec3s &b)
{
    vec3s result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline vec3s operator-(const vec3s &a, const s32 &b)
{
    vec3s result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;

    return result;
}

inline vec3s operator-(const s32 &b, const vec3s &a)
{
    vec3s result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;

    return result;
}

inline vec3s operator*(const vec3s &a, s32 b)
{
    vec3s result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}

inline vec3s operator*(s32 a, const vec3s &b)
{
    vec3s result = b * a;

    return result;
}

inline vec3s operator/(const vec3s &a, s32 b)
{
    vec3s result;

    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;

    return result;
}

inline vec3s operator/(s32 a, const vec3s &b)
{
    vec3s result;

    result.x = b.x / a;
    result.y = b.y / a;
    result.z = b.z / a;

    return result;
}


inline vec3s &operator*=(vec3s &a, const s32 &b)
{
    a = a * b;

    return a;
}

inline vec3s &operator/=(vec3s &a, const s32 &b)
{
    a = a / b;

    return a;
}

inline vec3s &operator+=(vec3s &a, const vec3s &b)
{
    a = a + b;

    return a;
}

inline vec3s &operator+=(vec3s &a, const s32 &b)
{
    a = a + b;

    return a;
}

inline vec3s &operator-=(vec3s &a, const vec3s &b)
{
    a = a - b;

    return a;
}

inline vec3s &operator-=(vec3s &a, const s32 &b)
{
    a = a - b;

    return a;
}
 
inline b32 operator==(const vec3s &a, const vec3s &b)
{
    return ((a.x == b.x) && (a.y  == b.y) && (a.z == b.z));
}
 
inline b32 operator!=(const vec3s &a, const vec3s &b)
{
    return !((a.x == b.x) && (a.y  == b.y) && (a.z == b.z));
}

//
// NOTE: Functions
//

inline vec3s Cross(const vec3s &a, const vec3s &b)
{
    vec3s result = Vec3s(a.y * b.z - a.z * b.y,
                     a.z * b.x - a.x * b.z,
                     a.x * b.y - b.x * a.y);

    return result;
}

inline s32 DistanceSq(const vec3s &a, const vec3s &b)
{
    s32 x = b.x - a.x,
        y = b.y - a.y,
        z = b.z - a.z;

    return (x*x + y*y + z*z);
}

inline r32 Distance(const vec3s &a, const vec3s &b)
{
    return AASqrt((r32)DistanceSq(a, b));
}

inline s32 Dot(const vec3s &a, const vec3s &b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline vec3s Hadamard(const vec3s &a, const vec3s &b)
{
    return Vec3s(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline s32 LengthSq(const vec3s &v)
{
    return Dot(v, v);
}

inline r32 Length(const vec3s &v)
{
    return AASqrt((r32)LengthSq(v));
}

// NOTE: A . (B x C)
inline s32 TripleScal(const vec3s &a, const vec3s &b, const vec3s &c)
{
    return Dot(a, Cross(b, c));
}

// NOTE: (B x C) x A
inline vec3s TripleVec(const vec3s &a, const vec3s &b, const vec3s &c)
{
    return Cross(a, Cross(b, c));
}

inline b32 IsZero(const vec3s &v)
{
    return ((v.x == 0) && (v.y == 0) && (v.z == 0));
}

//
// NOTE: vec3 unsigned int
//

union vec3u
{
    struct
    {
        u32 x, y, z;
    };
    struct
    {
        u32 u, v, w;
    };
    struct
    {
        u32 r, g , b;
    };
    u32 E[3];
};

inline vec3u Vec3u(u32 x, u32 y, u32 z)
{
    vec3u result;

    result.x = x;
    result.y = y;
    result.z = z;

    return result;
}

//
// NOTE: Static constants
//

static const vec3u VEC3U_XAXIS = {1, 0, 0};
static const vec3u VEC3U_YAXIS = {0, 1, 0};
static const vec3u VEC3U_ZAXIS = {0, 0, 1};
static const vec3u VEC3U_ORIGIN = {0, 0, 0};

//
// NOTE: Operators
//

inline vec3u operator+(const vec3u &a, const vec3u &b)
{
    vec3u result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline vec3u operator+(const vec3u &a, const u32 &b)
{
    vec3u result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;

    return result;
}

inline vec3u operator+(const u32 &b, const vec3u &a)
{
    vec3u result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;

    return result;
}

inline vec3u operator-(const vec3u &a, const vec3u &b)
{
    vec3u result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline vec3u operator-(const vec3u &a, const u32 &b)
{
    vec3u result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;

    return result;
}

inline vec3u operator-(const u32 &b, const vec3u &a)
{
    vec3u result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;

    return result;
}

inline vec3u operator*(const vec3u &a, u32 b)
{
    vec3u result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}

inline vec3u operator*(u32 a, const vec3u &b)
{
    vec3u result = b * a;

    return result;
}

inline vec3u operator/(const vec3u &a, u32 b)
{
    vec3u result;

    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;

    return result;
}

inline vec3u operator/(u32 a, const vec3u &b)
{
    vec3u result;

    result.x = b.x / a;
    result.y = b.y / a;
    result.z = b.z / a;

    return result;
}


inline vec3u &operator*=(vec3u &a, const u32 &b)
{
    a = a * b;

    return a;
}

inline vec3u &operator/=(vec3u &a, const u32 &b)
{
    a = a / b;

    return a;
}

inline vec3u &operator+=(vec3u &a, const vec3u &b)
{
    a = a + b;

    return a;
}

inline vec3u &operator+=(vec3u &a, const u32 &b)
{
    a = a + b;

    return a;
}

inline vec3u &operator-=(vec3u &a, const vec3u &b)
{
    a = a - b;

    return a;
}

inline vec3u &operator-=(vec3u &a, const u32 &b)
{
    a = a - b;

    return a;
}
 
inline b32 operator==(const vec3u &a, const vec3u &b)
{
    return ((a.x == b.x) && (a.y  == b.y) && (a.z == b.z));
}
 
inline b32 operator!=(const vec3u &a, const vec3u &b)
{
    return !((a.x == b.x) && (a.y  == b.y) && (a.z == b.z));
}

//
// NOTE: Functions
//

inline u32 Dot(const vec3u &a, const vec3u &b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline vec3u Hadamard(const vec3u &a, const vec3u &b)
{
    return Vec3u(a.x * b.x, a.y * b.y, a.z * b.z);
}

inline b32 IsZero(const vec3u &v)
{
    return ((v.x == 0) && (v.y == 0) && (v.z == 0));
}

} // NOTE: Namespace

#endif

