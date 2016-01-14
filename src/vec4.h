#ifndef VEC4_H
#define VEC4_H

#include "aamath.h"

union vec4
{
    struct
    {
        r32 x, y, z, w;
    };
    struct
    {
        r32 r, g, b, a;
    };
    vec3 xyz;
    vec3 rgb;
    r32 E[4];
};

inline vec4 VEC4(r32 x, r32 y, r32 z, r32 w)
{
    vec4 result;

    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;

    return result;
}

inline vec4 VEC4(vec3 v, r32 w)
{
    vec4 result;

    result.xyz = v;
    result.w = w;

    return result;
}

//
// NOTE: Static constants
//

static const vec4 VEC4_XAXIS = {1.0f, 0.0f, 0.0f, 0.0f};
static const vec4 VEC4_YAXIS = {0.0f, 1.0f, 0.0f, 0.0f};
static const vec4 VEC4_ZAXIS = {0.0f, 0.0f, 1.0f, 0.0f};
static const vec4 VEC4_WAXIS = {0.0f, 0.0f, 0.0f, 1.0f};
static const vec4 VEC4_ORIGIN = {0.0f, 0.0f, 0.0f, 0.0f};

//
// NOTE: Operators
//

inline vec4 operator-(const vec4 &a)
{
    vec4 result;

    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    result.w = -a.w;

    return result;
}

inline vec4 operator+(const vec4 &a, const vec4 &b)
{
    vec4 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return result;
}

inline vec4 operator+(const vec4 &a, const r32 &b)
{
    vec4 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;
    result.w = a.w + b;

    return result;
}

inline vec4 operator+(const r32 &b, const vec4 &a)
{
    vec4 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;
    result.w = a.w + b;

    return result;
}

inline vec4 operator-(const vec4 &a, const vec4 &b)
{
    vec4 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return result;
}

inline vec4 operator-(const vec4 &a, const r32 &b)
{
    vec4 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;
    result.w = a.w - b;

    return result;
}

inline vec4 operator-(const r32 &b, const vec4 &a)
{
    vec4 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;
    result.w = a.w - b;

    return result;
}

inline vec4 operator*(const vec4 &a, r32 b)
{
    vec4 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;

    return result;
}

inline vec4 operator*(r32 a, const vec4 &b)
{
    vec4 result = b * a;

    return result;
}

inline vec4 operator/(const vec4 &a, r32 b)
{
    vec4 result;

    r32 oneOverB = 1.0f / b;

    result.x = a.x * oneOverB;
    result.y = a.y * oneOverB;
    result.z = a.z * oneOverB;
    result.w = a.w * oneOverB;

    return result;
}

inline vec4 operator/(r32 a, const vec4 &b)
{
    vec4 result;

    r32 oneOverA = 1.0f / a;

    result.x = b.x * oneOverA;
    result.y = b.y * oneOverA;
    result.z = b.z * oneOverA;
    result.w = b.w * oneOverA;

    return result;
}


inline vec4 &operator*=(vec4 &a, const r32 &b)
{
    a = a * b;

    return a;
}

inline vec4 &operator/=(vec4 &a, const r32 &b)
{
    a = a / b;

    return a;
}

inline vec4 &operator+=(vec4 &a, const vec4 &b)
{
    a = a + b;

    return a;
}

inline vec4 &operator+=(vec4 &a, const r32 &b)
{
    a = a + b;

    return a;
}

inline vec4 &operator-=(vec4 &a, const vec4 &b)
{
    a = a - b;

    return a;
}

inline vec4 &operator-=(vec4 &a, const r32 &b)
{
    a = a - b;

    return a;
}
 
inline b32 operator==(const vec4 &a, const vec4 &b)
{
    return (AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y)
            && AreEqual(a.z, b.z)
            && AreEqual(a.w, b.w));
}
 
inline b32 operator!=(const vec4 &a, const vec4 &b)
{
    return !(AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y)
            && AreEqual(a.z, b.z)
            && AreEqual(a.w, b.w));
}

//
// NOTE: Functions
//

inline vec4 Cross(const vec4 &a, const vec4 &b)
{
    vec4 result = VEC4(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - b.x * a.y,
                 a.w); // set to 0 or use a/b?

    return result;
}

inline r32 DistanceSq(const vec4 &a, const vec4 &b)
{
    r32 x = b.x - a.x,
        y = b.y - a.y,
        z = b.z - a.z;

    return (x*x + y*y + z*z);
}

inline r32 Distance(const vec4 &a, const vec4 &b)
{
    return AASqrt(DistanceSq(a, b));
}

inline r32 Dot(const vec4 &a, const vec4 &b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline vec4 Hadamard(const vec4 &a, const vec4 &b)
{
    return VEC4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * a.w);
}

inline r32 LengthSq(const vec4 &a)
{
    return Dot(a, a);
}

inline r32 Length(const vec4 &a)
{
    return AASqrt(LengthSq(a));
}

