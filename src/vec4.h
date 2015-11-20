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

inline r32 Dot(v4 a, v4 b)
{
    return(a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

#define VEC4_H
#endif
