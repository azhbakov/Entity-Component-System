#pragma once

#include <memory>

#include "IComponent.hpp"

namespace un {
	class ComponentFactory {
		public:
			template<class ComponentType, class... Args>
			static std::shared_ptr<ComponentType> CreateComponent (Args&&... args) {
				ComponentType *o = new ComponentType(args...);
				auto sptr = std::shared_ptr<ComponentType>(o); // TO DO: make_shared
				sptr->_self = std::weak_ptr<IComponent>(sptr);
				return sptr;
			}
		};
}