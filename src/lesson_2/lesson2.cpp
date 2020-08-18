#include "common.h"


const char* vertexShaderSource = "#version 460 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 460 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 0.0f);\n"
"}\n\0";

using namespace LearnOpenGL;


bool CheckShader(const int &shader)
{
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return false;
    }
    return true;
}

bool CreateShader(int& shader, const GLenum &type, const GLchar* const* string)
{
    shader = glCreateShader(type);
    glShaderSource(shader, 1, string, NULL);
    glCompileShader(shader);
    if (!CheckShader(shader))
        return false;
    return true;
}

bool LinkShader(int &Linkshader, const int& shader1, const int& shader2)
{
    Linkshader = glCreateProgram();
    glAttachShader(Linkshader, shader1);
    glAttachShader(Linkshader, shader2);
    glLinkProgram(Linkshader);

    if (!CheckShader(Linkshader))
        return false;
    return true;

    glDeleteShader(shader1);
    glDeleteShader(shader2);
}

void SetVertex(std::vector<float> &vertices)
{
    vertices =
    {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角 
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

unsigned int createVBO(const std::vector<float> vertices)
{
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, (vertices.size() * sizeof(float)), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()* sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    return EBO;
}

void SetGLMode(const GLenum &mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);
}

int main()
{
    std::unique_ptr<LearnOpenGLCommon> learnopengl = std::make_unique<LearnOpenGLCommon>(4, 6, 1280, 768, "Lesson 2");

    auto window = learnopengl->GetGlfwWindows();

    //创建一个着色器对象
    int vertexShader = 0;
    if (!CreateShader(vertexShader, GL_VERTEX_SHADER, &vertexShaderSource))
    {
        return false;
    }

    //片段着色器
    int fragmentShader = 0;
    if (!CreateShader(vertexShader, GL_FRAGMENT_SHADER, &fragmentShaderSource))
    {
        return false;
    }

    //连接着色器
    int shaderProgram = 0;
    if (!LinkShader(shaderProgram, vertexShader, fragmentShader))
    {
        return false;
    }

    std::vector<float> vertices;
    SetVertex(vertices);

    std::vector<unsigned int> indices;
    SetIndex(indices);

    unsigned int VBO, VAO, EBO;
    
    VAO = createVAO();
    VBO = createVBO(vertices);
    EBO = createEBO(indices);

    SetGLMode(GL_FILL);

    while (!glfwWindowShouldClose(window))
    {
        learnopengl->processInput();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    return 0;
}

