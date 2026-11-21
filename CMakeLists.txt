cmake_minimum_required(VERSION 4.0.0)
project("RayTracing")
add_executable("main" "main.cpp" math/color.h math/vec3.h rayTracing/ray.h)