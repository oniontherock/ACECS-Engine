#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "../../World/LevelTypeDefinitions.hpp"
#include "../Components/Component.hpp"
#include "../Components/ComponentIDs.hpp"
#include "../Events/Event.hpp"
#include "../Events/EventIDs.hpp"
#include "../Events/EventPool.hpp"
#include "../TypeDefinitions.hpp"
#include <array>
#include <cstdint>
#include <iostream>
#include <optional>
#include <queue>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

template <class T>
class SmartVector {
	std::vector<T*> vec;

public:

	SmartVector() {
		vec = std::vector<T*>();
	}
	~SmartVector() {
		for (uint16_t i = 0; i < vec.size(); i++) {
			delete vec[i];
		}
	}

	inline T* operator[] (int ind) {
		return vec[ind];
	}

	inline std::vector<T*>& getVec() { 
		return vec;
	}

	typename inline std::vector<T*>::iterator begin() { return vec.begin(); }
	typename inline std::vector<T*>::const_iterator begin() const { return vec.begin(); }
	typename inline std::vector<T*>::iterator end() { return vec.end(); }
	typename inline std::vector<T*>::const_iterator end() const { return vec.end(); }
	inline size_t size() const { return vec.size(); }

	template <class C>
	inline std::vector<C*> convertToType() {

		std::vector<C*> tempVec(vec.begin(), vec.end());

		std::transform(vec.begin(), vec.end(), tempVec.begin(), [](T* t) { return static_cast<C*>(t); });;

		return tempVec;
	}
};

typedef SmartVector<EntityEvents::Event> EventVector;

template <class CastType, class T>
class CastedVector {

	SmartVector<T>& vecToCast;

public:
	CastedVector(SmartVector<T>& vecToCast) :
		vecToCast(vecToCast)
	{}

	inline CastType* operator[] (int ind) {
		return static_cast<CastType*>(vecToCast[ind]);
	}

	typename inline std::vector<T*>::iterator begin() { return vecToCast.begin(); }
	typename inline std::vector<T*>::const_iterator begin() const { return vecToCast.begin(); }
	typename inline std::vector<T*>::iterator end() { return vecToCast.end(); }
	typename inline std::vector<T*>::const_iterator end() const { return vecToCast.end(); }
	inline size_t size() const { return vecToCast.size(); }

};

struct Entity {
private:
	bool hasAnyEvent = false;

	void componentsAllTerminate();
	void eventsAllTerminate();
	void terminate();
public:
	explicit Entity();
	explicit Entity(EntityId _id, EntityUpdateType _updateType);
	explicit Entity(EntityId _id, EntityUpdateType _updateType, LevelPosition _levelId);

	Entity(Entity& other);
	Entity& operator= (const Entity& other);
	~Entity();

	void componentsInitialize();
	void eventsInitialize();

	EntityUpdateType updateType;

	// the Id of this entity, every entity has a unique Id.
	// Ids are used to access entities in the EntityManager's "entities" vector
	EntityId Id;
	// the id of the level that this entity belongs to,
	// if all three components are equal to the max uint32_t value, then this entity does not belong to a level
	LevelPosition levelId;

	std::vector<ComponentUniquePtr> componentsVector;

	std::vector<EventVector> eventsVector;


	template <class T>
	T* entityComponentGet() {
		return static_cast<T*>(componentsVector[EntityComponents::ComponentIDs<T>::ID].get());
	}
	template <class T>
	bool entityComponentHas() {
		return static_cast<bool>(componentsVector[EntityComponents::ComponentIDs<T>::ID]);
	}
	template <class T>
	void entityComponentAdd(EntityComponents::Component* component) {
		componentsVector[EntityComponents::ComponentIDs<T>::ID] = ComponentUniquePtr(component);
	}
	// checks if the entity has the component, and if not, adds it
	template <class T>
	void entityComponentAddNoOverwrite(EntityComponents::Component* component) {
		if (entityComponentHas<T>()) return;

		entityComponentAdd<T>(component);
	}
	template <class T>
	void entityComponentTerminate() {
		componentsVector[EntityComponents::ComponentIDs<T>::ID].reset();
	}
	bool entityComponentHasAtIndex(EntityComponents::ComponentTypeID index);
	void entityComponentAddAtIndex(EntityComponents::Component* component, EntityComponents::ComponentTypeID index);
	// checks if the entity has the component, and if not, adds it
	void entityComponentAddAtIndexNoOverwrite(EntityComponents::Component* component, EntityComponents::ComponentTypeID index);


	template <class T>
	T* entityEventGet(uint16_t ind) {
		return static_cast<T*>(eventsVector[EntityEvents::EventIDs<T>::ID][ind]);
	}
	template <class T>
	T* entityEventGet() {
		return entityEventGet<T>(0);
	}
	template <class T>
	T* entityEventGetSafe(uint16_t ind) {
		if (eventsVector[EntityEvents::EventIDs<T>::ID].size() <= 0) return nullptr;

		return entityEventGet(ind);
	}
	template <class T>
	T* entityEventGetSafe() {
		return entityEventGetSafe<T>(0);
	}
	template <class T>
	bool entityEventHas() {
		return eventsVector[EntityEvents::EventIDs<T>::ID].getVec().size() > 0;
	}
	// sets an event to active
	template <class T>
	void entityEventAdd() {
		hasAnyEvent = true;

		eventsVector[EntityEvents::EventIDs<T>::ID].getVec().push_back(EventPool::eventPoolTake<T>());
	}
	// sets an event to active and returns the event so it's members may be modified
	template <class T>
	T* entityEventAddAndGet() {
		entityEventAdd<T>();
		return entityEventGet<T>(uint16_t(eventsVector[EntityEvents::EventIDs<T>::ID].getVec().size()) - 1);
	}
	void entityEventTerminate(EntityEvents::EventTypeID eventId, uint16_t ind);

	template <class T>
	void entityEventTerminate(uint16_t ind) {
		entityEventTerminate(EntityEvents::EventIDs<T>::ID, ind);
	}
	template <class T>
	CastedVector<T, EntityEvents::Event> entityEventGetAllOfType() {

		EntityEvents::EventTypeID eventId = EntityEvents::EventIDs<T>::ID;

		return CastedVector<T, EntityEvents::Event>(eventsVector[eventId]);
	}
	void entityEventTerminateAllOfType(EntityEvents::EventTypeID eventId);
	template <class T>
	void entityEventTerminateAllOfType() {
		entityEventTerminateAllOfType(EntityEvents::EventIDs<T>::ID);
	}


	void entityUpdate();
	void componentsUpdate();
};


#endif