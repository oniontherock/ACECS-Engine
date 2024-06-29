#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <cstdint>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <iostream>
#include <vector>

#include "../TypeDefinitions.hpp"

struct Entity;

namespace Components {

	// base component class,
	struct Component {
		virtual void system(Entity& entity) {
		}

		bool hasSystem = false;
	};

	inline std::vector<std::function<void(Entity&)>> systems;

	// used to initialize component IDs, defined in the ComponentRegistry file
	void initialize();
};

#endif