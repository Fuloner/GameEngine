#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

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

    //使用 C++11 的原始字符串字面量 R"(...)" 来存储 GLSL 顶点着色器代码
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;

        void main()
        {
            gl_Position = vec4(position.x, position.y, position.z, 1.0);
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //glCreateShader 创建一个空的着色器对象，参数 GL_VERTEX_SHADER 表明这是一个顶点着色器，返回一个无符号整型标识符
    const char* vertexShaderCStr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr); //设置着色器源码
    glCompileShader(vertexShader); //编译着色器

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success); //glGetShaderiv 获取着色器参数，GL_COMPILE_STATUS 返回编译是否成功
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR:VERTEX_SHADER_COMPILATION_FAILED" << infoLog << std::endl;
    }

    std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderCStr = vertexShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderCStr, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR:FRAGMENT_SHADER_COMPILATION_FAILED" << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetShaderiv(shaderProgram, GL_LINK_STATUS, &success);
    if (&success)
    {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR:SHADER_PROGRAM_LINKING_FAILED" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

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