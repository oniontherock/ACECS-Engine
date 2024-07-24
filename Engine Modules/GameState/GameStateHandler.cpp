#include "GameStateHandler.hpp"

std::unordered_map<GameStateName, GameState*> GameStateHandler::gameStates = std::unordered_map<GameStateName, GameState*>();
GameStateName GameStateHandler::gameStateNameCur = "";

GameStateTransition::GameStateTransition(GameStateName _toStateName, std::vector<InputName> _transitionInputs) :
	toStateName(_toStateName),
	linkedInputs(_transitionInputs)
{}


GameState::GameState(std::vector<GameStateTransition> _transitions, std::function<void()> _updateFunc, std::vector<PanelName> _panelNames) :
	transitions(_transitions),
	updateFunc(_updateFunc),
	panelNames(_panelNames)
{}

void GameStateHandler::gameStateUpdate() {
	auto& curGameState = gameStates[gameStateNameCur];

	// iterate through the game state's transitions
	for (uint16_t curTransitionInd = 0; curTransitionInd < curGameState->transitions.size(); curTransitionInd++) {
		// get the current transition
		auto& curTransition = curGameState->transitions[curTransitionInd];

		// iterate through every input of the current transition
		for (uint16_t curTransitionInputInd = 0; curTransitionInputInd < curTransition.linkedInputs.size(); curTransitionInputInd++) {
			// check if the current input of the current transition is active, if it is, transition to that state, and end the check
			if (InputInterface::inputGetActive(curTransition.linkedInputs[curTransitionInputInd])) {
				gameStateNameCur = curTransition.toStateName;
				return;
			}
		}
	}
}

const void GameStateHandler::gameStateRun() {
	std::invoke(gameStates[gameStateNameCur]->updateFunc);
}

// checks if gameStateCurName is valid, and if it is, returns true, otherwise, prints an error and returns false
bool GameStateHandler::gameStateNameCurCheckValid() {
	if (std::strcmp(gameStateNameCur, "") == 0) {
		std::cerr << "ERROR: Uninitialized game state. Please set game state to an initial value" << std::endl;
	}
	if (!gameStateExists(gameStateNameCur)) {
		std::cerr << "ERROR: Unknown game state: " << "\"" << gameStateNameCur << "\"" << std::endl;
	}
	else {
		return true;
	}
	return false;
}

bool GameStateHandler::gameStateExists(GameStateName stateName) {
	return gameStates.count(stateName);
}

void GameStateHandler::gameStateProcess() {
	if (!gameStateNameCurCheckValid()) return;
	gameStateUpdate();
	gameStateRun();
}

void GameStateHandler::gameStateTerminate(GameStateName name) {
	delete gameStates[name];
	gameStates.erase(name);
}

void GameStateHandler::gameStateAdd(GameStateName name, std::vector<GameStateTransition> transitions, std::vector<PanelName> panels, std::function<void()> updateFunc) {

	for (const auto& panelNameCur : panels) {
		if (!PanelManager::panelExists(panelNameCur)) {
			std::cerr << "ERROR: Attempted to add a GameState with non-existent panel: " << "\"" << panelNameCur << "\"" << std::endl;
		}
	}

	gameStates.insert({ name, new GameState(transitions, updateFunc, panels) });
}

// does some error checking on every state, should be called after adding new game states
void GameStateHandler::gameStatesAddedStatesFinalize() {
	for (const auto& [stateNameCur, gameStateCur] : gameStates) {
		for (const auto& gameStateTransitionCur : gameStateCur->transitions) {
			if (!gameStateExists(gameStateTransitionCur.toStateName)) {
				std::cerr << "ERROR: Attempted to add a GameState with non-existent transition: " << "\"" << gameStateTransitionCur.toStateName
					<< "\"" << std::endl;
			}
		}
	}
}

void GameStateHandler::gameStateForceSet(GameStateName gameStateName) {
	gameStateNameCur = gameStateName;
}

void GameStateHandler::gameStatesAllTerminate() {
	for (const auto& [key, value] : gameStates) {
		delete value;
	}
	gameStates.clear();
}

const std::vector<PanelName>& GameStateHandler::gameStateGetPanels() {
		return gameStates[gameStateNameCur]->panelNames;
	}
