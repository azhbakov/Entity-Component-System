#include "PhysicsSubsystem.hpp"
#include "Box2D/Box2D.h"
#include "IPhysicsBody.hpp"

#include "WeakPtrStorage.hpp"

#ifdef ENABLE_LOG
	#include "Logger.hpp"
#endif

using namespace un;

void PhysicsSubsystem::UpdatePhysics () {
	#ifdef SIMPLE_LOGGER
		LOG ({"Physics Subsystem"}, "Updating physics...");
	#endif

	_physicsBodies.RemoveExpired ();

	for (auto it = _physicsBodies->begin(); it != _physicsBodies->end(); it++) {
		#ifdef SIMPLE_LOGGER
			LOG ({"Physics Subsystem"}, "Pre-Updating physics body " + it->lock()->ToString() + "...");
		#endif
		
		it->lock()->PreUpdatePhysics ();

		#ifdef SIMPLE_LOGGER
			LOG ({"Physics Subsystem"}, "Physics body " + it->lock()->ToString() + " pre-updated.");
		#endif
	}

	_world.Step (_time_step, _velocity_iter, _position_iter);

	for (auto it = _physicsBodies->begin(); it != _physicsBodies->end(); it++) {
		#ifdef SIMPLE_LOGGER
			LOG ({"Physics Subsystem"}, "Post-Updating physics body " + it->lock()->ToString() + "...");
		#endif
		
		it->lock()->PostUpdatePhysics ();

		#ifdef SIMPLE_LOGGER
			LOG ({"Physics Subsystem"}, "Physics body " + it->lock()->ToString() + " post-updated.");
		#endif
	}

	#ifdef SIMPLE_LOGGER
		LOG ({"Physics Subsystem"}, "Physics updated.");
	#endif
}

void PhysicsSubsystem::RegisterPhysicsBody (std::weak_ptr<IPhysicsBody> physicsBody) {
	_physicsBodies.AddPointer (physicsBody);

	#ifdef SIMPLE_LOGGER
	LOG ({"Physics Subsystem"}, "Registered physics body " + physicsBody.lock()->ToString() + ".");
	#endif
}