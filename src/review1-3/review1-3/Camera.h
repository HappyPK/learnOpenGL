#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
typedef glm::vec3 Vector3d;
typedef glm::vec4 Vector4d;
typedef glm::mat4 Mat4d;
#define PI 3.1415926535898

class Camera
{
public:
    // constructor with vectors
    Camera(const Vector3d& pos, const Vector3d& target,const Vector3d& up);

    Mat4d getModelViewMatrix();
    Mat4d getPerspectMat(float viewAngle, float aspect, float Near, float Far);

    void rotateY(const float& xoffset);
    void rotateX(const float& yoffset);

private:
    Vector3d m_pos;
    Vector3d m_target;
    Vector3d m_up;

    float m_factor;

private:
    Vector4d Dir() 
    { 
        return Vector4d((m_pos - m_target), 1.0f);
    }

    Vector3d Right()
    {
        glm::vec3 cameraDirection = glm::normalize(m_pos - m_target);
        glm::vec3 cameraRight = glm::normalize(glm::cross(m_up, cameraDirection));
        return cameraRight;
    }
};

Camera::Camera(const Vector3d& pos, const Vector3d& target, const Vector3d& up):
    m_pos(pos),m_target(target),m_up(up)
{
    m_factor = 0.5;
}


Mat4d Camera::getModelViewMatrix()
{
    return glm::lookAt(m_pos, m_target, m_up);
}

Mat4d Camera::getPerspectMat(float viewAngle, float aspect, float Near, float Far)
{
    return glm::perspective(viewAngle, aspect, Near, Far);
}

void Camera::rotateY(const float& xoffset)
{
    float angle = xoffset * m_factor;
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));

    auto dir = trans * Dir();
    auto up = trans * Vector4d(m_up, 1.0f);
    m_up = Vector3d(up.x, up.y, up.z);
    auto pos = trans * Vector4d(m_pos, 1.0f);
    m_pos = Vector3d(pos.x, pos.y, pos.z);
}

void Camera::rotateX(const float& yoffset)
{
    float angle = yoffset * m_factor;
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::rotate(trans, glm::radians(angle), Right());

    auto dir = trans * Dir();
    auto up = trans * Vector4d(m_up, 1.0f);
    m_up = Vector3d(up.x, up.y, up.z);
    auto pos = trans * Vector4d(m_pos, 1.0f);
    m_pos = Vector3d(pos.x, pos.y, pos.z);
}
