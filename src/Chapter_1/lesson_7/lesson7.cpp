#include "common.h"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define USE_MORE_ATTRIBUTE true
#define SCR_WIDITH 1280
#define SCR_HEIGHT 768

void SetVertex(std::vector<float>& vertices)
{
    vertices = {
        // positions          // texture coords
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

        -0.5f, 0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, 0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, 0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, 0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f,  0.0f, 1.0f };
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void createVAO(uint32_t &VAO)
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
}

void createEBO(std::vector<unsigned int> indices, uint32_t &EBO)
{
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void SetGLMode(const GLenum& mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

void createTexture(const std::string &image, uint32_t &texture)
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

int main()
{
    std::unique_ptr<LearnOpenGLCommon> learnopengl = std::make_unique<LearnOpenGLCommon>(4, 6, SCR_WIDITH, SCR_HEIGHT, "Lesson 6");

    auto window = learnopengl->GetGlfwWindows();
    
    std::string VertexPath = "..\\..\\..\\..\\..\\src\\Chapter_1\\lesson_7\\shader\\vertex.shader";
    std::string FragmentPath = "..\\..\\..\\..\\..\\src\\Chapter_1\\lesson_7\\shader\\fragment.shader";
    std::unique_ptr<MyShader> myShader = std::make_unique<MyShader>(VertexPath.c_str(), FragmentPath.c_str());
    

    stbi_set_flip_vertically_on_load(true);

    std::vector<float> vertices;
    SetVertex(vertices);

    std::vector<unsigned int> indices;
    SetIndex(indices);

    unsigned int VBO, VAO, EBO, Texture1, Texture2;
    createVAO(VAO);
    createVBO(vertices, VBO);
    createEBO(indices, EBO);

    createTexture("container.jpg", Texture1);
    createTexture("awesomeface.png", Texture2);

    myShader->use();
    myShader->setInt("texture1", 0);
    myShader->setInt("texture2", 1);
    glEnable(GL_DEPTH_TEST);

    glm::vec3 cubePositions[] = 
    {
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

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDITH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    myShader->setMat4("projection", projection);

    int timeIndex = 0;
    glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    while (!glfwWindowShouldClose(window))
    {
        learnopengl->processInput(cameraPos, cameraFront, cameraUp);
        
        glClearColor((float)(timeIndex++) *0.001f, (float)(timeIndex++) * 0.002f, (float)(timeIndex++) * 0.0022f, 1.0f);
        if (timeIndex > 1000)
            timeIndex = 0;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind Texture
        glActiveTexture(GL_TEXTURE0); // 在绑定纹理之前先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, Texture1);
        glActiveTexture(GL_TEXTURE1); // 在绑定纹理之前先激活纹理单元
        glBindTexture(GL_TEXTURE_2D, Texture2);

        myShader->use();

        
        glm::mat4 view = glm::mat4(1.0f);


        view = glm::lookAt
        (
            cameraPos,
            cameraPos+ cameraFront,
            cameraUp
        );
        myShader->setMat4("view", view);

        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);;
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * (i+5);
            model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            myShader->setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return 0;
}

