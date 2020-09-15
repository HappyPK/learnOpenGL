#include "common.h"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

const float SCR_WIDITH = 1280;
const float SCR_HEIGHT = 768;
float lastX = SCR_WIDITH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

void SetVertex(std::vector<float>& vertices)
{
    vertices = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };
}

void SetIndex(std::vector<unsigned int>& indices)
{
    indices =
    { // 注意索引从0开始! 
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
}

void createVBO(const std::vector<float> vertices, uint32_t& VBO)
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void createVAO(uint32_t& VAO)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

void createEBO(std::vector<unsigned int> indices, uint32_t& EBO)
{
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void SetGLMode(const GLenum& mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void createTexture(const std::string& image, uint32_t& texture)
{
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;

    std::string path = "..\\..\\..\\..\\..\\pic\\" + image;
    std::string pureName = image.substr(image.find_last_of(".") + 1);
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        if (pureName == "png")
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else if (pureName == "jpg" || pureName == "jpeg")
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
            stbi_image_free(data);
            return;
        }

        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
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
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

int main()
{
    std::unique_ptr<LearnOpenGLCommon> learnopengl = std::make_unique<LearnOpenGLCommon>(4, 6, SCR_WIDITH, SCR_HEIGHT, "Lesson 7-2");
    auto window = learnopengl->GetGlfwWindows();
    learnopengl->SetCursorPosCallback(mouse_callback);
    learnopengl->SetscrollfunCallback(scroll_callback);
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    std::string cube_VertexPath = "..\\..\\..\\..\\..\\src\\Chapter_2\\lesson_2_1\\shader\\lightCube\\lightCube_vertex.shader";
    std::string cube_FragmentPath = "..\\..\\..\\..\\..\\src\\Chapter_2\\lesson_2_1\\shader\\lightCube\\lightCube_fragment.shader";
    std::unique_ptr<MyShader> myCubeShader = std::make_unique<MyShader>(cube_VertexPath.c_str(), cube_FragmentPath.c_str());


    std::string light_VertexPath = "..\\..\\..\\..\\..\\src\\Chapter_2\\lesson_2_1\\shader\\lighting\\lighting_vertex.shader";
    std::string light_FragmentPath = "..\\..\\..\\..\\..\\src\\Chapter_2\\lesson_2_1\\shader\\lighting\\lighting_fragment.shader";
    std::unique_ptr<MyShader> myLightShader = std::make_unique<MyShader>(light_VertexPath.c_str(), light_FragmentPath.c_str());

    stbi_set_flip_vertically_on_load(true);

    std::vector<float> vertices;
    SetVertex(vertices);

    std::vector<unsigned int> indices;
    SetIndex(indices);

    unsigned int cubeVAO, VBO, lightCubeVAO;
    createVAO(cubeVAO);
    createVBO(vertices, VBO);

    createVAO(lightCubeVAO);
    createVBO(vertices, VBO);

    glEnable(GL_DEPTH_TEST);
   
    // lighting
    glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

    int timeIndex = 0;

    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        learnopengl->processInputWithCamera(camera, deltaTime);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
      
        myLightShader->use();
        myLightShader->setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        myLightShader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDITH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = glm::mat4(1.0f); 
        view = camera.GetViewMatrix();
        myLightShader->setMat4("projection", projection);
        myLightShader->setMat4("view", view);

        // world transformation
        glm::mat4 model = glm::mat4(1.0f);
        myLightShader->setMat4("model", model);
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // also draw the lamp object
        myCubeShader->use();
        myCubeShader->setMat4("projection", projection);
        myCubeShader->setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        myCubeShader->setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &cubeVAO);

    return 0;
}
