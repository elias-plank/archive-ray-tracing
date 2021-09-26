#include "RenderThreadPool.h"

RenderThreadPool::RenderThreadPool(uint32_t imageWidth, uint32_t imageHeight, uint32_t samplesPerPixel, uint32_t maxDepth) 
	: aspectRatio((double)imageWidth / (double)imageHeight), imageWidth(imageWidth), imageHeight(imageHeight), samplesPerPixel(samplesPerPixel), maxDepth(maxDepth), camera(aspectRatio), outputImage(imageWidth, imageHeight)
{
	
}

void RenderThreadPool::AddHittable(const std::shared_ptr<Hittable>& hittable) {

	world.Add(hittable);
}

void RenderThreadPool::Render(const std::string& filePath, uint32_t threads) {

    std::printf("Utilizing %d threads.\n", static_cast<int>(threads));

    threadPool.resize(threads);

    auto renderBegin = std::chrono::high_resolution_clock::now();

    for (uint32_t i = 0; i < threads; i++) {

        auto x0 = i * (imageWidth / threads);
        auto x1 = (i + 1) * (imageWidth / threads);
        
        threadPool[i] = std::thread(&RenderThreadPool::renderWorker, this,  x0, x1);
    }

    for (auto& t : threadPool) {

        t.join();
    }

    auto renderEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = renderEnd - renderBegin;
    std::printf("Total render duration: %lf seconds.\n", duration.count());

    outputImage.Write(filePath);
}

void RenderThreadPool::renderWorker(uint32_t x0, uint32_t x1) {

    auto renderBegin = std::chrono::high_resolution_clock::now();

	for (uint32_t y = 0; y < imageHeight; y++) {
	
        for (uint32_t x = x0; x < x1; x++) {

            Vector3 pixelColor{ 0, 0, 0 };

            for (int32_t s = 0; s < samplesPerPixel; s++) {

                auto u = (x + RandomDouble()) / (imageWidth - 1);
                auto v = (y + RandomDouble()) / (imageHeight - 1);

                Ray ray = camera.GetRay(u, v);
                pixelColor += rayColor(ray, world, maxDepth);
            }

            // somehow the image is flipped, so we have to do this hack
            outputImage.Set(x, imageHeight - y - 1, Color::FromVector3(pixelColor, samplesPerPixel));
        }
	}

    auto renderEnd = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = renderEnd - renderBegin;

    std::printf("Render of section %d - %d took %lf seconds.\n", static_cast<int>(x0), static_cast<int>(x1), duration.count());
}

Vector3 RenderThreadPool::rayColor(const Ray& ray, const Hittable& world, int32_t depth) {

    HitRecord record{};

    if (depth <= 0) {

        return Vector3{ 0, 0, 0 };
    }

    if (world.Hit(ray, 0.001, Infinity, record)) {

        Ray scattered{};
        Vector3 attenuation{};

        if (record.Material->Scatter(ray, record, attenuation, scattered)) {

            return attenuation * rayColor(scattered, world, depth - 1);
        }
        else {

            return Vector3{ 0, 0, 0 };
        }
    }

    Vector3 unitDirection = ray.Direction().Unit();

    auto t = (unitDirection.Y() + 1.0) * 0.5;
    return Vector3{ 1, 1, 1 } *(1.0 - t) + Vector3{ 0.5, 0.7, 1.0 } *t;
}