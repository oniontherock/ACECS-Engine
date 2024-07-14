#include "LevelUpdater.hpp"


void LevelUpdater::levelsUpdate() {
	for (uint32_t levelActiveInd = 0; levelActiveInd < World::levelsActiveVector.size(); levelActiveInd++) {

		LevelPosition levelActivePosition = World::levelsActiveVector[levelActiveInd];

		Level* levelActiveCur = World::levelGet(levelActivePosition);

		for (uint32_t entityIdInd = 0; entityIdInd < levelActiveCur->entities.size(); i++) {
			EntityManager::entityUpdate(levelActiveCur->entities[entityIdInd]);
		}
	}
}


