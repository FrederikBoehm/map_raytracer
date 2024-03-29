#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "cuda_runtime.h"

#include <cstdint>
#include <vector>

#include "scene/scene.hpp"
#include "camera/camera.hpp"
#include "../common/frame.hpp"

namespace rt {
  struct SDeviceFrame {
    uint16_t width;
    uint16_t height;
    uint8_t bpp;
    float* data;
    uint8_t* dataBytes;
  };

  class CSampler;

	class Raytracer {
  public:

    Raytracer(uint16_t frameWidth, uint16_t frameHeight);
    ~Raytracer();

    SFrame renderFrame();
	private:
    uint16_t m_frameWidth;
    uint16_t m_frameHeight;
    uint8_t m_bpp;

    CHostScene m_scene;
    CCamera m_hostCamera;
    uint16_t m_numSamples;
    float m_tonemappingFactor;
    float m_gamma;
    CCamera* m_deviceCamera;
    SDeviceFrame* m_deviceFrame;
    float* m_deviceFrameData;
    uint8_t* m_deviceFrameDataBytes;
    CSampler* m_deviceSampler;
    const uint16_t m_blockSize;

    static glm::vec3 getSpherePosition(float sphereRadius, uint8_t index, uint8_t maxSpheres);

    void allocateDeviceMemory();
    void copyToDevice();
    void initDeviceData();
    void freeDeviceMemory();

    SFrame retrieveFrame() const;
	};

}

#endif // !RAYTRACER_H
