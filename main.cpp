#include <glad/glad.h>  // This will now find 'include/glad/glad.h'
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main() {

    // Initalizes GLFW and then tells it what specific version of OpenGL we are using
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Creates the Window Context
    GLFWwindow* window = glfwCreateWindow(800, 600, "Solar", NULL, NULL);

    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Makes Our Window the Current Context on the Main Thread
    glfwMakeContextCurrent(window);

    // Loads Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Makes Sure that Glad Viewport is the same size as our window
    glViewport(0,0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Rendering Loop
    while(!glfwWindowShouldClose(window)) {
        // Processes Input Through GLFW
        processInput(window);

        // Rendering Commands
        
        // Sets the Color Buffer to A tealish color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Clears the Screen with the Color Buffer
        glClear(GL_COLOR_BUFFER_BIT);


        // Swaps the 2D Buffer to Render to the Screen
        glfwSwapBuffers(window);
        // Checks for any events such as input
        glfwPollEvents();
    }


    // Cleans up all resources allocated by GLFW
    glfwTerminate();
    return 0;
}

// Resizes the Viewport anytime the Window Size Gets Changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0,0, width, height);
}
void processInput(GLFWwindow *window) {
    // If escape is pressed, close window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}