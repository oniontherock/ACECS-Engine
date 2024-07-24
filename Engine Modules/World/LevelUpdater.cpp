#include "LevelUpdater.hpp"


void LevelUpdater::levelsUpdate() {
	for (uint32_t levelActiveInd = 0; levelActiveInd < levelsActiveVector.size(); levelActiveInd++) {

		LevelPosition levelActivePosition = levelsActiveVector[levelActiveInd];

		BaseLevel* levelActiveCur = LevelGrid<BaseLevel>::levelGet(levelActivePosition);

		for (uint32_t entityIdInd = 0; entityIdInd < levelActiveCur->entities.size(); entityIdInd++) {
			EntityManager::entityUpdate(levelActiveCur->entities[entityIdInd]);
		}
	}
}

