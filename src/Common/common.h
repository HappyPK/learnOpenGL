#include <iostream>
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "camera.h"

class LearnOpenGLCommon
{
public:
	LearnOpenGLCommon(const int& PROFILE, const int& CORE_PROFILE, const int& width, const int& height, const char* name);
	~LearnOpenGLCommon();

public:
	bool InitGlfwWindows(const int& width, const int& height, const char* name);

	GLFWwindow* GetGlfwWindows() { return m_window; }
	void processInput();
	void processInput(glm::vec3 &cameraPos, glm::vec3 &cameraFront, glm::vec3 &cameraUp);
	void processInputWithCamera(Camera &camera, float deltaTime);

public://callback
	void SetscrollfunCallback(GLFWscrollfun callback);
	void SetCursorPosCallback(GLFWcursorposfun callback);

private:
	void GlfwInit();
	void SetOpenGlVersion(const int& PROFILE, const int& CORE_PROFILE);
	bool CreateWindows(const int& width, const int& height, const char* name);
	bool CreateGladLoader();
	void MakeContextCurrent();
	void SetframebuffersizefunCallback(GLFWframebuffersizefun callback);

private:
	GLFWwindow* m_window;
};

void DefaultFramebufferSizeCallback(GLFWwindow* window, int width, int height);
