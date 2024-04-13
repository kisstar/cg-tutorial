#include <glad/glad.h>
#include "cube.cpp"

int createVAO()
{
    // 生成一个 VBO 对象
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    // 生成一个 VAO 对象
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // 绑定 VAO
    // 顶点数组对象可以像顶点缓冲对象那样被绑定，任何随后的顶点属性调用都会储存在这个 VAO 中
    // 通过 VAO，当配置顶点属性指针时，你只需要将那些调用执行一次，之后再绘制物体的时候只需要绑定相应的 VAO 即可
    glBindVertexArray(VAO);

    // 绑定缓冲类型（此处是顶点缓冲对象），把顶点数据复制到缓冲的内存中
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // 告诉 OpenGL 该如何解析顶点数据
    glVertexAttribPointer(0 /* 指定要配置的顶点属性 */,
                          3 /* 顶点属性的大小 */,
                          GL_FLOAT /* 数据的类型 */,
                          GL_FALSE /* 是否标准化 */,
                          5 * sizeof(float) /* 步长 */,
                          (void *)0 /* 位置数据在缓冲中起始位置的偏移量 */);
    // 启用顶点属性
    glEnableVertexAttribArray(0);

    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // 解除绑定的顶点缓冲区对象
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // 当 VAO 是活动的时，不解除对 EBO 的绑定

    // 解绑 VAO
    glBindVertexArray(0);

    return VAO;
}
