#ifndef QUAT_H
#define QUAT_H

#include "aamath.h"
#include "vec3.h"
#include "vec4.h"

typedef union _quat
{
    struct
    {
        r32 w, x, y, z;
    };
    struct
    {
        r32 w;
        vec3 xyz;
    };
    vec4 v;
    r32 E[4];
} quat;

inline quat Quat(r32 w, r32 x, r32 y, r32 z)
{
    quat result;

    result.w = w;
    result.x = x;
    result.y = y;
    result.z = z;

    return result;
}

inline quat Quat(r32 w, vec3 v)
{
    quat result;

    result.w = w;
    result.xyz = v;

    return result;
}

//
// NOTE: Static constants
//

static const quat QUAT_IDENTITY = {1.0f, 0.0f, 0.0f, 0.0f};
static const quat QUAT_ZERO = {0.0f, 0.0f, 0.0f, 0.0f};

//
// NOTE: Operators
//

inline quat operator-(const quat &q)
{
    quat result;

    result.v = -q.v;

    return result;
}

inline quat operator-(const quat &a, const quat &b)
{
    quat result;

    result.v = a.v - b.v;

    return result;
}

inline quat operator+(const quat &a, const quat &b)
{
    quat result;

    result.v = a.v + b.v;

    return result;
}

inline quat operator*(const quat &a, const quat &b)
{
    quat result;

    result.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    result.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
    result.y = a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z;
    result.z = a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x;

    return result;
}

inline quat operator*(const quat &q, const r32 x)
{
    quat result;

    result.v = q.v * x;

    return result;
}

inline quat operator*(const r32 x, const quat &q)
{
    quat result;

    result.v = q.v * x;

    return result;
}

inline quat &operator-=(quat &a, const quat &b)
{
    a = a - b;

    return a;
}

inline quat &operator+=(quat &a, const quat &b)
{
    a = a + b;

    return a;
}

inline quat &operator*=(quat &a, const r32 &b)
{
    a = a * b;

    return a;
}

inline quat &operator*=(quat &a, const quat &b)
{
    a = a * b;

    return a;
}

inline b32 operator==(const quat &a, const quat &b)
{
    return (AreEqual(a.w, b.w)
            && AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y)
            && AreEqual(a.z, b.z));
}

inline b32 operator!=(const quat &a, const quat &b)
{
    return !(AreEqual(a.w, b.w)
            && AreEqual(a.x, b.x)
            && AreEqual(a.y, b.y)
            && AreEqual(a.z, b.z));
}

//
// NOTE: Functions
//

inline quat Conjugate(const quat &q)
{
    quat result;

    result.w = q.w;
    result.xyz = -q.xyz;

    return result;
}

inline r32 Dot(const quat &a, const quat &b)
{
    return Dot(a.v, b.v);
}

inline quat Inverse(const quat &q)
{
    quat result;
    r32 norm = Dot(q, q);

    if (IsZero(norm))
    {
        // NOTE: Assert?
        return QUAT_IDENTITY;
    }

    r32 recip = 1.0f / norm;
    result.w = q.w * recip;
    result.xyz = q.xyz * -recip;

    return result;
}

inline r32 Norm(const quat &q)
{
    return Dot(q.v, q.v);
}

inline void Normalize(quat &q)
{
    r32 norm = Norm(q);

    if (IsZero(norm))
    {
        q = QUAT_ZERO;
    }
    else
    {
        r32 recip = InvSqrt(norm);

        q.v *= recip;
    }
}

inline r32 Magnitude(const quat &q)
{
    return AASqrt(Norm(q));
}

// NOTE: z-y-x
inline quat QuatRollYawPitch(r32 z, r32 y, r32 x)
{
    quat result = QUAT_IDENTITY;

    result.xyz *= 0.5f;

    r32 sx, cx;
    SinCos(x, sx, cx);

    r32 sy, cy;
    SinCos(y, sy, cy);

    r32 sz, cz;
    SinCos(z, sz, cz);

    result.w = (cx * cy * cz) - (sx * sy * sz);
    result.x = (sx * cy * cz) + (cx * sy * sz);
    result.y = (cx * sy * cz) - (sx * cy * sz);
    result.z = (cx * cy * sz) + (sx * sy * cx);

    return result;
}

inline quat QuatRollYawPitch(vec3 v)
{
    return QuatRollYawPitch(v.z, v.y, v.x);
}

// NOTE: See minorlogic's post on gamedev.net
inline quat QuatFromTo(const vec3 &from, const vec3 &to)
{
    quat result;

    vec3 axis = Cross(from, to);

    result.w = Dot(from, to);
    result.xyz = axis;

    Normalize(result);

    result.w += 1.0f;

    if (result.w <= EPSILON)
    {
        if (from.z * from.z > from.x * from.x)
        {
            result = Quat(0.0f, 0.0f, from.z, -from.y);
        }
        else
        {
            result = Quat(0.0f, from.y, -from.x, 0.0f);
        }
    }

    Normalize(result);

    return result;
}

inline quat QuatFromTo(const vec4 &from, const vec4 &to)
{
    return QuatFromTo(from.xyz, to.xyz);
}

