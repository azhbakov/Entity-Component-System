#pragma once

#include <string>

namespace un {

	class IPhysicsBody {
		public:
			virtual ~IPhysicsBody () {}

			virtual void PreUpdatePhysics () = 0;
			virtual void PostUpdatePhysics () = 0;
			virtual std::string ToString () = 0;
	};

}