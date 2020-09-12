#include "common.h"

int main()
{
    std::unique_ptr<LearnOpenGLCommon> learnopengl = std::make_unique<LearnOpenGLCommon>(4, 6, 1280, 768, "Lesson 1");
    auto window = learnopengl->GetGlfwWindows();


    while (!glfwWindowShouldClose(window))
    {
        learnopengl->processInput();

        //×´Ì¬ÉèÖÃ
        glClearColor(0.31f, 0.31f, 0.9f, 0.0f);
        glClearDepth(0);
        //×´Ì¬Ê¹ÓÃ
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	return 0;
}