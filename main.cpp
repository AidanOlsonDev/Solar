#include <glad/glad.h>  // This will now find 'include/glad/glad.h'
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void checkShaderStatus(unsigned int shaderIndex);
void checkProgramStatus(unsigned int programIndex);

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

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

    // Vertices to draw to Screen
    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.0f, 0.5f, 0.0f,
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    // Id for Buffer used for Vertex Data
    unsigned int VBO;
    // Generates Buffer and ID
    glGenBuffers(1, &VBO);
    // Binds the Buffer to the Graphics Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Copies the vertice data into the Buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ID For Vertex Shader
    unsigned int vertexShader;
    // Creates the shader and assings the ID to vertexShader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Specifies the source of the Shader
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    // Actually compiles the shader
    glCompileShader(vertexShader);

    checkShaderStatus(vertexShader);

    // ID for the Fragment Shader
    unsigned int fragmentShader;
    // Creates the actual shader and assings the ID to fragmentShader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Specifies the Source of the Shader
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    // Compiles the Shader
    glCompileShader(fragmentShader);

    checkShaderStatus(fragmentShader);

    // Program Id
    unsigned int shaderProgram;
    // Creates the Program and assigns the ID to shaderProgram
    shaderProgram = glCreateProgram();

    // Attaches both shaders to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    // Links the shaders in the program together.
    glLinkProgram(shaderProgram);

    checkProgramStatus(shaderProgram);

    // Tells OpenGL to use our shaderProgram

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

   

    // Rendering Loop
    while(!glfwWindowShouldClose(window)) {
        // Processes Input Through GLFW
        processInput(window);

        // Rendering Commands
        
        // Sets the Color Buffer to A tealish color
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Clears the Screen with the Color Buffer
        glClear(GL_COLOR_BUFFER_BIT);

         glUseProgram(shaderProgram);
         glBindVertexArray(VAO);
         glDrawArrays(GL_TRIANGLES, 0 , 3);


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

// Checks the Status of the shader compilation
void checkShaderStatus(unsigned int shaderIndex) {
    int success;
    char infoLog[512];
    // Returns whether or not the compilation was successful and stores it in success
    glGetShaderiv(shaderIndex, GL_COMPILE_STATUS, &success);

    if (!success) {
        // Gets the Error Log and stores it in infoLog
        glGetShaderInfoLog(shaderIndex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}

void checkProgramStatus(unsigned int programIndex) {
    int success;
    char infoLog[512];

    glGetProgramiv(programIndex, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(programIndex, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM:::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}