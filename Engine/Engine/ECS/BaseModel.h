#pragma once
#include <string>
#include <glm\glm.hpp>

class BaseModel {
public:
    int index;              // list index
    std::string objectName; // objects name
    int objectIndex;        // objects index ie: cube index of type cube
    int objectTypeID;       // cube, light, camera, sphere, plane, obj model

    glm::vec3 position;     // Position of the object
    glm::vec3 scale;        // Scale of the object
    glm::vec3 rotation;     // rotation of the object
    glm::mat4 modelMatrix;  // Model matrix for transformations

	bool isSelected;        // this for the selection in the scene list box not sure it should be here or not

	unsigned int textureID; // not sure if this should be here or not, but it is needed for the cube model

    virtual ~BaseModel() = default;

};
