#include "BoxCollider.hpp"

#include <memory>
#include <cmath>

#include "GameObject.hpp"
#include "PhysicsSubsystem.hpp"
#include "Component.hpp"
#include "Box2DWorld.hpp"
#include "Box2D/Box2D.h"

using namespace un;
using namespace std;

BoxCollider::BoxCollider (weak_ptr<GameObject>& g, PhysicsSubsystem& ps, float width, float height, bool isDynamic)
	: PhysicsBody(g, ps) {
	
	Transform& transform = GetTransform();

	b2BodyDef bodyDef;
	if (isDynamic) {
		bodyDef.type = b2_dynamicBody;
	} else {
		bodyDef.type = b2_staticBody;
	}
	bodyDef.position.Set(transform.X(), transform.Y());

	_body = ps.GetWorld().CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(width/2.0f - width/100.0f, height/2.0f - height/100.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	_body->CreateFixture(&fixtureDef);
}

