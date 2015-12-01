#ifndef MAT3_H
#define MAT3_H

#include "vec3.h"

union mat3
{
    struct
    {
        r32 xx, xy, xz,
            yx, yy, yz,
            zx, zy, zz;
    };
    struct
    {
        v3 x, y, z;
    };
    r32 m[9];
};
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

    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;

    return result;
}

inline mat3 operator+(const mat3 &a, const r32 &b)
{
    mat3 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;

    return result;
}

inline mat3 operator+(const r32 &b, const mat3 &a)
{
    mat3 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;

    return result;
}

inline mat3 operator+(const mat3 &a, const mat3 &b)
{
    mat3 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline mat3 operator-(const mat3 &a, const r32 &b)
{
    mat3 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;

    return result;
}

inline mat3 operator-(const r32 &b, const mat3 &a)
{
    mat3 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;

    return result;
}

inline mat3 operator-(const mat3 &a, const mat3 &b)
{
    mat3 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline mat3 operator*(const mat3 &a, const r32 &b)
{
    mat3 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}

inline mat3 operator*(const r32 &b, const mat3 &a)
{
    mat3 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}

// NOTE: row vector * matrix
inline v3 operator*(const v3 &a, const mat3 &b)
{
    v3 result;

    result.x = a.x * b.xx + a.y * b.yx + a.z * b.zx;
    result.y = a.x * b.xy + a.y * b.yy + a.z * b.zy;
    result.z = a.x * b.xz + a.y * b.yz + a.z * b.zz;

    return result;
}

// NOTE: matrix * column vector
inline v3 operator*(const mat3 &a, const v3 &b)
{
    v3 result;

    result.x = a.xx * b.x + a.xy * b.y + a.xz * b.z;
    result.y = a.yx * b.x + a.yy * b.y + a.yz * b.z;
    result.z = a.zx * b.x + a.zy * b.y + a.zz * b.z;

    return result;
}

inline mat3 operator*(const mat3 &a, const mat3 &b)
{
    mat3 result;

    result.xx = a.xx * b.xx + a.xy * b.yx + a.xz * b.zx;
    result.xy = a.xx * b.xy + a.xy * b.yy + a.xz * b.zy;
    result.xz = a.xx * b.xz + a.xy * b.yz + a.xz * b.zz;

    result.yx = a.yx * b.xx + a.yy * b.yx + a.yz * b.zx;
    result.yy = a.yx * b.xy + a.yy * b.yy + a.yz * b.zy;
    result.yz = a.yx * b.xz + a.yy * b.yz + a.yz * b.zz;

    result.zx = a.zx * b.xx + a.zy * b.yx + a.zz * b.zx;
    result.zy = a.zx * b.xy + a.zy * b.yy + a.zz * b.zy;
    result.zz = a.zx * b.xz + a.zy * b.yz + a.zz * b.zz;

    return result;
}

inline mat3 operator/(const mat3 &a, const r32 &b)
{
    mat3 result;

    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;

    return result;
}

inline mat3 operator/(const r32 &b, const mat3 &a)
{
    mat3 result;

    result.x = a.x / b;
    result.y = a.y / b;
    result.z = a.z / b;

    return result;
}

inline mat3 &operator+=(mat3 &a, const r32 &b)
{
    a.x = a.x + b;
    a.y = a.y + b;
    a.z = a.z + b;

    return a;
}

inline mat3 &operator+=(mat3 &a, const mat3 &b)
{
    a.x = a.x + b.x;
    a.y = a.y + b.y;
    a.z = a.z + b.z;

    return a;
}

inline mat3 &operator-=(mat3 &a, const r32 &b)
{
    a.x -= b;
    a.y -= b;
    a.z -= b;

    return a;
}

inline mat3 &operator-=(mat3 &a, const mat3 &b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;

    return a;
}

inline mat3 &operator*=(mat3 &a, const r32 &b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;

    return a;
}

// NOTE: row vector *= matrix
inline v3 &operator*=(v3 &a, const mat3 &b)
{
    a = a * b;

    return a;
}

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
    for(u32 i = 0; i < 9; ++i)
    {
        if(!IsEqual(a.m[i], b.m[i]))
            return false;
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

inline mat3 Transpose(const mat3 &m)
{
    mat3 result;

    result.xx = m.xx;
    result.xy = m.yx;
    result.xz = m.zx;
    result.yx = m.xy;
    result.yy = m.yy;
    result.yz = m.zy;
    result.zx = m.xz;
    result.zy = m.yz;
    result.zz = m.zz;
    
    return result;
}

inline void TransposeModify(mat3 &m)
{
    r32 temp = m.xy;
    m.xy = m.yx;
    m.yx = temp;

    temp = m.xz;
    m.xz = m.zx;
    m.zx = temp;

    temp = m.yz;
    m.yz = m.zy;
    m.zy = temp;
}

inline mat3 Adjoint(const mat3 &m)
{
    mat3 result;

    result.xx = (m.yy * m.zz - m.yz * m.zy);
    result.xy = (m.xy * m.zz - m.xz * m.zy);
    result.xz = (m.xy * m.yz - m.xz * m.yy);

    result.yx = (m.yx * m.zz - m.yz * m.zx);
    result.yy = (m.xx * m.zz - m.xz * m.zx);
    result.yz = (m.xx * m.yz - m.xz * m.yx);
    
    result.zx = (m.yx * m.zy - m.yy * m.zx);
    result.zy = (m.xx * m.zy - m.xy * m.zx);
    result.zz = (m.xx * m.yy - m.xy * m.yx);

    return result;
}

inline r32 Determinant(const mat3 &m)
{
    return (m.xx * (m.yy * m.zz - m.yz * m.zy)
          - m.xy * (m.yx * m.zz - m.yz * m.zx)
          + m.xz * (m.yx * m.zy - m.yy * m.zx));
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
    
    result = invdet * Adjoint(m);

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

#endif

