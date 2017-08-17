//
// Created by marting422 on 11.08.17.
//

#include <src/GUI/include/BoxLayout.hpp>
#include <iostream>

using namespace un;

void BoxLayout::AddComponent (IInteractableGraphics *d) {
	_content.push_back(d);
}

void BoxLayout::RemoveComponent (IInteractableGraphics *d) {
	for (auto i = _content.begin(); i != _content.end(); i++) {
		if ((*i) == d) {
			_content.erase(i);
			return;
		}
	}
}

float BoxLayout::GetWidth () const {
	if (_orientation == Vertical) {
		auto max = std::max_element(_content.begin(), _content.end(),
		                            [](IInteractableGraphics *a, IInteractableGraphics *b) -> bool {
			                            return a->GetWidth() < b->GetWidth();
		                            });
		return (*max)->GetWidth();
	} else {
		float width = 0;
		for (auto i = _content.begin(); i != _content.end(); i++) {
			width += (*i)->GetWidth();
		}
		return width;
	}
}
float BoxLayout::GetHeight () const {
	if (_orientation == Vertical) {
		float height = 0;
		for (auto i = _content.begin(); i != _content.end(); i++) {
			height += (*i)->GetHeight();
		}
		return height;
	} else {
		auto max = std::max_element(_content.begin(), _content.end(),
		                            [](IInteractableGraphics *a, IInteractableGraphics *b) -> bool {
			                            return a->GetHeight() < b->GetHeight();
		                            });
		return (*max)->GetHeight();
	}
}
void BoxLayout::Draw (sf::RenderTarget& window, int windowX, int windowY) {
	float elementPos = 0;
	for (auto i = _content.begin(); i != _content.end(); i++) {
		if (_orientation == Vertical) {
			(*i)->Draw(window, windowX, windowY + elementPos);
			elementPos += (*i)->GetHeight();
		} else {
			(*i)->Draw(window, windowX + elementPos, windowY);
			elementPos += (*i)->GetWidth();
		}
	}
}

void BoxLayout::CheckMouseEvent (sf::Window& window, int windowX, int windowY) {
	float elementPos = 0;
	for (auto i = _content.begin(); i != _content.end(); i++) {
		if (_orientation == Vertical) {
			(*i)->CheckMouseEvent(window, windowX, windowY + elementPos);
			elementPos += (*i)->GetHeight();
		} else {
			(*i)->CheckMouseEvent(window, windowX + elementPos, windowY);
			elementPos += (*i)->GetWidth();
		}
	}
}