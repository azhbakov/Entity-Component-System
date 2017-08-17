#pragma once

#include <memory>
#include <iostream>

#include "IComponent.hpp"
#include "GameObject.hpp"
#include "ComponentsEnum.hpp"
#include "ComponentFactory.hpp"

#define SET_TYPE(type) \
virtual ComponentType GetType () { return type; } \
static ComponentType StaticGetType () { return type; }

#define GET_SELF(type) \
std::weak_ptr<type> GetSelf () { return std::static_pointer_cast<type>(_self.lock()); }

namespace un {

	class Component : public IComponent {
		
		template<class ComponentType, class... Args>
		friend std::shared_ptr<ComponentType> ComponentFactory::CreateComponent (Args&&... args);

		private:
			std::weak_ptr<GameObject> _gameObject;
		protected:
			explicit Component (std::weak_ptr<GameObject>& g) : _gameObject(g) {}
			std::weak_ptr<IComponent> _self;
		public:
			~Component () override = default;

			void Start () override {}
			void Update () override {}

			std::weak_ptr<GameObject> GetGameObject () const { return _gameObject; }
			Transform& GetTransform () const { return _gameObject.lock()->GetTransform();}

			ComponentType GetType () override = 0;
	};
}