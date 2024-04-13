#include <iostream>
#include <glad/glad.h>

#define CHECK_GL(glFunc)                                                                                                              \
    glFunc;                                                                                                                           \
    {                                                                                                                                 \
        int e = glGetError();                                                                                                         \
        if (e != 0)                                                                                                                   \
        {                                                                                                                             \
            std::string errorString = "";                                                                                             \
            switch (e)                                                                                                                \
            {                                                                                                                         \
            case GL_INVALID_ENUM:                                                                                                     \
                errorString = "GL_INVALID_ENUM";                                                                                      \
                break;                                                                                                                \
            case GL_INVALID_VALUE:                                                                                                    \
                errorString = "GL_INVALID_VALUE";                                                                                     \
                break;                                                                                                                \
            case GL_INVALID_OPERATION:                                                                                                \
                errorString = "GL_INVALID_OPERATION";                                                                                 \
                break;                                                                                                                \
            case GL_OUT_OF_MEMORY:                                                                                                    \
                errorString = "GL_OUT_OF_MEMORY";                                                                                     \
                break;                                                                                                                \
            default:                                                                                                                  \
                break;                                                                                                                \
            }                                                                                                                         \
            std::cout << "GL ERROR " << errorString.c_str() << " in " << __PRETTY_FUNCTION__ << " at line " << __LINE__ << std::endl; \
            abort();                                                                                                                  \
        }                                                                                                                             \
    }
#define STRINGIZE(x) #x
#define SHADER_STRING(text) STRINGIZE(text)

const std::string vertexString = SHADER_STRING(
    // 设定了输入变量的位置值
    layout(location = 0) in vec3 aPos;
    layout(location = 1) in vec3 aColor;
    layout(location = 2) in vec2 aTexCoord;

    out vec3 ourColor;
    out vec2 TexCoord;

    uniform mat4 transform;

    void main() {
        ourColor = aColor;

        gl_Position = transform * vec4(aPos, 1.0f);
        TexCoord = vec2(aTexCoord.x, aTexCoord.y);
    });

const std::string fragString = SHADER_STRING(
    // 片段着色器只需要一个输出变量，这个变量是一个 4 分量向量，它表示的是最终的输出颜色
    out vec4 FragColor;

    in vec3 ourColor;
    in vec2 TexCoord;

    uniform sampler2D ourTexture;

    void main() {
        FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
    });

int createProgram(const std::string &vertexSource, const std::string &fragmentSource)
{
    const std::string preString = "\
    #version 330 \n\
    ";
    std::string vertexCombineSource = preString + vertexSource;
    std::string fragmentCombineSource = preString + fragmentSource;
    const char *vertexResultStr = vertexCombineSource.c_str();
    const char *fragmentResultStr = fragmentCombineSource.c_str();

    // 编译顶点着色器
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    CHECK_GL(glShaderSource(vertexShader, 1, &vertexResultStr, NULL));
    CHECK_GL(glCompileShader(vertexShader));

    // 编译片段着色器
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    CHECK_GL(glShaderSource(fragmentShader, 1, &fragmentResultStr, NULL));
    CHECK_GL(glCompileShader(fragmentShader));

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    CHECK_GL(glAttachShader(shaderProgram, vertexShader));
    CHECK_GL(glAttachShader(shaderProgram, fragmentShader));
    CHECK_GL(glLinkProgram(shaderProgram));
    // CHECK_GL(glUseProgram(shaderProgram)); // 激活程序对象
    CHECK_GL(glDeleteShader(vertexShader));
    CHECK_GL(glDeleteShader(fragmentShader));

    return shaderProgram;
}
