#include <iostream>
#include <cmath>
#include <stdio.h>
#include "../include/shader.h"
#include "../include/glad.h"
#include <GLFW/glfw3.h>

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"out vec3 bPos;\n"
"void main() {\n"
"    bPos = aPos;\n"
"    gl_Position = vec4(aPos, 1.0);\n"
"    ourColor = aColor;\n"
"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"in vec3 ourColor;\n"
"in vec3 bPos;\n"
"out vec4 FragColor;\n"
"void main() {\n"
"    FragColor = vec4(ourColor, 1.0f);\n"
"}\0";


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main(){

    //////////////////////////////////////////////////////////////////////////////
    //              GLFW Window Instantiation
    //////////////////////////////////////////////////////////////////////////////

    if(!glfwInit()){
        std::cout << "Problem?" << std::endl;
        return -1;
    } //initilized glfw with the glfw version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //first option is what we need to configure
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //second option sets value of option
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //second option sets value of option

    //Creating the window opject with some error checking.
    //(Width, Height, Name of window, ignore the last two)
    GLFWwindow* window = glfwCreateWindow(800, 600, "Learning", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create the window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //Make context of our window the main context on the current thread?
    glfwMakeContextCurrent(window);

    if (window == NULL){
        std::cout << "Failed to open GLFW window" << std::endl;
        return -1;
    }

    //initilize glad
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initilize GLAD" << std::endl;
        return -1;
    }

    //Tells openGL the size of the rendering window.
    //(first two are location of lower corner, last two are width and height)
    glViewport(0, 0, 1400, 1050);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Shader Shader("../shaders/vertexShader.cpp", "../shaders/fragmentShader.cpp");


/*
    //////////////////////////////////////////////////////////////////////////////
    //             Creating and Linking Shaders
    //////////////////////////////////////////////////////////////////////////////

    int success;
    char infoLog[512];

    //Creating the Shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);;
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);;
    unsigned int shaderProgram = glCreateProgram();


    //Copy Shader source and Compile
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);


    //error checking!
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FALIURE::VERTEX\n" << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FALIURE::FRAGMENT\n" << infoLog << std::endl;
    }


    //Attach and link the compiled shaders to the Program, then delete for housekeeping
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram); 
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    //error checking!
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FALIURE\n" << infoLog << std::endl;
    }
*/

    //////////////////////////////////////////////////////////////////////////////
    //                  Creating/Configuring VAOs, VBOs
    //////////////////////////////////////////////////////////////////////////////


    float vertices[] {
        //positions         //Colors
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   //bottom left
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,    //left
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f     //bottom
    };


    //Generating VAOs and VBOs, then binding 
    unsigned int VAO, VBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);


    //Binding, copying buffer data, and setting attribute settings.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);   

    
    // unsigned int EBO;
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    while(!glfwWindowShouldClose(window)){
        processInput(window);

        Shader.use();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glUseProgram(shaderProgram);

        // float timeValue = glfwGetTime();
        // float colorChangerValue = (sin(timeValue) / 2.0f) + 0.5f;
        // int vertexColorLocation = glGetUniformLocation(shaderProgram, "colorChanger");
        // glUniform1f(vertexColorLocation, colorChangerValue);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);


        





        //swaps the buffer that contains all color data for each pixel on the screen
        glfwSwapBuffers(window);
        //checks if events are triggered (keyboard, window resizing)
        glfwPollEvents();
        

    }

    std::cout << glGetError() << std::endl;


    //cleanup
    glfwTerminate();
    return 0;
}

//callback to change openGL's viewport when the window size is changed
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);    
}

//fuction to handle all future human input
void processInput(GLFWwindow *window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
    else if((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)){

        GLint polygonMode[2];
        glGetIntegerv(GL_POLYGON_MODE, &(polygonMode[0]));

        if(polygonMode[0] == GL_FILL){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    }
}