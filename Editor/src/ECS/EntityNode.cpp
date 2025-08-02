#include "EntityNode.h"
#include <imgui\ImGuiAF.h>
#include <imgui\imgui.h>
#include <imgui\imgui_internal.h>
#include "..\GlobalVars.h"

EntityNode* EntityNode::Instance()
{
    return nullptr;
}

void EntityNode::Initialize()
{
}

std::vector<std::unique_ptr<BaseModel>>& EntityNode::GetModels()
{
    return ObjectVector;
}

// This function would handle the management of entities in the system.
void EntityNode::EntityManagmentSystem(std::vector<std::unique_ptr<BaseModel>>& ObjectVector,
    int& currentIndex, int& index, int& objectIndex, int& indexTypeID)
{
    ImGui::Begin("Entity Management System"); // start of the window
	ImGui::Text("Entity Management System"); // title of the window
    ImGui::End();
}