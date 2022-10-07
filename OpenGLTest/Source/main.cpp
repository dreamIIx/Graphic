#include <iostream>
#include <thread>

#include "err_def.hpp"
#include "shader.hpp"
#include "buf.hpp"
#include "tx.hpp"
#include "va.hpp"
#include "model.hpp"
#include "window.hpp"
#include "fly_like_camera.hpp"

//#define GLFW_INCLUDE_VULKAN
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define MAIN_INLINE         inline
#define MAIN_CONSTEXPR      constexpr

MAIN_INLINE MAIN_CONSTEXPR int win_width = 1640;
MAIN_INLINE MAIN_CONSTEXPR int win_height = 980;

void processInput(dx::Window& window, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp, float deltaTime);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

dx::FlyLikeCamera camera;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    dx::Window window(win_width, win_height, "OpenGLTest");

    ER_IFN(gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)),
        ::std::cerr << "[ERR] Failed to initialize GLAD" << ::std::endl;,
            return -1;)

    //window.switchFullcreen();
    glViewport(0, 0, win_width, win_height);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);

    static MAIN_CONSTEXPR GLfloat vertices[] = {
        -1.f, -1.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, -1.f,
        1.f, -1.f, -1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, -1.f,
        -1.f, 1.f, -1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f, -1.f,
        1.f, 1.f, -1.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, -1.f,

        -1.f, -1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f,
        1.f, -1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f,
        -1.f, 1.f, 1.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f,
        1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0.f, 0.f, 1.f,

        -1.f, -1.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, -1.f, 0.f, 0.f,
        -1.f, 1.f, -1.f, 0.f, 0.f, 1.f, 1.f, 0.f, -1.f, 0.f, 0.f,
        -1.f, -1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, -1.f, 0.f, 0.f,
        -1.f, 1.f, 1.f, 0.f, 1.f, 0.f, 1.f, 1.f, -1.f, 0.f, 0.f,

        1.f, -1.f, -1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f,
        1.f, 1.f, -1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f,
        1.f, -1.f, 1.f, 0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f,
        1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 0.f, 0.f,

        -1.f, -1.f, -1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f, -1.f, 0.f,
        1.f, -1.f, -1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, -1.f, 0.f,
        -1.f, -1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, -1.f, 0.f,
        1.f, -1.f, 1.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f, -1.f, 0.f,

        -1.f, 1.f, -1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f,
        1.f, 1.f, -1.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f,
        -1.f, 1.f, 1.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 1.f, 0.f,
        1.f, 1.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 0.f, 1.f, 0.f,
    };

    static MAIN_CONSTEXPR GLuint indices[] = {
        0, 1, 2,
        1, 2, 3,
        4, 5, 6,
        5, 6, 7,
        8, 9, 10,
        9, 10, 11,
        12, 13, 14,
        13, 14, 15,
        16, 17, 18,
        17, 18, 19,
        20, 21, 22,
        21, 22, 23
    };

    glm::vec3 cubePositions[] = {
        glm::vec3( 0.f, -1.f, 0.f),
        glm::vec3( 2.f, 5.f, -15.f),
        glm::vec3(-7.5f, -2.2f, 8.5f),
        glm::vec3(-3.8f, -6.f, -12.3f),
        glm::vec3( 2.4f, 5.4f, -3.5f),
        glm::vec3(-1.7f, 3.f, -7.5f),
        glm::vec3( 1.3f, -7.f, -2.5f),
        glm::vec3( 1.5f, 2.f, -2.5f),
        glm::vec3( 1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.f, 3.5f),
        glm::vec3(-7.f, 0.f, -3.f)
    };

    auto tx_init_misc = []()
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        };

    dx::Shader test_shader(::std::string("./shaders/test1.vs"), ::std::string("./shaders/test1.fs"));
    dx::Shader test_lightingShader(::std::string("./shaders/lighting.vs"), ::std::string("./shaders/lighting.fs"));
    dx::VertexArray VAO;
    dx::VertexArray lightVAO;
    dx::Buffer VBO(&vertices, sizeof vertices, GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    dx::Buffer EBO(&indices, sizeof indices, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

    VAO.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), reinterpret_cast<void*>(0));
    //glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    //glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), reinterpret_cast<void*>(6 * sizeof(GLfloat)));
    //glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), reinterpret_cast<void*>(8 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    lightVAO.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), reinterpret_cast<void*>(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), reinterpret_cast<void*>(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(GLfloat), reinterpret_cast<void*>(8 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);

    dx::Texture texture1(GL_TEXTURE_2D);
    texture1.loadImage("./txs/sbs_txs_pack/128x128/Tile/Tile 19 - 128x128.png", GL_TEXTURE_2D, tx_init_misc);
    dx::Texture texture2(GL_TEXTURE_2D);
    texture2.loadImage("./txs/sbs_txs_pack/128x128/Tile/Tile 19 - 128x128 - specular.png", GL_TEXTURE_2D, tx_init_misc);

    glm::mat4 model(1.f);
    glm::mat4 view(1.f);
    glm::mat4 projection;
    model = glm::rotate(model, glm::radians(-60.f), glm::vec3(1.f, 0.f, 0.f)) * glm::rotate(model, glm::radians(65.f), glm::vec3(0.f, 0.f, 1.f));
    projection = glm::perspective(glm::radians(45.f), static_cast<float>(win_width) / win_height, 0.1f, 100.f);

    test_shader.use();
    //test_shader.setInt("texture1", 0);
    //test_shader.setInt("texture2", 1);
    glUniformMatrix4fv(glGetUniformLocation(test_shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(test_shader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
    glUniform3f(glGetUniformLocation(test_shader, "viewPos"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
    glUniform1f(glGetUniformLocation(test_shader, "material.shininess"), 32.f);
    //glUniform3f(glGetUniformLocation(test_shader, "material.ambient"), 0.5f, 0.5f, 0.5f);
    //glUniform3f(glGetUniformLocation(test_shader, "material.diffuse"), 1.f, 0.5f, 0.31f);
    //glUniform3f(glGetUniformLocation(test_shader, "material.specular"), 0.7f, 0.7f, 0.7f);
    glUniform4f(glGetUniformLocation(test_shader, "light.position"), cubePositions[10].x, cubePositions[10].y, cubePositions[10].z, 1.f);
    glUniform3f(glGetUniformLocation(test_shader, "light.direction"), camera.cameraFront.x, camera.cameraFront.y, camera.cameraFront.z);
    glUniform3f(glGetUniformLocation(test_shader, "light.diffuse"), 0.5f, 0.5f, 0.5f);
    glUniform3f(glGetUniformLocation(test_shader, "light.ambient"), 0.1f, 0.1f, 0.1f);
    glUniform3f(glGetUniformLocation(test_shader, "light.specular"), 1.f, 1.f, 1.f);
    test_shader.setFloat("light.constant", 0.001f);
    test_shader.setFloat("light.linear", 0.09f);
    test_shader.setFloat("light.quadratic", 0.0032f);
    test_shader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
    test_shader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));

    test_lightingShader.use();
    glUniformMatrix4fv(glGetUniformLocation(test_lightingShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(test_lightingShader, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    float deltaTime = 0.f;
    float lastFrame = 0.f;
        
    dx::Model mdlBackpack("./txs/backpack", "./models/backpack/backpack.obj");
    
    glEnable(GL_DEPTH_TEST);
    while(!window.is_closed())
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window, camera.cameraPos, camera.cameraFront, camera.cameraUp, deltaTime);
        view = glm::lookAt(camera.cameraPos, camera.cameraPos + camera.cameraFront, camera.cameraUp);

        glClearColor(0.1, 0.1, 0.1, 1.);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        GLfloat timeValue = glfwGetTime();
        GLfloat redValue = ::std::abs(::std::sin(timeValue + M_PI_2 + M_PI_4) * ::std::sin(timeValue + M_PI_2 + M_PI_4));
        GLfloat grValue = ::std::abs(::std::sin(timeValue + M_PI_2) * ::std::sin(timeValue + M_PI_2));
        GLfloat blValue = ::std::abs(::std::sin(timeValue + M_PI_4) * ::std::sin(timeValue + M_PI_4));
        model = glm::rotate(model, static_cast<float>(glfwGetTime()) * glm::radians(50.f), glm::vec3(0.5f, 1.f, 0.f));

        test_shader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.f, -10.f, 0.f));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        glUniformMatrix4fv(glGetUniformLocation(test_shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniform3f(glGetUniformLocation(test_shader, "uniColor"), redValue, grValue, blValue);
        glUniformMatrix4fv(glGetUniformLocation(test_shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniform3f(glGetUniformLocation(test_shader, "viewPos"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
        glUniform4f(glGetUniformLocation(test_shader, "light.position"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z, 1.f);
        glUniform3f(glGetUniformLocation(test_shader, "light.direction"), camera.cameraFront.x, camera.cameraFront.y, camera.cameraFront.z);
        mdlBackpack.draw(test_shader);

        test_shader.use();
        dx::Texture::activate(GL_TEXTURE0);
        test_shader.setInt("material.diffuse", 0);
        texture1.bind(GL_TEXTURE_2D);
        dx::Texture::activate(GL_TEXTURE1);
        test_shader.setInt("material.specular", 1);
        texture2.bind(GL_TEXTURE_2D);
        glUniform3f(glGetUniformLocation(test_shader, "uniColor"), redValue, grValue, blValue);
        glUniformMatrix4fv(glGetUniformLocation(test_shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniform3f(glGetUniformLocation(test_shader, "viewPos"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z);
        glUniform4f(glGetUniformLocation(test_shader, "light.position"), camera.cameraPos.x, camera.cameraPos.y, camera.cameraPos.z, 1.f);
        glUniform3f(glGetUniformLocation(test_shader, "light.direction"), camera.cameraFront.x, camera.cameraFront.y, camera.cameraFront.z);
/*
        float radius = 10.f;
        float camX = sin(glfwGetTime() * 2) * radius - 5.f;
        float camZ = cos(glfwGetTime()) * radius;
        view = glm::lookAt(glm::vec3(camX, 0.f, camZ), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
        glUniformMatrix4fv(glGetUniformLocation(test_shader, "view"), 1, GL_FALSE, glm::value_ptr(view));
*/
        VAO.bind();
        EBO.bind(GL_ELEMENT_ARRAY_BUFFER);
        for(unsigned i {0}; i < 10u; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(-1.0f, 1.f, -0.5f));
            glUniformMatrix4fv(glGetUniformLocation(test_shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray(0);
        dx::Texture::activate(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        lightVAO.bind();
        EBO.bind(GL_ELEMENT_ARRAY_BUFFER);
        test_lightingShader.use();
        glUniformMatrix4fv(glGetUniformLocation(test_lightingShader, "view"), 1, GL_FALSE, glm::value_ptr(view));
        model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[10]);
        //model = glm::rotate(model, glm::radians(45.f), glm::vec3(1.0f, 1.f, 1.f));
        glUniformMatrix4fv(glGetUniformLocation(test_lightingShader, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        dx::Texture::activate(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        //VAO.bind();
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    static bool firstMouse = true;
    static float lastX = static_cast<float>(win_width) / 2.f;
    static float lastY = static_cast<float>(win_height) / 2.f;
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.062f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    camera.yaw += xoffset;
    camera.pitch += yoffset;

    if(camera.pitch > 89.f)
    {
        camera.pitch = 89.f;
    }
    if(camera.pitch < -89.f)
    {
        camera.pitch = -89.f;
    }

    camera.direction.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    camera.direction.y = sin(glm::radians(camera.pitch));
    camera.direction.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
    camera.cameraFront = glm::normalize(camera.direction);
}

void processInput(dx::Window& window, glm::vec3& cameraPos, glm::vec3& cameraFront, glm::vec3& cameraUp, float deltaTime)
{
    float cameraSpeed = 6.f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        //window.switch2Fullcreen();
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        cameraPos += cameraSpeed * cameraUp;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        cameraPos -= cameraSpeed * cameraUp;
    }
}