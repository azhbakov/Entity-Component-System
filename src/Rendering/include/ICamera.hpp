#pragma once

#include <string>
#include <vector>

#include "IRenderer.hpp"

namespace un {

	class ICamera {
		public:
			virtual ~ICamera() {}
			virtual void UpdateCamera (std::vector<std::weak_ptr<IRenderer>>::iterator begin, std::vector<std::weak_ptr<IRenderer>>::iterator end) = 0;
			virtual std::string ToString () = 0;
	};

}