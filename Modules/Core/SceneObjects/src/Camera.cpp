#include "Camera.h"

Camera::Camera()
    :transform(Transform{}), fov(45.f), nearClipPlane(0.01f), farClipPlane(10.f)
{
    transform.SetPosition(0.f);
    
}

void Camera::SetFOV(float val)
{
    fov = val;
}

void Camera::SetNearClipPlane(float val)
{
    nearClipPlane = val;
}

void Camera::SetFarClipPlane(float val)
{
    farClipPlane = val;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt( transform.GetWorldPosition(),
        transform.GetWorldPosition() + transform.GetWorldForwardDirection(),
            transform.GetWorldUpDirection()
    );
}

glm::mat4 Camera::GetPerspectiveProjectionMatrix(uint16_t screenWidth, uint16_t screenHeight)
{
    return glm::perspective(glm::radians(fov), static_cast<float>(screenWidth)/static_cast<float>(screenHeight), nearClipPlane, farClipPlane);
}