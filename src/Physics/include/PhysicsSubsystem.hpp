#pragma once

#include "Box2D/Box2D.h"

#include "WeakPtrStorage.hpp"
#include "IPhysicsBody.hpp"

namespace un {

	class PhysicsSubsystem {
		private:
			float _time_step;
			int _velocity_iter;
			int _position_iter;
			b2World _world;

			WeakPtrStorage<IPhysicsBody> _physicsBodies;
		public:
			PhysicsSubsystem (float gravityX = 0.0, float gravityY = -10.0,
								float time_step = 1.0f/60.0f, int velocity_iter = 6, int position_iter = 2) 
				: _world (b2Vec2(gravityX, gravityY)), _time_step(time_step), _velocity_iter(velocity_iter), _position_iter(position_iter) {}
			~PhysicsSubsystem () {}
			
			void UpdatePhysics ();
			void RegisterPhysicsBody (std::weak_ptr<IPhysicsBody> physicsBody);
			b2World& GetWorld() { return _world; }
	};

}