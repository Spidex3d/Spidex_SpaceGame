#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "BaseModel.h"
#include "../../../Engine/Engine/ECS/ObjectManager.h"
#include "../Editor/src/ECS/SelectedObjectManager.h"
#include <imgui\imgui.h>
#include "../Camera/Camera.h"
#include <stb\stb_image.h>


class EntityNode : public BaseModel
{
public:

	//glm::mat4 modelMatrix;

	static EntityNode* Instance();

	void Initialize();

	std::vector<std::unique_ptr<BaseModel>>& GetModels();

	PlayerModel* GetPlayerCube(std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int PlayerIdx);

	void EntityManagmentSystem(std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex,
		int& index, int& objectIndex, int& indexTypeID);

	// Render the editor Grid
	void RenderGrid(const glm::mat4& view, const glm::mat4& projection,
		std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex, int& Gridobjidx);


	void RenderScene(const glm::mat4& view, const glm::mat4& projection,
		std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex, Shader& shader, Camera& camera);

		// Cube This is the temperary player model, it will be replaced with a player model later.
	void RenderCube(const glm::mat4& view, const glm::mat4& projection,
		std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex, int& PlayerIdx);

	void EntityMainBaseLevel(std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex,
		int& index, int& objectIndex, int& indexTypeID);

private:

	glm::mat4 modelMatrix;

	void onRightClick(int objectId) {
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
			ImGui::OpenPopup(("NodePopup" + std::to_string(objectId)).c_str());
		}

	}

	
};

