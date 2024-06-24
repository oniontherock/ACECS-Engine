#ifndef __COMPONENT_ID_ALLOCATOR_H__
#define __COMPONENT_ID_ALLOCATOR_H__

#include <unordered_map>
#include <functional>
#include <string>
#include <iostream>

#include "ComponentIDs.hpp"

template <class B>
class ComponentIDAllocator {
    Components::ComponentTypeID totalAllocatedTypes;
public:

    static ComponentIDAllocator<B>& getInstance() {
        static ComponentIDAllocator<B> instance;
        return instance;
    }

    template <class T>
    void registerComponent() {
        Components::ComponentIDs<T>::ID = totalAllocatedTypes;

        totalAllocatedTypes++;
    }
};
#define COMPONENT_ID_ALLOCATOR(Class) ComponentIDAllocator<Class>::getInstance()

#define REGISTER_COMPONENT_ID(base_class, derived_class) \
  COMPONENT_ID_ALLOCATOR(base_class).registerComponent<derived_class>();

#endif