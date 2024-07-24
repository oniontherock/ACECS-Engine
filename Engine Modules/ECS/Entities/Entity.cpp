#include "Entity.hpp"

Entity::Entity() {
	updateType = EntityUpdateType::Frame;
	Id = 0;
};

void Entity::entityCreate(EntityId id, EntityUpdateType _updateType) {
	Id = id;
	updateType = _updateType;

	componentsInitialize();
	eventsInitialize();
}
void Entity::entityCreate(EntityId id, EntityUpdateType _updateType, LevelPosition _levelId) {
	Id = id;
	updateType = _updateType;
	levelId = _levelId;

	componentsInitialize();
	eventsInitialize();
}
void Entity::entityBecomeOther(Entity& other) {

	Id = other.Id;
	updateType = other.updateType;
	levelId = other.levelId;

	componentsVector = std::move(other.componentsVector);
	eventsVector = std::move(other.eventsVector);
}

void Entity::componentsInitialize() {
	componentsVector = std::vector<ComponentUniquePtr>(EntityComponents::totalComponents);
};

void Entity::eventsInitialize() {
	auto& allEvents = EntityEvents::allEvents;

	for (uint16_t i = 0; i < allEvents.size(); i++) {
		eventsVector.push_back(Duplicatable::duplicateAndConvertToType<EntityEvents::Event>(allEvents[i]));
	}
};

bool Entity::entityComponentHasAtIndex(EntityComponents::ComponentTypeID index) {
	return static_cast<bool>(componentsVector[index]);
}
void Entity::entityComponentAddAtIndex(EntityComponents::Component* component, EntityComponents::ComponentTypeID index) {
	componentsVector[index] = ComponentUniquePtr(component);
}
void Entity::entityComponentAddAtIndexNoOverwrite(EntityComponents::Component* component, EntityComponents::ComponentTypeID index) {
	if (entityComponentHasAtIndex(index)) return;

	entityComponentAddAtIndex(component, index);
}

void Entity::entityUpdate() {
	componentsUpdate();
	// deactivating all events is basically just clearing the entity's events
	if (hasAnyEvent) eventsAllDeactivate();
}
void Entity::componentsUpdate() {
	for (uint16_t i = 0; i < EntityComponents::totalComponents; i++) {

		if (!static_cast<bool>(componentsVector[i])) continue;
		if (!componentsVector[i]->hasSystem) continue;

		componentsVector[i]->system(*this);
	}
}

void Entity::componentsAllTerminate() {
	for (EntityComponents::ComponentTypeID i = 0; i < EntityComponents::totalComponents; i++) {
		componentsVector[i].reset();
	}
}

void Entity::eventsAllDeactivate() {
	for (uint16_t i = 0; i < eventsVector.size(); i++) {
		eventsVector[i]->isActive = false;
	}

	hasAnyEvent = false;
}

void Entity::eventsAllTerminate() {
	for (uint16_t i = 0; i < eventsVector.size(); i++) {

		if (eventsVector[i] != nullptr) {
			eventsVector[i].reset();
		}
	}

	hasAnyEvent = false;
}

void Entity::terminate() {
	componentsAllTerminate();
	eventsAllTerminate();
}