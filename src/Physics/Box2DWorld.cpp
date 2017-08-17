#include "Box2DWorld.hpp"
#include "Box2D/Box2D.h"

using namespace un;

b2World& Box2DWorld::Instance () {
	static b2World _instance (b2Vec2(0.0f, -10.0f));
	return _instance;
}

void Box2DWorld::Update () {
	Instance().Step (TIME_STEP, VELOCITY_ITER, POSITION_ITER);
}