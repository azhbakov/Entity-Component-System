#pragma once

#include <memory>

#include "GameObject.hpp"
#include "Component.hpp"
#include "Box2DWorld.hpp"
#include "Box2D/Box2D.h"
#include "PhysicsBody.hpp"

namespace un {

	class BoxCollider : public PhysicsBody {
		public:
			BoxCollider (std::weak_ptr<GameObject>& g, PhysicsSubsystem& ps, float width, float height, bool isDynamic = true);
			virtual ~BoxCollider() {}

			/* From Component */
			virtual void Start () { PhysicsBody::Start(); }
			virtual std::string ToString  () { return "Box Collider of " + PhysicsBody::ToString(); }

			SET_TYPE (ComponentType::BOXCOLLIDER)
			GET_SELF (BoxCollider)
	};

}