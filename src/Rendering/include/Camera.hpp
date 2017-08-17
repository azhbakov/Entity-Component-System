#pragma once

#include <memory>
#include <iterator>
#include <set>

#include "Component.hpp"
#include "IRenderer.hpp"
#include "ICamera.hpp"
#include "ComponentsEnum.hpp"
#include "RenderingLayers.hpp"

#include <SFML/Graphics.hpp>

namespace un {

	class Camera : public Component, public ICamera {
		private:
			sf::RenderWindow& _window;
			/*float _viewWidth;
			float _viewHeight;*/

			std::set<RenderingLayer> _layers;

			//std::multiset<std::weak_ptr<IRenderer>, bool(*)(const std::weak_ptr<IRenderer>&, const std::weak_ptr<IRenderer>&)> _renderers;

			bool HasMatchingLayers (std::weak_ptr<IRenderer> renderer);
			void Render (std::weak_ptr<IRenderer> renderer);
			void UpdateCameraPosition ();
		public:
			Camera (std::weak_ptr<GameObject> g, sf::RenderWindow& window, float viewWidth, float viewHeight);
			~Camera () {}

			void AddRenderingLayer (RenderingLayer layer);
			void RemoveRenderingLayer (RenderingLayer layer);

			// From Component
			virtual void Start ();
			virtual void Update () {}

			SET_TYPE (ComponentType::CAMERA)
			GET_SELF (Camera)

			// From ICamera
			virtual void UpdateCamera (std::vector<std::weak_ptr<IRenderer>>::iterator begin, std::vector<std::weak_ptr<IRenderer>>::iterator end);
			virtual std::string ToString  () { return "Camera"; }
			// void AddRenderer (std::weak_ptr<IRenderer> renderer);
			// void RemoveRenderer (IRenderer *renderer);

	};
}