#include "Physics.h"

void Physics::update(float dt)
{

	if (!physics_space.empty()) {
		
		for (auto i : physics_space) {	//Pointer has permanence regardless of referencing
			
			if (i->is_simulated()) {
				i->transform() += (Transform(i->get_velocity(), i->get_angular_velocity(), {0,0,0}) * dt);
			}

		}





	}

}
