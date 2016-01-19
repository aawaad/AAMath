#ifndef MAT4_H
#define MAT4_H

#include "aamath.h"
#include "vec3.h"
#include "vec4.h"
#include "mat3.h"
#include "quat.h"

// TODO: #define to switch between row/column major?

// NOTE: Column vectors, column-major matrices -- T * R * S * v
typedef union _mat4
{
    struct
    {
        /* NOTE: Row-major
        r32 xx, xy, xz, xw,
            yx, yy, yz, yw,
            zx, zy, zz, zw,
            tx, ty, tz, ww;
        */

        // NOTE: Column-major
        r32 xx, yx, zx, tx,
            xy, yy, zy, ty,
            xz, yz, zz, tz,
            xw, yw, zw, ww;
    };
    /* NOTE: Row-major easy vector accessors
    struct
    {
        vec4 x, y, z, t;
    };
    */
    // NOTE: Column-major component accessors (e.g. x = Xx, Yx, Zx, Tx);
    struct
    {
        vec4 x, y, z, w;
    };

    vec4 v[4];
    r32 m[4][4];
} mat4;

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

    result.v[0] = -a.v[0];
    result.v[1] = -a.v[1];
    result.v[2] = -a.v[2];
    result.v[3] = -a.v[3];

    return result;
}

inline mat4 operator+(const mat4 &a, const r32 &b)
{
    mat4 result;

    result.v[0] = a.v[0] + b;
    result.v[1] = a.v[1] + b;
    result.v[2] = a.v[2] + b;
    result.v[3] = a.v[3] + b;

    return result;
}

/*inline mat4 operator+(const r32 &b, const mat4 &a)
{
    mat4 result;

    result.v[0] = a.v[0] + b;
    result.v[1] = a.v[1] + b;
    result.v[2] = a.v[2] + b;
    result.v[3] = a.v[3] + b;

    return result;
}*/

inline mat4 operator+(const mat4 &a, const mat4 &b)
{
    mat4 result;

    result.v[0] = a.v[0] + b.v[0];
    result.v[1] = a.v[1] + b.v[1];
    result.v[2] = a.v[2] + b.v[2];
    result.v[3] = a.v[3] + b.v[3];

    return result;
}

inline mat4 operator-(const mat4 &a, const r32 &b)
{
    mat4 result;

    result.v[0] = a.v[0] - b;
    result.v[1] = a.v[1] - b;
    result.v[2] = a.v[2] - b;
    result.v[3] = a.v[3] - b;
    
    return result;
}

/*inline mat4 operator-(const r32 &b, const mat4 &a)
{
    mat4 result;

    result.v[0] = a.v[0] - b.v[0];
    result.v[1] = a.v[1] - b.v[1];
    result.v[2] = a.v[2] - b.v[2];
    result.v[3] = a.v[3] - b.v[3];

    return result;
}*/

inline mat4 operator-(const mat4 &a, const mat4 &b)
{
    mat4 result;

    result.v[0] = a.v[0] - b.v[0];
    result.v[1] = a.v[1] - b.v[1];
    result.v[2] = a.v[2] - b.v[2];
    result.v[3] = a.v[3] - b.v[3];

    return result;
}

inline mat4 operator*(const mat4 &a, const r32 &b)
{
    mat4 result;

    result.v[0] = a.v[0] * b;
    result.v[1] = a.v[1] * b;
    result.v[2] = a.v[2] * b;
    result.v[3] = a.v[3] * b;

    return result;
}

/*inline mat4 operator*(const r32 &b, const mat4 &a)
{
    mat4 result;

    result.v[0] = a.v[0] * b;
    result.v[1] = a.v[1] * b;
    result.v[2] = a.v[2] * b;
    result.v[3] = a.v[3] * b;

    return result;
}*/

/* NOTE: row vector * matrix
inline vec4 operator*(const vec4 &v, const mat4 &m)
{
    vec4 result;

    result.x = v.x * m.xx + v.y * m.yx + v.z * m.zx + v.w * m.tx;
    result.y = v.x * m.xy + v.y * m.yy + v.z * m.zy + v.w * m.ty;
    result.z = v.x * m.xz + v.y * m.yz + v.z * m.zz + v.w * m.tz;
    result.w = v.x * m.xw + v.y * m.yw + v.z * m.zw + v.w * m.w;

    return result;
}
*/

