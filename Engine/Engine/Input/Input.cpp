#include "Input.h"
#include "../Editor/src/GlobalVars.h"

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool mouse = true;


float deltaTime = 0.0f;
float lastFrame = 0.0f;
float fov = 45.0f;

// 5° (about 0.087 radians).



void processPlayerMovement(GLFWwindow* window, CubeModel* playerCube, float deltaTime) {
    if (!playerCube) return;
    float speed = 1.0f * deltaTime;
    float tiltSpeed = glm::radians(40.0f) * deltaTime;
    float turnSpeed = glm::radians(240.0f) * deltaTime;
    float pitchSpeed = glm::radians(40.0f) * deltaTime;

    constexpr float maxTilt = glm::radians(30.0f);
    constexpr float maxTurn = glm::radians(30.0f);
    constexpr float maxPitch = glm::radians(20.0f);

    // Key states
    bool upPressed = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
    bool rightPressed = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
    bool leftPressed = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
    bool flyUpPressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    bool flyDownPressed = glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;

    // --- ROLL AND YAW (TILT AND TURN) ---
    if (upPressed && rightPressed) {
        playerCube->rotation.z = glm::max(playerCube->rotation.z - tiltSpeed, -maxTilt);
        playerCube->rotation.y = glm::max(playerCube->rotation.y - turnSpeed, -maxTurn);
    }
    else if (upPressed && leftPressed) {
        playerCube->rotation.z = glm::min(playerCube->rotation.z + tiltSpeed, maxTilt);
        playerCube->rotation.y = glm::min(playerCube->rotation.y + turnSpeed, maxTurn);
    }
    // --- PITCH (NOSE UP/DOWN) ---
    else if (upPressed && flyUpPressed) {
        playerCube->rotation.x = glm::max(playerCube->rotation.x + pitchSpeed, maxPitch);
    }
    else if (upPressed && flyDownPressed) {
        playerCube->rotation.x = glm::min(playerCube->rotation.x - pitchSpeed, -maxPitch);
    }
    // --- RETURN TO NEUTRAL ---
    else {
        if (playerCube->rotation.z > 0.0f)
            playerCube->rotation.z = glm::max(playerCube->rotation.z - tiltSpeed, 0.0f);
        else if (playerCube->rotation.z < 0.0f)
            playerCube->rotation.z = glm::min(playerCube->rotation.z + tiltSpeed, 0.0f);

        if (playerCube->rotation.y > 0.0f)
            playerCube->rotation.y = glm::max(playerCube->rotation.y - turnSpeed, 0.0f);
        else if (playerCube->rotation.y < 0.0f)
            playerCube->rotation.y = glm::min(playerCube->rotation.y + turnSpeed, 0.0f);

        if (playerCube->rotation.x > 0.0f)
            playerCube->rotation.x = glm::max(playerCube->rotation.x - pitchSpeed, 0.0f);
        else if (playerCube->rotation.x < 0.0f)
            playerCube->rotation.x = glm::min(playerCube->rotation.x + pitchSpeed, 0.0f);
    }

    // --- BANK TURNING LOGIC ---
    float bankFactor = playerCube->rotation.z / maxTilt; // -1 to +1
    float currentYawRate = tiltSpeed * bankFactor;
    playerCube->rotation.y += currentYawRate * deltaTime;

    // --- SHIP LOCAL AXES ---
    glm::mat4 rotMatrix = glm::mat4(1.0f);
    rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.y, glm::vec3(0, 1, 0));
    rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.x, glm::vec3(1, 0, 0));
    rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.z, glm::vec3(0, 0, 1));

    glm::vec3 shipForward = glm::vec3(rotMatrix * glm::vec4(0, 0, -1, 0));
    glm::vec3 shipUp = glm::vec3(rotMatrix * glm::vec4(0, 1, 0, 0));
    glm::vec3 shipRight = glm::vec3(rotMatrix * glm::vec4(1, 0, 0, 0));

    // --- MOVE USING SHIP'S ORIENTATION ---
    if (upPressed)
        playerCube->position += shipForward * speed;
    /*if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        playerCube->position -= shipForward * speed;*/
    if (leftPressed)
        playerCube->position -= shipRight * speed;
    if (rightPressed)
        playerCube->position += shipRight * speed;
    if (flyUpPressed)
        playerCube->position += shipUp * speed;
    if (flyDownPressed)
        playerCube->position -= shipUp * speed;

    // Update model matrix
    playerCube->modelMatrix = glm::translate(glm::mat4(1.0f), playerCube->position);
    playerCube->modelMatrix = glm::rotate(playerCube->modelMatrix, playerCube->rotation.y, glm::vec3(0, 1, 0));
    playerCube->modelMatrix = glm::rotate(playerCube->modelMatrix, playerCube->rotation.x, glm::vec3(1, 0, 0));
    playerCube->modelMatrix = glm::rotate(playerCube->modelMatrix, playerCube->rotation.z, glm::vec3(0, 0, 1));
    playerCube->modelMatrix = glm::scale(playerCube->modelMatrix, playerCube->scale);
}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    // change window Opacity 
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        glfwSetWindowOpacity(window, 0.5f);

    // change window Opacity back to normal
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        glfwSetWindowOpacity(window, 1.0f);
}

