#pragma once

#include <memory>
#include <set>

#include "IRenderer.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"
#include "RenderingLayers.hpp"

#include <SFML/Graphics.hpp>

namespace un {

	class Renderer : public Component, public IRenderer {
		private:
			std::set<RenderingLayer> _layers;
			int _sortingOrder;

			void SyncTransformToRenderer();
		public:
			Renderer (std::weak_ptr<GameObject>& g, int sortingOrder);
			~Renderer () override = default;
			
			/* From Component */
			void Start () override;
			void Update () final {}
			std::string ToString () override { return GetGameObject().lock()->ToString(); }
			
			/* From IRenderer */
			void UpdateRenderer () override;
			const sf::Drawable& GetRenderData () const override = 0;
			sf::Transformable& GetTransformData() override = 0;
			int GetSortingOrder () const final { return _sortingOrder; }

			std::set<RenderingLayer>& GetRenderingLayers () override { return _layers; }
			void AddRenderingLayer (RenderingLayer layer) override;
			void RemoveRenderingLayer (RenderingLayer layer) override;

			GET_SELF(Renderer);
	};

}