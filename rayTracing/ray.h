#ifndef RAY_H
#define RAY_H
#include "../math/vec3.h"
class ray
{
private:
    point3 origin;
    vec3 dir;

public:
    ray() {}
    ray(const point3 &origin, const vec3 &dir) : origin{origin}, dir{dir} {}
    const point3 &getOrigin() const { return origin; }
    const vec3 &direction() const { return dir; }
    point3 at(double t) const { return origin + t * dir; }
};
#endif