#ifndef HITTABLE_LIST
#define HITTABLE_LIST
#include "hittable.h"
#include <memory>
#include <vector>
class hittableList {
public:
  std::vector<std::shared_ptr<hittable>> objects;
  hittableList() { objects = {}; }
  hittableList(std::shared_ptr<hittable> object) {
    objects = {};
    objects.push_back(object);
  }
  void add(std::shared_ptr<hittable> object){
    objects.push_back(object);
  }
  bool hit(ray &r, interval i, hitRecord &rec) {
    float minT = i.max();
    bool hitAny = false;

    for (std::shared_ptr<hittable> &ob : objects) {
      if (ob->hit(r, i, rec)) {
        hitAny = true;
        if (rec.t < minT) {
          minT = rec.t;
        }
      }
    }
    return hitAny;
  }
};
#endif