// NOTE: matrix * column vector
inline vec4 operator*(const mat4 &m, const vec4 &v)
{
    vec4 result;

    result.x = m.xx * v.x + m.yx * v.y + m.zx * v.z + m.tx * v.w;
    result.y = m.xy * v.x + m.yy * v.y + m.zy * v.z + m.ty * v.w;
    result.z = m.xz * v.x + m.yz * v.y + m.zz * v.z + m.tz * v.w;
    result.w = m.xw * v.x + m.yw * v.y + m.zw * v.z + m.ww * v.w;

    return result;
}

inline mat4 operator*(const mat4 &a, const mat4 &b)
{
    mat4 result;

    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            result.m[i][j] = 0;
            for(int k = 0; k < 4; ++k)
            {
                result.m[i][j] += a.m[k][j] * b.m[i][k];
            }
        }
    }

    return result;
}

inline mat4 operator/(const mat4 &a, const r32 &b)
{
    mat4 result;

    r32 r = 1.0f / b;

    result.v[0] = a.v[0] * r;
    result.v[1] = a.v[1] * r;
    result.v[2] = a.v[2] * r;
    result.v[3] = a.v[3] * r;

    return result;
}

/*inline mat4 operator/(const r32 &b, const mat4 &a)
{
    mat4 result;

    r32 r = 1.0f / b;

    result.v[0] = a.v[0] * r;
    result.v[1] = a.v[1] * r;
    result.v[2] = a.v[2] * r;
    result.v[3] = a.v[3] * r;

    return result;
}*/

inline mat4 &operator+=(mat4 &a, const r32 &b)
{
    a.v[0] += b;
    a.v[1] += b;
    a.v[2] += b;
    a.v[3] += b;

    return a;
}

inline mat4 &operator+=(mat4 &a, const mat4 &b)
{
    a.v[0] += b.v[0];
    a.v[1] += b.v[1];
    a.v[2] += b.v[2];
    a.v[3] += b.v[3];

    return a;
}

inline mat4 &operator-=(mat4 &a, const r32 &b)
{
    a.v[0] -= b;
    a.v[1] -= b;
    a.v[2] -= b;
    a.v[3] -= b;

    return a;
}

inline mat4 &operator-=(mat4 &a, const mat4 &b)
{
    a.v[0] -= b.v[0];
    a.v[1] -= b.v[1];
    a.v[2] -= b.v[2];
    a.v[3] -= b.v[3];

    return a;
}

inline mat4 &operator*=(mat4 &a, const r32 &b)
{
    a.v[0] *= b;
    a.v[1] *= b;
    a.v[2] *= b;
    a.v[3] *= b;

    return a;
}

