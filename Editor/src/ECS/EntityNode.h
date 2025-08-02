#pragma once
#include <vector>
#include <memory>
#include "BaseModel.h"

class EntityNode
{
public:

	static EntityNode* Instance();

	void Initialize();

	std::vector<std::unique_ptr<BaseModel>>& GetModels();

	void EntityManagmentSystem(std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex,
		int& index, int& objectIndex, int& indexTypeID);

};

