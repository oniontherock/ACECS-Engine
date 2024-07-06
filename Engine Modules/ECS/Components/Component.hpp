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
#include "../Duplicatable.hpp"

struct Entity;

namespace EntityComponents {

	// base component class
	struct Component : public Duplicatable{

		virtual ~Component() = default;

		std::unique_ptr<Duplicatable> duplicate() override {
			return std::unique_ptr<Duplicatable>(new Component());
		}

		virtual void system(Entity& entity) {
		}

		bool hasSystem = false;
	};

	// used to initialize component IDs, defined in the ECSRegistry.cpp file
	void componentIDsInitialize();

};

#endif