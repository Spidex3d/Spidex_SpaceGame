#pragma once
#include <vector>
#include <memory>
#include "BaseModel.h"
#include "SelectedObjectManager.h"
#include <imgui\imgui.h>


class EntityNode
{
public:

	static EntityNode* Instance();

	void Initialize();

	std::vector<std::unique_ptr<BaseModel>>& GetModels();

	void EntityManagmentSystem(std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex,
		int& index, int& objectIndex, int& indexTypeID);

	void EntityMainBaseLevel(std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex,
		int& index, int& objectIndex, int& indexTypeID);

private:

	void onRightClick(int objectId) {
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
			ImGui::OpenPopup(("NodePopup" + std::to_string(objectId)).c_str());
		}

	}
};

