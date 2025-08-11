#include "EntityNode.h"
#include <imgui\ImGuiAF.h>
#include <imgui\imgui.h>
#include <imgui\imgui_internal.h>
#include <iostream>
#include "../../../Editor/src/GlobalVars.h"
#include "../../../Engine/Engine/Shader/ShaderManager.h"
#include "../../../Engine/Engine/ECS/ObjectManager.h"
#include "../../../Engine/Engine/Texture/Textures.h"
#include "../../../Editor/src/ECS/SelectedObjectManager.h"


EntityNode* EntityNode::Instance()
{
    return nullptr;
}

void EntityNode::Initialize()
{
    BaseModel* selectedData = nullptr;  // Define the external variable

    // Add The Default editor grid on start up                       TO DO ADD THIS TO SETTINGS
    ObjectVector.push_back(std::make_unique<MainGrid>(0, "Main Grid", grid_square, grid_size));
}

std::vector<std::unique_ptr<BaseModel>>& EntityNode::GetModels()
{
    return ObjectVector;
}

// This function would handle the management of entities in the system.
void EntityNode::EntityManagmentSystem(std::vector<std::unique_ptr<BaseModel>>& ObjectVector,
    int& currentIndex, int& index, int& objectIndex, int& indexTypeID)
{
    if (!GameFullScreen) // If game mode hide the the EntityManagmentSystem pannel
    {
		
        ImGui::Begin("Entity Management System"); // start of the window
        auto flags = ImGuiTreeNodeFlags_DefaultOpen;
        if (ImGui::TreeNodeEx("Editor Scene", flags)) {

            for (const auto& data : ObjectVector) {

                ImGuiTreeNodeFlags nodeFlags = flags | (SelectedObjectManager::Instance().GetSelectedData() == data.get() ? ImGuiTreeNodeFlags_Selected : 0);

                bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)data->objectIndex, nodeFlags,
                    "  %s : %d : Type ID : %d",
                    // %d : %s : %d : Type ID : %d",
                     //"Object: %d : %s : %d : Type ID : %d",
                    data->objectName.c_str(), data->objectIndex, data->objectTypeID);
                // data->index, data->objectName.c_str(), data->objectIndex, data->objectTypeID);
             // #####

             // #####
                if (ImGui::IsItemClicked()) {
                    SelectedObjectManager::Instance().SetSelectedData(data.get());
                    data->isSelected = true;

                    std::cout << "Data Selected was " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;
                }

                if (ImGui::IsItemHovered()) {
                    // Perform actions when the node is hovered
                    ImGui::SetTooltip("Right click to Edit %s | %d", data->objectName.c_str(), data->objectIndex);

                }

                if (nodeOpen) {
                    //this->onRightClick(data->objectIndex); // Pass a unique identifier
                    this->onRightClick(data->index); // Pass a unique identifier

                    if (ImGui::BeginPopup(("NodePopup" + std::to_string(data->index)).c_str())) {
                        ImGui::TextColored(COLOR_LIGHTBLUE, ICON_FA_EDIT " ENTITY");
                        ImGui::Separator(); // Draw a line
                        if (ImGui::Selectable(ICON_FA_PEN_ALT " Edit")) {
                            SelectedObjectManager::Instance().SetSelectedData(data.get());

                            // Copy the current name to the buffer
                            strncpy_s(nameBuffer, data->objectName.c_str(), sizeof(nameBuffer));
                            nameBuffer[sizeof(nameBuffer) - 1] = '\0';


                            std::cout << "Object Selected To Edit " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;

                            switch (data.get()->objectTypeID) {
                            case 0: // Grid
                                break;
                            case 1: // cube
                                // showObjectEditor = true;
                                // IsTexture = true;

                                std::cout << "Data Selected  is a Cube " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;

                                break;
                            case 2: // plane
                                //showObjectEditor = true;

                                break;
                            case 3:
                                break;
                            case 4: //

                                break;
                            case 5:
                                // showObjectEditor = true;
                                 //IsTexture = true;
                                break;
                            case 6:
                                break;
                            case 7:
                                break;
                            case 8:
                                //showObjectEditor = true;
                                break;
                            case 9:
                                //showObjectEditor = true;
                                break;
                            case 10:
                                //showObjectEditor = true;
                                break;
                            case 11: // pyramid
                                //showObjectEditor = true;

                                break;
                            case 12: // 0bj file
                                //showObjectEditor = true;
                                //dialogType = false; // set to false and not show the add texture button

                                break;
                            case 13:
                                break;
                            case 14:
                                //showObjectEditor = true;
                                //dialogType = false; // set to false and not show the add texture button

                                break;
                            case 15: // Edit Object cube
                                //ShowHalfEdgeEditor = true;
                                break;
                            case 16: // Not in use
                                break;
                            case 17: // Not in use
                                break;
                            case 18: // Not in use
                                break;
                            case 19: // Not in use
                                break;
                            case 20: // sun light LIGHT_SUN
                                //ShowLightEditor = true;
                                break;
                            case 21: // Point
                                //ShowLightEditor = true;

                                break;
                            case 22: // Spot
                                break;
                            case 23: // Area
                                //ShowLightEditor = true;
                                break;
                            case 24: // Not in use
                                break;
                            case 25: // Floor / celing
                                //showTerrainEditor = true;
                                //dialogType = true;
                                break;
                            case 26:   // Terrain  
                                //showTerrainEditor = true;
                                //dialogType = true;
                                break;
                            case 27: // Water
                                //showTerrainEditor = true;
                                //dialogType = true;
                                break;
                            case 28:
                                break;
                            case 29:
                                break;
                            case 30:
                                //ShowSkyEditor = true;
                                //dialogType = true;
                                break;
                            case 31:
                                //ShowSkyEditor = true;
                                break;
                            case 32:
                                //ShowSkyEditor = true;
                                break;

                            default:
                                std::cout << "Data Selected Something Else " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;
                                break;

                            }


                        }
                        if (ImGui::Selectable(ICON_FA_PLUS " New")) {
                            // open a window or popup to select the object
                            std::cout << "Object To Add " << std::endl;
                        }
                        if (ImGui::Selectable(ICON_FA_COPY " Clone")) {

                            std::cout << "Data Selected To Clone " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;
                        }
                        if (ImGui::Selectable(ICON_FA_TRASH_ALT " Delete")) {
                            // open window to ask if your sure
                            std::cout << "Data Selected To Delete " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;
                        }

                        ImGui::EndPopup();
                    }

                    ImGui::TreePop();

                }

            }
            ImGui::TreePop();

        }
        ImGui::End();
    }

    else
    {
        // gridNogrid = true; // Hide the grid in the entity management system window
    }
}

