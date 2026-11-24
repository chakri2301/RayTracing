#include "./rayTracing/hittableList.h"
#include "math/color.h"
#include "math/others.h"
#include "math/vec3.h"
#include "rayTracing/hittable.h"
#include "rayTracing/ray.h"
#include "rayTracing/sphere.h"
#include <iostream>
#include <memory>
using namespace std;

// float hitSphere(const point3 &center, float radius, ray &r)
// {
//     vec3 OC = center - r.getOrigin(); // O - origin of ray, C center of
//     Circle float b = -2 * dot(r.direction(), OC); float a =
//     dot(r.direction(), r.direction()); float c = dot(OC, OC) - radius *
//     radius; float disc = b * b - 4 * a * c; if (disc < 0)
//     {
//         return -1;
//     }
//     else
//     {
//         return (-b - sqrt(disc)) / (2.0 * a); // lower one so that we can get
//         front face
//     }
// }
color RayColor(ray &r, hittableList &world) {
  vec3 center = point3(0, 0, -1);
  hitRecord rec;
  if (world.hit(r, interval(0, infinity), rec)) {
    return 0.5* (rec.N + color(1, 1, 1));
  }
  vec3 unitV = unitVector(r.direction());
  float a = 0.5 * (unitV.y + 1.0);
  return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
int main() {
  float aspectRatio = 0.625f;
  int imageWidth = 800;
  int imageHeight = (int)imageWidth * aspectRatio;
  imageHeight = (imageHeight < 1) ? 1 : imageHeight;

  // World
  hittableList world;
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  // Camera
  float focalLength = 1.0f;
  float viewPortHeight = 2.0f;
  float viewPortWidth = viewPortHeight * (float)(imageWidth) / imageHeight;
  vec3 cameraCenter = point3(0, 0, 0);

  vec3 viewPortU = vec3(viewPortWidth, 0, 0);
  vec3 viewPortV = vec3(0, -viewPortHeight, 0);

  vec3 pixeldU = viewPortU / imageWidth;
  vec3 pixeldV = viewPortV / imageHeight;
  vec3 viewportUpperLeft =
      cameraCenter - vec3(0, 0, focalLength) - viewPortU / 2 - viewPortV / 2;
  vec3 pixel00Loc = viewportUpperLeft + 0.5 * (pixeldU + pixeldV);

  cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";
  for (int j = 0; j < imageHeight; j++) {
     clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
    for (int i = 0; i < imageWidth; i++) {
      vec3 pixelCenter = (i * pixeldU) + (j * pixeldV) + pixel00Loc;
      vec3 rayDirection = pixelCenter - cameraCenter;
      ray r(cameraCenter, rayDirection);
      write_color(cout, RayColor(r, world));
    }
  }
  clog << "\rDone.                 \n";
}