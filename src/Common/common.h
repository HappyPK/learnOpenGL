#include <iostream>
#include"glad/glad.h"
#include"GLFW/glfw3.h"
#include <vector>
#include <string>

namespace LearnOpenGL
{
	class LearnOpenGLCommon
	{
	public:
		LearnOpenGLCommon(const int& PROFILE, const int& CORE_PROFILE, const int& width, const int& height, const char* name);
		~LearnOpenGLCommon();

	public:
		bool InitGlfwWindows(const int& width, const int& height, const char* name);

		GLFWwindow* GetGlfwWindows() { return m_window; }
		void processInput();
	private:
		void GlfwInit();
		void SetOpenGlVersion(const int& PROFILE, const int& CORE_PROFILE);
		bool CreateWindows(const int& width, const int& height, const char* name);
		bool CreateGladLoader();
		void MakeContextCurrent();
		void SetCallback(GLFWframebuffersizefun callback);

	private:
		GLFWwindow* m_window;
	};

	void DefaultFramebufferSizeCallback(GLFWwindow* window, int width, int height);

}
