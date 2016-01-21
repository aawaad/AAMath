#ifndef MAT3_H
#define MAT3_H

#include "aamath.h"
#include "vec3.h"
#include "quat.h"

namespace aam
{

// NOTE: Column vectors, column-major matrices
typedef union _mat3
{
    struct
    {
        /* NOTE: row-major
        r32 xx, xy, xz,
            yx, yy, yz,
            zx, zy, zz;
        */

        // NOTE: Column-major
        r32 xx, yx, zx,
            xy, yy, zy,
            xz, yz, zz;
    };
    
    struct
    {
        vec3 x, y, z;
    };

    vec3 v[3];
    r32 m[3][3];
} mat3;
//
// NOTE: Static constants
//

static const mat3 MAT3_IDENTITY = {1.0f, 0.0f, 0.0f,
                                   0.0f, 1.0f, 0.0f,
                                   0.0f, 0.0f, 1.0f};

//
// NOTE: Operators
//

inline mat3 operator-(const mat3 &a)
{
    mat3 result;

    result.v[0] = -a.v[0];
    result.v[1] = -a.v[1];
    result.v[2] = -a.v[2];

    return result;
}

inline mat3 operator+(const mat3 &a, const r32 &b)
{
    mat3 result;

    result.v[0] = a.v[0] + b;
    result.v[1] = a.v[1] + b;
    result.v[2] = a.v[2] + b;

    return result;
}

inline mat3 operator+(const r32 &b, const mat3 &a)
{
    mat3 result;

    result.v[0] = a.v[0] + b;
    result.v[1] = a.v[1] + b;
    result.v[2] = a.v[2] + b;

    return result;
}

inline mat3 operator+(const mat3 &a, const mat3 &b)
{
    mat3 result;

    result.v[0] = a.v[0] + b.v[0];
    result.v[1] = a.v[1] + b.v[1];
    result.v[2] = a.v[2] + b.v[2];

    return result;
}

inline mat3 operator-(const mat3 &a, const r32 &b)
{
    mat3 result;

    result.v[0] = a.v[0] - b;
    result.v[1] = a.v[1] - b;
    result.v[2] = a.v[2] - b;

    return result;
}

/*inline mat3 operator-(const r32 &b, const mat3 &a)
{
    mat3 result;

    result.v[0] = a.v[0] - b.v[0];
    result.v[1] = a.v[1] - b.v[1];
    result.v[2] = a.v[2] - b.v[2];

    return result;
}*/

inline mat3 operator-(const mat3 &a, const mat3 &b)
{
    mat3 result;

    result.v[0] = a.v[0] - b.v[0];
    result.v[1] = a.v[1] - b.v[1];
    result.v[2] = a.v[2] - b.v[2];

    return result;
}

inline mat3 operator*(const mat3 &a, const r32 &b)
{
    mat3 result;

    result.v[0] = a.v[0] * b;
    result.v[1] = a.v[1] * b;
    result.v[2] = a.v[2] * b;

    return result;
}

/*inline mat3 operator*(const r32 &b, const mat3 &a)
{
    mat3 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}*/

/* NOTE: row vector * matrix
inline vec3 operator*(const vec3 &a, const mat3 &b)
{
    vec3 result;

    result.x = a.x * b.xx + a.y * b.yx + a.z * b.zx;
    result.y = a.x * b.xy + a.y * b.yy + a.z * b.zy;
    result.z = a.x * b.xz + a.y * b.yz + a.z * b.zz;

    return result;
}*/

// NOTE: matrix * column vector
inline vec3 operator*(const mat3 &m, const vec3 &v)
{
    vec3 result;

    result.x = m.xx * v.x + m.yx * v.y + m.zx * v.z;
    result.y = m.xy * v.x + m.yy * v.y + m.zy * v.z;
    result.z = m.xz * v.x + m.yz * v.y + m.zz * v.z;

    return result;
}

// NOTE: m.xx = a.xx * b.xx + a.xy * b.yx + a.xz * b.zx
//       x axis * axis x
//       y axis * axis y
//       z axis * axis z
inline mat3 operator*(const mat3 &a, const mat3 &b)
{
    mat3 result;

    result.m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0];
    result.m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1];
    result.m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2];

    result.m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0];
    result.m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1];
    result.m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2];

    result.m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0];
    result.m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1];
    result.m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2];

    return result;
}

