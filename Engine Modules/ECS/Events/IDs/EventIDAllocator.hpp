#ifndef __EVENT_ID_ALLOCATOR_H__
#define __EVENT_ID_ALLOCATOR_H__

#include <unordered_map>
#include <functional>
#include <string>
#include <iostream>

#include "EventIDs.hpp"

template <class B>
class EventIDAllocator {
    EntityEvents::EventTypeID totalAllocatedTypes;
public:

    static EventIDAllocator<B>& getInstance() {
        static EventIDAllocator<B> instance;
        return instance;
    }

    template <class T>
    void registerEvent() {
        EntityEvents::EventIDs<T>::ID = totalAllocatedTypes;

        totalAllocatedTypes++;
    }
};
#define EVENT_ID_ALLOCATOR(Class) EventIDAllocator<Class>::getInstance()

#define REGISTER_EVENT_ID(base_class, derived_class) \
  EVENT_ID_ALLOCATOR(base_class).registerEvent<derived_class>();

#endif