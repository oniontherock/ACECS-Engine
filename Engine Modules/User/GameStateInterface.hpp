#ifndef __GAME_STATE_REGISTRY_H__
#define __GAME_STATE_REGISTRY_H__

#include <iostream>
#include "../GameState.hpp"

namespace GameStateInterface {
	void registerGameStates();
	void runGameState();
}

#endif