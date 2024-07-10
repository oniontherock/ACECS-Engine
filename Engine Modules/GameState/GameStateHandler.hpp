#ifndef __GAME_STATE_HANDLER_H__
#define __GAME_STATE_HANDLER_H__

#include <unordered_map>
#include <functional>
#include <cstdint>
#include <iostream>
#include "../Graphics/Panel.hpp"
#include "../Graphics/PanelManager.hpp"
#include "../Input/InputInterface.hpp"

typedef const char* GameStateName;

struct GameStateTransition {

	GameStateTransition(GameStateName _toStateName, std::vector<InputName> _transitionInputs) :
		toStateName(_toStateName),
		linkedInputs(_transitionInputs)
	{}

	// the name of the state that this transition leads to
	GameStateName toStateName;

	// vector of inputs that trigger a transition
	std::vector<InputName> linkedInputs;
};

struct GameState {

	GameState(std::vector<GameStateTransition> _transitions, std::function<void()> _updateFunc, std::vector<PanelName> _panelNames) :
		transitions(_transitions),
		updateFunc(_updateFunc),
		panelNames(_panelNames)
	{}

	// vector of different GameStateTransitions linked to this GameStates
	std::vector<GameStateTransition> transitions;
	// vector of different PanelNames belonging to this GameState
	std::vector<PanelName> panelNames;
	// this GameState's update function
	std::function<void()> updateFunc;
};


namespace {
	class GameStateHandler {
	public:
		static bool gameStateExists(GameStateName stateName) {
			return gameStates.count(stateName);
		}
	private:

		static inline std::unordered_map<GameStateName, GameState*> gameStates = std::unordered_map<GameStateName, GameState*>();

		static inline GameStateName gameStateNameCur = "";

		static void gameStateUpdate() {

			auto& curGameState = gameStates[gameStateNameCur];

			Input::Interface inputInterface{};

			// iterate through the game state's transitions
			for (uint16_t curTransitionInd = 0; curTransitionInd < curGameState->transitions.size(); curTransitionInd++) {
				// get the current transition
				auto& curTransition = curGameState->transitions[curTransitionInd];

				// iterate through every input of the current transition
				for (uint16_t curTransitionInputInd = 0; curTransitionInputInd < curTransition.linkedInputs.size(); curTransitionInputInd++) {
					// check if the current input of the current transition is active, if it is, transition to that state, and end the check
					if (inputInterface.inputGetActive(curTransition.linkedInputs[curTransitionInputInd])) {
						gameStateNameCur = curTransition.toStateName;
						return;
					}
				}
			}
		}

		static const void gameStateRun() {
			std::invoke(gameStates[gameStateNameCur]->updateFunc);
		}

		// checks if gameStateCurName is valid, and if it is, returns true, otherwise, prints an error and returns false
		static bool gameStateNameCurCheckValid() {
			if (std::strcmp(gameStateNameCur, "") == 0) {
				std::cerr << "ERROR: Uninitialized game state. Please set game state to an initial value" << std::endl;
			}
			if (!gameStateExists(gameStateNameCur)) {
				std::cerr << "ERROR: Unknown game state: " << "\"" << gameStateNameCur << "\"" << std::endl;
			} else {
				return true;
			}
			return false;
		}

	public:

		static void gameStateProcess() {
			if (!gameStateNameCurCheckValid()) return;
			gameStateUpdate();
			gameStateRun();
		}

		static void gameStateTerminate(GameStateName name) {
			delete gameStates[name];
			gameStates.erase(name);
		}

		static void gameStateAdd(GameStateName name, std::vector<GameStateTransition> transitions, std::vector<PanelName> panels, std::function<void()> updateFunc) {

			for (const auto& panelNameCur : panels) {
				if (!PanelManager::panelExists(panelNameCur)) {
					std::cerr << "ERROR: Attempted to add a GameState with non-existent panel: " << "\"" << panelNameCur << "\"" << std::endl;
				}
			}

			gameStates.insert({ name, new GameState(transitions, updateFunc, panels) });
		}

		// does some error checking on every state, should be called after adding new game states
		static void gameStateFinalizeAddedStates() {
			for (const auto& [gameStateNameCur, gameStateCur] : gameStates) {
				for (const auto& gameStateTransitionCur : gameStateCur->transitions) {
					if (!gameStateExists(gameStateTransitionCur.toStateName)) {
						std::cerr << "ERROR: Attempted to add a GameState with non-existent transition: " << "\"" << gameStateTransitionCur.toStateName
							<< "\"" << std::endl;
					}
				}
			}
		}

		static void gameStateForceSet(GameStateName gameStateName) {
			gameStateNameCur = gameStateName;
		}

		static void gameStatesAllTerminate() {
			for (const auto& [key, value] : gameStates) {
				delete value;
			}
			gameStates.clear();
		}

		static const std::vector<PanelName>& gameStateGetPanels() {
			return gameStates[gameStateNameCur]->panelNames;
		}
	};
}

#endif
