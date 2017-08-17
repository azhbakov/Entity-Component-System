#include <string>

namespace un {

	class UnException {
		private:
			std::string _message;
		public:
			UnException (std::string message) : _message(message) {} 
			std::string what () { return _message; }
	};

}