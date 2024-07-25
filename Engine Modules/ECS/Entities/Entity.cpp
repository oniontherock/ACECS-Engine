#include "Entity.hpp"

Entity::Entity() {
	updateType = EntityUpdateType::Frame;
	Id = 0;
}
Entity::Entity(EntityId _id, EntityUpdateType _updateType) {
	Id = _id;
	updateType = _updateType;

	componentsInitialize();
	eventsInitialize();
}
Entity::Entity(EntityId _id, EntityUpdateType _updateType, LevelPosition _levelId) {
	Id = _id;
	updateType = _updateType;
	levelId = _levelId;

	componentsInitialize();
	eventsInitialize();
}

template <class T>
static void copyUniquePtrVector(std::vector<std::unique_ptr<T>>& A, const std::vector<std::unique_ptr<T>>& B) {
	for (uint16_t i = 0; i < B.size(); i++) {
		if (!static_cast<bool>(B[i])) {
			A.push_back(std::unique_ptr<T>(nullptr));
			continue;
		}
		A.push_back(Duplicatable::duplicateAndConvertToType<T>(B[i].get()));
	}
}
template <class T>
static void copyUniquePtrVector(std::vector<std::unique_ptr<T>>& A, std::vector<std::unique_ptr<T>>& B) {
	for (uint16_t i = 0; i < B.size(); i++) {
		if (!static_cast<bool>(B[i])) {
			A.push_back(std::unique_ptr<T>(nullptr));
			continue;
		}
		A.push_back(Duplicatable::duplicateAndConvertToType<T>(B[i].get()));
	}
}

Entity::Entity(Entity& other) {
	Id = other.Id;
	updateType = other.updateType;
	levelId = other.levelId;

	copyUniquePtrVector<EntityComponents::Component>(componentsVector, other.componentsVector);
	copyUniquePtrVector<EntityEvents::Event>(eventsVector, other.eventsVector);
}
Entity& Entity::operator= (const Entity& other) {

	Id = other.Id;
	updateType = other.updateType;
	levelId = other.levelId;

	copyUniquePtrVector<EntityComponents::Component>(componentsVector, other.componentsVector);
	copyUniquePtrVector<EntityEvents::Event>(eventsVector, other.eventsVector);

	return *this;
}
Entity::~Entity() {
	terminate();
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