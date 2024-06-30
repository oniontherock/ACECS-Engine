#ifndef __GAME_STATE_HANDLER_H__
#define __GAME_STATE_HANDLER_H__

#include <unordered_map>
#include <functional>
#include <cstdint>
#include <iostream>
#include "../Input.hpp"

typedef const char* GameStateName;

struct GameStateTransition {

	GameStateTransition(GameStateName _toStateName, std::vector<InputName> _transitionInputs) :
		toStateName(_toStateName),
		transitionInputs(_transitionInputs)
	{}

	// the name of the state that this transition leads to
	GameStateName toStateName;

	std::vector<InputName> transitionInputs;
};

struct GameState {

	GameState(std::vector<GameStateTransition> _transitions, std::function<void()> _updateFunc) :
		transitions(_transitions),
		updateFunc(_updateFunc)
	{}

	std::vector<GameStateTransition> transitions;
	std::function<void()> updateFunc;
};

namespace {
	class GameStateHandler {
		static inline std::unordered_map<GameStateName, GameState*> gameStates;

		static inline GameStateName curGameStateName = "";

		static inline void updateState() {

			auto& curGameState = gameStates[curGameStateName];

			Input::Interface inputInterface{};

			// iterate through the game state's transitions
			for (uint16_t curTransitionInd = 0; curTransitionInd < curGameState->transitions.size(); curTransitionInd++) {
				// get the current transition
				auto& curTransition = curGameState->transitions[curTransitionInd];

				// iterate through every input of the current transition
				for (uint16_t curTransitionInputInd = 0; curTransitionInputInd < curTransition.transitionInputs.size(); curTransitionInputInd++) {
					// check if the current input of the current transition is active, if it is, transition to that state, and end the check
					if (inputInterface.getInputActive(curTransition.transitionInputs[curTransitionInputInd])) {
						curGameStateName = curTransition.toStateName;
						return;
					}
				}
			}
		}

		static inline const void runState() {
			std::invoke(gameStates[curGameStateName]->updateFunc);
		}
	public:

		static inline void process() {
			if (std::strcmp(curGameStateName, "") == 0) {
				std::cout << "ERROR: Uninitialized game state. Please set game state to an initial value" << std::endl;
				return;
			}
			else if (!gameStates.count(curGameStateName)) {
				std::cout << "ERROR: Unknown game state: " << "\"" << curGameStateName << "\"" << std::endl;
				return;
			}
			updateState();
			runState();
		}

		static inline void deleteGameState(GameStateName name) {
			delete gameStates[name];
			gameStates.erase(name);
		}

		static inline void addGameState(GameStateName name, std::vector<GameStateTransition> transitions, std::function<void()> updateFunc) {
			gameStates.insert({ name, new GameState(transitions, updateFunc) });
		}

		static inline void forceSetGameState(GameStateName gameStateName) {
			curGameStateName = gameStateName;
		}
	};
}

#endif
