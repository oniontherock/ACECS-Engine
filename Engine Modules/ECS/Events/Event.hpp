#ifndef __EVENT_H__
#define __EVENT_H__

#include <cstdint>
#include <vector>
#include <queue>
#include <iostream>

#include "../Duplicatable.hpp"

namespace EntityEvents {

	struct Event : public Duplicatable {

		std::unique_ptr<Duplicatable> duplicate() override {
			return std::unique_ptr<Duplicatable>(new Event());
		}

		bool isActive = false;
	};

	void eventIDsInitialize();
}


#endif