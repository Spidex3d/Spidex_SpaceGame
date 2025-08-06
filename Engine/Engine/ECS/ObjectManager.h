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
