#pragma once
#include "Box2D/Box2D.h"

#define TIME_STEP 1.0f / 60.0f
#define VELOCITY_ITER 6
#define POSITION_ITER 2

namespace un {

	class Box2DWorld {
		private:
			//b2World& _instance;
			Box2DWorld () {}
			Box2DWorld (const Box2DWorld& b) = delete;
			Box2DWorld& operator= (const Box2DWorld& b) = delete;
			~Box2DWorld () {}

		public:
			static b2World& Instance ();
			static void Update ();

	};

}