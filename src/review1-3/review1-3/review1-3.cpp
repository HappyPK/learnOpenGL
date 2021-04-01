#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shade.h"
#include "Image.h"
#include "Camera.h"
#include "ShaderSource.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Eigen/Dense"  
#include "Eigen/LU"  
#include "Eigen/Core" 

#include <math.h>

// settings
const unsigned int SCR_WIDTH  = 960;
const unsigned int SCR_HEIGHT = 540;

float Zoom         =  1.0;
bool  firstMouse   =  true;
float lastX        =  SCR_WIDTH / 2.0f;
float lastY        =  SCR_HEIGHT / 2.0f;
bool  BUTTON_LEFT =  false;
bool  BUTTON_RIGHT = false;

namespace
{
	std::shared_ptr<Camera> pCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
		Zoom -= (float)yoffset * 0.05;
	}

	void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{		
		if (BUTTON_LEFT)
		{
			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
				return;
			}
			float xoffset = lastX - xpos;
			float yoffset =  lastY - ypos;

			pCamera->rotateY(xoffset);
			pCamera->rotateX(yoffset);

			lastX = xpos;
			lastY = ypos;
		}
		else if (BUTTON_RIGHT)
		{
			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
				return;
			}
			float xoffset = lastX - xpos;
			float yoffset = lastY - ypos;

			pCamera->translateX(xoffset);
			pCamera->translateY(yoffset);

			lastX = xpos;
			lastY = ypos;
		}
	}

	void MouseButtonFun_CallBack(GLFWwindow* window, int button, int action, int mods)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_LEFT:
		{
			if (action == GLFW_PRESS)
			{
				BUTTON_LEFT = true;
			}
			else if (action == GLFW_RELEASE)
			{
				firstMouse = true;
				BUTTON_LEFT = false;
			}
			break;
		}
		case GLFW_MOUSE_BUTTON_RIGHT:
		{
			if (action == GLFW_PRESS)
			{
				BUTTON_RIGHT = true;
			}
			else if (action == GLFW_RELEASE)
			{
				firstMouse = true;
				BUTTON_RIGHT = false;
			}
			break;
		}
		default:
			return;
		}
	}

	bool genTexture(const std::string& imagePath, unsigned int& textureIndex)
	{
		ImagePtr image = std::make_shared<Image>(imagePath);
		if (!image->genGLTexture(textureIndex))
			return false;
		return true;
	}
}

float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

const std::string texturePath1 = "..\\..\\..\\..\\..\\src\\image\\container.jpg";
const std::string texturePath2 = "..\\..\\..\\..\\..\\src\\image\\awesomeface.png";

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetMouseButtonCallback(window,MouseButtonFun_CallBack);
	glfwSetScrollCallback(window, scroll_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	ShaderPtr pMyShader = std::make_shared<Shader>(vertexShaderSource, fragmentShaderSource);

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	unsigned int texture1, texture2;
	genTexture(texturePath1, texture1);
	genTexture(texturePath2, texture2);

	pMyShader->use();

	pMyShader->setInt("texture1", 0);
	pMyShader->setInt("texture2", 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		pMyShader->setFloat("fmix", 0.5 * sin(glfwGetTime()) + 0.5);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = pCamera->getModelViewMatrix();
		glm::mat4 projection = pCamera->getPerspectMat(Zoom, (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1, 100.0);

		pMyShader->setMat4("view", view);
		pMyShader->setMat4("projection", projection);
		pMyShader->setMat4("model", model);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}