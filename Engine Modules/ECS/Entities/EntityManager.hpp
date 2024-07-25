#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <unordered_set>
#include <string>
#include <functional>
#include <vector>

#include "../Components/ComponentTemplateManager.hpp"

#include "Entity.hpp"
#include "../TypeDefinitions.hpp"

#include "../../World/LevelTypeDefinitions.hpp"
#include "../../World/LevelGrid.hpp"

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
	creates a new entity instance, places it in a specified room, and returns it's ID

	@param updateType: the update type of the entity
	@param level: the LevelPosition of the level the entity should be placed in
	*/
	EntityId entityCreate(LevelPosition level, EntityUpdateType updateType = EntityUpdateType::Frame);
	/**
	creates a new entity instance, places it in a specified room, and returns it's ID

	@param updateType: the update type of the entity
	@param levelX: the X coordinate of the level the entity should be placed in
	@param levelY: the Y coordinate of the level the entity should be placed in
	@param levelZ: the Z coordinate of the level the entity should be placed in
	*/
	EntityId entityCreate(LevelCoordinate levelX, LevelCoordinate levelY, LevelCoordinate levelZ, EntityUpdateType updateType = EntityUpdateType::Frame);
	/**
	creates a new entity instance, applies a component template to it, and returns it's ID

	@param templateName: the name of the component template to be applied to the entity
	@param updateType: the update type of the entity
	*/
	EntityId entityCreate(ComponentTemplateName templateName, EntityUpdateType updateType = EntityUpdateType::Frame);
	/**
	creates a new entity instance, places it in a specified room, applies a component template to it, and returns it's ID

	@param templateName: the name of the component template to be applied to the entity
	@param updateType: the update type of the entity
	@param level: the LevelPosition of the level the entity should be placed in
	*/
	EntityId entityCreate(LevelPosition level, ComponentTemplateName templateName, EntityUpdateType updateType = EntityUpdateType::Frame);
	/**
	creates a new entity instance, places it in a specified room, applies a component template to it, and returns it's ID

	@param templateName: the name of the component template to be applied to the entity
	@param updateType: the update type of the entity
	@param levelX: the X coordinate of the level the entity should be placed in
	@param levelY: the Y coordinate of the level the entity should be placed in
	@param levelZ: the Z coordinate of the level the entity should be placed in
	*/
	EntityId entityCreate(LevelCoordinate levelX, LevelCoordinate levelY, LevelCoordinate levelZ, ComponentTemplateName templateName, EntityUpdateType updateType = EntityUpdateType::Frame);

	void entityAddToRoom(EntityId entityId, LevelPosition level);
	void entityAddToRoom(EntityId entityId, LevelCoordinate levelX, LevelCoordinate levelY, LevelCoordinate levelZ);

	Entity& entityGet(EntityId entityId);
	void entityTerminate(EntityId entityID);
	void entitiesAllDelete();
};

#endif