inline mat3 operator/(const mat3 &a, const r32 &b)
{
    mat3 result;

    r32 r = 1.0f / b;

    result.x = a.x * r;
    result.y = a.y * r;
    result.z = a.z * r;

    return result;
}

/*inline mat3 operator/(const r32 &b, const mat3 &a)
{
    mat3 result;

    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;

    return result;
}*/

inline mat3 &operator+=(mat3 &a, const r32 &b)
{
    a.v[0] = a.v[0] + b;
    a.v[1] = a.v[1] + b;
    a.v[2] = a.v[2] + b;

    return a;
}

inline mat3 &operator+=(mat3 &a, const mat3 &b)
{
    a.v[0] += b.v[0];
    a.v[1] += b.v[1];
    a.v[2] += b.v[2];

    return a;
}

inline mat3 &operator-=(mat3 &a, const r32 &b)
{
    a.v[0] -= b;
    a.v[1] -= b;
    a.v[2] -= b;

    return a;
}

inline mat3 &operator-=(mat3 &a, const mat3 &b)
{
    a.v[0] -= b.v[0];
    a.v[1] -= b.v[1];
    a.v[2] -= b.v[2];

    return a;
}

inline mat3 &operator*=(mat3 &a, const r32 &b)
{
    a.v[0] *= b;
    a.v[1] *= b;
    a.v[2] *= b;

    return a;
}

/* NOTE: row vector *= matrix
inline vec3 &operator*=(vec3 &a, const mat3 &b)
{
    a = a * b;

    return a;
}*/

inline mat3 &operator*=(mat3 &a, const mat3 &b)
{
    a = a * b;

    return a;
}

inline mat3 &operator/=(mat3 &a, const r32 &b)
{
    a = a / b;

    return a;
}

inline b32 operator==(const mat3 &a, const mat3 &b)
{
    for(u32 y = 0; y < 3; ++y)
    {
        for(u32 x = 0; x < 3; ++x)
        {
            if(!AreEqual(a.m[y][x], b.m[y][x]))
                return false;
        }
    }

    return true;
}

inline b32 operator!=(const mat3 &a, const mat3 &b)
{
    return !(a == b);
}

//
// NOTE: Functions
//

inline mat3 Transposed(const mat3 &m)
{
    mat3 result;

    result.m[0][0] = m.m[0][0];
    result.m[0][1] = m.m[1][0];
    result.m[0][2] = m.m[2][0];
    result.m[1][0] = m.m[0][1];
    result.m[1][1] = m.m[1][1];
    result.m[1][2] = m.m[2][1];
    result.m[2][0] = m.m[0][2];
    result.m[2][1] = m.m[1][2];
    result.m[2][2] = m.m[2][2];
    
    return result;
}

inline void Transpose(mat3 &m)
{
    r32 temp = m.m[0][1];
    m.m[0][1] = m.m[1][0];
    m.m[1][0] = temp;

    temp = m.m[0][2];
    m.m[0][2] = m.m[2][0];
    m.m[2][0] = temp;

    temp = m.m[1][2];
    m.m[1][2] = m.m[2][1];
    m.m[2][1] = temp;
}

inline mat3 Adjoint(const mat3 &m)
{
    mat3 result;

    result.xx = m.yy * m.zz - m.zy * m.yz;
    result.yx = m.xy * m.zz - m.zy * m.xz;
    result.zx = m.xy * m.yz - m.yy * m.xz;

    result.xy = m.yx * m.zz - m.yz * m.zx;
    result.yy = m.xx * m.zz - m.zx * m.xz;
    result.zy = m.xx * m.yz - m.yx * m.xz;

    result.xz = m.yx * m.zy - m.zx * m.yy;
    result.yz = m.xx * m.zy - m.zx * m.xy;
    result.zz = m.xx * m.yy - m.yx * m.xy;

    return result;
}

inline r32 Determinant(const mat3 &m)
{
    return (m.xx * (m.yy * m.zz - m.zy * m.yz)
          - m.yx * (m.xy * m.zz - m.zy * m.xz)
          + m.zx * (m.xy * m.yz - m.yy * m.zx));
}

