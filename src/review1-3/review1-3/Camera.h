#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
typedef glm::vec3 Vector3d;
typedef glm::mat4 Mat4d;
#define PI 3.1415926535898

class Camera
{
public:
    // constructor with vectors
    Camera(const Vector3d& pos, const Vector3d& target,const Vector3d& up);

    void Camera::updateViewMat();

    Mat4d getModelViewMatrix();
    Mat4d getPerspectMat(float viewAngle, float aspect, float Near, float Far);
    void slide(float du, float dv, float dn);
    void roll(float angle);
    void yaw(float angle);
    void pitch(float angle);
    float getDist();

private:
    glm::mat3 getNuvMat();
private:
    Vector3d m_pos;
    Vector3d m_target;
    Vector3d m_up;

    glm::vec3 m_zaxis;//n
    glm::vec3 m_xaxis;//u
    glm::vec3 m_yaxis;//v

    Mat4d m_viewMat;
    Mat4d m_perspectMat;
};

Camera::Camera(const Vector3d& pos, const Vector3d& target, const Vector3d& up):
    m_pos(pos),m_target(target),m_up(up)
{
    updateViewMat();
}

void Camera::updateViewMat()
{
    m_zaxis = glm::normalize(m_pos - m_target);
    m_xaxis = glm::normalize(glm::cross(glm::normalize(m_up), m_zaxis));
    m_yaxis = glm::cross(m_zaxis, m_xaxis);

    glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
    translation[3][0] = -m_pos.x; // Third column, first row
    translation[3][1] = -m_pos.y;
    translation[3][2] = -m_pos.z;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = m_xaxis.x; // First column, first row
    rotation[1][0] = m_xaxis.y;
    rotation[2][0] = m_xaxis.z;
    rotation[0][1] = m_yaxis.x; // First column, second row
    rotation[1][1] = m_yaxis.y;
    rotation[2][1] = m_yaxis.z;
    rotation[0][2] = m_zaxis.x; // First column, third row
    rotation[1][2] = m_zaxis.y;
    rotation[2][2] = m_zaxis.z;

    m_viewMat = rotation * translation;
}

Mat4d Camera::getModelViewMatrix()
{
    updateViewMat();
    return m_viewMat;
}

Mat4d Camera::getPerspectMat(float viewAngle, float aspect, float Near, float Far)
{
    return glm::perspective(viewAngle, aspect, Near, Far);
}

glm::mat3 Camera::getNuvMat()
{
    glm::mat3 NUVMat;

    NUVMat[0][0] = m_xaxis.x; NUVMat[0][1] = m_xaxis.y; NUVMat[0][2] = m_xaxis.z;
    NUVMat[1][0] = m_yaxis.x; NUVMat[1][1] = m_yaxis.y; NUVMat[1][2] = m_yaxis.z;
    NUVMat[2][0] = m_zaxis.x; NUVMat[2][1] = m_zaxis.y; NUVMat[2][2] = m_zaxis.z;

    return NUVMat;
}

void Camera::slide(float du, float dv, float dn)
{
    Vector3d dvet(du, dv, dn);
    auto nuvMat = getNuvMat();
    m_pos = m_pos + dvet * nuvMat;
    m_target = m_target + dvet * nuvMat;
    updateViewMat();
}

void Camera::roll(float angle)
{
    float cs = cos(angle * PI / 180);
    float sn = sin(angle * PI / 180);
    Vector3d t(m_xaxis);
    Vector3d s(m_yaxis);
    m_xaxis = cs * t - sn * s;
    m_yaxis = sn * t + cs * s;

    updateViewMat(); 
}

void Camera::pitch(float angle)
{
    float cs = cos(angle * PI / 180);
    float sn = sin(angle * PI / 180);
    Vector3d t(m_yaxis);
    Vector3d s(m_zaxis);

    m_yaxis = cs * t - sn * s;
    m_zaxis = sn * t + cs * s;

    updateViewMat();
}

void Camera::yaw(float angle)
{
    float cs = cos(angle * PI / 180);
    float sn = sin(angle * PI / 180);
    Vector3d t(m_zaxis);
    Vector3d s(m_xaxis);

    m_zaxis = cs * t - sn * s;
    m_xaxis = sn * t + cs * s;

    updateViewMat();
}

float Camera::getDist()
{
    float dist = pow(m_pos.x, 2) + pow(m_pos.y, 2) + pow(m_pos.z, 2);
    return pow(dist, 0.5);
}