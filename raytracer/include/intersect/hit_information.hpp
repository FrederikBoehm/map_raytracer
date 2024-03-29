#ifndef HIT_INFORMATION_HXX
#define HIT_INFORMATION_HXX

#include <cstdint>
#include <glm/glm.hpp>

namespace rt {
  struct SHitInformation {
    bool hit;
    glm::vec3 pos; // World pos
    glm::vec3 normal; // World space normal
    float t;
    uint16_t objectId;
  };
}
#endif