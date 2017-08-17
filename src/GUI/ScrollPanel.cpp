#include <iostream>
#include "ScrollPanel.hpp"

using namespace un;
using namespace std;

bool ScrollPanel::NeedHorizontalBar () {
	return _content->GetWidth() > GetWidth();
}
bool ScrollPanel::NeedVerticalBar () {
	return _content->GetHeight() > GetHeight();
}

void ScrollPanel::InitPanelSizes() {
	/* Init scroll view */
	int scrollViewWidth;
	if (NeedVerticalBar()) {
		scrollViewWidth = GetWidth() - _scrollBarWidth;
	} else {
		scrollViewWidth = GetWidth();
	}

	int scrollViewHeight;
	if (NeedHorizontalBar()) {
		scrollViewHeight = GetHeight() - _scrollBarWidth;
	} else {
		scrollViewHeight = GetHeight();
	}

	_scrollView.left = 0;
	_scrollView.top = 0;
	_scrollView.width = scrollViewWidth;
	_scrollView.height = scrollViewHeight;

	/* Init vertical bar */
	if (NeedVerticalBar()) {
		_vertBar.left = scrollViewWidth;
		_vertBar.top = 0;
		_vertBar.width = _scrollBarWidth;
		_vertBar.height = GetBarLength(_scrollView.height, _content->GetHeight());
	}

	/* Init horizontal bar */
	if (NeedHorizontalBar()) {
		_horBar.left = 0;
		_horBar.top = _scrollView.height;
		_horBar.width = GetBarLength (_scrollView.width, _content->GetWidth());
		_horBar.height = _scrollBarWidth;
	}
}

void ScrollPanel::SetContent(IInteractableGraphics *content) {
	_content = content;
	_scrollViewTexture.create(_content->GetWidth(), _content->GetHeight());
	_scrollViewTexture.clear(sf::Color::White);
	_content->Draw(_scrollViewTexture, 0, 0);
	_scrollViewTexture.display();

	InitPanelSizes();
}

int ScrollPanel::GetBarLength (int barZoneLength, int contentLength) {
	float ratio = (float)contentLength/barZoneLength;
	return barZoneLength/ratio;  //300 517 100 30
};

int ScrollPanel::GetClipPosition (int barPosition, int barZoneLength, float contentLength) {
	float uvPosition = (float)barPosition/(float)barZoneLength;
	return uvPosition*contentLength;
}

int ScrollPanel::GetClipPositionX () {
	return GetClipPosition (_horBar.left, _scrollView.width, _content->GetWidth());
}

int ScrollPanel::GetClipPositionY() {
	return GetClipPosition (_vertBar.top, _scrollView.height, _content->GetHeight());
}

void ScrollPanel::DrawScrollBarBackgrounds (sf::RenderTarget& renderTarget, int windowX, int windowY) {
	sf::Color backgroundColor = sf::Color (230, 230, 230);
	sf::Color outlineColor = sf::Color::Black;
	float thickness = 1.0f;

	if (NeedVerticalBar()) {
		auto backgroundShape = sf::RectangleShape(sf::Vector2f(_scrollBarWidth, GetHeight()));
		backgroundShape.setPosition(windowX + _scrollView.width, windowY + 0);
		backgroundShape.setOutlineColor(outlineColor);
		backgroundShape.setOutlineThickness(thickness);
		backgroundShape.setFillColor(backgroundColor);

		renderTarget.draw (backgroundShape);
	}

	if (NeedHorizontalBar()) {
		auto backgroundShape = sf::RectangleShape(sf::Vector2f(GetWidth(), _scrollBarWidth));
		backgroundShape.setPosition(windowX + 0, windowY + _scrollView.height);
		backgroundShape.setOutlineColor(outlineColor);
		backgroundShape.setOutlineThickness(thickness);
		backgroundShape.setFillColor(backgroundColor);

		renderTarget.draw (backgroundShape);
	}
}

