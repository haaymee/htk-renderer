#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "glm/gtc/quaternion.hpp"

struct Transform
{
    Transform();
    
    void AddPositionOffset(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void SetPosition(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    void AddRotationXOffset(float angle);
    void AddRotationYOffset(float angle);
    void AddRotationZOffset(float angle);

    void SetRotation(float x = 0.0f, float y = 0.0f, float z = 0.0f);
    void SetRotation(const glm::quat& rotation);

    void AddScaleOffset(float x, float y, float z);
    void AddScaleOffset(float val = 0.0f);
    void SetScale(float x, float y, float z);
    void SetScale(float val = 1.0f);

    void UpdateModelMatrices();

    glm::mat4 GetWorldModelMatrix() const;
    glm::vec3 GetWorldPosition() const;
    glm::vec3 GetEulerWorldRotation() const;
    glm::vec3 GetWorldScale() const;
    glm::vec3 GetWorldForwardDirection() const;
    
    glm::mat4 GetLocalModelMatrix() const {return localModel;}
    glm::vec3 GetLocalPosition() const {return localPosition;}
    glm::vec3 GetEulerLocalRotation() const;
    glm::vec3 GetLocalScale() const {return localScale;}
    
    bool IsDirty() const {return dirty;}
    
private:

    void MarkDirty();
    
private:

    Transform* parent = nullptr;
    std::vector<Transform*> children = {};
    
    glm::vec3 localPosition {0.0f};
    glm::quat localRotation {1.0f,0.f,0.f,0.f};
    glm::vec3 localScale {1.0f};

    glm::vec3 localForwardDir {0,0,1};
    
    glm::mat4 localModel {1.0f};
    bool dirty = false;
};
