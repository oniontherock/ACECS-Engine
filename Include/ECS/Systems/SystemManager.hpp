#pragma once
#include <unordered_map>
#include <functional>

#include "../Entities/Entity.hpp"
#include "../Components/Component.hpp"
#include "../Components/IDs/ComponentIDs.hpp"

typedef std::function<void(EntityID entityID)> System;

namespace SystemManager {
	using namespace Components;

	// map of systems, keys are ComponentTypes
	inline std::unordered_map<ComponentTypeID, System> systems;


	inline void addSystem(System system, ComponentTypeID componentID) {
		systems.insert({ componentID, system });
	}

	inline void callSystem(EntityID entity, ComponentTypeID componentID) {
		systems[componentID](entity);
	}

	inline bool typeHasSystem(ComponentTypeID componentID) {
		return systems.find(componentID) != systems.end();
	}
};

