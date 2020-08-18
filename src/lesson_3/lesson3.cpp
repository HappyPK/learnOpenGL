#include "common.h"
#include "Shader.h"
#define USE_MORE_ATTRIBUTE true

using namespace LearnOpenGL;

void SetVertex(std::vector<float>& vertices)
{
    if (USE_MORE_ATTRIBUTE)
    {
        vertices =
        {
            // 位置              // 颜色
            0.5f, -0.5f, 0.0f,  0.5f, 1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 1.0f,   // 左下
            0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.5f    // 顶部
        };
    }
    else
    {
        vertices =
        {
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f   // 左上角 
        };
    }

}

void SetIndex(std::vector<unsigned int>& indices)
{
    indices =
    { // 注意索引从0开始! 
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };
}

unsigned int createVBO(const std::vector<float> vertices)
{
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);
    
    int cout = USE_MORE_ATTRIBUTE ? 6 : 3;
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, cout * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    if (USE_MORE_ATTRIBUTE)
    {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, cout * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    return VBO;
}

unsigned int createVAO()
{
    unsigned int  VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    return VAO;
}

unsigned int createEBO(std::vector<unsigned int> indices)
{
    unsigned int  EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    return EBO;
}

void SetGLMode(const GLenum& mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

int main()
{
    std::unique_ptr<LearnOpenGLCommon> learnopengl = std::make_unique<LearnOpenGLCommon>(4, 6, 1280, 768, "Lesson 2");

    auto window = learnopengl->GetGlfwWindows();

    std::string VertexPath = "..\\..\\..\\..\\src\\lesson_3\\shader\\vertex.shader";
    std::string FragmentPath = "..\\..\\..\\..\\src\\lesson_3\\shader\\fragment.shader";
    std::unique_ptr<MyShader> myShader = std::make_unique<MyShader>(VertexPath.c_str(),FragmentPath.c_str());

    myShader->use();

    std::vector<float> vertices;
    SetVertex(vertices);

    std::vector<unsigned int> indices;
    SetIndex(indices);

    unsigned int VBO, VAO, EBO;

    VAO = createVAO();
    VBO = createVBO(vertices);
    EBO = createEBO(indices);

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

