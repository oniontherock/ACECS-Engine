#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "LevelTypeDefinitions.hpp"
#include "../ECS/Entities/Entity.hpp"
#include "../ECS/TypeDefinitions.hpp"

struct BaseLevel {

	BaseLevel();
	BaseLevel(LevelCoordinate _idX, LevelCoordinate _idY, LevelCoordinate _idZ);
	BaseLevel(LevelPosition _id);

	LevelPosition levelPosition;

	void entityIdAdd(EntityId id);
	void entityIdRemove(EntityId id);

	// list of EntityIDs belonging to this room 
	std::vector<EntityId> entities;
};

template <class Level>
using LevelPtr = std::unique_ptr<Level>;

using BaseLevelPtr = LevelPtr<BaseLevel>;

#endif