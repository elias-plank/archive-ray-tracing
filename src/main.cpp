#include "Common.h"
#include "Image.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"

#include <chrono>
#include <thread>

[[nodiscard]] static Vector3 RayColor(const Ray& ray, const Hittable& world, int32_t depth) {

    HitRecord record{};

    if(depth <= 0) {

        return Vector3{ 0, 0, 0 };
    }

    if(world.Hit(ray, 0.001, Infinity, record)) {

        Ray scattered{};
        Vector3 attenuation{};

        if(record.Material->Scatter(ray, record, attenuation, scattered)) {

            return attenuation * RayColor(scattered, world, depth - 1);
        }
        else {

            return Vector3{ 0, 0, 0 };
        }
    }

    Vector3 unitDirection = ray.Direction().Unit();

    auto t = (unitDirection.Y() + 1.0) * 0.5;
    return Vector3{ 1, 1, 1 } * (1.0 - t) + Vector3{ 0.5, 0.7, 1.0 } * t;
}

int main() {

    // Image
    static constexpr auto aspectRatio = 16.0 / 9.0;
    static constexpr auto width = 1920;
    static constexpr auto height = static_cast<uint32_t>(width / aspectRatio);
    static constexpr auto samplesPerPixel = 100;
    static constexpr auto maxDepth = 50;

    // World
    HittableList world{};
    auto materialGround = std::make_shared<Lambertian>(Vector3{ 0.8, 0.8, 0.0 });
    auto materialCenter = std::make_shared<Lambertian>(Vector3{ 0.47, 0.31, 0.66 });
    auto materialLeft   = std::make_shared<Metal>(Vector3{ 0.8, 0.8, 0.8 });
    auto materialRight  = std::make_shared<Metal>(Vector3{ 0.8, 0.6, 0.2 });

    world.Add(std::make_shared<Sphere>(Vector3{ 0.0, -100.5, -1.0 }, 100.0, materialGround));
    world.Add(std::make_shared<Sphere>(Vector3{ 0.0,    0.0, -1.0 },   0.5, materialCenter));
    world.Add(std::make_shared<Sphere>(Vector3{-1.0,    0.0, -1.0 },   0.5, materialLeft));
    world.Add(std::make_shared<Sphere>(Vector3{ 1.0,    0.0, -1.0 },   0.5, materialRight));


    //Camera
    Camera camera{aspectRatio, 1.0};

    // Render
    Image outputImage{width, height};

    std::chrono::time_point renderBegin = std::chrono::high_resolution_clock::now();

    for (uint32_t y = 0; y < height; y++) {

        for (uint32_t x = 0; x < width; x++) {

            Vector3 pixelColor{0, 0, 0};

            for(int32_t s = 0; s < samplesPerPixel; s++) {

                auto u = (x + RandomDouble()) / (width - 1);
                auto v = (y + RandomDouble()) / (height - 1);

                Ray ray = camera.GetRay(u, v);
                pixelColor += RayColor(ray, world, maxDepth);
            }

            // somehow the image is flipped, so we have to do this hack
            outputImage.Set(x, height - y - 1, Color::FromVector3(pixelColor, samplesPerPixel));
        }
    }

    std::chrono::time_point renderEnd = std::chrono::high_resolution_clock::now();
    auto renderDuration = std::chrono::duration_cast<std::chrono::milliseconds>(renderEnd - renderBegin).count();
    std::printf("Render took %lf milliseconds\n", static_cast<double>(renderDuration));

    std::chrono::time_point writeBegin = std::chrono::high_resolution_clock::now();
    outputImage.Write("../assets/output.ppm");
    std::chrono::time_point writeEnd = std::chrono::high_resolution_clock::now();
    auto writeDuration = std::chrono::duration_cast<std::chrono::milliseconds>(writeEnd - writeBegin).count();
    std::printf("Write took %lf milliseconds\n", static_cast<double>(writeDuration));

    return 0;
}
