#include "RenderThreadPool.h"

int main(int, char**) {

    static constexpr auto aspectRatio = 16.0 / 9.0;
    static constexpr auto width = 640;
    static constexpr auto height = static_cast<int>(width / aspectRatio);
    static constexpr auto samplesPerPixel = 100;
    static constexpr auto maxDepth = 50;
    static constexpr auto threads = 8;

    RenderThreadPool threadPool{ width, height, samplesPerPixel, maxDepth };

    auto materialGround = std::make_shared<Metal>(Vector3{ 0.3, 0.3, 0.3 });
    auto materialCenter = std::make_shared<Lambertian>(Vector3{ 0.47, 0.31, 0.66 });
    auto materialLeft = std::make_shared<Metal>(Vector3{ 0.8, 0.8, 0.8 });
    auto materialRight = std::make_shared<Metal>(Vector3{ 0.2, 0.2, 0.8 });

    threadPool.AddHittable(std::make_shared<Sphere>(Vector3{ 0.0, -100.5, -1.0 }, 100.0, materialGround));
    threadPool.AddHittable(std::make_shared<Sphere>(Vector3{ 0.0,    0.0, -1.0 },   0.5, materialCenter));
    threadPool.AddHittable(std::make_shared<Sphere>(Vector3{-1.0,    0.0, -1.0 },   0.5, materialLeft));
    threadPool.AddHittable(std::make_shared<Sphere>(Vector3{ 1.0,    0.0, -1.0 },   0.5, materialRight));

    threadPool.Render("output.ppm", 8);

    return 0;
}
