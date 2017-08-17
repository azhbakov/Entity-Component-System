#pragma once

#include <memory>

#include "Renderer.hpp"
#include "GameObject.hpp"
#include "ComponentsEnum.hpp"

#include <SFML/Graphics.hpp>

namespace un {

	class SpriteRenderer : public Renderer {
		private:
			sf::Sprite _sprite;
		public:
			SpriteRenderer (std::weak_ptr<GameObject>& g, int sortingOrder, const sf::Texture& texture);
			
			void SetTexture (sf::Texture& texture);
			void SetTextureRect (int x, int y, int width, int height);
			void SetSize (float widthUnits, float heightUnits);

			sf::Sprite *operator->() { return &_sprite; }
			sf::Sprite *operator*() { return &_sprite; }

			const sf::Drawable& GetRenderData () const override;
			sf::Transformable& GetTransformData() override;
			void UpdateRenderer () override;
			std::string ToString  () override { return "Sprite Renderer"; }

			SET_TYPE (ComponentType::SPRITERENDERER)
			GET_SELF (SpriteRenderer)
	};

}