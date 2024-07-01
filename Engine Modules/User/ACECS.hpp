#ifndef __ACECS_H__
#define __ACECS_H__

#include "../GameState.hpp"
#include "ECSRegistry.hpp"

namespace {
	class Engine{
	private:
		// inputs are registered here
		static inline void inputsRegister() {
			Input::Interface inputInterface{};

			inputInterface.inputRegister("Example", KeySet{ KeyEvent("E", Pressed) });
		}
		
		// game states are registered here
		static inline void gameStateRegister() {
			GameStateHandler::gameStateAdd("Example State",
				std::vector<GameStateTransition>{
				GameStateTransition("Other Example State", std::vector<InputName>{ "Example Button" })
			},
				[]() {
					// ... update game state specific things here ...
				}
			);
		}
	public:
		// initialize the ACECS engine by registering all inputs, initializing the ECS module, and registering game states.
		// of course, certain modules do not have to be initialized if the user does not want them to be
		static inline void engineInitialize() {
			inputsRegister();
			ECSRegistry::ECSInitialize();
			gameStateRegister();
		}
		// update certain modules of the engine, like the input system, and the game state.
		// note that certain modules, like the ECS system, are updated inside the GameStateHandler,
		// because you don't want to update the ECS system if the GameState is currently paused, for example.
		static inline void engineUpdate() {
			 Input::Interface().inputUpdate();

			GameStateHandler::gameStateProcess();
		}
		// terminates certain engine modules, like the ECS or GameStateHandler
		static inline void engineTerminate() {
			ECSRegistry::ECSTerminate();
			GameStateHandler::gameStatesAllTerminate();
		}

	};
}

#endif