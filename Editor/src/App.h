#pragma once
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../Engine/Engine/Render/RenderDraw.h"
#include "GUI/MainScreen.h"

class App
{
public:
    App();
    ~App();

    static App* Instance();

    void Initialize(GLFWwindow* window);

    void RunApp();

    void MainCamera();
    glm::mat4 GetViewMatrix();
    glm::mat4 GetProjectionMatrix(float aspectRatio);

   // void Timer();

    void AppShutdown();

private:
    GLFWwindow* window;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

};