// Render Grid
void EntityNode::RenderGrid(const glm::mat4& view, const glm::mat4& projection,
    std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex, int& Gridobjidx)
{
    ShaderManager::defaultGridShader->Use();
    ShaderManager::defaultGridShader->setMat4("projection", projection);
    ShaderManager::defaultGridShader->setMat4("view", view);

    for (const auto& model : ObjectVector) {  // ObjectVector = 1
        if (auto* grid = dynamic_cast<MainGrid*>(model.get())) {

            glm::mat4 modelMatrix = glm::mat4(1.0f);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, -0.5f, 0.0f));
            modelMatrix = glm::scale(modelMatrix, glm::vec3(20.0f, 0.0f, 20.0f));
            ShaderManager::defaultGridShader->setMat4("model", modelMatrix);

            grid->DrawGrid();
        }
    }
}
// pull together all the items to render and render them all at once
void EntityNode::RenderScene(const glm::mat4& view, const glm::mat4& projection,
    std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex, Shader& shader, Camera& camera)
{
    EntityNode::RenderCube(view, projection, ObjectVector, currentIndex, PlayerIdx);

}

// This is the tempory player model, it will be replaced with a player model later.
void EntityNode::RenderCube(const glm::mat4& view, const glm::mat4& projection,
    std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex, int& PlayerIdx)
{
    stbi_set_flip_vertically_on_load(true);
	Textures textures;

    if (ShouldAddPlayer) { // so we add the cube
        PlayerIdx = ObjectVector.size();
        std::unique_ptr<CubeModel> newCube = std::make_unique<CubeModel>(currentIndex++, "DefaultCube", PlayerIdx);

        newCube->position = glm::vec3(0.0f, 0.0f, 0.0f);
        newCube->scale = glm::vec3(1.0f, 1.0f, 1.0f);
        newCube->modelMatrix = glm::translate(glm::mat4(1.0f), newCube->position);
        newCube->modelMatrix = glm::scale(newCube->modelMatrix, newCube->scale);

       // newCube->textureID = textures.OBJ_Textures("Texture/UsedTexture/OBJ_Textures/default_1.jpg");

        ObjectVector.push_back(std::move(newCube));

        ShouldAddPlayer = false; // Reset the flag after adding the cube
    }

    //if (ShouldUpdateCube) { // then we update the cube position and scale

    //    int selectedIndex = SelectedDataManager::Instance().GetSelectedData()->objectIndex;

    //    if (selectedIndex >= 0 && selectedIndex < ObjectVector.size()) { // -1 to remove the grid

    //        glm::vec3 newCubePosition = glm::vec3(object_Pos[0], object_Pos[1], object_Pos[2]); // New position
    //        ObjectVector[selectedIndex]->position = newCubePosition;

    //        glm::vec3 newCubeScale = glm::vec3(object_Scale[0], object_Scale[1], object_Scale[2]); // New scale
    //        ObjectVector[selectedIndex]->scale = newCubeScale;

    //        //glm::mat4 newCubeRotation = glm::mat4(object_Rotation[0], object_Rotation[1], object_Rotation[2], object_Rotation[3]); // New Rotation
    //       // ObjectVector[index]->rotation = newCubeRotation;


    //        ObjectVector[selectedIndex]->modelMatrix = glm::mat4(1.0f);
    //        ObjectVector[selectedIndex]->modelMatrix = glm::translate(ObjectVector[selectedIndex]->modelMatrix, newCubePosition);
    //        ObjectVector[selectedIndex]->modelMatrix = glm::scale(ObjectVector[selectedIndex]->modelMatrix, newCubeScale);

    //    }

    //    ShouldUpdateCube = false;

    //}

    for (const auto& model : ObjectVector) {
        ShaderManager::defaultGridShader->Use();
        ShaderManager::defaultGridShader->setMat4("view", view);
        ShaderManager::defaultGridShader->setMat4("projection", projection);


        /*ApplySunLights(*ShaderManager::defaultShader, view, projection, ObjectVector);
        ApplyPointLights(*ShaderManager::defaultShader, view, projection, ObjectVector);
        ApplyAreaLights(*ShaderManager::defaultShader, view, projection, ObjectVector);*/


        if (auto* cube = dynamic_cast<CubeModel*>(model.get())) {
            glm::mat4 modelMatrix = glm::mat4(1.0f);
            //modelMatrix = glm::mat4(1.0f);
            ShaderManager::defaultGridShader->setMat4("model", cube->modelMatrix);
            glActiveTexture(GL_TEXTURE0);

            glBindTexture(GL_TEXTURE_2D, cube->textureID);
            cube->DrawCube();
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}

void EntityNode::EntityMainBaseLevel(std::vector<std::unique_ptr<BaseModel>>& ObjectVector,
    int& currentIndex, int& index, int& objectIndex, int& indexTypeID)
{
    // this will set up the base level skybox main planet and the player
}
