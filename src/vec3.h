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
