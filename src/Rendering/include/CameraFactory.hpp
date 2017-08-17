#pragma once

#include "Game.hpp"
#include "ICamera.hpp"

namespace un {
	class CameraFactory {
		public:
			template<class CameraClass, typename... Args>
			static CameraClass Instantiate (Args&&... args) {
				CameraClass& newCamera = CameraClass (args...);
				Game::Instance().RegisterCamera(newCamera);
			}
	}
}