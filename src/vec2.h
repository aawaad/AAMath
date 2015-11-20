#ifndef VEC2_H

union v2
{
    struct
    {
        r32 x, y;
    };
    r32 E[2];
};

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
