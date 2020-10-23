/* C++ includes */
#include <iostream>
#include <cassert>

#include <fmt/core.h>

/* OpenGL includes */

/*
 * By default, glfw only exposes a couple of old OpenGl functions (for windows
 * compatibility). We set that macro to enable all that we need.
 */
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

//#include <GL/gl.h>
//#include <GL/glext.h>


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

    if(glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
        current_color += 0.01f;

    if(glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
        current_color -= 0.01f;
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

    // Pyramid like triangle
    /* Shaders setup */
//    std::vector<double> vertices_triangle_right = 
//    {
//        0.5, 0.5, 0.0, // top right
//        0.5, -0.45, 0.0, // bottom right right
//        -0.45, 0.5, 0.0, // top left right
//    };

    Vertex<float> avertices_triangle_right[] =
    {
        {0.5, 0.5, 0.0}, // top right
        {0.5, -0.45, 0.0}, // bottom right right
        {-0.45, 0.5, 0.0} // top left right
     };

//    std::vector<double> vertices_triangle_left = 
//    {
//        0.45, -0.5, 0.0, // bottom right left
//        -0.5, -0.5, 0.0,// bottom left
//        -0.5, 0.45, 0.0, // top left left
//    };

    Vertex<float> avertices_triangle_left[] = 
    {
         { 0.45, -0.5, 0.0}, // bottom right left
         { -0.5, -0.5, 0.0},// bottom left
         { -0.5, 0.45, 0.0}, // top left left
     };

    Program_Shader p1;
    Program_Shader p2;
    {
    
        Vertex_Shader right = Vertex_Shader(Shaders::basic, avertices_triangle_right);
        right.compile();

        Vertex_Shader left = Vertex_Shader(Shaders::basic, avertices_triangle_left);
        left.compile();

        // TODO: Filter points with a lambda ?
        Fragment_Shader color_orange = Fragment_Shader(Shaders::Fragments::orange);
        color_orange.compile();

        Fragment_Shader color_blue = Fragment_Shader(Shaders::Fragments::blue);
        color_blue.compile();

        p1.link(left, color_blue);
        p2.link(right, color_orange);

    }
    //TODO: change line smothness and width (GL_LINE_WIDTH and GL_LINE_SMOOTH)
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* Main loop */
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        /* Backgroung color */
        glClearColor(0.2f, current_color, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        p1.use();
        p1.draw();

        p2.use();
        p2.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    std::cout << "Goodbye" << std::endl;
}
