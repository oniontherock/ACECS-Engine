#ifndef __REGISTRY_H__
#define __REGISTRY_H__
#include "../Include Helpers/ECSDependences.hpp"
#include <functional>

#pragma region Systems
struct SystemRegistry {
	static void createSystems();
};
#pragma endregion Systems
#pragma region Events
// whenever you create a new type, ensure you register it in the implementation file of this header
namespace EntityEvents {
#pragma region user_defined_events
	/// Event convention:
	///struct EventConvention: public Event {
	///	EventConvention(int _variable) : variable(_variable) {};
	/// 
	/// int variable
	///};
#pragma endregion user_defined_events
}
#pragma endregion Events
#pragma region Components
// use this file to define new component types.
// whenever you create a new type, ensure you register it in the implementation file of this header
namespace Components {
#pragma region user_defined_components_section
	/// Component convention::
	///struct ComponentConvention : public Component {
	///	ComponentConvention(int _variable) : variable(_variable) {};
	///
	///	int variable;
	///};
#pragma endregion user_defined_components_section
}
#pragma endregion Components

#endif