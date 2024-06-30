#ifndef __ACECS_H__
#define __ACECS_H__

#include "../GameState.hpp"
#include "ECSRegistry.hpp"

namespace {
	class Engine{
	private:
		static inline void registerInputs() {
			Input::Interface inputInterface{};

			inputInterface.registerInput("Example", KeySet{ KeyEvent("E", Pressed) });
		}
		
		static inline void registerGameState() {
			GameStateHandler::gameStateAdd("Play",
				std::vector<GameStateTransition>{
				GameStateTransition("Pause", std::vector<InputName>{ "Pause" })
			},
				[]() {
					std::cout << "hello sire" << std::endl;
				}
			);
		}
	public:
		static inline void initialize() {
			registerInputs();
			ECSRegistry::initializeECS();
		}
		static inline void update() {
			Input::Interface inputInterface{};

			inputInterface.updateInput();

			GameStateHandler::gameStateProcess();
		}
		static inline void terminate() {
			ECSRegistry::terminateECS();
		}

	};
}

#endif