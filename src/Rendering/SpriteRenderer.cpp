#include "SpriteRenderer.hpp"
#include "Game.hpp"


using namespace std;
using namespace un;

SpriteRenderer::SpriteRenderer (weak_ptr<GameObject>& g, int sortingOrder, const sf::Texture& texture)
	: Renderer(g, sortingOrder), _sprite(texture) {
	sf::IntRect rect = _sprite.getTextureRect ();
	_sprite.setOrigin (rect.width/2.0f, rect.height/2.0f);	
}

void SpriteRenderer::SetTexture (sf::Texture& texture) {
	_sprite.setTexture(texture);
}

void SpriteRenderer::SetTextureRect (int x, int y, int width, int height) {
	_sprite.setTextureRect (sf::IntRect(x, y, width, height));
	_sprite.setOrigin (width/2.0f, height/2.0f);
}


void SpriteRenderer::SetSize (float widthUnits, float heightUnits) {
	float ppu = Game::Instance().PIXELS_PER_UNIT;
	sf::IntRect rect = _sprite.getTextureRect ();
	float factorX = widthUnits / (rect.width/ppu); 
	float factorY = heightUnits / (rect.height/ppu); 
	_sprite.setScale (factorX, factorY);
}

void SpriteRenderer::UpdateRenderer () {
	Renderer::UpdateRenderer();
}

const sf::Drawable& SpriteRenderer::GetRenderData () const { 
	return _sprite;
}

sf::Transformable& SpriteRenderer::GetTransformData () {
	return _sprite;
}
