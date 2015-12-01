#ifndef MAT4_H
#define MAT4_H

#include "vec4.h"
#include "mat3.h"

union mat4
{
    struct
    {
        r32 xx, xy, xz, xw,
            yx, yy, yz, yw,
            zx, zy, zz, zw,
            tx, ty, tz, w;
    };
    struct
    {
        v4 x, y, z, t;
    };
    r32 m[16];
};

//
// NOTE: Static constants
//

static const mat4 MAT4_IDENTITY = {1.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 1.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 1.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 1.0f};

//
// NOTE: Operators
//

inline mat4 operator-(const mat4 &a)
{
    mat4 result;

    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    result.t = -a.t;

    return result;
}

inline mat4 operator+(const mat4 &a, const r32 &b)
{
    mat4 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;
    result.t = a.t + b;

    return result;
}

inline mat4 operator+(const r32 &b, const mat4 &a)
{
    mat4 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;
    result.t = a.t + b;

    return result;
}

inline mat4 operator+(const mat4 &a, const mat4 &b)
{
    mat4 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.t = a.t + b.t;

    return result;
}

inline mat4 operator-(const mat4 &a, const r32 &b)
{
    mat4 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;
    result.t = a.t - b;

    return result;
}

inline mat4 operator-(const r32 &b, const mat4 &a)
{
    mat4 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;
    result.t = a.t - b;

    return result;
}

inline mat4 operator-(const mat4 &a, const mat4 &b)
{
    mat4 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.t = a.t - b.t;

    return result;
}

inline mat4 operator*(const mat4 &a, const r32 &b)
{
    mat4 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.t = a.t * b;

    return result;
}

inline mat4 operator*(const r32 &b, const mat4 &a)
{
    mat4 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.t = a.t * b;

    return result;
}

// NOTE: row vector * matrix
inline v4 operator*(const v4 &a, const mat4 &b)
{
    v4 result;

    result.x = a.x * b.xx + a.y * b.yx + a.z * b.zx + a.w * b.xw;
    result.y = a.x * b.xy + a.y * b.yy + a.z * b.zy + a.w * b.yw;
    result.z = a.x * b.xz + a.y * b.yz + a.z * b.zz + a.w * b.zw;
    result.w = a.x * b.tx + a.y * b.ty + a.z * b.tz + a.w * a.w;

    return result;
}

// NOTE: matrix * column vector
inline v4 operator*(const mat4 &a, const v4 &b)
{
    v4 result;

    result.x = a.xx * b.x + a.xy * b.y + a.xz * b.z + a.xw * b.w;
    result.y = a.yx * b.x + a.yy * b.y + a.yz * b.z + a.yw * b.w;
    result.z = a.zx * b.x + a.zy * b.y + a.zz * b.z + a.zw * b.w;
    result.w = a.tx * b.x + a.ty * b.y + a.tz * b.z + a.w * b.w;

    return result;
}

inline mat4 operator*(const mat4 &a, const mat4 &b)
{
    mat4 result;

    result.xx = a.xx * b.xx + a.xy * b.yx + a.xz * b.zx + a.xw * b.tx;
    result.xy = a.xx * b.xy + a.xy * b.yy + a.xz * b.zy + a.xw * b.ty;
    result.xz = a.xx * b.xz + a.xy * b.yz + a.xz * b.zz + a.xw * b.tz;
    result.xw = a.xx * b.xw + a.xy * b.yw + a.xz * b.zw + a.xw * b.w;

    result.yx = a.yx * b.xx + a.yy * b.yx + a.yz * b.zx + a.yw * b.tx;
    result.yy = a.yx * b.xy + a.yy * b.yy + a.yz * b.zy + a.yw * b.ty;
    result.yz = a.yx * b.xz + a.yy * b.yz + a.yz * b.zz + a.yw * b.tz;
    result.yw = a.yx * b.xw + a.yy * b.yw + a.yz * b.zw + a.yw * b.w;

    result.zx = a.zx * b.xx + a.zy * b.yx + a.zz * b.zx + a.zw * b.tx;
    result.zy = a.zx * b.xy + a.zy * b.yy + a.zz * b.zy + a.zw * b.ty;
    result.zz = a.zx * b.xz + a.zy * b.yz + a.zz * b.zz + a.zw * b.tz;
    result.zw = a.zx * b.xw + a.zy * b.yw + a.zz * b.zw + a.zw * b.w;

    result.tx = a.tx * b.xx + a.ty * b.yx + a.tz * b.zx + a.w * b.tx;
    result.ty = a.tx * b.xy + a.ty * b.yy + a.tz * b.zy + a.w * b.ty;
    result.tz = a.tx * b.xz + a.ty * b.yz + a.tz * b.zz + a.w * b.tz;
    result.w  = a.tx * b.xw + a.ty * b.yw + a.tz * b.zw + a.w * b.w;

    return result;
}

inline mat4 operator/(const mat4 &a, const r32 &b)
{
    mat4 result;

    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;
    result.t = a.t / b;

    return result;
}

