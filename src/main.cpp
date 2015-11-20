#include <stdio.h>
#include <stdint.h>
#include "aatypes.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"

/*
    TODO:

    Vectors:
    x   v2, v3, v4    (float)  
        v2i, v3i, v4i (int)
        v2u, v3u, v4u (uint)

    x   operators

    x   cross, perpendicular (2D)
        distance
        distance squared
    x   dot
        length
        length squared
        normalize
        reflect
        refract
        scalar triple product
        vector triple product

        zero

        statics (x, y, z axes; w; origin (0, 0, 0, 0))

    Matrices:
        mat3, mat4
        mat3i, mat4i

        operators

        component-wise multiply
        determinant
        identity
        inverse
        transpose

        translation
        rotation (matrix)
        rotation (quaternion)
        rotation (pitch, yaw, roll)
        rotation (axis, angle)
        rotation (x, y, z separate)
        scale

    Quaternions:
        magnitude
        norm
        normalize
        conjugate
        inverse

        operators

        dot
        rotate
        lerp
        slerp
        approx slerp

        zero
        identity

    Lines:
        line2, line3

        operators

        transform
        distance
        closest points

    Rays:
        ray2, ray3

        operators
        
        transform
        ditance
        closest points

    Common:
        constants (pi, tau/2pi, halfpi, epsilon etc)
        
        abs
        ceil
        floor
        isinf
        isnan
        min
        max
        round
        lerp

    SIMD optimisations?
    Self-implemented cstdlib functions?

*/

int main(int argv, char **argc)
{
    v2 dim2 = {};
    dim2.x = 0.5f;
    dim2.y = 0.5f;

    v3 dim3 = {};
    dim3.x = 0.5f;
    dim3.y = 0.5f;
    dim3.z = 0.5f;
    
    for (u32 i = 0; i < 3; ++i)
    {
        dim3.E[i] = (r32)i;
    }

    v4 dim4 = {};
    dim4.xyz = dim3;
    dim4.a = 0;

    v3 x = {1, 0, 0};
    v3 y = {.707f, .707f, 0};

    printf("dot: %3.f\n", Dot(x, y));

    v2 dir2 = {1, 0};
    v2 dir2perp = Perpendicular(dir2);

    printf("perp: %3.f, %3.f\n", dir2perp);

    y = {0, 1, 0};
    v3 cross = Cross(x, y);

    printf("cross: <%3.f, %3.f, %3.f>\n", cross.x, cross.y, cross.z);

    y = y + x;
    y = y - x;
    y = -y;
    y = 2 * y;
    y *= 2;
    y += x;

    return 0;
}
