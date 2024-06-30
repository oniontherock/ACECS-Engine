#ifndef __ECS_REGISTRY_H__
#define __ECS_REGISTRY_H__

// ECS constants must be included first, as it defines important macros for the ACECS Engine
#include "ECSConstants.hpp"

#include "../ECS.hpp"
#include "SFML/Graphics.hpp"
#include <functional>

void initializeECS();
void terminateECS();

// avoid having undefined constructor arguments for events or components,
// as it's more convenient to not have to define every event/component all the time

#pragma region Events
// whenever you create a new type, ensure you register it in the implementation file of this header
namespace EntityEvents {
#pragma region user_defined_events
	struct EventExample : public Event {
		EventExample(uint16_t _var = 0) : var(_var) {};

		uint16_t var;
	};
#pragma endregion user_defined_events
}
#pragma endregion Events
#pragma region Components
// use this file to define new component types.
// whenever you create a new type, ensure you register it in the implementation file of this header
namespace Components {
#pragma region user_defined_components_section
	struct ComponentExample final : public Component {
		void system(Entity& entity) override;

		ComponentExample(uint16_t _var = 0) : var(_var) {
			hasSystem = true;
		};

		uint16_t var;
	};
#pragma endregion user_defined_components_section
}
#pragma endregion Components

#endif