/* NOTE: row vector *= matrix
inline vec4 &operator*=(vec4 &v, const mat4 &m)
{
    v = v * m;

    return v;
}*/

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
    for(u32 y = 0; y < 4; ++y)
    {
        for(u32 x = 0; x < 4; ++x)
        {
            if(!AreEqual(a.m[y][x], b.m[y][x]))
                return false;
        }
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

inline mat4 Transposed(const mat4 &m)
{
    mat4 result;

    for(u32 i = 0; i < 4; ++i)
    {
        for(u32 j = 0; j < 4; ++j)
        {
            result.m[i][j] = m.m[j][i];
        }
    }
    
    return result;
}

inline void Transpose(mat4 &m)
{
    r32 temp = m.m[0][1];
    m.m[0][1] = m.m[1][0];
    m.m[1][0] = temp;

    temp = m.m[0][2];
    m.m[0][2] = m.m[2][0];
    m.m[2][0] = temp;

    temp = m.m[0][3];
    m.m[0][3] = m.m[3][0];
    m.m[3][0] = temp;

    temp = m.m[1][2];
    m.m[1][2] = m.m[2][1];
    m.m[2][1] = temp;

    temp = m.m[1][3];
    m.m[1][3] = m.m[3][1];
    m.m[3][1] = temp;

    temp = m.m[2][3];
    m.m[2][3] = m.m[3][2];
    m.m[3][2] = temp;
}

inline mat3 Adjoint(const mat4 &m)
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

inline r32 Determinant(const mat4 &m)
{
    return (m.xx * (m.yy * m.zz - m.zy * m.yz)
          - m.yx * (m.xy * m.zz - m.zy * m.xz)
          + m.zx * (m.xy * m.yz - m.yy * m.xz));
}

// NOTE: Get matrix's upper 3x3 matrix (rotation + scaling)
inline mat3 Upper3x3(const mat4 &m)
{
    mat3 result;

    result.x = m.x.xyz;
    result.y = m.y.xyz;
    result.z = m.z.xyz;

    return result;
}

inline mat4 Mat4Identity()
{
    mat4 result;

    result.v[0] = { 1.0f, 0.0f, 0.0f, 0.0f };
    result.v[1] = { 0.0f, 1.0f, 0.0f, 0.0f };
    result.v[2] = { 0.0f, 0.0f, 1.0f, 0.0f };
    result.v[3] = { 0.0f, 0.0f, 0.0f, 1.0f };

    return result;
}

inline mat4 Inverse(const mat4 &m)
{
    mat4 result;

    r32 co1 = m.yy * m.zz - m.zy * m.yz,
        co2 = m.xy * m.zz - m.zy * m.xz,
        co3 = m.xy * m.yz - m.yy * m.xz;

    r32 det = m.xx * co1 - m.yx * co2 + m.zx * co3;

    if(!IsZero(det))
    {
        r32 invdet = 1.0f / det;

        // NOTE: Adjoint / det
        result.xx = invdet * co1;
        result.xy = invdet * co2;
        result.xz = invdet * co3;
        result.xw = 0;

        result.yx = invdet * (m.yx * m.zz - m.yz * m.zx);
        result.yy = invdet * (m.xx * m.zz - m.zx * m.xz);
        result.yz = invdet * (m.xx * m.yz - m.yx * m.xz);
        result.yw = 0;

        result.zx = invdet * (m.yx * m.zy - m.zx * m.yy);
        result.zy = invdet * (m.xx * m.zy - m.zx * m.xy);
        result.zz = invdet * (m.xx * m.yy - m.yx * m.xy);
        result.zw = 0;

        // NOTE: multiply translation by transposed 3x3
        result.tx = -result.xx * m.tx - result.yx * m.ty - result.zx * m.tz;
        result.ty = -result.xy * m.ty - result.yy * m.ty - result.zy * m.tz;
        result.tz = -result.xz * m.tz - result.yz * m.ty - result.zz * m.tz;
        result.ww = 1.0f;
    }
    else
    {
        // NOTE: Singular matrix
        Assert(false)
        result = MAT4_IDENTITY;
    }

    return result;
}

inline mat4 Hadamard(const mat4 &a, const mat4 &b)
{
    mat4 result;

    result.v[0] = Hadamard(a.v[0], b.v[0]);
    result.v[1] = Hadamard(a.v[1], b.v[1]);
    result.v[2] = Hadamard(a.v[2], b.v[2]);
    result.v[3] = Hadamard(a.v[3], b.v[3]);

    return result;
}

// NOTE: Rotation by Euler (Z*Y*Z)
inline void SetRotation(mat4 &m, const r32 x, const r32 y, const r32 z)
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
//       Rotation by Euler (Z*Y*Z)
inline void SetRotation(mat4 &m, const vec3 &v)
{
    SetRotation(m, v.x, v.y, v.z);
}

// NOTE: Proxy for above
//       Rotation by Euler (Z*Y*Z)
inline void SetRotation(mat4 &m, const vec4 &v)
{
    SetRotation(m, v.x, v.y, v.z);
}

// NOTE: Axis angle rotation
inline void SetRotation(mat4 &m, const vec3 &v, const r32 a)
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

// NOTE: Proxy for above
//       Axis angle rotation
inline void SetRotation(mat4 &m, vec4 v, const r32 a)
{
    SetRotation(m, v.xyz, a);
}

// NOTE: Set rotation from 3x3 rotation matrix
inline void SetRotation(mat4 &m, const mat3 &r)
{
    m.x.xyz = r.x;
    m.tx = 0;
    m.y.xyz = r.y;
    m.ty = 0;
    m.z.xyz = r.z;
    m.tz = 0;
    m.w.xyz = {};
    m.ww = 0;
}

// NOTE: Set rotation from quaternion
inline void SetRotation(mat4 &m, quat &q)
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

inline void SetRotationX(mat4 &m, const r32 a)
{
    r32 s, c;
    SinCos(a, s, c);

    m.x.xyz = Vec3(1.0f, 0.0f, 0.0f);
    m.y.xyz = Vec3(0.0f, c, -s);
    m.z.xyz = Vec3(0.0f, s, c);
}

inline void SetRotationY(mat4 &m, const r32 a)
{
    r32 s, c;
    SinCos(a, s, c);

    m.x.xyz = Vec3(c, 0.0f, s);
    m.y.xyz = Vec3(0.0f, 1.0f, 0.0f);
    m.z.xyz = Vec3(-s, 0.0f, c);
}

inline void SetRotationZ(mat4 &m, const r32 a)
{
    r32 s, c;
    SinCos(a, s, c);

    m.x.xyz = Vec3(c, s, 0.0f);
    m.y.xyz = Vec3(-s, c, 0.0f);
    m.z.xyz = Vec3(0.0f, 0.0f, 1.0f);
}

inline void SetScale(mat4 &m, const r32 x, const r32 y, const r32 z)
{
    m.x.xyz = Vec3(x, 0.0f, 0.0f);
    m.y.xyz = Vec3(0.0f, y, 0.0f);
    m.z.xyz = Vec3(0.0f, 0.0f, z);
}

inline void SetScale(mat4 &m, const vec3 &v)
{
    SetScale(m, v.x, v.y, v.z);
}

inline void SetScale(mat4 &m, const vec4 &v)
{
    SetScale(m, v.x, v.y, v.z);
}

inline void SetTranslation(mat4 &m, const vec3 &v)
{
    m.tx = v.x;
    m.ty = v.y;
    m.tz = v.z;
}

inline void SetTranslation(mat4 &m, const vec4 &v)
{
    SetTranslation(m, v.xyz);
}

// NOTE: Rotation by Euler (Z*X*Y)
inline mat4 Mat4Rotation(const r32 x, const r32 y, const r32 z)
{
    mat4 result;

    r32 sx, cx;
    SinCos(x, sx, cx);

    r32 sy, cy;
    SinCos(y, sy, cy);

    r32 sz, cz;
    SinCos(z, sz, cz);

    result.xx = cy * cz;
    result.yx = -(cy * sz);
    result.zx = sy;
    result.tx = 0;

    result.xy = (sx * sy * cz) + (cx * sz);
    result.yy = -(sx * sy * sz) + (cx * cz);
    result.zy = -(sx * cy);
    result.ty = 0;

    result.xz = -(cx * sy * cz) + (sx * sz);
    result.yz = (cx * sy * sz) + (sx * cz);
    result.zz = cx * cy;
    result.tz = 0;

    result.xw = 0;
    result.yw = 0;
    result.zw = 0;
    result.ww = 1.0f;

    return result;
}

// NOTE: Proxy for above
// NOTE: Rotation by Euler (Z*X*Y)
inline mat4 Mat4Rotation(const vec3 &v)
{
    return Mat4Rotation(v.x, v.y, v.z);
}

// NOTE: Proxy for above
// NOTE: Rotation by Euler (Z*X*Y)
inline mat4 Mat4Rotation(const vec4 &v)
{
    return Mat4Rotation(v.x, v.y, v.z);
}

/* NOTE: Rotation by Euler (YXZ (y-up) / Rotation Pitch Yaw)
inline mat4 Mat4RotationRPY(const r32 x, const r32 y, const r32 z)
{
    mat4 result = {};
    result.w = 1.0f;

    r32 sx, cx;
    SinCos(x, sx, cx);

    r32 sy, cy;
    SinCos(y, sy, cy);

    r32 sz, cz;
    SinCos(z, sz, cz);

    result.xx = (cx * cz) + (sx * sy * sz);
    result.xy = (cz * sx * sy) - (cx * sz);
    result.xz = cy * sx;
    result.yx = cy * sz;
    result.yy = cy * cz;
    result.yz = -sy;
    result.zx = (cx * sy * sz) - (cz * sx);
    result.zy = (cx * cz * sy) + (sx * sz);
    result.zz = cx * cy;

    return result;
}*/

// NOTE: Axis angle rotation
inline mat4 Mat4Rotation(const vec4 &v, const r32 a)
{
    mat4 result;

    r32 s, c, t;
    SinCos(a, s, c);
    t = 1.0f - c;

    Normalize(v);

    r32 tx = t * v.x, ty = t * v.y, tz = t * v.z,
        sx = s * v.x, sy = s * v.y, sz = s * v.z,
        txy = tx * v.y, tyz = tx * v.z, txz = tx * v.z;

    result.xx = tx * v.x + c;
    result.yx = txy - sz;
    result.zx = txz + sy;
    result.tx = 0;

    result.xy = txy + sz;
    result.yy = ty * v.y + c;
    result.zy = tyz - sx;
    result.ty = 0;

    result.xz = txz - sy;
    result.yz = tyz + sx;
    result.zz = tz * v.z + c;
    result.tz = 0;

    result.xw = 0;
    result.yw = 0;
    result.zw = 0;
    result.ww = 1.0f;

    return result;
}

// NOTE: Rotation from quaternion
inline mat4 Mat4Rotation(const quat &q)
{
    // NOTE: Assert unit quaternion
    mat4 result;

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
    result.xy = xy - wz;
    result.xz = xz + wy;
    result.tx = 0;

    result.yx = xy + wz;
    result.yy = 1.0f - (xx + zz);
    result.yz = yz - wx;
    result.ty = 0;

    result.zx = xz - wy;
    result.zy = yz + wx;
    result.zz = 1.0f - (xx + yy);
    result.tz = 0;

    result.xw = 0;
    result.yw = 0;
    result.zw = 0;
    result.ww = 1.0f;

    // IMPORTANT: Remove/fix!
    //return Transpose(result);
    return result;
}

inline mat4 Mat4RotationX(const r32 a)
{
    mat4 result = {};
    result.ww = 1.0f;

    r32 s, c;
    SinCos(a, s, c);

    result.xx = 1.0f;
    result.y.xyz = Vec3(0.0f, c, -s);
    result.z.xyz = Vec3(0.0f, s, c);

    return result;
}

inline mat4 Mat4RotationY(const r32 a)
{
    mat4 result = {};
    result.ww = 1.0f;

    r32 s, c;
    SinCos(a, s, c);

    result.x.xyz = Vec3(c, 0.0f, s);
    result.yy = 1.0f;
    result.z.xyz = Vec3(-s, 0.0f, c);

    return result;
}

inline mat4 Mat4RotationZ(const r32 a)
{
    mat4 result = {};
    result.ww = 1.0f;

    r32 s, c;
    SinCos(a, s, c);

    result.x.xyz = Vec3(c, s, 0.0f);
    result.y.xyz = Vec3(-s, c, 0.0f);
    result.zz = 1.0f;

    return result;
}


inline mat4 Mat4Scaling(const r32 x, const r32 y, const r32 z)
{
    mat4 result = {};
    result.ww = 1.0f;

    result.xx = x;
    result.yy = y;
    result.zz = z;

    return result;
}

inline mat4 Mat4Scaling(const vec3 &v)
{
    return Mat4Scaling(v.x, v.y, v.z);
}

inline mat4 Mat4Scaling(const vec4 &v)
{
    return Mat4Scaling(v.x, v.y, v.z);
}

inline mat4 Mat4Translation(const vec3 &v)
{
    mat4 result = MAT4_IDENTITY;

    result.tx = v.x;
    result.ty = v.y;
    result.tz = v.z;

    return result;
}

inline mat4 Mat4Translation(const vec4 &v)
{
    return Mat4Translation(v.xyz);
}

// NOTE: See Mike Day, Extracting Euler Angles from a Rotation Matrix
// https://d3cw3dd2w32x2b.cloudfront.net/wp-content/uploads/2012/07/euler-angles1.pdf}
inline vec4 GetEulerAngles(const mat4 &m)
{
    vec4 result;

    result.x = atan2f(m.yz, m.zz);
    r32 c2 = AASqrt((m.xx * m.xx) + (m.xy * m.xy));
    result.y = atan2f(-m.xz, c2);
    r32 s, c;
    SinCos(result.x, s, c);
    result.z = atan2f((s * m.zx) - (c * m.yx), (c * m.yy) - (s * m.zy));
    result.w = 0;

    return result;
}

inline void GetAxisAngle(const mat4 &m, vec4 &axis, r32 &angle)
{
    r32 trace = m.xx + m.yy + m.zz;
    angle = acosf(0.5f * (trace - 1.0f));

    if(IsZero(angle))
    {
        // NOTE: Could be anything if angle is zero, so return the up/Y axis
        axis = VEC4_YAXIS;
    }
    else if(angle < PI - EPSILON)
    {
        axis = Vec4(m.zy - m.yz, m.xz - m.zx, m.yx - m.xy, 0);
        Normalize(axis);
    }
    else
    {
        r32 sqrt, oneOverSqrt;

        axis.w = 0;

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

inline quat GetQuaternion(const mat4 &m)
{
    quat result;
    r32 trace = 1.0f + m.xx + m.yy + m.zz;

    if(trace > EPSILON)
    {
        r32 s = AASqrt(trace) * 2.0f,
            oneOverS = 1.0f / s;
        result.w = s * 0.25f;
        result.x = (m.zy - m.yz) * s;
        result.y = (m.xz - m.zx) * s;
        result.z = (m.yx - m.xy) * s;
    }
    else if(m.xx > m.yy && m.xx > m.zz)
    {
        r32 s = AASqrt(1.0f + m.xx - m.yy - m.zz) * 2.0f,
            oneOverS = 1.0f / s;
        result.w = (m.zy - m.yz) * s;
        result.x = s * 0.25f;
        result.y = (m.xy + m.yx) * s;
        result.z = (m.xz + m.zx) * s;
    }
    else if(m.yy > m.zz)
    {
        r32 s = AASqrt(1.0f + m.yy - m.xx - m.zz) * 2.0f,
            oneOverS = 1.0f / s;
        result.w = (m.xz - m.zx) * s;
        result.x = (m.xy + m.yx) * s;
        result.y = s * 0.25f;
        result.z = (m.yz + m.zy) * s;
    }
    else
    {
        r32 s = AASqrt(1.0f + m.zz - m.xx - m.yy) * 2.0f,
            oneOverS = 1.0f / s;
        result.w = (m.yx - m.xy) * s;
        result.x = (m.xz + m.zx) * s;
        result.y = (m.yz + m.zy) * s;
        result.z = s * 0.25f;
    }

    return result;
}

// NOTE: Left-handed
/*
inline mat4 PerspectiveFOV(const r32 fov, const r32 aspect, const r32 nearDist, const r32 farDist)
{
    mat4 result = {};

    if(fov <= 0 || aspect == 0)
    {
        // NOTE: Assert
        result = MAT4_IDENTITY;
    }
    else
    {
        r32 depth = farDist - nearDist;
        r32 oneOverDepth = 1.0f / depth;

        result.yy = 1.0f / tanf(0.5f * fov);
        result.xx = result.yy / aspect;
        result.zz = farDist * oneOverDepth;
        result.tz = (-farDist * nearDist) * oneOverDepth;
        result.zw = 1.0f;
        result.ww = 0;
    }

    return result;
}

mat4 Perspective(const r32 fov, const r32 aspect, const r32 nearDist, const r32 farDist)
{
    mat4 result = {};

    r32 depth = nearDist - farDist;
    r32 tanHalfFOV = tanf(0.5f * fov);

    result.xx = 1.0f / (tanHalfFOV * aspect);
    result.yy = 1.0f / tanHalfFOV;
    result.zz = (-nearDist - farDist) / depth;
    result.tz = 2.0f * farDist * nearDist / depth;
    result.zw = 1.0f;
    result.ww = 0.0f;

    return result;
}
*/

// NOTE: Construct a perspective projection matrix
//       Vertical FOV in degrees
inline mat4 Perspective(const r32 fov, const r32 aspect, const r32 nearZ, const r32 farZ)
{
    mat4 result = {};

    r32 d = 1.0f / tanf(fov / 360.0f * PI);
    r32 dist = farZ - nearZ;
    r32 recip = 1.0f / dist;

    result.xx = d / aspect;
    result.yy = d;
    result.zz = (nearZ + farZ) * recip;
    result.tz = (2.0f * farZ * nearZ) * recip;
    result.zw = -1.0f;
    result.ww = 0.0f;

    return result;
}

inline mat4 Orthographic(const r32 left, const r32 right, const r32 bottom, const r32 top, const r32 near, const r32 far)
{
    mat4 result = {};

    r32 width = right - left,
        height = top - bottom,
        depth = far - near;

    result.xx = width * 0.5f;
    result.yy = height * 0.5f;
    result.zz = -(depth * 0.5f);
    result.xw = -((right + left) / width);
    result.yw = -((top + bottom) / height);
    result.zw = -((far + near) / depth);
    result.ww = 1.0f;

    return result;
}

// NOTE: Left-handed
inline mat4 LookAt(const vec4 &eye, const vec4 &at, const vec4 &up)
{
    mat4 result;

    vec4 z = Normalized(at - eye);
    vec4 x = Normalized(Cross(up, z));
    vec4 y = Cross(z, x);

    result.xx = x.x;
    result.xy = x.y;
    result.xz = x.z;
    result.xw = 0;

    result.yx = y.x;
    result.yy = y.y;
    result.yz = y.z;
    result.yw = 0;

    result.zx = z.x;
    result.zy = z.y;
    result.zz = z.z;
    result.zw = 0;

    result.tx = Dot(x, -eye);
    result.ty = Dot(y, -eye);
    result.tz = Dot(z, -eye);
    result.ww = 0;

    return result;
}

#endif

