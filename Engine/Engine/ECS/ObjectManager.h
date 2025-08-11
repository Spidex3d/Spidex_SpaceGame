#pragma once
#include <glad/glad.h>
#include <vector>
#include <string>
#include "BaseModel.h"
#include "../../../Editor/src/GlobalVars.h" // For MAIN_GRID constant

class MainGrid : public BaseModel {

public:
    GLuint GridVAO, GridVBO;
    std::vector<float> gridVertices;

    MainGrid(int idx, const std::string& name, float size, int divisions) {
        index = idx;             // list index
        objectName = name;       // grid name
        objectIndex = idx;       // grid index
        objectTypeID = MAIN_GRID;        // Example type ID for Grid = 0

        gridVertices = createGridVertices(size, divisions);
        SetUp();
    }

    std::vector<float> createGridVertices(float size, int divisions) {
        std::vector<float> vertices;
        float step = size / divisions;
        float halfSize = size / 2.0f;

        for (int i = 0; i <= divisions; ++i) {
            float coord = -halfSize + i * step;
            // Vertical lines
            vertices.push_back(coord);
            vertices.push_back(0.0f);
            vertices.push_back(-halfSize);
            vertices.push_back(coord);
            vertices.push_back(0.0f);
            vertices.push_back(halfSize);
            // Horizontal lines
            vertices.push_back(-halfSize);
            vertices.push_back(0.0f);
            vertices.push_back(coord);
            vertices.push_back(halfSize);
            vertices.push_back(0.0f);
            vertices.push_back(coord);
        }
        return vertices;
    }

    void SetUp() {
        glGenVertexArrays(1, &GridVAO);
        glGenBuffers(1, &GridVBO);

        glBindVertexArray(GridVAO);
        glBindBuffer(GL_ARRAY_BUFFER, GridVBO);
        glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    //void DrawGrid() const override {
    void DrawGrid() {
        glBindVertexArray(GridVAO);
        glDrawArrays(GL_LINES, 0, gridVertices.size() / 3);
        glBindVertexArray(0);
    }

};

class CubeModel : public BaseModel {
public:
    GLuint VAO, VBO;

    CubeModel(int idx, const std::string& name, int playerIdx) {
        index = idx;             // list index
        objectName = name;       // cube name
        objectIndex = playerIdx;         // start index for a cube
        objectTypeID = OBJ_CUBE; // Example type ID for Cube set in config = 1



        position = glm::vec3(0.0f, 0.0f, 0.0f); // Initial position
        scale = glm::vec3(1.0f, 1.0f, 1.0f);    // Initial scale
        modelMatrix = glm::mat4(1.0f);


        GLfloat vertices[] = { //  Normal         Tex cords
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,

       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f,

       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
       -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
       -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,0.0f, 0.0f,
       -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,0.0f, 1.0f

        };

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);
        // vertices
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Texture location 1
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)3);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Normal attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
        glEnableVertexAttribArray(0);
    }

    ~CubeModel() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }

    void DrawCube() {

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
private:
};

class SphereModel : public BaseModel {
public:

    GLuint VAO, VBO, EBO;
    GLsizei elementCount;
    SphereModel(int idx, const std::string& name, int Sphereobjidx) {

        index = idx;
        objectName = name;
        objectIndex = Sphereobjidx;
        objectTypeID = OBJ_SPHERE;

        position = glm::vec3(0.0f);
        scale = glm::vec3(1.0f);
        modelMatrix = glm::mat4(1.0f);

        const unsigned int X_SEGMENTS = 32;
        const unsigned int Y_SEGMENTS = 32;
        std::vector<float> data;
        std::vector<unsigned int> indices;

        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y) {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x) {
                float xSegment = (float)x / X_SEGMENTS;
                float ySegment = (float)y / Y_SEGMENTS;
                float xPos = std::cos(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);
                float yPos = std::cos(ySegment * M_PI);
                float zPos = std::sin(xSegment * 2.0f * M_PI) * std::sin(ySegment * M_PI);

                data.push_back(xPos);
                data.push_back(yPos);
                data.push_back(zPos);

                data.push_back(xPos); // Normal
                data.push_back(yPos);
                data.push_back(zPos);

                data.push_back(xSegment); // Texture coords
                data.push_back(ySegment);
            }
        }

        for (unsigned int y = 0; y < Y_SEGMENTS; ++y) {
            for (unsigned int x = 0; x < X_SEGMENTS; ++x) {
                unsigned int i1 = y * (X_SEGMENTS + 1) + x;
                unsigned int i2 = (y + 1) * (X_SEGMENTS + 1) + x;

                indices.push_back(i1);
                indices.push_back(i2);
                indices.push_back(i1 + 1);

                indices.push_back(i1 + 1);
                indices.push_back(i2);
                indices.push_back(i2 + 1);
            }
        }

        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        elementCount = static_cast<GLsizei>(indices.size());

    }
    void DrawSphere() {
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    ~SphereModel() {
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
};
