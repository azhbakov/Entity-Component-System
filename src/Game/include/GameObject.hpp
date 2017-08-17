#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>
#include <vector>
#include <memory>

#include "Transform.hpp"
#include "IComponent.hpp"
#include "ComponentsEnum.hpp"
#include "ComponentFactory.hpp"

namespace un {

	#define DEFAULT_OBJECT_NAME "GameObject"

	class GameObject final {
		private:
			std::string _name;
			std::string _tag;
			Transform _transform;

			std::weak_ptr<GameObject> _self;

			std::vector<std::shared_ptr<IComponent>> _components;
	
			GameObject() : GameObject(DEFAULT_OBJECT_NAME, 0, 0) {}
			
			GameObject(std::string name) : GameObject(name, 0, 0) {}
			
			GameObject(float worldX, float worldY) : GameObject(DEFAULT_OBJECT_NAME, worldX, worldY) {}
			
			GameObject(std::string name, float worldX, float worldY);
		public:
			static std::shared_ptr<GameObject> CreateGameObject () {return CreateGameObject(DEFAULT_OBJECT_NAME, 0,0);}
			static std::shared_ptr<GameObject> CreateGameObject (std::string name) {return CreateGameObject(name, 0, 0);}
			static std::shared_ptr<GameObject> CreateGameObject (float worldX, float worldY) {return CreateGameObject(DEFAULT_OBJECT_NAME, worldX, worldY);}
			static std::shared_ptr<GameObject> CreateGameObject (std::string name, float worldX, float worldY);
			
			~GameObject(); // destroy components

			void Start ();

			void Update ();

			void Destroy ();

			template<class T, typename... Args> 
			std::weak_ptr<T> AddComponent (Args&&... args) {
				//std::shared_ptr<T> newComponent = std::make_shared<T> (_self, args...);
				//std::shared_ptr<T> newComponent = Component<T>::CreateComponent (_self, args...)
				std::shared_ptr<T> newComponent = ComponentFactory::CreateComponent<T> (_self, args...);
				_components.push_back (newComponent);

				#ifdef SIMPLE_LOGGER
					Logger::Instance().Log ({"GameObject"}, "Added new component " + _components.back()->ToString() + " to GameObject: " + this->ToString());
				#endif

				return std::weak_ptr<T> (newComponent);
			}

			template<class T>
			std::weak_ptr<T> GetComponent () const {
				ComponentType requestedType = T::StaticGetType();

				for (std::shared_ptr<IComponent> c : _components) {
					if (c->GetType() == requestedType) {
						return std::weak_ptr<T> (std::dynamic_pointer_cast<T>(c));
					}
				}

				return std::weak_ptr<T> ();
			}

			void SetName (std::string name) { _name = name; }
			std::string GetName () const { return _name; }
			
			// Move..
			Transform& GetTransform () { return _transform; }
			
			void SetTag (std::string tag) { _tag = tag; }
			std::string GetTag () const { return _tag; }

			std::string ToString ();

	};

}

#endif