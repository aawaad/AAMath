#ifndef VEC4_H

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
// NOTE: Operators
//

inline v4 operator-(v4 &a)
{
    v4 result;

    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;
    result.w = -a.w;

    return result;
}

inline v4 operator+(v4 &a, v4 &b)
{
    v4 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    result.w = a.w + b.w;

    return result;
}

inline v4 operator-(v4 &a, v4 &b)
{
    v4 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    result.w = a.w - b.w;

    return result;
}

inline v4 operator*(v4 &a, r32 b)
{
    v4 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;
    result.w = a.w * b;

    return result;
}

inline v4 operator*(r32 a, v4 &b)
{
    v4 result = b * a;

    return result;
}

inline v4 &operator*=(v4 &a, r32 b)
{
    a = a * b;

    return a;
}

inline v4 &operator+=(v4 &a, v4 &b)
{
    a = a + b;

    return a;
}

inline v4 &operator-=(v4 &a, v4 &b)
{
    a = a - b;

    return a;
}

//
// NOTE: Functions
//

inline r32 Dot(v4 a, v4 b)
{
    return(a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

#define VEC4_H
#endif
