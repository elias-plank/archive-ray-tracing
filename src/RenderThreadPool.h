//
// Created by Elias on 9/26/2021.
//

#ifndef RAYTRACING_RENDERTHREADPOOL_H
#define RAYTRACING_RENDERTHREADPOOL_H

#include "Common.h"
#include "Image.h"
#include "HittableList.h"
#include "Sphere.h"
#include "Camera.h"
#include "Material.h"

#include <thread>
#include <vector>

class RenderThreadPool {

private:
    std::vector<std::thread> threadPool{};
    uint32_t imageWidth{};
    uint32_t imageHeight{};
    uint32_t samplesPerPixel{};
    uint32_t maxDepth{};

    HittableList world{};
    Camera camera;
    Image outputImage;

public:
    RenderThreadPool(uint32_t imageWidth, uint32_t imageHeight, uint32_t samplesPerPixel, uint32_t maxDepth, const Camera& camera);
	
    void AddHittable(const std::shared_ptr<Hittable>& hittable);
    void Render(const std::string& filePath, uint32_t threads);

private:
    void renderWorker(uint32_t x0, uint32_t x1);

private:
    [[nodiscard]] static Vector3 rayColor(const Ray& ray, const Hittable& world, int32_t depth);
};

#endif // RAYTRACING_RENDERTHREADPOOL_H