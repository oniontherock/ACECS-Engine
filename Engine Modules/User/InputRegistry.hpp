#ifndef __INPUT_REGISTRY_H__
#define __INPUT_REGISTRY_H__

#include "../Input.hpp"

void initializeInput();
void terminateInput();

namespace InputRegistry {
	void registerInputs();
};

#endif