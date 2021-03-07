#include <iostream>
#include "Shade.h"
#include "image.h"
#include "camera/camera.h"
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// settings
const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 8.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(1.0f, 1.0f, 3.0f);

unsigned int loadTexture(const char* path);

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    //std::cout <<xpos <<" " <<ypos << std::endl;
    lastX = xpos;
    lastY = ypos;

    //camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
    0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};

glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
};

// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(0.7f,  0.2f,  2.0f),
    glm::vec3(2.3f, -3.3f, -4.0f),
    glm::vec3(-4.0f,  2.0f, -12.0f),
    glm::vec3(0.0f,  0.0f, -3.0f)
};

const std::string color_VertexPath   = "..\\..\\..\\..\\..\\src\\Chapter_2\\lesson_2_8\\shader\\color_vs.shader";
const std::string color_FragmentPath = "..\\..\\..\\..\\..\\src\\Chapter_2\\lesson_2_8\\shader\\color_fs.shader";
const std::string light_VertexPath   = "..\\..\\..\\..\\..\\src\\Chapter_2\\lesson_2_8\\shader\\light_vs.shader";
const std::string light_FragmentPath = "..\\..\\..\\..\\..\\src\\Chapter_2\\lesson_2_8\\shader\\light_fs.shader";

const std::string texturePath1       = "..\\..\\..\\..\\..\\src\\image\\container2.png";
const std::string texturePath2       = "..\\..\\..\\..\\..\\src\\image\\container2_specular.png";


int main()
{
    Image image;
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
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    std::unique_ptr<Shader> mycolor_Shader = std::make_unique<Shader>(color_VertexPath.c_str(), color_FragmentPath.c_str());
    std::unique_ptr<Shader> mylight_Shader = std::make_unique<Shader>(light_VertexPath.c_str(), light_FragmentPath.c_str());
   
    
    unsigned int VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);//创建


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);//绑定
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);//设置数据

    // 位置属性
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
    
    unsigned int diffuseMap = loadTexture(texturePath1.c_str());
    unsigned int specularMap = loadTexture(texturePath2.c_str());

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mycolor_Shader->use();
        mycolor_Shader->setFloat("material.shininess", 32.0f);
        mycolor_Shader->setVec3("viewPos", camera.Position);

        // directional light
        mycolor_Shader->setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
        mycolor_Shader->setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
        mycolor_Shader->setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
        mycolor_Shader->setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
        // point light 1
        mycolor_Shader->setVec3("pointLights[0].position", pointLightPositions[0]);
        mycolor_Shader->setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
        mycolor_Shader->setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
        mycolor_Shader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        mycolor_Shader->setFloat("pointLights[0].constant", 1.0f);
        mycolor_Shader->setFloat("pointLights[0].linear", 0.7);
        mycolor_Shader->setFloat("pointLights[0].quadratic", 1.8);
        // point light 2
        mycolor_Shader->setVec3("pointLights[1].position", pointLightPositions[1]);
        mycolor_Shader->setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
        mycolor_Shader->setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
        mycolor_Shader->setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
        mycolor_Shader->setFloat("pointLights[1].constant", 1.0f);
        mycolor_Shader->setFloat("pointLights[1].linear", 0.7);
        mycolor_Shader->setFloat("pointLights[1].quadratic", 1.8);
        // point light 3
        mycolor_Shader->setVec3("pointLights[2].position", pointLightPositions[2]);
        mycolor_Shader->setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
        mycolor_Shader->setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
        mycolor_Shader->setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
        mycolor_Shader->setFloat("pointLights[2].constant", 1.0f);
        mycolor_Shader->setFloat("pointLights[2].linear", 0.7);
        mycolor_Shader->setFloat("pointLights[2].quadratic", 1.9);
        // point light 4
        mycolor_Shader->setVec3("pointLights[3].position", pointLightPositions[3]);
        mycolor_Shader->setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
        mycolor_Shader->setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
        mycolor_Shader->setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
        mycolor_Shader->setFloat("pointLights[3].constant", 1.0f);
        mycolor_Shader->setFloat("pointLights[3].linear", 0.7);
        mycolor_Shader->setFloat("pointLights[3].quadratic", 1.8);
        // spotLight
        mycolor_Shader->setVec3("spotLight.position", camera.Position);
        mycolor_Shader->setVec3("spotLight.direction", camera.Front);
        mycolor_Shader->setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
        mycolor_Shader->setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
        mycolor_Shader->setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
        mycolor_Shader->setFloat("spotLight.constant", 1.0f);
        mycolor_Shader->setFloat("spotLight.linear", 0.09);
        mycolor_Shader->setFloat("spotLight.quadratic", 0.032);
        mycolor_Shader->setFloat("spotLight.cutOff", glm::cos(glm::radians(0.5f)));
        mycolor_Shader->setFloat("spotLight.outerCutOff", glm::cos(glm::radians(0.0f)));



        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        mycolor_Shader->setMat4("projection", projection);
        mycolor_Shader->setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);

        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuseMap);
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specularMap);


        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            //float angle = 40.0f * (i+1);
            //model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.6f, 0.5f));
            //model = glm::scale(model, glm::vec3(2.0f));
            mycolor_Shader->setMat4("model", model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }



        // also draw the lamp object
        mylight_Shader->use();
        mylight_Shader->setMat4("projection", projection);
        mylight_Shader->setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.05f)); // a smaller cube
        mylight_Shader->setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            mylight_Shader->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}


// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(const char* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}