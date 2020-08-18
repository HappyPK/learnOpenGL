#include "common.h"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define USE_MORE_ATTRIBUTE true

using namespace LearnOpenGL;

void SetVertex(std::vector<float>& vertices)
{
    vertices =
    {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
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

void createTexture(uint32_t &texture)
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
    
    std::string path = "..\\..\\..\\..\\pic\\wall.jpg";
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
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
    std::unique_ptr<LearnOpenGLCommon> learnopengl = std::make_unique<LearnOpenGLCommon>(4, 6, 1280, 768, "Lesson 4");

    auto window = learnopengl->GetGlfwWindows();

    std::string VertexPath = "..\\..\\..\\..\\learnOpenGL\\src\\lesson_4\\shader\\vertex.shader";
    std::string FragmentPath = "..\\..\\..\\..\\learnOpenGL\\src\\lesson_4\\shader\\fragment.shader";
    std::unique_ptr<MyShader> myShader = std::make_unique<MyShader>(VertexPath.c_str(),FragmentPath.c_str());

    myShader->use();

    std::vector<float> vertices;
    SetVertex(vertices);

    std::vector<unsigned int> indices;
    SetIndex(indices);

    unsigned int VBO, VAO, EBO, Texture;
    createVAO(VAO);
    createVBO(vertices, VBO);
    createEBO(indices, EBO);
    createTexture(Texture);
    SetGLMode(GL_FILL);
    float offset = 0.5f;
    myShader->setFloat("xOffset", offset);

    while (!glfwWindowShouldClose(window))
    {
        learnopengl->processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    return 0;
}

