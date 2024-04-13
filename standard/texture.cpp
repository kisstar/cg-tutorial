#include <iostream>
#include <stb_image.h>
#include <glad/glad.h>

int createTexture(const char *filename, bool use_RGBA)
{
    unsigned int texture;
    glGenTextures(1, &texture);
    // GL_TEXTURE0 默认被激活
    // glActiveTexture(GL_TEXTURE0);
    // 绑定纹理对象（之后任何的纹理指令都可以配置当前绑定的纹理）
    glBindTexture(GL_TEXTURE_2D, texture); // （会绑定这个纹理到当前激活的纹理单元）

    // 设置纹理环绕方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    // 设置纹理过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 多级渐远纹理主要是使用在纹理被缩小的情况下的
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, 0);

    if (data)
    {
        // 生成纹理
        if (use_RGBA)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    // 释放图像的内存
    stbi_image_free(data);

    return texture;
}
