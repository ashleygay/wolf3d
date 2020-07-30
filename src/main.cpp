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
    Point bottom_left = {-0.5f, -0.5f, 0.0f};
    Point bottom_right = {0.5f, -0.5f, 0.0f};
    Point up = {0.0f,0.5f, 0.0f};

    Shape<3> triangle_shape = {bottom_left, bottom_right, up};

    /* Shaders setup */
    //TODO: instead of directly passing the vertices, use and intermediate
    //templated object that takes care fo the funny stuff
    //(glVertexAttribPointer,...).
    std::vector<float> vertices = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,0.5f, 0.0f,
    };

    //TODO: automate the error handling on the compilation of the shaders and
    //on the linking with the shader program.
    Vertex_Shader<float> triangle = Vertex_Shader(vertices, Shaders::basic);
    int success = triangle.compile();
    if (!success)
    {
        std::cout << triangle.get_compile_error() << std::endl;
    }

    Fragment_Shader color = Fragment_Shader(Shaders::Fragments::orange);
    success = color.compile();
    if (!success)
    {
        std::cout << color.get_compile_error() << std::endl;
    }

    //TODO: Create before the shaders and use a {} scope to automatically
    //destroy the created shaders.
    Program_Shader p;
    p.attach_shader(triangle);
    p.attach_shader(color);
    success = p.link();
    if (!success)
    {
        std::cout << p.get_link_error() << std::endl;
    }

    //TODO: Do the following automatically in the shader destructor.
    p.detach_shader(triangle);
    p.detach_shader(color);

    //TODO: Figure out a better way to do that.
    //Create another method than attach_shader() ?
    p.set_VAO(triangle);

    /* Main loop */
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        /* Backgroung color */
        glClearColor(0.2f, current_color, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Draw an orange triangle. */
        //TODO: Okay for now ?
        p.use();
        p.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    std::cout << "Goodbye" << std::endl;
}
