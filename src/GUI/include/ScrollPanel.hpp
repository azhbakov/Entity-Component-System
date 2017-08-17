#pragma once

#include "IMouseListener.hpp"
#include <SFML/Graphics.hpp>
#include <src/GUI/include/InteractableGraphics.hpp>

namespace un {

	enum ScrollingState { DraggingHor, DraggingVert, Released};

	class ScrollPanel : public InteractableGraphics {
		private:
			int _width, _height;
			IInteractableGraphics *_content;

			/* Mouse processing*/
			int mouseOffsetInBar;
			ScrollingState _scrollingState;
			void LimitHorizontalBarPosition ();
			void LimitVerticalBarPosition ();

			/* Drawing entities */
			sf::RenderTexture _scrollViewTexture;
			sf::IntRect _scrollView;
			sf::IntRect _horBar;
			sf::IntRect _vertBar;
			const int _scrollBarWidth = 20;

			/* Drawing math */
			bool NeedHorizontalBar ();
			bool NeedVerticalBar ();
			int GetClipPosition (int barPosition, int barZoneLength, float contentLength);
			int GetClipPositionX ();
			int GetClipPositionY ();
			void InitPanelSizes ();
			int GetBarLength (int barZoneLength, int contentLength);

			/* Drawing */
			void DrawScrollBarBackgrounds (sf::RenderTarget& renderTarget, int windowX, int windowY);
			void DrawScrollBars (sf::RenderTarget& renderTarget, int windowX, int windowY);
			void DrawBackground (sf::RenderTarget& renderTarget, int windowX, int windowY);
			void DrawContent (sf::RenderTarget& renderTarget, int windowX, int windowY);
		public:
			ScrollPanel () : ScrollPanel (0, 0) {}
			ScrollPanel (int width, int height)
				: _width (width), _height(height), _scrollingState(Released) {}
			~ScrollPanel () override = default;

			void SetContent (IInteractableGraphics *content);

			void SetWidth (int width) { _width = width; }
			void SetHeigth (int height) { _height = height; }

			/* IDrawable */
			float GetWidth () const override { return _width; }
			float GetHeight () const override { return _height; }
			void Draw (sf::RenderTarget& window, int windowX, int windowY) override;

			/* MouseListener */
			void CheckMouseEvent (sf::Window& window, int windowX, int windowY) override;
	};

}