inline mat3 Inverse(const mat3 &m)
{
    mat3 result;

    r32 det = Determinant(m);

    if(IsZero(det))
    {
        // NOTE: assert?
        result = MAT3_IDENTITY;
        return result;
    }

    r32 invdet = 1.0f / det;
    
    result = Adjoint(m) * invdet;

    return result;
}

inline mat3 Hadamard(const mat3 &a, const mat3 &b)
{
    mat3 result;

    result.x = Hadamard(a.x, b.x);
    result.y = Hadamard(a.y, b.y);
    result.z = Hadamard(a.z, b.z);

    return result;
}

// NOTE: Rotation by Euler (Z*Y*X)
inline void SetRotation(mat3 &m, const r32 x, const r32 y, const r32 z)
{
    r32 sx, cx;
    SinCos(x, sx, cx);

    r32 sy, cy;
    SinCos(y, sy, cy);

    r32 sz, cz;
    SinCos(z, sz, cz);

    m.xx = cy * cz;
    m.yx = -(cy * sz);
    m.zx = sy;
    m.xy = (sx * sy * cz) + (cx * sz);
    m.yy = -(sx * sy * sz) + (cx * cz);
    m.zy = -(sx * cy);
    m.xz = -(cx * sy * cz) + (sx * sz);
    m.yz = (cx * sy * sz) + (sx * cz);
    m.zz = cx * cy;
}

// NOTE: Proxy for above
//       Rotation by Euler (Z*Y*X)
inline void SetRotation(mat3 &m, const vec3 &v)
{
    SetRotation(m, v.x, v.y, v.z);
}

// NOTE: Axis angle rotation
inline void SetRotation(mat3 &m, vec3 v, r32 a)
{
    r32 s, c, t;
    SinCos(a, s, c);
    t = 1.0f - c;

    Normalize(v);

    r32 tx = t * v.x, ty = t * v.y, tz = t * v.z,
        sx = s * v.x, sy = s * v.y, sz = s * v.z,
        txy = tx * v.y, tyz = tx * v.z, txz = tx * v.z;

    m.xx = tx * v.x + c;
    m.yx = txy - sz;
    m.zx = txz + sy;
    m.xy = txy + sz;
    m.yy = ty * v.y + c;
    m.zy = tyz - sx;
    m.xz = txz - sy;
    m.yz = tyz + sx;
    m.zz = tz * v.z + c;
}

inline void SetRotation(mat3 &m, quat &q)
{
    // NOTE: Assert unit quaternion

    r32 xs, ys, zs,
        wx, wy, wz,
        xx, xy, xz,
        yy, yz, zz;

    xs = q.x + q.x;
    ys = q.y + q.y;
    zs = q.z + q.z;
    wx = q.w * xs;
    wy = q.w * ys;
    wz = q.w * zs;
    xx = q.x * xs;
    xy = q.x * ys;
    xz = q.x * zs;
    yy = q.y * ys;
    yz = q.y * zs;
    zz = q.z * zs;

    m.xx = 1.0f - (yy + zz);
    m.yx = xy - wz;
    m.zx = xz + wy;

    m.xy = xy + wz;
    m.yy = 1.0f - (xx + zz);
    m.zy = yz - wx;

    m.xz = xz - wy;
    m.yz = yz + wx;
    m.zz = 1.0f - (xx + yy);
}

inline void SetRotationX(mat3 &m, const r32 a)
{
    r32 s, c;
    SinCos(a, s, c);

    m.x = Vec3(1.0f, 0.0f, 0.0f);
    m.y = Vec3(0.0f, c, -s);
    m.z = Vec3(0.0f, s, c);
}

inline void SetRotationY(mat3 &m, const r32 a)
{
    r32 s, c;
    SinCos(a, s, c);

    m.x = Vec3(c, 0.0f, s);
    m.y = Vec3(0.0f, 1.0f, 0.0f);
    m.z = Vec3(-s, 0.0f, c);
}

inline void SetRotationZ(mat3 &m, const r32 a)
{
    r32 s, c;
    SinCos(a, s, c);

    m.x = Vec3(c, s, 0.0f);
    m.y = Vec3(-s, c, 0.0f);
    m.z = Vec3(0.0f, 0.0f, 1.0f);
}

inline void SetScale(mat3 &m, const r32 x, const r32 y, const r32 z)
{
    m.x = Vec3(x, 0.0f, 0.0f);
    m.y = Vec3(0.0f, y, 0.0f);
    m.z = Vec3(0.0f, 0.0f, z);
}