inline vec4 Normalize(const vec4 &v)
{
    vec4 result;
    r32 oneOverLength = InvSqrt(LengthSq(v));

    result.x = v.x * oneOverLength;
    result.y = v.y * oneOverLength;
    result.z = v.z * oneOverLength;
    result.w = 0;

    return result;
}

inline vec4 Reflect(const vec4 &v, const vec4 &n)
{
    return v - 2.0f * (Dot(v, n) * n);
}

inline vec4 Refract(const vec4 &v, const vec4 &n, r32 idx)
{
    r32 ndotv = Dot(n, v);
    r32 k = 1.0f - idx * idx * (1.0f - ndotv * ndotv);
    if (k < 0.0f)
        return VEC4(0.0f, 0.0f, 0.0f, 0.0f);
    else
        return idx * v - (idx * ndotv + AASqrt(k)) * n;
}

// A . (B x C)
inline r32 TripleScal(const vec4 &a, const vec4 &b, const vec4 &c)
{
    return Dot(a, Cross(b, c));
}

// (B x C) x A
inline vec4 TripleVec(const vec4 &a, const vec4 &b, const vec4 &c)
{
    return Cross(a, Cross(b, c));
}

inline b32 IsZero(const vec4 &v)
{
    return (LengthSq(v) <= EPSILON);
}

inline b32 IsUnit(const vec4 &v)
{
    return IsZero(1.0f - v.x * v.x - v.y * v.y - v.z * v.z);
}

//
// NOTE: vec4 signed int
//

union vec4s
{
    struct
    {
        s32 x, y, z, w;
    };
    struct
    {
        s32 r, g, b, a;
    };
    vec3s xyz;
    vec3s rgb;
    s32 E[4];
};

inline vec4s VEC4S(s32 x, s32 y, s32 z, s32 w)
{
    vec4s result;

    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;

    return result;
}

inline vec4s VEC4S(vec3s v, s32 w)
{
    vec4s result;

    result.xyz = v;
    result.w = w;

    return result;
}

//
// NOTE: Static constants
//

static const vec4s VEC4S_XAXIS = {1, 0, 0, 0};
static const vec4s VEC4S_YAXIS = {0, 1, 0, 0};
static const vec4s VEC4S_ZAXIS = {0, 0, 1, 0};
static const vec4s VEC4S_WAXIS = {0, 0, 0, 1};
static const vec4s VEC4S_ORIGIN = {0, 0, 0, 0};

//
// NOTE: Operators
//

inline vec4s operator-(const vec4s &a)
{
    vec4s result;

    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    result.w = -a.w;

    return result;
}

inline vec4s operator+(const vec4s &a, const vec4s &b)
{
    vec4s result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return result;
}

inline vec4s operator+(const vec4s &a, const s32 &b)
{
    vec4s result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;
    result.w = a.w + b;

    return result;
}

inline vec4s operator+(const s32 &b, const vec4s &a)
{
    vec4s result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;
    result.w = a.w + b;

    return result;
}

inline vec4s operator-(const vec4s &a, const vec4s &b)
{
    vec4s result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return result;
}

inline vec4s operator-(const vec4s &a, const s32 &b)
{
    vec4s result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;
    result.w = a.w - b;

    return result;
}

inline vec4s operator-(const s32 &b, const vec4s &a)
{
    vec4s result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;
    result.w = a.w - b;

    return result;
}

inline vec4s operator*(const vec4s &a, s32 b)
{
    vec4s result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;

    return result;
}

inline vec4s operator*(s32 a, const vec4s &b)
{
    vec4s result = b * a;

    return result;
}

inline vec4s operator/(const vec4s &a, s32 b)
{
    vec4s result;

    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;
    result.w = a.w / b;

    return result;
}

inline vec4s operator/(s32 a, const vec4s &b)
{
    vec4s result;

    result.x = b.x / a;
    result.y = b.y / a;
    result.z = b.z / a;
    result.w = b.w / a;

    return result;
}


inline vec4s &operator*=(vec4s &a, const s32 &b)
{
    a = a * b;

    return a;
}

inline vec4s &operator/=(vec4s &a, const s32 &b)
{
    a = a / b;

    return a;
}

inline vec4s &operator+=(vec4s &a, const vec4s &b)
{
    a = a + b;

    return a;
}

inline vec4s &operator+=(vec4s &a, const s32 &b)
{
    a = a + b;

    return a;
}

inline vec4s &operator-=(vec4s &a, const vec4s &b)
{
    a = a - b;

    return a;
}

inline vec4s &operator-=(vec4s &a, const s32 &b)
{
    a = a - b;

    return a;
}
 
inline b32 operator==(const vec4s &a, const vec4s &b)
{
    return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w));
}
 
inline b32 operator!=(const vec4s &a, const vec4s &b)
{
    return !((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w));
}

//
// NOTE: Functions
//

inline vec4s Cross(const vec4s &a, const vec4s &b)
{
    vec4s result = VEC4S(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - b.x * a.y,
                 a.w); // set to 0 or use a/b?

    return result;
}

