#include <stdio.h>
#include <stdint.h>
#include "aamath.h"

/*
    TODO: x = done, \ = partial, ? = consider

    Vectors:
    x   vec2, vec3, vec4    (float)  
    x   vec2s, vec3s, vec4s (int)
    x   vec2u, vec3u, vec4u (uint)

    x   operators

    x   cross, perpendicular (2D)
    x   distance
    x   distance squared
    x   dot
    x   hadamard product
    x   length
    x   length squared
    x   normalize
    x   reflect
    x   refract
    x   scalar triple product
    x   vector triple product

    x   IsZero
    x   IsUnit

    x   statics (x, y, z axes; w; origin (0, 0, 0, 0))

    Matrices:
    x   mat3, mat4
   ?    mat3i, mat4i

    x   operators

    x   adjoint
    x   determinant
    x   identity
    x   inverse
    x   hadamard product
    x   transpose
        
        set:
    x   translation
    x   rotation (quaternion)
    x   rotation (pitch, yaw, roll)
    x   rotation (axis, angle)
    x   rotation (x, y, z separate)
    x   scale

    x   perspective projection
     x   LH
     x   RH
    x   orthogonal
     x   LH
     x   RH

        get:
    x   to euler angles
    x   to axis angle
    x   to quaternion

    Quaternions:
    x   magnitude
    x   norm
    x   normalize
    x   conjugate
    x   inverse

    x   operators

    x   dot
    x   rotate
    x   lerp
    x   slerp
    x   approx slerp

    x   zero
    x   identity

    Lines:
        line2, line3

        operators

        transform
    x   distance
     x   line point
     x   line seg point
     x   line line
     x   line seg line seg
    x   closest points
     x   line point
     x   line seg point
     x   line line
     x   line seg line seg

    Rays:
        ray2, ray3

        operators
        
        transform
    x   distance
     x   ray point
     x   ray ray
     x   ray line
    x   closest points
     x   ray point
     x   ray ray
     x   ray line

    Triangles:
        point in triangle
        barycentric coords
        triangle-triangle intersection
        triangle-ray intersection

    Planes:
    x   transform
    x   distance
    x   closest point
    x   plane test
     x   plane point
     x   plane sphere
     x   plane AABB

    Common:
    x   constants (pi, tau/2pi, halfpi, epsilon etc) 
        
        abs
        ceil
    x   clamp
        floor
    x   areequal
    x   iszero
        isinf
    x   isnan
        min
        max
        round
        lerp

    Collision:
    x   AABB
     x   AABB AABB
     x   AABB ray
        OBB
    x   Bounding spheres
     x   sphere sphere
     x   sphere ray
        Capsules

    SIMD optimisations?
    Self-implemented standard library functions (cos, sin etc)?

*/

using namespace aam;

int main(int argv, char **argc)
{
    vec2 dim2 = {};
    dim2.x = 0.5f;
    dim2.y = 0.5f;

    vec3 dim3 = {};
    dim3.x = 0.5f;
    dim3.y = 0.5f;
    dim3.z = 0.5f;
    
    for (u32 i = 0; i < 3; ++i)
    {
        dim3.E[i] = (r32)i;
    }

    vec4 dim4 = {};
    dim4.xyz = dim3;
    dim4.a = 0.0f;

    vec3 x = {1.0f, 0.0f, 0.0f};
    vec3 y = {1.0f, 1.0f, 0.0f};
    Normalize(y);

    printf("dot: %.3f\n", Dot(x, y));
    printf("dot: %.3f\n", Dot(VEC3_XAXIS, y));

    vec2 dir2 = {1, 0};
    vec2 dir2perp = Perpendicular(dir2);

    printf("perp: %3.f, %3.f\n", dir2perp.x, dir2perp.y);

    y = {0.0f, 1.0f, 0.0f};
    vec3 cross = Cross(x, y);

    printf("cross: <%.3f, %.3f, %.3f>\n", cross.x, cross.y, cross.z);

    mat4 t = Mat4Translation(5.0f, 5.0f, 5.0f);
    mat4 r = Mat4RotationZ(PIOVERFOUR);
    mat4 s = Mat4Scaling(1.0f, 3.0f, 2.0f);
    mat4 wrld = t * r * s;
    mat4 view = LookAt(Vec4(0, 2.0f, 2.0f, 0), VEC4_ORIGIN, VEC4_YAXIS);
    mat4 pers = Perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    mat4 WVP = pers * view * wrld;

    y = y + x;
    y = y - x;
    y = -y;
    y = 2.0f * y;
    y *= 2.0f;
    y += x;
    y == x;

    printf("sqrt 9: %f\n", AASqrt(9.f));
    printf("inv sqrt 9: %f\n", InvSqrt(9.f));

    return 0;
}

