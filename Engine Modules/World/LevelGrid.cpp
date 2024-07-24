#include "LevelGrid.hpp"

BaseLevelPtrGrid levelGrid = BaseLevelPtrGrid(0);

template <class Level>
std::vector<LevelPosition> LevelGrid<Level>::levelsActiveVector = std::vector<LevelPosition>(0);

template <class Level>
LevelPosition LevelGrid<Level>::levelCur = LevelPosition(0, 0, 0);


