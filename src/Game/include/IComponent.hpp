#pragma once

#include <memory>
#include <string>
#include <iostream>

#include "ComponentsEnum.hpp"

namespace un {
	class IComponent {
		public:
			IComponent () = default;
			IComponent (const IComponent& c) = delete;
			IComponent (IComponent&& c) = default;
			IComponent &operator= (const IComponent& c) = delete;
			IComponent &operator= (IComponent&& c) = default;
			virtual ~IComponent() = default;

			virtual void Start () = 0;
			virtual void Update () = 0;

			virtual std::string ToString () = 0;
			/*
				C++ don't feature reliable RTTI mechanics. Thus IComponent::GetType method is used
				to define actual Component type in runtime for implementation of GameObject::GetComponent
				method.
				Enum ComponentType must contain entry for each component type. Such entry is returned by
				every Component object on GetType call. Same entry must be returned on static GetType call of the component class.
			*/
			virtual ComponentType GetType () = 0; 
			// static virtual ComponentType GetType () = 0; // unfortunatelly not allowed 
	};
}