void ScrollPanel::DrawScrollBars (sf::RenderTarget& renderTarget, int windowX, int windowY) {
	sf::Color outlineColor = sf::Color::Black;
	sf::Color barColor = sf::Color (240, 240, 240);
	float thickness = 1.0f;

	if (NeedVerticalBar()) {
		auto barShape = sf::RectangleShape(sf::Vector2f(_vertBar.width, _vertBar.height));
		barShape.setPosition(windowX + _vertBar.left, windowY + _vertBar.top);
		barShape.setOutlineColor(outlineColor);
		barShape.setOutlineThickness(thickness);
		barShape.setFillColor(barColor);

		renderTarget.draw (barShape);
	}

	if (NeedHorizontalBar()) {
		auto barShape = sf::RectangleShape(sf::Vector2f(_horBar.width, _horBar.height));
		barShape.setPosition(windowX + _horBar.left, windowY + _horBar.top);
		barShape.setOutlineColor(outlineColor);
		barShape.setOutlineThickness(thickness);
		barShape.setFillColor(barColor);

		renderTarget.draw (barShape);
	}
}

void ScrollPanel::DrawBackground (sf::RenderTarget& renderTarget, int windowX, int windowY) {
	sf::Color outlineColor = sf::Color::Black;
	sf::Color backgroundColor = sf::Color (240, 240, 240);
	float thickness = 1.0f;

	auto backgroundRect = sf::RectangleShape(sf::Vector2f(_scrollView.width, _scrollView.height));
	backgroundRect.setPosition(windowX, windowY);
	backgroundRect.setOutlineColor(outlineColor);
	backgroundRect.setOutlineThickness(thickness);
	backgroundRect.setFillColor(backgroundColor);

	renderTarget.draw(backgroundRect);
}

void ScrollPanel::DrawContent (sf::RenderTarget& renderTarget, int windowX, int windowY) {
	_scrollViewTexture.clear(sf::Color::White);
	_content->Draw(_scrollViewTexture, 0, 0);
	_scrollViewTexture.display();

	sf::IntRect scrollViewClip (GetClipPositionX(),
	                            GetClipPositionY(),
	                            min(_scrollView.width, (int)_content->GetWidth()),
	                            min(_scrollView.height, (int)_content->GetHeight()));
	sf::Sprite scrollViewSprite (_scrollViewTexture.getTexture(), scrollViewClip);
	scrollViewSprite.setPosition(windowX, windowY);

	renderTarget.draw(scrollViewSprite);
}

void ScrollPanel::Draw (sf::RenderTarget& renderTarget, int windowX, int windowY) {
	CenterView (renderTarget);
	DrawBackground(renderTarget, windowX, windowY);
	DrawContent(renderTarget, windowX, windowY);
	DrawScrollBarBackgrounds(renderTarget, windowX, windowY);
	DrawScrollBars(renderTarget, windowX, windowY);
}

void ScrollPanel::LimitHorizontalBarPosition () {
	int leftLimit = _scrollView.left;
	int rightLimit = _scrollView.left + _scrollView.width - _horBar.width;
	if (rightLimit < _horBar.left) {
		_horBar.left = rightLimit;
	} else if (_horBar.left < leftLimit) {
		_horBar.left = leftLimit;
	}
}
void ScrollPanel::LimitVerticalBarPosition () {
	int topLimit = _scrollView.top + _scrollView.height - _vertBar.height;
	int bottomLimit = _scrollView.top;
	if (topLimit < _vertBar.top) {
		_vertBar.top = topLimit;
	} else if (_vertBar.top < bottomLimit) {
		_vertBar.top = bottomLimit;
	}
}

void ScrollPanel::CheckMouseEvent (sf::Window& window, int windowX, int windowY) {
	sf::Vector2i pos = sf::Mouse::getPosition(window);

	pos.x -= windowX;
	pos.y -= windowY;

	/* Content's mouse processing */
	if (_scrollView.contains(pos)) {
		_content->CheckMouseEvent(window, windowX + _scrollView.left - GetClipPositionX(), windowY + _scrollView.top - GetClipPositionY());
	}

	/* Bars mouse processing */
	UpdateMouseState();

	if (_mouseState == Idle) {
		_scrollingState = Released;
	} else {

		if (_mouseState == Press) {
			if (_vertBar.contains(pos)) {
				_scrollingState = ScrollingState::DraggingVert;
				mouseOffsetInBar = pos.y - _vertBar.top;
			} else if (_horBar.contains(pos)) {
				_scrollingState = ScrollingState::DraggingHor;
				mouseOffsetInBar = pos.x - _horBar.left;
			}
		} else if (_mouseState == Drag) {
			if (_scrollingState == DraggingHor) {
				_horBar.left = pos.x - mouseOffsetInBar;
				LimitHorizontalBarPosition();
			} else if (_scrollingState == DraggingVert) {
				_vertBar.top = pos.y - mouseOffsetInBar;
				LimitVerticalBarPosition();
			}
		}
	}
}