inline void SetScale(mat3 &m, const vec3 &v)
{
    SetScale(m, v.x, v.y, v.z);
}

// NOTE: Rotation by Euler (Z*Y*X)
inline mat3 Mat3Rotation(const r32 x, const r32 y, const r32 z)
{
    mat3 result;

    r32 sx, cx;
    SinCos(x, sx, cx);

    r32 sy, cy;
    SinCos(y, sy, cy);

    r32 sz, cz;
    SinCos(z, sz, cz);

    result.xx = cy * cz;
    result.yx = -(cy * sz);
    result.zx = sy;
    result.xy = (sx * sy * cz) + (cx * sz);
    result.yy = -(sx * sy * sz) + (cx * cz);
    result.zy = -(sx * cy);
    result.xz = -(cx * sy * cz) + (sx * sz);
    result.yz = (cx * sy * sz) + (sx * cz);
    result.zz = cx * cy;

    return result;
}

// NOTE: Proxy for above
//       Rotation by Euler (Z*Y*X)
inline mat3 Mat3Rotation(const vec3 &v)
{
    return Mat3Rotation(v.x, v.y, v.z);
}

// NOTE: Axis angle rotation
inline mat3 Mat3Rotation(const vec3 &v, const r32 a)
{
    mat3 result;

    r32 s, c, t;
    SinCos(a, s, c);
    t = 1.0f - c;

    Normalize((vec3 &)v);

    r32 tx = t * v.x, ty = t * v.y, tz = t * v.z,
        sx = s * v.x, sy = s * v.y, sz = s * v.z,
        txy = tx * v.y, tyz = tx * v.z, txz = tx * v.z;

    result.xx = tx * v.x + c;
    result.yx = txy - sz;
    result.zx = txz + sy;
    result.xy = txy + sz;
    result.yy = ty * v.y + c;
    result.zy = tyz - sx;
    result.xz = txz - sy;
    result.yz = tyz + sx;
    result.zz = tz * v.z + c;

    return result;
}

inline mat3 Mat3Rotation(const quat &q)
{
    mat3 result;

    // NOTE: Assert unit quaternion

    r32 xs, ys, zs,
        wx, wy, wz,
        xx, xy, xz,
        yy, yz, zz;

    xs = q.x + q.x;
    ys = q.y + q.y;
    zs = q.z + q.z;
    wx = q.w * xs;
    wy = q.w * ys;
    wz = q.w * zs;
    xx = q.x * xs;
    xy = q.x * ys;
    xz = q.x * zs;
    yy = q.y * ys;
    yz = q.y * zs;
    zz = q.z * zs;

    result.xx = 1.0f - (yy + zz);
    result.yx = xy - wz;
    result.zx = xz + wy;

    result.xy = xy + wz;
    result.yy = 1.0f - (xx + zz);
    result.zy = yz - wx;

    result.xz = xz - wy;
    result.yz = yz + wx;
    result.zz = 1.0f - (xx + yy);

    return result;
}

inline mat3 Mat3RotationX(const r32 a)
{
    mat3 result;

    r32 s, c;
    SinCos(a, s, c);

    result.x = Vec3(1.0f, 0.0f, 0.0f);
    result.y = Vec3(0.0f, c, -s);
    result.z = Vec3(0.0f, s, c);

    return result;
}

inline mat3 Mat3RotationY(const r32 a)
{
    mat3 result;

    r32 s, c;
    SinCos(a, s, c);

    result.x = Vec3(c, 0.0f, s);
    result.y = Vec3(0.0f, 1.0f, 0.0f);
    result.z = Vec3(-s, 0.0f, c);

    return result;
}

inline mat3 Mat3RotationZ(const r32 a)
{
    mat3 result;

    r32 s, c;
    SinCos(a, s, c);

    result.x = Vec3(c, s, 0.0f);
    result.y = Vec3(-s, c, 0.0f);
    result.z = Vec3(0.0f, 0.0f, 1.0f);

    return result;
}

inline mat3 Mat3Scaling(const r32 x, const r32 y, const r32 z)
{
    mat3 result;
    
    result.x = Vec3(x, 0.0f, 0.0f);
    result.y = Vec3(0.0f, y, 0.0f);
    result.z = Vec3(0.0f, 0.0f, z);

    return result;
}

