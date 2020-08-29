#include "common.h"

namespace LearnOpenGL
{
    void DefaultFramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }


    LearnOpenGLCommon::LearnOpenGLCommon(const int& PROFILE, const int& CORE_PROFILE, const int& width, const int& height, const char* name):
        m_window(nullptr)
    {
        GlfwInit();
        SetOpenGlVersion(PROFILE, CORE_PROFILE);
        if (!InitGlfwWindows(width, height, name))
        {
            glfwTerminate();
        }
    }

    LearnOpenGLCommon::~LearnOpenGLCommon()
    {
        glfwTerminate();
    }

    void LearnOpenGLCommon::processInput(glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp)
    {
        if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window, true);
        if (glfwGetKey(m_window, GLFW_KEY_ENTER) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_window, true);

        float deltaTime = 0.0f; // 当前帧与上一帧的时间差
        float lastFrame = 0.0f; // 上一帧的时间
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float cameraSpeed = 0.005f * deltaTime; // adjust accordingly
        if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    void LearnOpenGLCommon::GlfwInit()
    {
        glfwInit();
    }

    void LearnOpenGLCommon::SetOpenGlVersion(const int& PROFILE, const int& CORE_PROFILE)
    {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    bool LearnOpenGLCommon::CreateWindows(const int& width, const int& height, const char* name)
    {
        m_window = glfwCreateWindow(width, height, name, NULL, NULL);
        if (m_window == NULL)
        {
            std::cout << "Failed to create GLFW window" << std::endl;
            glfwTerminate();
            return false;
        }
        return true;
    }

    bool LearnOpenGLCommon::CreateGladLoader()
    {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cout << "Failed to initialize GLAD" << std::endl;
            return false;
        }
        return true;
    }

    void LearnOpenGLCommon::MakeContextCurrent()
    {
        glfwMakeContextCurrent(m_window);
    }

    void LearnOpenGLCommon::SetCallback(GLFWframebuffersizefun callback)
    {
        glfwSetFramebufferSizeCallback(m_window, callback);
    }

    bool LearnOpenGLCommon::InitGlfwWindows(const int& width, const int& height, const char* name)
    {
        if (!CreateWindows(width, height, name))
        {
            return false;
        }
        
        MakeContextCurrent();
        CreateGladLoader();
        SetCallback(DefaultFramebufferSizeCallback);

        return true;
    }
}
