#include "Transform.h"

#include "glm/ext/matrix_transform.hpp"

Transform::Transform()
    : position(glm::vec3(0.0f, 0.0f, 0.0f)), rotation(glm::vec3(0.0f, 0.0f, 0.0f)), scale(glm::vec3(1.0f, 1.0f, 1.0f))
{
    
}

void Transform::AddPositionOffset(float x, float y, float z)
{
    position.x += x;
    position.y += y;
    position.z += z;

    MarkDirty();
}

void Transform::SetPosition(float x, float y, float z)
{
    position = glm::vec3(x, y, z);
    MarkDirty();
}

void Transform::AddRotationXOffset(float angle)
{
    rotation.x += angle;
    MarkDirty();
}

void Transform::AddRotationYOffset(float angle)
{
    rotation.y += angle;
    MarkDirty();
}

void Transform::AddRotationZOffset(float angle)
{
    rotation.z += angle;
    MarkDirty();
}

void Transform::SetRotation(float x, float y, float z)
{
    rotation = glm::vec3(x, y, z);
    MarkDirty();
}

void Transform::AddScaleOffset(float x, float y, float z)
{
    scale.x += x;
    scale.y += y;
    scale.z += z;
    MarkDirty();
}

void Transform::AddScaleOffset(float val)
{
    scale.x += val;
    scale.y += val;
    scale.z += val;
    MarkDirty();
}

void Transform::SetScale(float val)
{
    scale = glm::vec3(val);
    MarkDirty();
}

void Transform::SetScale(float x, float y, float z)
{
    scale = glm::vec3(x, y, z);
    MarkDirty();
}

void Transform::MarkDirty()
{
    dirty = true;
}

void Transform::UpdateModelMatrix()
{
    // position
    model = glm::translate(glm::mat4(1.0f), position);
    
    // rotation
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    
    // scale
    model = glm::scale(model, scale);

    dirty = false;
}
