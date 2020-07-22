/* C++ includes */
#include <iostream>
#include <cassert>

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

static double current_color = 0.3f;

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        current_color += 0.01f;

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        current_color -= 0.01f;
}

int main()
{
    std::cout << "Hello there" << std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Pyramid like triangle
    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,0.5f, 0.0f,
    };

    /* Shaders setup */
    auto triangle = Vertex_Shader(vertices, Shaders::basic);
    assert(triangle.compile());

    auto color = Fragment_Shader(Shaders::Fragments::yellow);
    assert(color.compile());

    Program_Shader p;
    p.attach_shader(triangle);
    p.attach_shader(color);
    assert(p.link());
    p.use();

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

    /* Main loop */
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);
        glClearColor(0.2f, current_color, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
        std::cout << "Color : " << current_color << std::endl;
    }

    glfwTerminate();
    std::cout << "Goodbye" << std::endl;
}
