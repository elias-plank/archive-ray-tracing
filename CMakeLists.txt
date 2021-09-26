cmake_minimum_required(VERSION 3.20)
project(RayTracing)

set(CMAKE_CXX_STANDARD 20)

add_executable(RayTracing src/main.cpp src/Image.cpp src/Image.h src/Color.h src/Vector3.cpp src/Vector3.h src/Color.cpp src/Ray.cpp src/Ray.h src/Hittable.cpp src/Hittable.h src/Sphere.cpp src/Sphere.h src/HittableList.cpp src/HittableList.h src/Common.h src/Camera.cpp src/Camera.h src/Material.cpp src/Material.h src/RenderThreadPool.h src/RenderThreadPool.cpp)
