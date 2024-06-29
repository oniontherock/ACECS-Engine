#ifndef __TYPE_ID_ALLOCATOR_H__
#define __TYPE_ID_ALLOCATOR_H__

#include <unordered_map>
#include <functional>
#include <string>
#include <iostream>

// substitute for ComponentTypeID or EventTypeID
typedef uint16_t TypeID;


template <class B>
class TypeIDAllocator {
    static inline TypeID totalAllocatedTypes = 0;
public:
    template <class Registry>
    static void registerType() {
        Registry::setID(totalAllocatedTypes);

        totalAllocatedTypes++;
    }
};

#endif