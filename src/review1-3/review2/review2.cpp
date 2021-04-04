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
	std::shared_ptr<Camera> pCamera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	std::shared_ptr<Camera> pEye = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));

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
		pEye->Scroll(yoffset);
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
			float xoffset = xpos - lastX ;
			float yoffset = ypos - lastY ;

			pCamera->rotateY(xoffset, 0.1);
			pCamera->rotateX(yoffset, 0.1);

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

			pEye->rotateY(xoffset, 0.1);
			pEye->rotateX(yoffset, 0.1);

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

// positions all containers
float d = 3.0f;
glm::vec3 cubePositions[] = 
{
	glm::vec3( 1.0f,  1.0f, 1.0f)* d,
	glm::vec3(-1.0f,  1.0f, 1.0f)* d,
	glm::vec3(-1.0f, -1.0f, 1.0f)* d,
	glm::vec3( 1.0f, -1.0f, 1.0f)* d,
	glm::vec3( 1.0f,  1.0f, -1.0f)* d,
	glm::vec3(-1.0f,  1.0f, -1.0f)* d,
	glm::vec3(-1.0f, -1.0f, -1.0f)* d,
	glm::vec3( 1.0f, -1.0f, -1.0f)* d
};

float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
};
const std::string texturePath1 = "..\\..\\..\\..\\..\\src\\image\\container2.png";
const std::string texturePath2 = "..\\..\\..\\..\\..\\src\\image\\container2_specular.png";
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
	ShaderPtr pMyLightShader = std::make_shared<Shader>(Light_vertexShaderSource, Light_fragmentShaderSource);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindVertexArray(VAO);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	unsigned int lightCubeVAO;
	glGenVertexArrays(1, &lightCubeVAO);
	glBindVertexArray(lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	unsigned int textureID1, textureID2;
	genTexture(texturePath1, textureID1);
	genTexture(texturePath2, textureID2);

	pMyShader->use();
	pMyShader->setInt("material.diffuse", 0);
	pMyShader->setInt("material.specular", 1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = pEye->getModelViewMatrix();
		std::cout << Zoom << std::endl;
		glm::mat4 projection = pEye->getPerspectMat(Zoom, (GLfloat)SCR_WIDTH / (GLfloat)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::vec3 lightPos = pCamera->getCameraPos();

		pMyShader->use();
		pMyShader->setVec3("viewPos", pEye->getCameraPos());
		
		float shininess = 64.0;
		pMyShader->setFloat("material.shininess", shininess);
		
		pMyShader->setVec3("light.direction", -lightPos);
		pMyShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
		pMyShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
		pMyShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

		pMyShader->setMat4("view", view);
		pMyShader->setMat4("projection", projection);

		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureID2);

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 8; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 0.0f * i;
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			pMyShader->setMat4("model", model);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		pMyLightShader->use();
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.00001f));

		pMyLightShader->setMat4("view", view);
		pMyLightShader->setMat4("projection", projection);
		pMyLightShader->setMat4("model", model);

		glBindVertexArray(lightCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return 0;
}