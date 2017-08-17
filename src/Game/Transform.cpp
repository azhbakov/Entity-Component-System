#include "Transform.hpp"

#include <sstream>
#include <string>

using namespace std;
using namespace un;

void Transform::SetPosition (float x, float y) {
	_x = x;
	_y = y;
}

void Transform::Translate (float x, float y) {
	_x += x;
	_y += y;
}

string Transform::ToString () {
	stringstream ss;
	ss << "[" << "x: " << _x << ", y: " << _y << ", r: " << _r << "]";
	return ss.str();
}