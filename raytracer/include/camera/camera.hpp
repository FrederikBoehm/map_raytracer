#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

#include "intersect/ray.hpp"
#include "utility/qualifiers.hpp"
#include "sampling/sampler.hpp"

namespace rt {
  class CCamera {
    
  public:
    /*
      Creates a Camera object
      sensorWidth: width of the sensor in pixels
      sensorHeight: height of the sensor in pixels
      fov: horizontal fov in degrees
      pos: world position of the camera
      lookAt: world position of the target that the cam looks to
      up: world direction of the up vector
    */
    DH_CALLABLE CCamera(uint16_t sensorWidth, uint16_t sensorHeight, float fov, const glm::vec3& pos, const glm::vec3& lookAt, const glm::vec3& up, CSampler* sampler = nullptr);

    /*
      Samples the specified pixel randomly. Returns a ray in world space.
      Origin (0, 0) is bottom left.
    */
    D_CALLABLE Ray samplePixel(uint16_t x, uint16_t y, CSampler& sampler);

    DH_CALLABLE uint16_t sensorWidth() const;
    DH_CALLABLE uint16_t sensorHeight() const;

    H_CALLABLE void setSampler(CSampler* sampler);
  private:

    const float m_pixelSize;

    // Width and height of sensor in pixels, in our scale one pixel has width and height of 1e-5 meters = 10 micrometers
    uint16_t m_sensorWidth;
    uint16_t m_sensorHeight;
    float m_fov; // Horizontal FOV in rad
    float m_nearPlaneDistance;

    glm::vec3 m_position; // World position of camera
    glm::mat4 m_worldToView;
    glm::mat4 m_viewToWorld;

    CSampler* m_sampler;

    DH_CALLABLE static float getNearPlaneDistance(uint16_t sensorWidth, float fov, float pixelSize);

  };

  inline uint16_t CCamera::sensorWidth() const {
    return m_sensorWidth;
  }

  inline uint16_t CCamera::sensorHeight() const {
    return m_sensorHeight;
  }

  inline void CCamera::setSampler(CSampler* sampler) {
    m_sampler = sampler;
  }

}

#endif // !CAMERA_HPP
