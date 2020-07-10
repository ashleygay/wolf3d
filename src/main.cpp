/* C++ includes */
#include <iostream>

/* OpenGL includes */

/*
 * By default, glfw only exposes a couple of old OpenGl functions (for windows
 * compatibility). We set that macro to enable all that we need.
 */
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

/* Project includes */
#include <shader_manager.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

static double color = 0.3f;

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        color += 0.01f;

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        color -= 0.01f;
}

int main()
{

    Shader_Manager m;
    std::cout << "Hello there" << std::endl;
    std::cout << "Hello there" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Pyramid like triangle
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,0.5f, 0.0f,
    };

  // Generate a buffer and buffer ID.
    unsigned int VBO;
    glGenBuffers(1, &VBO);

  // Bind the newly created buffer to an array,.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // Copy the vertex data into the buffer memory.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


    // Initialize vertex shader

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, color, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
        std::cout << "Color : " << color << std::endl;
    }

    glfwTerminate();
    std::cout << "Goodbye" << std::endl;
}
