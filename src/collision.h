#ifndef COLLISION_H
#define COLLISION_H

#include "aamath.h"
#include "vec3.h"

namespace aam {

typedef struct _line3
{
    vec3 origin,
         direction;
} line3;

inline line3 Line3(const vec3 &origin, const vec3 direction)
{
    line3 result;

    result.origin = origin;
    result.direction = direction;

    return result;
}

typedef struct _lineseg3
{
    vec3 origin,
         direction;
} lineseg3;

inline lineseg3 LineSeg3(const vec3 &origin, const vec3 direction)
{
    lineseg3 result;

    result.origin = origin;
    result.direction = direction;

    return result;
}

typedef struct _ray3
{
    vec3 origin,
         direction;
} ray3;

inline ray3 Ray3(const vec3 &origin, const vec3 direction)
{
    ray3 result;

    result.origin = origin;
    result.direction = direction;

    return result;
}

inline vec3 ClosestPoint(const line3 &line, const vec3 &point)
{
    vec3 result;

    vec3 w = point - line.origin;
    r32 vSq = LengthSq(line.direction);
    r32 proj = Dot(w, line.direction);

    result = line.origin + (proj / vSq) * line.direction;
    return result;
}

inline r32 DistanceSq(const line3 &line, const vec3 &point)
{
    r32 result;

    vec3 w = point - line.origin;
    r32 vSq = LengthSq(line.direction);
    r32 wSq = LengthSq(w);
    r32 proj = Dot(w, line.direction);

    result = wSq - proj * proj / vSq;
}

// NOTE: Normalised direction
inline r32 DistanceSqN(const line3 &line, const vec3 &point)
{
    r32 result;

    AAM_Assert(AreEqual(Length(line.direction), 1.0f));

    vec3 w = point - line.origin;
    r32 wSq = LengthSq(w);
    r32 proj = Dot(w, line.direction);

    result = wSq - proj * proj;
}

inline vec3 ClosestPoint(const lineseg3 &line, const vec3 &point)
{
    vec3 result;

    vec3 w = point - line.origin;
    r32 proj = Dot(w, line.direction);

    if(proj <= 0)
    {
        result = line.origin;
    }
    else
    {
        r32 vSq = LengthSq(line.direction);

        if(proj >= vSq)
        {
            result = line.origin + line.direction;
        }
        else
        {
            result = line.origin + (proj / vSq) * line.direction;
        }
    }

    return result;
}

inline r32 DistanceSq(const lineseg3 &line, const vec3 &point)
{
    r32 result;

    vec3 w = point - line.origin;

    r32 proj = Dot(w, line.direction);

    if(proj <= 0)
    {
        result = LengthSq(w);
    }
    else
    {
        r32 vSq = LengthSq(line.direction);

        if(proj >= vSq)
        {
            result = Dot(w, w) - 2.0f * proj + vSq;
        }
        else
        {
            result = LengthSq(w) - proj * proj / vSq;
        }
    }

    return result;
}

inline void ClosestPoints(const line3 &lineA, const line3 &lineB, vec3 &pointA, vec3 &pointB)
{
    vec3 w = lineA.origin - lineB.origin;
    r32 a = Dot(lineA.direction, lineA.direction),
        b = Dot(lineA.direction, lineB.direction),
        c = Dot(lineB.direction, lineB.direction),
        d = Dot(lineA.direction, w),
        e = Dot(lineB.direction, w),
        div = a * c - b * b;

    if(IsZero(div))
    {
        pointA = lineA.origin;
        pointB = lineB.origin + (e / c) * lineB.direction;
    }
    else
    {
        pointA = lineA.origin + ((b * e - c * d) / div) * lineA.direction;
        pointB = lineB.origin + ((a * e - b * d) / div) * lineB.direction;
    }
}

inline r32 DistanceSq(const line3 &lineA, const line3 &lineB)
{
    r32 result;

    vec3 w = lineA.origin - lineB.origin;
    r32 a = Dot(lineA.direction, lineA.direction),
        b = Dot(lineA.direction, lineB.direction),
        c = Dot(lineB.direction, lineB.direction),
        d = Dot(lineA.direction, w),
        e = Dot(lineB.direction, w),
        div = a * c - b * b;

    if(IsZero(div))
    {
        result = LengthSq(w - (e / c) * lineB.direction);
    }
    else
    {
        vec3 wc = w + ((b * e - c * d) / div) * lineA.direction
                    - ((a * e - b * d) / div) * lineB.direction;
        result = LengthSq(w);
    }

    return result;
}

inline void ClosestPoints(const lineseg3 &lineA, const lineseg3 &lineB, vec3 &pointA, vec3 &pointB)
{
    vec3 w = lineA.origin - lineB.origin;
    r32 a = Dot(lineA.direction, lineA.direction),
        b = Dot(lineA.direction, lineB.direction),
        c = Dot(lineB.direction, lineB.direction),
        d = Dot(lineA.direction, w),
        e = Dot(lineB.direction, w),
        div = a * c - b * b;

    r32 sc, tc, sn, sd, tn, td;

    if(IsZero(div))
    {
        sd = td = c;
        sn = 0.0f;
        tn = e;
    }
    else
    {
        sd = td = div;
        sn = b * e - c * d;
        tn = a * e - b * d;

        // NOTE: Clamp S point
        if(sn < 0.0f)
        {
            sn = 0.0f;
            tn = e;
            td = c;
        }
        // NOTE: Clamp S point
        if(sn > sd)
        {
            sn = sd;
            tn = e + b;
            td = c;
        }
    }

    // NOTE: Clamp T point
    if(tn < 0.0f)
    {
        tc = 0.0f;

        // NOTE: Clamp S point
        if(-d < 0.0f)
        {
            sc = 0.0f;
        }
        else if (-d > a)
        {
            sc = 1.0f;
        }
        else
        {
            sc = -d / a;
        }
    }
    else if (tn > td)
    {
        tc = 1.0f;

        if((-d + b) > 0.0f)
        {
            sc = 0.0f;
        }
        else if((-d + b) > a)
        {
            sc = 1.0f;
        }
        else
        {
            sc = (-d + b) / a;
        }
    }
    else
    {
        tc = tn / td;
        sc = sn / sd;
    }

    pointA = lineA.origin + sc * lineA.direction;
    pointB = lineB.origin + tc * lineB.direction;
}

inline r32 DistanceSq(const lineseg3 &lineA, const lineseg3 &lineB)
{
    r32 result;

    vec3 a, b;
    ClosestPoints(lineA, lineB, a, b);

    result = LengthSq(a - b);
    return result;
}

inline vec3 ClosestPoint(const ray3 &ray, const vec3 &point)
{
    vec3 result;

    vec3 w = point - ray.origin;
    r32 proj = Dot(w, ray.direction);

    if(proj <= 0.0f)
    {
        result = ray.origin;
    }
    else
    {
        r32 vSq = LengthSq(ray.direction);

        result = ray.origin + (proj / vSq) * ray.direction;
    }

    return result;
}

inline r32 DistanceSq(const ray3 &ray, const vec3 &point)
{
    r32 result;

    vec3 w = point - ray.origin;
    r32 proj = Dot(w, ray.direction);

    if(proj <= 0.0f)
    {
        result = LengthSq(w);
    }
    else
    {
        r32 vSq = LengthSq(ray.direction);
        result = Dot(w, w) - (proj / vSq) * proj;
    }

    return result;
}

inline void ClosestPoints(const ray3 &rayA, const ray3 &rayB, vec3 &pointA, vec3 &pointB)
{
    vec3 w = rayA.origin - rayB.origin;
    r32 a = Dot(rayA.direction, rayA.direction),
        b = Dot(rayA.direction, rayB.direction),
        c = Dot(rayB.direction, rayB.direction),
        d = Dot(rayA.direction, w),
        e = Dot(rayB.direction, w),
        div = a * c - b * b;

    r32 sc, tc, sn, sd, tn, td;

    if(IsZero(div))
    {
        sd = td = c;
        sn = 0.0f;
        tn = e;
    }
    else
    {
        sd = td = div;
        sn = b * e - c * d;
        tn = a * e - b * d;

        if(sn < 0.0f)
        {
            sn = 0.0f;
            tn = e;
            td = c;
        }
    }

    if(tn < 0.0f)
    {
        tc = 0.0f;

        if(-d < 0.0f)
        {
            sc = 0.0f;
        }
        else
        {
            sc = -d / a;
        }
    }
    else
    {
        tc = tn / td;
        sc = sn / sd;
    }

    pointA = rayA.origin + sc * rayA.direction;
    pointB = rayB.origin + tc * rayB.direction;
}

inline r32 DistanceSq(const ray3 &rayA, const ray3 &rayB)
{
    r32 result;

    vec3 a, b;
    ClosestPoints(rayA, rayB, a, b);

    result = LengthSq(a - b);
    return result;
}

inline void ClosestPoints(const ray3 &ray, const line3 &line, vec3 pointA, vec3 pointB)
{
    vec3 w = ray.origin - line.origin;
    r32 a = Dot(ray.direction, ray.direction),
        b = Dot(ray.direction, line.direction),
        c = Dot(line.direction, line.direction),
        d = Dot(ray.direction, w),
        e = Dot(line.direction, w),
        div = a * c - b * b;

    if(IsZero(div))
    {
        pointA = ray.origin;
        pointB = line.origin + (e / c) * line.direction;
    }
    else
    {
        r32 sn, sc, tc;

        sn = b * e - c * d;

        if(sn < 0.0f)
        {
            sc = 0.0f;
            tc = e / c;
        }
        else if(sn > div)
        {
            sc = 1.0f;
            tc = (e + b) / c;
        }
        else
        {
            sc = sn / div;
            tc = (a * e - b * d) / div;
        }

        pointA = ray.origin + sc * ray.direction;
        pointB = line.origin + tc * line.direction;
    }
}

inline r32 DistanceSq(const ray3 &ray, const line3 &line)
{
    r32 result;

    vec3 a, b;
    ClosestPoints(ray, line, a, b);

    result = LengthSq(a - b);
    return result;
}

typedef struct _sphere
{
    vec3 origin;
    r32 radius;
} sphere;

inline sphere Sphere(const vec3 &origin, const r32 radius)
{
    sphere result;

    result.origin = origin;
    result.radius = radius;

    return result;
}

typedef struct _plane
{
    vec3 normal;
    r32 offset;
} plane;

inline plane Plane()
{
    plane result = {};

    result.normal.y = 1.0f;

    return result;
}

inline plane Plane(const r32 a, const r32 b, const r32 c, const r32 d)
{
    plane result;

    r32 lenSq = a*a + b*b + c*c;
    AAM_Assert(!IsZero(lenSq));

    if(IsZero(lenSq))
    {
        result.normal = VEC3_YAXIS;
        result.offset = 0.0f;
    }
    else
    {
        r32 recip = InvSqrt(lenSq);
        result.normal = Vec3(a * recip, b * recip, c * recip);
        result.offset = d * recip;
    }

    return result;
}

inline plane Plane(const vec3 &a, const vec3 &b, const vec3 &c)
{
    plane result;

    vec3 u = b - a,
         v = c - a,
         w = Cross(u, v);

    r32 lenSq = LengthSq(w);
    AAM_Assert(!IsZero(lenSq));

    if(IsZero(lenSq))
    {
        result.normal = VEC3_YAXIS;
    }
    else
    {
        r32 recip = InvSqrt(lenSq);
        result.normal = Vec3(w.x * recip, w.y * recip, w.z * recip);
        result.offset = -Dot(result.normal, a);
    }

    return result;
}

inline plane Plane(const vec3 &normal, const r32 offset)
{
    plane result;

    result.normal = normal;
    result.offset = offset;

    return result;
}

inline r32 Test(const plane &plane, const vec3 &point)
{
    r32 result;

    result = Dot(plane.normal, point) + plane.offset;

    return result;
}

inline vec3 ClosestPoint(const plane &plane, const vec3 &point)
{
    vec3 result;

    result = point - Test(plane, point) * plane.normal;

    return result;
}

inline plane Transform(const plane &p, const r32 scale, const quat &rotation, const vec3 &translation)
{
    plane result;

    mat3 m = Mat3Rotation(rotation);
    result.normal = m * p.normal / scale;

    vec3 t = m * translation;
    result.offset = -Dot(t, p.normal) / scale + p.offset;

    return result;
}

// NOTE: Gets min/max points and sets origin to centre, radius to centre -> furthest point
inline sphere BoundingSphere(const vec3 *vertices, const u32 count)
{
    sphere result;
    AAM_Assert(vertices);

    vec3 min = {},
         max = {};

    for(u32 i = 1; i < count; ++i)
    {
        if(vertices[i].x < min.x)
            min.x = vertices[i].x;
        else if(vertices[i].x > max.x)
            max.x = vertices[i].x;
        if(vertices[i].y < min.y)
            min.y = vertices[i].y;
        else if(vertices[i].y > max.y)
            max.y = vertices[i].y;
        if(vertices[i].z < min.z)
            min.z = vertices[i].z;
        else if(vertices[i].z > max.z)
            max.z = vertices[i].z;
    }

    result.origin = 0.5f * (min + max);

    r32 maxDist = DistanceSq(result.origin, vertices[0]);
    for(u32 i = 1; i < count; ++i)
    {
        r32 dist = DistanceSq(result.origin, vertices[i]);
        if(dist > maxDist)
            maxDist = dist;
    }

    result.radius = AASqrt(maxDist);

    return result;
}

inline b32 Intersects(const sphere &a, const sphere &b)
{
    b32 result = false;

    r32 distSq = DistanceSq(a.origin, b.origin);
    if(distSq <= (a.radius + b.radius))
        result = true;

    return result;
}

inline b32 Intersects(const sphere &s, const ray3 &ray)
{
    b32 result = false;

    vec3 w = s.origin - ray.origin;
    r32 wSq = LengthSq(w),
        proj = Dot(w, ray.direction),
        rSq = s.radius * s.radius;

    if(proj >= 0.0f || wSq < rSq)
    {
        r32 vSq = LengthSq(ray.direction);
        result = (vSq * wSq - proj * proj <= vSq * s.radius * s.radius);
    }

    return result;
}

// NOTE: Returns the signed distance, 0 if colliding
inline r32 Test(const plane &p, const sphere &s)
{
    r32 result,
        dist = Test(p, s.origin);

    if(dist > s.radius)
    {
        result = dist - s.radius;
    }
    else if(dist < -s.radius)
    {
        result = dist + s.radius;
    }
    else
    {
        result = 0.0f;
    }

    return result;
}

typedef struct _aabb
{
    vec3 min,
         max;
} aabb;

inline aabb AABB(const vec3 &min, const vec3& max)
{
    aabb result;

    result.min = min;
    result.max = max;

    return result;
}

inline aabb AABB(const vec3 *vertices, const u32 count)
{
    aabb result;
    AAM_Assert(vertices);

    result.min = vertices[0];
    result.max = vertices[0];

    for(u32 i = 1; i < count; ++i)
    {
        if(vertices[i].x < result.min.x)
            result.min.x = vertices[i].x;
        else if(vertices[i].x > result.max.x)
            result.max.x = vertices[i].x;
        if(vertices[i].y < result.min.y)
            result.min.y = vertices[i].y;
        else if(vertices[i].y > result.max.y)
            result.max.y = vertices[i].y;
        if(vertices[i].z < result.min.z)
            result.min.z = vertices[i].z;
        else if(vertices[i].z > result.max.z)
            result.max.z = vertices[i].z;
    }

    return result;
}

inline b32 Intersects(const aabb &a, const aabb &b)
{
    if(a.min.x > b.max.x || b.min.x > a.max.x)
        return false;
    if(a.min.y > b.max.y || b.min.y > a.max.y)
        return false;
    if(a.min.z > b.max.z || b.min.z > a.max.z)
        return false;
    return true;
}

inline b32 Intersects(const aabb &bb, const ray3 &r)
{
    r32 maxS = 0.0f,
        minT = FLT_MAX;

    // NOTE: Test against x, y and z
    for(u32 i = 0; i < 3; ++i)
    {
        r32 s, t,
            recip = 1.0f / r.direction.E[i];

        if(recip >= 0.0f)
        {
            s = (bb.min.E[i] - r.origin.E[i]) * recip;
            t = (bb.max.E[i] - r.origin.E[i]) * recip;
        }
        else
        {
            s = (bb.max.E[i] - r.origin.E[i]) * recip;
            t = (bb.min.E[i] - r.origin.E[i]) * recip;
        }

        if(s > maxS)
            maxS = s;
        if(t < minT)
            minT = t;

        // NOTE: No overlap when S is greater than T, so test fails
        if(maxS > minT)
            return false;
    }

    return true;
}

// NOTE: Returns the signed distance, 0 if colliding
inline r32 Test(const aabb &bb, const plane &p)
{
    vec3 diagMin, diagMax;

    if(p.normal.x >= 0)
    {
        diagMin.x = bb.min.x;
        diagMax.x = bb.max.x;
    }
    else
    {
        diagMin.x = bb.max.x;
        diagMax.x = bb.min.x;
    }

    if(p.normal.y >= 0)
    {
        diagMin.y = bb.min.y;
        diagMax.y = bb.max.y;
    }
    else
    {
        diagMin.y = bb.max.y;
        diagMax.y = bb.min.y;
    }

    if(p.normal.z >= 0)
    {
        diagMin.z = bb.min.z;
        diagMax.z = bb.max.z;
    }
    else
    {
        diagMin.z = bb.max.z;
        diagMax.z = bb.min.z;
    }

    // NOTE: Minimum on positive side of plane -> box on positive side
    r32 test = Test(p, diagMin);
    if(test >= 0.0f)
        return test;

    // NOTE: Min and max on opposite sides (intersection)
    test = Test(p, diagMax);
    if(test >= 0.0f)
        return 0.0f;

    // NOTE: Maximum on negative side of plane
    return test;
}

} // NOTE: Namespace

#endif

