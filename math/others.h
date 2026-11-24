#ifndef OTHERS_H
#define OTHERS_H
#include <limits>
const float infinity = std::numeric_limits<float>::infinity();
const double pi = 3.1415926535897932385;
inline float degToRad(float degrees) { return degrees * pi / 180.0; }
inline float radToDeg(float radians) { return radians * 180 / pi; }
class interval {
private:
  float m;
  float M;

public:
  inline float min(){
    return m;
  }
  inline float max(){
    return M;
  }
  interval(float min, float max) : m(min), M(max) {};
  inline bool contains(float t) { return m <= t && t <= M; }
  inline bool surrounds(float t) { return m < t && t < M; }
  static const interval empty;
  static const interval universe;
};
const interval interval::universe = interval(-infinity, +infinity);
const interval interval::empty = interval(+infinity, -infinity);

#endif