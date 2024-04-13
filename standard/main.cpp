#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.cpp"
#include "data.cpp"
#include "texture.cpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    if (!glfwInit()) // 初始化 GLFW
    {
        std::cerr << "Could not initialize GLFW!" << std::endl;

        return 1;
    }

    // 配置 GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS

    // 创建窗口
    GLFWwindow *window = glfwCreateWindow(800, 600, "CG Tutorial", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // 通知 GLFW 将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);

    // 初始化 GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // 告诉 OpenGL 渲染窗口的尺寸大小，即视口
    glViewport(0, 0, 800, 600);
    // 告诉 GLFW 我们希望每当窗口调整大小的时候调用这个函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // 创建并编译着色器程序
    int shaderProgram = createProgram(vertexString, fragString);
    int VAO = createVAO();
    stbi_set_flip_vertically_on_load(true); // 翻转Y轴
    int texture = createTexture("static-resources/container.jpeg", false);

    // 渲染循环
    while (!glfwWindowShouldClose(window)) // 检查一次 GLFW 是否被要求退出
    {
        // 输入
        processInput(window);

        // 渲染指令
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindTexture(GL_TEXTURE_2D, texture);
        CHECK_GL(glUseProgram(shaderProgram));
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 检查并调用事件，交换缓冲
        glfwSwapBuffers(window); // 交换颜色缓冲
        glfwPollEvents();        // 函数检查有没有触发什么事件、更新窗口状态，并调用对应的回调函数
    }

    glfwTerminate();

    return 0;
}