inline mat4 operator/(const r32 &b, const mat4 &a)
{
    mat4 result;

    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;
    result.t = a.t / b;

    return result;
}

inline mat4 &operator+=(mat4 &a, const r32 &b)
{
    a.x = a.x + b;
    a.y = a.y + b;
    a.z = a.z + b;
    a.t = a.t + b;

    return a;
}

inline mat4 &operator+=(mat4 &a, const mat4 &b)
{
    a.x = a.x + b.x;
    a.y = a.y + b.y;
    a.z = a.z + b.z;
    a.t = a.t + b.t;

    return a;
}

inline mat4 &operator-=(mat4 &a, const r32 &b)
{
    a.x -= b;
    a.y -= b;
    a.z -= b;
    a.t -= b;

    return a;
}

inline mat4 &operator-=(mat4 &a, const mat4 &b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.t -= b.t;

    return a;
}

inline mat4 &operator*=(mat4 &a, const r32 &b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
    a.t *= b;

    return a;
}

// NOTE: row vector *= matrix
inline v4 &operator*=(v4 &a, const mat4 &b)
{
    a = a * b;

    return a;
}

inline mat4 &operator*=(mat4 &a, const mat4 &b)
{
    a = a * b;

    return a;
}

inline mat4 &operator/=(mat4 &a, const r32 &b)
{
    a = a / b;

    return a;
}

inline b32 operator==(const mat4 &a, const mat4 &b)
{
    for(u32 i = 0; i < 16; ++i)
    {
        if(!IsEqual(a.m[i], b.m[i]))
            return false;
    }

    return true;
}

inline b32 operator!=(const mat4 &a, const mat4 &b)
{
    return !(a == b);
}

//
// NOTE: Functions
//

inline mat4 Transpose(const mat4 &m)
{
    mat4 result;

    result.xx = m.xx;
    result.xy = m.yx;
    result.xz = m.zx;
    result.xw = m.tx;
    result.yx = m.xy;
    result.yy = m.yy;
    result.yz = m.zy;
    result.yw = m.ty;
    result.zx = m.xz;
    result.zy = m.yz;
    result.zz = m.zz;
    result.zw = m.tz;
    result.tx = m.xw;
    result.ty = m.yw;
    result.tz = m.zw;
    result.w = m.w;
    
    return result;
}

inline void TransposeModify(mat4 &m)
{
    r32 temp = m.xy;
    m.xy = m.yx;
    m.yx = temp;

    temp = m.xz;
    m.xz = m.zx;
    m.zx = temp;

    temp = m.xw;
    m.xw = m.tx;
    m.tx = temp;

    temp = m.yz;
    m.yz = m.zy;
    m.zy = temp;

    temp = m.yw;
    m.yw = m.ty;
    m.ty = temp;

    temp = m.zw;
    m.zw = m.tz;
    m.tz = temp;
}

inline mat4 Adjoint(const mat4 &m)
{
    mat4 result;

    result.xx = (m.yy * m.zz - m.yz * m.zy);
    result.xy = (m.xy * m.zz - m.xz * m.zy);
    result.xz = (m.xy * m.yz - m.xz * m.yy);

    result.yx = (m.yx * m.zz - m.yz * m.zx);
    result.yy = (m.xx * m.zz - m.xz * m.zx);
    result.yz = (m.xx * m.yz - m.xz * m.yx);
    
    result.zx = (m.yx * m.zy - m.yy * m.zx);
    result.zy = (m.xx * m.zy - m.xy * m.zx);
    result.zz = (m.xx * m.yy - m.xy * m.yx);

    result.xw = m.xw;
    result.xy = m.xy;
    result.xz = m.xz;

    result.t = m.t;

    return result;
}

inline r32 Determinant(const mat4 &m)
{
    return (m.xx * (m.yy * m.zz - m.yz * m.zy)
          - m.xy * (m.yx * m.zz - m.yz * m.zx)
          + m.xz * (m.yx * m.zy - m.yy * m.zx));
}

inline mat3 Upper3x3(const mat4 &m)
{
    mat3 result;

    result.x = m.x.xyz;
    result.y = m.y.xyz;
    result.z = m.z.xyz;

    return result;
}

inline mat4 Inverse(const mat4 &m)
{
    mat4 result;

    r32 det = Determinant(m);

    if(IsZero(det))
    {
        // NOTE: assert?
        result = MAT4_IDENTITY;
        return result;
    }

    r32 invdet = 1.0f / det;
    
    result = invdet * Adjoint(m);

    // NOTE: should probably do this directly
    result.t.xyz *= -Upper3x3(m);

    return result;
}

inline mat4 Hadamard(const mat4 &a, const mat4 &b)
{
    mat4 result;

    result.x = Hadamard(a.x, b.x);
    result.y = Hadamard(a.y, b.y);
    result.z = Hadamard(a.z, b.z);
    result.t = Hadamard(a.t, b.t);

    return result;
}

#endif

