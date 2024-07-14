#include "LevelUpdater.hpp"


void LevelUpdater::levelsUpdate() {
	for (uint32_t levelActiveInd = 0; levelActiveInd < GameWorld::levelsActiveVector.size(); levelActiveInd++) {

		LevelPosition levelActivePosition = GameWorld::levelsActiveVector[levelActiveInd];

		Level* levelActiveCur = GameWorld::levelGet(levelActivePosition);

		for (uint32_t entityIdInd = 0; entityIdInd < levelActiveCur->entities.size(); i++) {
			EntityManager::entityUpdate(levelActiveCur->entities[entityIdInd]);
		}
	}
}


