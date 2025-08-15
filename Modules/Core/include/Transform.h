#pragma once

#include <glm/glm.hpp>

struct Transform
{
    Transform();
    
    void AddPositionOffset(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void SetPosition(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    void AddRotationXOffset(float angle);
    void AddRotationYOffset(float angle);
    void AddRotationZOffset(float angle);

    void SetRotation(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    void AddScaleOffset(float x, float y, float z);
    void AddScaleOffset(float val = 0.0f);
    void SetScale(float x, float y, float z);
    void SetScale(float val = 1.0f);

    void UpdateModelMatrix();
    
    bool IsDirty() const {return dirty;}
    glm::mat4 GetModelMatrix() const {return model;}
    
private:

    void MarkDirty();
    
private:

    glm::vec3 position {0.0f};
    glm::vec3 rotation {0.0f};
    glm::vec3 scale {1.0f};
    
    glm::mat4 model {1.0f};
    bool dirty = false;
};
