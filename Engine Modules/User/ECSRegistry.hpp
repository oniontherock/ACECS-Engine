#ifndef __ECS_REGISTRY_H__
#define __ECS_REGISTRY_H__

#include "../ECS.hpp"
#include "SFML/Graphics.hpp"
#include <functional>

namespace ECSRegistry {
	void ECSInitialize();
	void ECSTerminate();
}

// avoid having undefined constructor arguments for events or components,
// as it's more convenient to not have to define every event/component all the time

// whenever you create a new type, ensure you register it in the implementation file of this header
namespace EntityEvents {
	struct EventExample final : public Event {
		DUPLICATE_OVERRIDE(EventExample)

		EventExample(uint16_t _var = 0) : var(_var) {};

		uint16_t var;
	};
}
// use this file to define new component types.
// whenever you create a new type, ensure you register it in the implementation file of this header
namespace EntityComponents {
	struct ComponentExample final : public Component {
		DUPLICATE_OVERRIDE(ComponentExample)

		void system(Entity& entity) final;

		ComponentExample(uint16_t _var = 0) : var(_var) {
			hasSystem = true;
		};

		uint16_t var;
	};
}

#endif