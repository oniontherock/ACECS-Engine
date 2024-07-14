#ifndef __LEVEL_TYPE_DEFINITIONS_H__
#define __LEVEL_TYPE_DEFINITIONS_H__

#include "SFML/System/Vector3.hpp"
#include <cstdint>

// position of a level in the GameWorld's levelGrid
using LevelPosition = sf::Vector3<uint32_t>;

typedef uint32_t LevelCoordinate;

#endif
