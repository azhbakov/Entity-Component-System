#pragma once

#include <memory>

#include "PhysicsSubsystem.hpp"
#include "IPhysicsBody.hpp"
#include "Component.hpp"
#include "Box2D/Box2D.h"

namespace un {

	class PhysicsBody : public Component, public IPhysicsBody {
		private:
			PhysicsSubsystem& _ps;
			bool IsSync ();
			void SyncBoxToBody ();
			void SyncBodyToBox ();
		protected:
			b2Body *_body;
		public:
			PhysicsBody (std::weak_ptr<GameObject>& g, PhysicsSubsystem& ps) : Component(g), _ps(ps) {}
			virtual ~PhysicsBody () {}

			//b2Body *operator->() { return _body; }

			/* From Component */
			virtual void Start ();
			virtual void Update () final {}

			/* From IPhysicsBody */
			virtual void PreUpdatePhysics ();
			virtual void PostUpdatePhysics ();
			virtual std::string ToString () { return GetGameObject().lock()->ToString(); };			
	
			GET_SELF (PhysicsBody);
	};

}