inline s32 DistanceSq(const vec4s &a, const vec4s &b)
{
    s32 x = b.x - a.x,
        y = b.y - a.y,
        z = b.z - a.z;

    return (x*x + y*y + z*z);
}

inline r32 Distance(const vec4s &a, const vec4s &b)
{
    return AASqrt((r32)DistanceSq(a, b));
}

inline s32 Dot(const vec4s &a, const vec4s &b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline vec4s Hadamard(const vec4s &a, const vec4s &b)
{
    return VEC4S(a.x * b.x, a.y * b.y, a.z * b.z, a.w * a.w);
}

inline s32 LengthSq(const vec4s &a)
{
    return Dot(a, a);
}

inline r32 Length(const vec4s &a)
{
    return AASqrt((r32)LengthSq(a));
}

// NOTE: A . (B x C)
inline s32 TripleScal(const vec4s &a, const vec4s &b, const vec4s &c)
{
    return Dot(a, Cross(b, c));
}

// NOTE: (B x C) x A
inline vec4s TripleVec(const vec4s &a, const vec4s &b, const vec4s &c)
{
    return Cross(a, Cross(b, c));
}

inline b32 IsZero(const vec4s &v)
{
    return ((v.x == 0) && (v.y == 0) && (v.z == 0));
}

//
// NOTE: vec4 unsigned int
//

union vec4u
{
    struct
    {
        u32 x, y, z, w;
    };
    struct
    {
        u32 r, g, b, a;
    };
    vec3u xyz;
    vec3u rgb;
    u32 E[4];
};

inline vec4u VEC4U(u32 x, u32 y, u32 z, u32 w)
{
    vec4u result;

    result.x = x;
    result.y = y;
    result.z = z;
    result.w = w;

    return result;
}

inline vec4u VEC4U(vec3u v, u32 w)
{
    vec4u result;

    result.xyz = v;
    result.w = w;

    return result;
}

//
// NOTE: Static constants
//

static const vec4u VEC4U_XAXIS = {1, 0, 0, 0};
static const vec4u VEC4U_YAXIS = {0, 1, 0, 0};
static const vec4u VEC4U_ZAXIS = {0, 0, 1, 0};
static const vec4u VEC4U_WAXIS = {0, 0, 0, 1};
static const vec4u VEC4U_ORIGIN = {0, 0, 0, 0};

//
// NOTE: Operators
//

inline vec4u operator+(const vec4u &a, const vec4u &b)
{
    vec4u result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return result;
}

inline vec4u operator+(const vec4u &a, const u32 &b)
{
    vec4u result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;
    result.w = a.w + b;

    return result;
}

inline vec4u operator+(const u32 &b, const vec4u &a)
{
    vec4u result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;
    result.w = a.w + b;

    return result;
}

inline vec4u operator-(const vec4u &a, const vec4u &b)
{
    vec4u result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return result;
}

inline vec4u operator-(const vec4u &a, const u32 &b)
{
    vec4u result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;
    result.w = a.w - b;

    return result;
}

inline vec4u operator-(const u32 &b, const vec4u &a)
{
    vec4u result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;
    result.w = a.w - b;

    return result;
}

inline vec4u operator*(const vec4u &a, u32 b)
{
    vec4u result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;

    return result;
}

inline vec4u operator*(u32 a, const vec4u &b)
{
    vec4u result = b * a;

    return result;
}

inline vec4u operator/(const vec4u &a, u32 b)
{
    vec4u result;

    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;
    result.w = a.w / b;

    return result;
}

inline vec4u operator/(u32 a, const vec4u &b)
{
    vec4u result;

    result.x = b.x / a;
    result.y = b.y / a;
    result.z = b.z / a;
    result.w = b.w / a;

    return result;
}


inline vec4u &operator*=(vec4u &a, const u32 &b)
{
    a = a * b;

    return a;
}

inline vec4u &operator/=(vec4u &a, const u32 &b)
{
    a = a / b;

    return a;
}

inline vec4u &operator+=(vec4u &a, const vec4u &b)
{
    a = a + b;

    return a;
}

inline vec4u &operator+=(vec4u &a, const u32 &b)
{
    a = a + b;

    return a;
}

inline vec4u &operator-=(vec4u &a, const vec4u &b)
{
    a = a - b;

    return a;
}

inline vec4u &operator-=(vec4u &a, const u32 &b)
{
    a = a - b;

    return a;
}
 
inline b32 operator==(const vec4u &a, const vec4u &b)
{
    return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w));
}
 
inline b32 operator!=(const vec4u &a, const vec4u &b)
{
    return !((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w));
}

//
// NOTE: Functions
//

inline u32 Dot(const vec4u &a, const vec4u &b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline vec4u Hadamard(const vec4u &a, const vec4u &b)
{
    return VEC4U(a.x * b.x, a.y * b.y, a.z * b.z, a.w * a.w);
}

inline b32 IsZero(const vec4u &v)
{
    return ((v.x == 0) && (v.y == 0) && (v.z == 0));
}

#endif

