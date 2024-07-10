#ifndef __COMPONENT_IDS_H__
#define __COMPONENT_IDS_H__

// this file simply holds the component IDs, there really isn't much going on in here,
// and it should probably remain unchanged

#include <cstdint>
#include "Component.hpp"

namespace EntityComponents {

	// an ID representing a certain TYPE of component, NOT a specific component instance
	typedef uint16_t ComponentTypeID;

	// the maximum value for any ID
	inline ComponentTypeID maxID;
	// the total amount of components
	inline ComponentTypeID totalComponents;

	// ComponentTypesHolder is a sort of helper struct that holds the ComponentTypeID of every type of component,
	// an ID is simply an integer assigned uniquely to every child of base class "Component",
	// the way you get the ID of a component type is like this: "ComponentIDHolder<TYPE>::ID".
	template <class T>
	struct ComponentIDs {
		static ComponentTypeID ID;

		static void IDSet(ComponentTypeID value) {
			ID = value;

			if (ID > maxID) maxID = ID;

			if (ID + 1 > totalComponents) totalComponents = ID + 1;
		}
	};

	// define ComponentIDHolder's ID variable as 0 for every type.
	// note that the ID for every type is assigned later, 
	// if you wish to see how this is done, see the "Component.cpp" file, or the "TypeAllocator.hpp" file.

	// the ID of a component type, used for accessing certain types of components in arrays, among other things
	template <class T>
	ComponentTypeID ComponentIDs<T>::ID{ 0 };

	// a pair of ComponentTypeID and Component instance,
	// should be used when knowing the ID of a component is necessary, but knowing the type of component is not possible
	typedef std::pair<EntityComponents::ComponentTypeID, Component*> ComponentIndexInstancePair;

	// creates a new ComponentIndexInstancePair from the type T,
	// note that this function returns a pair containing a raw pointer, so do not forget to delete the raw pointer
	template <class T>
	ComponentIndexInstancePair createComponentPairFromType() {
		return ComponentIndexInstancePair(ComponentIDs<T>::ID, new T());
	}
};

#endif