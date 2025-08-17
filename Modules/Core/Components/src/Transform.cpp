#include "Transform.h"

#include "glm/ext/matrix_transform.hpp"

Transform::Transform()
    : localPosition(glm::vec3(0.0f, 0.0f, 0.0f)), localRotation(glm::vec3(0.0f, 0.0f, 0.0f)), localScale(glm::vec3(1.0f, 1.0f, 1.0f)),
        parent(nullptr), children({nullptr})
{
    
}

void Transform::AddPositionOffset(float x, float y, float z)
{
    localPosition.x += x;
    localPosition.y += y;
    localPosition.z += z;

    MarkDirty();
}

void Transform::AddPositionOffset(const glm::vec3& offsetDirection, float offsetValue)
{
    localPosition += offsetDirection * offsetValue;
    MarkDirty();
}

void Transform::SetPosition(float x, float y, float z)
{
    localPosition = glm::vec3(x, y, z);
    MarkDirty();
}

void Transform::AddRotationXOffset(float angle)
{
    localRotation = glm::normalize(
        glm::angleAxis(glm::radians(angle), glm::vec3(1.0f, 0.0f, 0.0f)) * localRotation
    );
    MarkDirty();
}

void Transform::AddRotationYOffset(float angle)
{
    localRotation = glm::normalize(
        glm::angleAxis(glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f)) * localRotation
    );
    MarkDirty();
}

void Transform::AddRotationZOffset(float angle)
{
    localRotation = glm::normalize(
        glm::angleAxis(glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f)) * localRotation
    );
    MarkDirty();
}

void Transform::SetRotation(float x, float y, float z)
{
    localRotation = glm::quat(glm::radians(glm::vec3(x, y, z)));
    MarkDirty();
}

void Transform::SetRotation(const glm::quat& rotation)
{
    localRotation = rotation;
    MarkDirty();
}

void Transform::AddScaleOffset(float x, float y, float z)
{
    localScale.x += x;
    localScale.y += y;
    localScale.z += z;
    MarkDirty();
}

void Transform::AddScaleOffset(float val)
{
    localScale.x += val;
    localScale.y += val;
    localScale.z += val;
    MarkDirty();
}

void Transform::SetScale(float val)
{
    localScale = glm::vec3(val);
    MarkDirty();
}

void Transform::SetScale(float x, float y, float z)
{
    localScale = glm::vec3(x, y, z);
    MarkDirty();
}

void Transform::MarkDirty()
{
    dirty = true;
}

void Transform::UpdateModelMatrices()
{
    localModel = glm::translate(glm::mat4(1.f), localPosition)
                * glm::mat4_cast(localRotation)
                * glm::scale(glm::mat4(1.f), localScale);

    dirty = false;
}

glm::mat4 Transform::GetWorldModelMatrix() const
{
    if (!parent)
        return localModel;

    return parent->GetWorldModelMatrix() * localModel;
}

glm::vec3 Transform::GetWorldPosition() const
{
    return glm::vec3(GetWorldModelMatrix()[3]);
}

glm::quat Transform::GetQuatWorldRotation() const
{
    return parent ? parent->GetQuatWorldRotation() * localRotation : localRotation;
}

glm::vec3 Transform::GetEulerWorldRotation() const
{
    if (!parent)
        return GetEulerLocalRotation();

    return parent->GetEulerWorldRotation() * localRotation;
}

glm::vec3 Transform::GetWorldScale() const
{
    return {
        glm::length(glm::vec3(GetWorldModelMatrix()[0])),
        glm::length(glm::vec3(GetWorldModelMatrix()[1])),
        glm::length(glm::vec3(GetWorldModelMatrix()[2]))
    };
}

glm::vec3 Transform::GetWorldForwardDirection() const
{
    return glm::normalize(GetQuatWorldRotation() * glm::vec3(0.f,0.f,-1.f));
}

glm::vec3 Transform::GetWorldUpDirection() const
{
    return glm::normalize(glm::cross(GetWorldRightDirection(), GetWorldForwardDirection()));
}

glm::vec3 Transform::GetWorldRightDirection() const
{
    glm::vec3 kWorldUp = glm::vec3(0.f,1.f,0.f);
    
    // Handle degeneracy if forward ~ worldUp
    glm::vec3 up = glm::abs(glm::dot(GetWorldForwardDirection(), kWorldUp)) > 0.999f
                 ? glm::vec3(0.0f, 0.0f, 1.0f)  // fallback up
                 : kWorldUp;

    // Right-handed: right = cross(forward, up)
    glm::vec3 r = glm::normalize(glm::cross(GetWorldForwardDirection(), up));
    return r;
}

glm::vec3 Transform::GetEulerLocalRotation() const
{
    return glm::degrees(glm::eulerAngles(localRotation));
}