inline quat QuatAxisAngle(vec3 axis, r32 angle)
{
    quat result;

    r32 lenSq = LengthSq(axis);

    if (!IsZero(lenSq))
    {
        angle *= 0.5f;

        r32 s, c;
        SinCos(angle, s, c);

        r32 sinOverLen = s / AASqrt(lenSq);
        result.w = c;
        result.xyz = axis * sinOverLen;
    }
    else
    {
        result = QUAT_IDENTITY;
    }

    return result;
}

inline quat QuatAxisAngle(vec4 axis, r32 angle)
{
    return QuatAxisAngle(axis.xyz, angle);
}

// NOTE: z-y-x
inline void Set(quat &q, r32 x, r32 y, r32 z)
{
    x *= 0.5f;
    y *= 0.5f;
    z *= 0.5f;

    r32 sx, cx;
    SinCos(x, sx, cx);

    r32 sy, cy;
    SinCos(y, sy, cy);

    r32 sz, cz;
    SinCos(z, sz, cz);

    q.w = (cx * cy * cz) - (sx * sy * sz);
    q.x = (sx * cy * cz) + (cx * sy * sz);
    q.y = (cx * sy * cz) - (sx * cy * sz);
    q.z = (cx * cy * sz) + (sx * sy * cx);
}

inline void Set(quat &q, vec3 v)
{
    Set(q, v.x, v.y, v.z);
}

// NOTE: See minorlogic's post on gamedev.net
inline void Set(quat &q, const vec3 &from, const vec3 &to)
{
    vec3 axis = Cross(from, to);

    q.w = Dot(from, to);
    q.xyz = axis;

    Normalize(q);

    q.w += 1.0f;

    if (q.w <= EPSILON)
    {
        if (from.z * from.z > from.x * from.x)
        {
            q = Quat(0.0f, 0.0f, from.z, -from.y);
        }
        else
        {
            q = Quat(0.0f, from.y, -from.x, 0.0f);
        }
    }

    Normalize(q);
}

inline void Set(quat &q, vec3 axis, r32 angle)
{
    r32 lenSq = LengthSq(axis);

    if (!IsZero(lenSq))
    {
        angle *= 0.5f;

        r32 s, c;
        SinCos(angle, s, c);

        r32 sinOverLen = s / AASqrt(lenSq);
        q.w = c;
        q.xyz = axis * sinOverLen;
    }
    else
    {
        q = QUAT_IDENTITY;
    }
}

// NOTE: Rotate vector by quaternion
//       See Essential Math, eq 5.12
inline vec3 Rotate(const quat &q, const vec3 &v)
{
    // NOTE: Assert unit quaternion
    
    vec3 result;

    r32 vMult = 2.0f * (q.x * v.x + q.y * v.y + q.z * v.z),
        crossMult = 2.0f * q.w,
        pMult = crossMult * q.w - 1.0f;

    result.x = pMult * v.x + vMult * q.x + crossMult * (q.y * v.z - q.z * v.y);
    result.y = pMult * v.y + vMult * q.y + crossMult * (q.z * v.x - q.x * v.z);
    result.z = pMult * v.z + vMult * q.z + crossMult * (q.x * v.y - q.y * v.x);
    result.w = v.w;

    return result;
}

inline vec4 Rotate(const quat &q, const vec4 &v)
{
    vec4 result;

    result.xyz = Rotate(q, v.xyz);
    result.w = v.w;

    return result;
}

inline void Lerp(quat &q, const quat &start, r32 t, const quat &end)
{
    r32 cos = Dot(start, end);

    q = end * t;

    if (cos >= EPSILON)
    {
        q += (1.0f - t) * start;
    }
    else
    {
        q += (t - 1.0f) * start;
    }
}

inline void Slerp(quat &q, const quat &start, r32 t, const quat &end)
{
    r32 cos = Dot(start, end);
    r32 startt, endt;

    if (cos >= EPSILON)
    {
        if ((1.0f - cos) > EPSILON)
        {
            r32 angle = acosf(cos);
            r32 recipSin = 1.0f / sinf(angle);

            startt = sinf((1.0f - t) * angle) * recipSin;
            endt = sinf(angle * t) * recipSin;
        }
        else
        {
            // NOTE: angle is close to zero, so use linear
            startt = 1.0f - t;
            endt = t;
        }
    }
    else
    {
        if ((1.0f + cos) > EPSILON)
        {
            r32 angle = acosf(-cos);
            r32 recipSin = 1.0f / sinf(angle);

            startt = sinf((1.0f - t) * angle) * recipSin;
            endt = sinf(angle * t) * recipSin;
        }
        else
        {
            startt = t - 1.0f;
            endt = t;
        }
    }

    q = (start * startt) + (end * endt);
}

// NOTE: From Essential Math, based on "Hacking Quaternions", Jonathan Blow, http://number-none.com/product/Hacking%20Quaternions/
inline void ApproxSlerp(quat &q, const quat &start, r32 t, const quat &end)
{
    r32 cos = Dot(start, end);

    r32 factor = 1.0f - 0.7878088f * cos;
    r32 k = 0.5069269f;
    factor *= factor;
    k *= factor;

    r32 b = 2 * k,
        c = -3 * k,
        d = 1 + k;

    t = t * (b * t + c) + d;

    q = end * t;

    if (cos >= EPSILON)
    {
        q += (1.0f - t) * start; 
    }
    else
    {
        q += (t - 1.0f) * start;
    }
}

#endif

