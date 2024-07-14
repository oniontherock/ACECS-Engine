#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <unordered_set>
#include <string>
#include <functional>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Entity.hpp"
#include "../TypeDefinitions.hpp"

#include "../../GameWorld/LevelTypeDefinitions.hpp"
#include "../../GameWorld/GameWorld.hpp"

namespace EntityManager {

	extern std::vector<Entity> entitiesVector;

	extern uint32_t entityCount;

	// updates every entity in existence.
	// note that this shouldn't be used for simply updating the entities,
	// as entities in active rooms are updated in the LevelUpdater.
	void entitiesUpdate();
	void entityUpdate(EntityId entityId);
	/**
	creates a new entity instance and returns it's ID

	@param updateType: the update type of the entity
	*/
	EntityId entityCreate(EntityUpdateType updateType = EntityUpdateType::Frame);
	/**
	creates a new entity instance, places it inside a specified room, and returns it's ID

	@param updateType: the update type of the entity
	@param level: the LevelPosition of the level the entity should be placed inside
	*/
	EntityId entityCreate(LevelPosition level, EntityUpdateType updateType = EntityUpdateType::Frame);
	/**
	creates a new entity instance, places it inside a specified room, and returns it's ID

	@param updateType: the update type of the entity
	@param levelX: the X coordinate of the level the entity should be placed inside
	@param levelY: the Y coordinate of the level the entity should be placed inside
	@param levelZ: the Z coordinate of the level the entity should be placed inside
	*/
	EntityId entityCreate(LevelCoordinate levelX, LevelCoordinate levelY, LevelCoordinate levelZ, EntityUpdateType updateType = EntityUpdateType::Frame);
	void entityTerminate(EntityId entityID);
	void entitiesAllDelete();
};

#endif