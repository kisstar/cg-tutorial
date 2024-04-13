#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>

void transform(int shaderProgram)
{
    // create transformations
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    // 把箱子放在窗口的右下角
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
    // 使用 GLFW 的时间函数来获取不同时间的角度
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));

    unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}
