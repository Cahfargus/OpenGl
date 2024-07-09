#include <iostream>
#include <cmath>
#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb_image.h"
#include "../include/shader.h"
#include "../include/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

    Shader Shader("../shaders/vertexShader.vs", "../shaders/fragmentShader.fs");


    //////////////////////////////////////////////////////////////////////////////
    //                  Creating/Configuring VAOs, VBOs
    //////////////////////////////////////////////////////////////////////////////


    float vertices[] = {
        //positions           //Colors            //Nick Tex    //Flag Tex
        -0.5f,  0.5f, 0.0f,   0.3f, 0.0f, 0.5f,   0.0f, 1.0f,   0.0f, 1.0f,    //top-left
         0.5f,  0.5f, 0.0f,   0.2f, 0.0f, 0.1f,   1.0f, 1.0f,   1.0f, 1.0,    //top-right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.5f, 0.0f,   0.0f, 0.4f,   0.0f, 0.0f,    //bottom-left
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.4f,   1.0f, 0.4f,   1.0f, 0.0f    //bottom-right
    };

    unsigned int indices[] = {
        1, 3, 0, //first triangle
        3, 2, 0  //second triangle
    };

    //Generating VAOs and VBOs, then binding 
    unsigned int VAO, VBO, EBO;   
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);


    //Binding, copying buffer data, and setting attribute settings. 0.2f, 0.2f,    //bottom-left
         0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 0.4f,   0.7f, 0.5f,
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 10 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);
   

    


    //////////////////////////////////////////////////////////////////////////////
    //                  Textures
    //////////////////////////////////////////////////////////////////////////////

    //create texture
    unsigned int texture, flag;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //setting how the textures should wrap and scale
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //MIPMAPS only for min
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //import image as readable data
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../textures/nick.jpg", &width, &height, &nrChannels, 0);
    //Generate texture from image and mipmap creating, then delete the original picture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);


    glGenTextures(1, &flag);
    glBindTexture(GL_TEXTURE_2D, flag);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //MIPMAPS only for min
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    data = stbi_load("../textures/beaver.jpg", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);    

    Shader.use();
    glUniform1i(glGetUniformLocation(Shader.ID, "fnick"), 0);
    Shader.setInt("fflag", 1);


    



    while(!glfwWindowShouldClose(window)){
        processInput(window);


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);


        float timeValue = glfwGetTime();
        float colorChangerValue = ((sin(timeValue) / 2.0f) + 0.7f)/ 1.25f;
        Shader.setFloat("textureChanger", colorChangerValue);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(0.5, -0.5, 0.0f));
        trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));

        

        unsigned int transformLoc = glGetUniformLocation(Shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, flag);

        Shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        trans = glm::mat4(1.0f);
        trans = glm::translate(trans, glm::vec3(-0.5, 0.5, 0.0f));
        trans = glm::scale(trans, glm::vec3(colorChangerValue, colorChangerValue, colorChangerValue));

        

        transformLoc = glGetUniformLocation(Shader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
    if((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)){

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