// Mouse callback (for Editor camera, not player)
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (mouse == true) {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        std::cout << "lastX: " << lastX << ", lastY: " << lastY << ", firstMouse: " << firstMouse << std::endl;

        lastX = xpos;
        lastY = ypos;

        // Camera rotation for editor (not for player movement)
        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
            camera.ProcessMouseMovement(xoffset, yoffset);
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

//Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//bool mouse = true;
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//float fov = 45.0f;
//float mouseSensitivity = 0.1f; // Adjust as needed
//
//void processPlayerMovement(GLFWwindow* window, CubeModel* playerCube, float deltaTime) {
//    if (!playerCube) return;
//    float speed = 5.0f * deltaTime;
//    float rotSpeed = 1.5f * deltaTime;
//
//    // Mouse movement for yaw/pitch
//    double mouseX, mouseY;
//    glfwGetCursorPos(window, &mouseX, &mouseY);
//    float xoffset = mouseX - lastX;
//    float yoffset = mouseY - lastY;
//    lastX = mouseX;
//    lastY = mouseY;
//    playerCube->rotation.y += xoffset * mouseSensitivity; // Yaw
//    playerCube->rotation.x += yoffset * mouseSensitivity; // Pitch
//
//    // Bank with A/D
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        playerCube->rotation.z += rotSpeed; // Bank left
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        playerCube->rotation.z -= rotSpeed; // Bank right
//
//    // Forward/backward
//    glm::mat4 rotMatrix = glm::mat4(1.0f);
//    // Yaw (Y axis)
//    rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.y, glm::vec3(0, 1, 0));
//    // Pitch (X axis)
//    rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.x, glm::vec3(1, 0, 0));
//    // Roll (Z axis)
//    rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.z, glm::vec3(0, 0, 1));
//
//    glm::vec3 forward = glm::vec3(rotMatrix * glm::vec4(0, 0, -1, 0));
//    glm::vec3 up = glm::vec3(rotMatrix * glm::vec4(0, 1, 0, 0));
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        playerCube->position += forward * speed;
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        playerCube->position -= forward * speed;
//    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
//        playerCube->position += up * speed;
//    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
//        playerCube->position -= up * speed;
//
//    // Update model matrix
//    playerCube->modelMatrix = glm::translate(glm::mat4(1.0f), playerCube->position);
//
//    // Yaw (Y axis)
//    rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.y, glm::vec3(0, 1, 0));
//    // Pitch (X axis)
//    rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.x, glm::vec3(1, 0, 0));
//    // Roll (Z axis)
//    rotMatrix = glm::rotate(rotMatrix, playerCube->rotation.z, glm::vec3(0, 0, 1));
//    
//    playerCube->modelMatrix = glm::scale(playerCube->modelMatrix, playerCube->scale);
//}
//
//void processInput(GLFWwindow* window) // this changed
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    // change widows Opacity 
//    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
//        glfwSetWindowOpacity(window, 0.5f);
//
//    // change widows Opacity back to normat
//    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
//        glfwSetWindowOpacity(window, 1.0f);
//
//}
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//
//    if (mouse == true) {
//
//        float xpos = static_cast<float>(xposIn);
//        float ypos = static_cast<float>(yposIn);
//
//        if (firstMouse)
//        {
//            lastX = xpos;
//            lastY = ypos;
//            firstMouse = false;
//        }
//
//        float xoffset = xpos - lastX;
//        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//        lastX = xpos;
//        lastY = ypos;
//
//        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_TRUE)
//            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//            camera.ProcessMouseMovement(xoffset, yoffset);
//    }
//}
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
//

//void processPlayerMovement(GLFWwindow* window, CubeModel* playerCube, float deltaTime) {
//    if (!playerCube) return;
//
//    float speed = 5.0f * deltaTime;
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        playerCube->position += glm::vec3(0.0f, 0.0f, -speed);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        playerCube->position += glm::vec3(0.0f, 0.0f, speed);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        playerCube->position += glm::vec3(-speed, 0.0f, 0.0f);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        playerCube->position += glm::vec3(speed, 0.0f, 0.0f);
//
//
//    // Update model matrix
//    playerCube->modelMatrix = glm::translate(glm::mat4(1.0f), playerCube->position);
//    playerCube->modelMatrix = glm::scale(playerCube->modelMatrix, playerCube->scale);
//}



/*if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
   camera.ProcessKeyboard(FORWARD, deltaTime);
if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);*/
    // UP - Down
    /*if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, -deltaTime);
    }*/