#include "GameStates.hpp"

#include "../World/LevelUpdater.hpp"

void GameStatePlay::gameStateUpdate() {
	LevelUpdater::levelsUpdate();
}

void GameStatePause::gameStateUpdate() {
}

