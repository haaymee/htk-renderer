#pragma once

#include "Transform.h"


class Camera
{
public:

    Camera();
    
    void SetFOV(float val);
    void SetNearClipPlane(float val);
    void SetFarClipPlane(float val);

    Transform& GetTransform() {return transform;}
    float GetFOV() const {return fov;}
    float GetNearClipPlane() const {return nearClipPlane;}
    float GetFarClipPlane() const {return farClipPlane;}
    
    glm::mat4 GetViewMatrix();
    glm::mat4 GetPerspectiveProjectionMatrix(uint16_t screenWidth, uint16_t screenHeight);

private:
    
    Transform transform;

    float fov = 45.0f;
    float nearClipPlane = 0.01f;
    float farClipPlane = 10.0f;
    
};
