#pragma once

#include <cstddef>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "err_def.hpp"

namespace dx
{

class FlyLikeCamera
{
public:
    float pitch;
    float yaw;
    float roll;
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    glm::vec3 direction;

    FlyLikeCamera() noexcept(true);

};

}