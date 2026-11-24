#ifndef HITTABLE_H
#define HITTABLE_H
#include "../math/vec3.h"
#include "ray.h"
#include "../math/others.h"
class hitRecord {
public:
  point3 p;
  vec3 N;
  float t;
  bool frontFace;
  void setFaceNormal(ray &r, vec3 &outwardNormal) {
    frontFace = (dot(r.direction(), outwardNormal) > 0) ? false : true;
    N = outwardNormal;
    if(!frontFace)
        N = -outwardNormal;
    }
};

class hittable {
public:
  virtual ~hittable() = default;
  virtual bool hit(ray &r, interval t_i,  hitRecord &rec) const = 0;
};
#endif