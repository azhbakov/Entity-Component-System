#pragma once

#include "Renderer.hpp"
#include <SFML/Graphics.hpp>

namespace un {

	class CircleRenderer final : public Renderer {
		private:
			sf::CircleShape _circle;
			bool _extending;
		public:
			CircleRenderer (std::weak_ptr<GameObject>& g, int sortingOrder, float radius);
			~CircleRenderer () override = default;

			void UpdateRenderer () override;

			const sf::Drawable& GetRenderData () const override;

			sf::Transformable& GetTransformData() override;

			std::string ToString  () override { return "Circle Renderer"; }

			SET_TYPE (ComponentType::CIRCLERENDERER)
			GET_SELF (CircleRenderer)
	};

}