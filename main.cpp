#include <iostream>
#include "math/vec3.h"
#include "math/color.h"
#include "rayTracing/ray.h"
using namespace std;

float hitSphere(const point3 &center, double radius, ray &r)
{
    vec3 OC = center - r.getOrigin(); // O - origin of ray, C center of Circle
    float b = -2 * dot(r.direction(), OC);
    float a = dot(r.direction(), r.direction());
    float c = dot(OC, OC) - radius * radius;
    float disc = b * b - 4 * a * c;
    if (disc < 0)
    {
        return -1;
    }
    else
    {
        return (-b - sqrt(disc)) / (2.0 * a); // lower one so that we can get front face
    }
}
color RayColor(ray r)
{
    vec3 center = point3(0,0,-1);
    float t = hitSphere(center, 0.5, r);
    if (t > 0.0)
    {
        vec3 N = unitVector(r.at(t) - center);
        return 0.5*color(N.x+1, N.y+1, N.z+1);
    }
    vec3 unitV = unitVector(r.direction());
    float a = 0.5 * (unitV.y + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.0, 0.0, 0.0);
}
int main()
{
    float aspectRatio = 0.625f;
    int imageWidth = 800;
    int imageHeight = (int)imageWidth * aspectRatio;
    imageHeight = (imageHeight < 1) ? 1 : imageHeight;

    // Camera
    float focalLength = 1.0f;
    float viewPortHeight = 2.0f;
    float viewPortWidth = viewPortHeight * (float)(imageWidth) / imageHeight;
    vec3 cameraCenter = point3(0, 0, 0);

    vec3 viewPortU = vec3(viewPortWidth, 0, 0);
    vec3 viewPortV = vec3(0, -viewPortHeight, 0);

    vec3 pixeldU = viewPortU / imageWidth;
    vec3 pixeldV = viewPortV / imageHeight;
    vec3 viewportUpperLeft = cameraCenter - vec3(0, 0, focalLength) - viewPortU / 2 - viewPortV / 2;
    vec3 pixel00Loc = viewportUpperLeft + 0.5 * (pixeldU + pixeldV);

    cout << "P3\n"
         << imageWidth << " " << imageHeight << "\n255\n";
    for (int j = 0; j < imageHeight; j++)
    {
        clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
        for (int i = 0; i < imageWidth; i++)
        {
            vec3 pixelCenter = (i * pixeldU) + (j * pixeldV) + pixel00Loc;
            vec3 rayDirection = pixelCenter - cameraCenter;
            ray r(cameraCenter, rayDirection);
            write_color(cout, RayColor(r));
        }
    }
    clog << "\rDone.                 \n";
}