#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

int main(void)
{
    //初始化GLFW库 如果失败 则直接退出程序
    if (!glfwInit())
    {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //设置 OpenGL 的主版本号为 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //设置 OpenGL 的次版本号为 3
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //请求 核心模式 核心模式移除了已废弃的旧功能（如固定管线、立即模式等），强制使用现代 OpenGL 编程方式（着色器、VBO 等）

    GLFWwindow* window =  glfwCreateWindow(1280, 720, "GameEngine", nullptr, nullptr); //创建窗口 高1280 宽720 命名为"GameEngine" 不设置为全屏模式 且 不共享资源
    
    //创建窗口失败 则输出错误信息 并 退出程序
    if (window == nullptr)
    {
        std::cout << "Error Create Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window, 500, 200); //设置窗口位置
    glfwMakeContextCurrent(window); //把 window 对应的 OpenGL 上下文设为当前线程的当前上下文。相当于告诉程序 "接下来这个线程里的 OpenGL 命令，都作用在这个窗口上。"

    //初始化 GLEW 库，加载当前 OpenGL 环境支持的函数指针
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        return -1;
    }

    //第一个三角形的顶点数据结构
    std::vector<float> vertices =
    {
        0.0f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    //进入主循环 glfwWindowShouldClose 用于接收关闭请求
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f); //设置清屏颜色 本身还没有真正把屏幕变成相应颜色
        glClear(GL_COLOR_BUFFER_BIT); //用刚才设置的清屏颜色清空颜色缓冲区
        glfwSwapBuffers(window); //交换前后缓冲区，把刚绘制好的画面显示到窗口上
        
        glfwPollEvents(); //处理所有待处理的事件
    }

    //退出循环后 销毁所有窗口并释放 GLFW 分配的资源
    glfwTerminate();

    return 0;
}