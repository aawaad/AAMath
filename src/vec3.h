#ifndef VEC3_H

union v3
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
};

//
// NOTE: Operators
//

inline v3 operator-(v3 &a)
{
    v3 result;

    result.x = -a.x;
    result.y = -a.y;
    result.z = -a.z;

    return result;
}

inline v3 operator+(v3 &a, v3 &b)
{
    v3 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

inline v3 operator-(v3 &a, v3 &b)
{
    v3 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

inline v3 operator*(v3 &a, r32 b)
{
    v3 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}

inline v3 operator*(r32 a, v3 &b)
{
    v3 result = b * a;

    return result;
}

inline v3 &operator*=(v3 &a, r32 b)
{
    a = a * b;

    return a;
}

inline v3 &operator+=(v3 &a, v3 &b)
{
    a = a + b;

    return a;
}

inline v3 &operator-=(v3 &a, v3 &b)
{
    a = a - b;

    return a;
}

//
// NOTE: Functions
//

inline r32 Dot(v3 a, v3 b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline v3 Cross(v3 a, v3 b)
{
    v3 result = {a.y * b.z + a.z * b.y,
                 a.z * b.x + a.x * b.z,
                 a.x * b.y + b.x * a.y};

    return result;
}

#define VEC3_H
#endif
