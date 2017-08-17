#pragma once

#include "Transform.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <set>
#include "RenderingLayers.hpp"

namespace un {

	class IRenderer {
		public:
			virtual ~IRenderer() = default;

			/* Game related */
			virtual void UpdateRenderer () = 0;
			virtual std::string ToString () = 0;

			/* Camera related */
			virtual const sf::Drawable& GetRenderData () const = 0;
			virtual sf::Transformable& GetTransformData() = 0;
			virtual int GetSortingOrder () const = 0;

			virtual std::set<RenderingLayer>& GetRenderingLayers () = 0;
			virtual void AddRenderingLayer (RenderingLayer layer) = 0;
			virtual void RemoveRenderingLayer (RenderingLayer layer) = 0;
	};

}