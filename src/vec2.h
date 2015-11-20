#ifndef VEC2_H

union v2
{
    struct
    {
        r32 x, y;
    };
    r32 E[2];
};

//
// NOTE: Operators
//

inline v2 operator-(v2 &a)
{
    v2 result;

    result.x = -a.x;
    result.y = -a.y;

    return result;
}

inline v2 operator+(v2 &a, v2 &b)
{
    v2 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline v2 operator-(v2 &a, v2 &b)
{
    v2 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline v2 operator*(v2 &a, r32 b)
{
    v2 result;

    result.x = a.x * b;
    result.y = a.y * b;

    return result;
}

inline v2 operator*(r32 a, v2 &b)
{
    v2 result = b * a;

    return result;
}

inline v2 &operator*=(v2 &a, r32 b)
{
    a = a * b;

    return a;
}

inline v2 &operator+=(v2 &a, v2 &b)
{
    a = a + b;

    return a;
}

inline v2 &operator-=(v2 &a, v2 &b)
{
    a = a - b;

    return a;
}

//
// NOTE: Functions
//

inline r32 Dot(v2 &a, v2 &b)
{
    return (a.x * b.x + a.y * b.y);
}

inline v2 Perpendicular(v2 &v)
{
    return {-v.y, v.x};
}

#define VEC2_H
#endif
