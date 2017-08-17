#include "PhysicsSubsystem.hpp"
#include "PhysicsBody.hpp"
#include "Game.hpp"
#include "Box2D/Box2D.h"

#ifdef ENABLE_LOG
	#include "Logger.hpp"
#endif

using namespace un;
using namespace std;

#define EPS 0.00001

void PhysicsBody::Start () {
	_ps.RegisterPhysicsBody (GetSelf());
}

bool PhysicsBody::IsSync () {
	b2Vec2 boxPos = _body->GetPosition();
	Transform& goTransform = GetTransform();
	if (fabs(boxPos.x - goTransform.X()) > EPS ||
		fabs(boxPos.y - goTransform.Y() > EPS)) {
		return false;
	}
	if (abs(_body->GetAngle() - goTransform.Rotation()) > EPS) {
		return false;
	}
	return true;
}

void PhysicsBody::SyncBoxToBody () {
	b2Vec2 pos = _body->GetPosition();
	GetTransform().SetPosition (pos.x, pos.y);
	GetTransform().SetRotation (_body->GetAngle());
}

void PhysicsBody::SyncBodyToBox () {
	Transform& t = GetTransform();
	_body->SetTransform(b2Vec2(t.X(), t.Y()), t.Rotation());
}

void PhysicsBody::PreUpdatePhysics () {
	if (IsSync()) { return; }
	SyncBodyToBox ();

	#ifdef SIMPLE_LOGGER
		LOG ({"Component", "Physics"}, "Detected gamelogical position update for " + ToString() + ", physics position updated.");
	#endif
}

void PhysicsBody::PostUpdatePhysics () {
	SyncBoxToBody ();

	#ifdef SIMPLE_LOGGER
		LOG ({"Component", "Physics"}, "Updated transform position for " + ToString() + " after physics update.");
	#endif
}