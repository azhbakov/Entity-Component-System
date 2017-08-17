#pragma once

#include "Component.hpp"
#include "ComponentsEnum.hpp"

#include <string>

namespace un {

	class MovementScript : public Component {
		private:
			float _speed;
		public:
			MovementScript (std::weak_ptr<GameObject> g, float speed)
				: Component(g), _speed(speed) {}
			virtual ~MovementScript () {}
			virtual void Update ();

			virtual std::string ToString () { return "MovementScript"; }

			SET_TYPE(ComponentType::MOVEMENTSCRIPT)
			GET_SELF(MovementScript)
	};

}