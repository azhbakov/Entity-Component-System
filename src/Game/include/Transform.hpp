#ifndef TRANSFORM_HPP
#define TRANSFORM_HPP

#include <string>

namespace un {
	
	class Transform final {
		private:
			float _x;
			float _y;

			float _r;
		public:
			Transform () : _x(0), _y(0), _r(0) {}
			Transform (float x, float y) : Transform (x, y, 0.0f) {}
			Transform (float x, float y, float r) : _x(x), _y(y), _r(r) {}
			~Transform () {}

			void SetPosition (float x, float y);
			void SetRotation (float angle) { _r = angle; }
			void Translate (float x, float y);

			float X() const { return _x; }
			float Y() const { return _y; }
			float Rotation () const { return _r; };

			std::string ToString ();
	};

}

#endif