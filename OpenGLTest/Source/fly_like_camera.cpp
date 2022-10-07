#include "fly_like_camera.hpp"

namespace dx
{

FlyLikeCamera::FlyLikeCamera() noexcept(true) :
    pitch(0.f), yaw(-90.f), roll(0.f), cameraPos(0.f, 0.f, 3.f), cameraFront(0.f, 0.f, -1.f), cameraUp(0.f, 1.f, 0.f),
    direction(
        ::std::cos(glm::radians(yaw)) * ::std::cos(glm::radians(pitch)),
        ::std::sin(glm::radians(pitch)),
        ::std::sin(glm::radians(yaw)) * ::std::cos(glm::radians(pitch)))
{

}

}