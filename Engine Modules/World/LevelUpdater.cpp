#include "LevelUpdater.hpp"


void LevelUpdater::levelsUpdate() {
	for (uint32_t levelActiveInd = 0; levelActiveInd < WorldGrid::levelsActiveVector.size(); levelActiveInd++) {

		LevelPosition levelActivePosition = WorldGrid::levelsActiveVector[levelActiveInd];

		Level* levelActiveCur = WorldGrid::levelGet(levelActivePosition);

		for (uint32_t entityIdInd = 0; entityIdInd < levelActiveCur->entities.size(); entityIdInd++) {
			EntityManager::entityUpdate(levelActiveCur->entities[entityIdInd]);
		}
	}
}