inline mat3 Mat3Scaling(const vec3 &v)
{
    return Mat3Scaling(v.x, v.y, v.z);
}

// NOTE: See Mike Day, Extracting Euler Angles from a Rotation Matrix
// https://d3cw3dd2w32x2b.cloudfront.net/wp-content/uploads/2012/07/euler-angles1.pdf}
inline vec3 GetEulerAngles(const mat3 &m)
{
    vec3 result;

    result.x = atan2f(m.yz, m.zz);
    r32 c2 = AASqrt((m.xx * m.xx) + (m.xy * m.xy));
    result.y = atan2f(-m.xz, c2);
    r32 s, c;
    SinCos(result.x, s, c);
    result.z = atan2f((s * m.zx) - (c * m.yx), (c * m.yy) - (s * m.zy));

    return result;
}

inline void GetAxisAngle(const mat3 &m, vec3 &axis, r32 &angle)
{
    r32 trace = m.xx + m.yy + m.zz;
    angle = acosf(0.5f * (trace - 1.0f));

    if(IsZero(angle))
    {
        // NOTE: Could be anything if angle is zero, so return the up/Y axis
        axis = VEC3_YAXIS;
    }
    else if(angle < PI - EPSILON)
    {
        axis = Vec3(m.zy - m.yz, m.xz - m.zx, m.yx - m.xy);
        Normalize(axis);
    }
    else
    {
        r32 sqrt, oneOverSqrt;

        if(m.xx > m.yy && m.xx > m.zz)
        {
            sqrt = AASqrt(m.xx - m.yy - m.zz + 1.0f);
            axis.x = 0.5f * sqrt;
            oneOverSqrt = 1.0f / sqrt;
            axis.y = m.xy * oneOverSqrt;
            axis.z = m.xz * oneOverSqrt;
        }
        else if(m.yy > m.zz)
        {
            sqrt = AASqrt(m.yy - m.xx - m.zz + 1.0f);
            axis.y = 0.5f * sqrt;
            oneOverSqrt = 1.0f / sqrt;
            axis.x = m.xy * oneOverSqrt;
            axis.z = m.yz * oneOverSqrt;
        }
        else
        {
            sqrt = AASqrt(m.zz - m.xx - m.yy + 1.0f);
            axis.z = 0.5f * sqrt;
            oneOverSqrt = 1.0f / sqrt;
            axis.x = m.xz * oneOverSqrt;
            axis.y = m.yz * oneOverSqrt;
        }
    }
}

inline quat GetQuaternion(const mat3 &m)
{
    quat result;
    r32 trace = 1.0f + m.xx + m.yy + m.zz;

    if (trace > EPSILON)
    {
        r32 s = AASqrt(trace) * 2.0f,
            oneOverS = 1.0f / s;
        result.w = s * 0.25f;
        result.x = (m.zy - m.yz) * oneOverS;
        result.y = (m.xz - m.zx) * oneOverS;
        result.z = (m.yx - m.xy) * oneOverS;
    }
    else if (m.xx > m.yy && m.xx > m.zz)
    {
        r32 s = AASqrt(1.0f + m.xx - m.yy - m.zz) * 2.0f,
            oneOverS = 1.0f / s;
        result.w = (m.zy - m.yz) * oneOverS;
        result.x = s * 0.25f;
        result.y = (m.xy + m.yx) * oneOverS;
        result.z = (m.xz + m.zx) * oneOverS;
    }
    else if (m.yy > m.zz)
    {
        r32 s = AASqrt(1.0f + m.yy - m.xx - m.zz) * 2.0f,
            oneOverS = 1.0f / s;
        result.w = (m.xz - m.zx) * oneOverS;
        result.x = (m.xy + m.yx) * oneOverS;
        result.y = s * 0.25f;
        result.z = (m.yz + m.zy) * oneOverS;
    }
    else
    {
        r32 s = AASqrt(1.0f + m.zz - m.xx - m.yy) * 2.0f,
            oneOverS = 1.0f / s;
        result.w = (m.yx - m.xy) * oneOverS;
        result.x = (m.xz + m.zx) * oneOverS;
        result.y = (m.yz + m.zy) * oneOverS;
        result.z = s * 0.25f;
    }

    return result;
}

} // NOTE: Namespace

#endif

