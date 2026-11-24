#ifndef SPHERE_H
#define SPHERE_H
#include "hittable.h"
#include "../math/vec3.h"
#include <iostream>
class sphere : public hittable
{
private:
    point3 C;
    float radius;

public:
    sphere(const point3& center, float radius): C(center), radius(std::fmax(radius, 0)){};
    bool hit(ray &r, interval i, hitRecord &rec) const override
    {
        vec3 OC = C - r.getOrigin(); // O - origin of ray, C center of Circle
        float b = -2 * dot(r.direction(), OC);
        float a = dot(r.direction(), r.direction());
        float c = dot(OC, OC) - radius * radius;
        float disc = b * b - 4 * a * c;
        float sqrtD = std::sqrt(disc);
        float root = (-b - sqrtD)/(2*a);
        
        if(!i.contains(root)){
            root =  (-b + sqrtD)/(2*a);
            if(!i.contains(root)){
                return false;
            }
        }
        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outwardNormal = (rec.p - C)/radius;
        rec.setFaceNormal(r, outwardNormal);
        return true;
    }
};
#endif