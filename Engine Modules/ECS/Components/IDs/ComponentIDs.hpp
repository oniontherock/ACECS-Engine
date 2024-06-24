#ifndef __COMPONENT_IDS_H__
#define __COMPONENT_IDS_H__

// this file simply holds the component IDs, there really isn't much going on in here,
// and it should probably remain unchanged

#include <cstdint>

namespace Components {

	// an ID representing a certain TYPE of component, NOT a specific component instance
	typedef uint16_t ComponentTypeID;

	// ComponentTypesHolder is a sort of helper struct that holds the ComponentTypeID of every type of component,
	// an ID is simply an integer assigned uniquely to every child of base class "Component",
	// the way you get the ID of a component type is like this: "ComponentIDHolder<TYPE>::ID".
	// component IDs are used for a few things, primaryily for iterating through component types in the ComponentManager
	template <class T>
	struct ComponentIDs {
		static ComponentTypeID ID;
	};

	// define ComponentIDHolder's ID variable as 0 for every type.
	// note that the ID for every type is assigned later, 
	// if you wish to see how this is done, see the "Component.cpp" file, or the "TypeAllocator.hpp" file.
	template <class T>
	ComponentTypeID ComponentIDs<T>::ID{ 0 };
};

#endif