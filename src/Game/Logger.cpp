#include "Logger.hpp"

#if DEBUG_PRINT == 1
	#include <iostream>
#endif

#include <ostream>
#include <sstream>

using namespace un;
using namespace std;

Logger& Logger::Instance () {
	static Logger _logger;
	return _logger;
}

void Logger::Log (vector<string> tags, string message) {
	_events.emplace_back (tags, message);

	#ifdef DEBUG_PRINT
		cout << _events.back().ToString() << endl;
	#endif
}

void Logger::Print (ostream& o) {
	int counter = 0;
	for (LoggerEvent e : _events) {
		o << counter << ":  " << e.ToString() << endl;
		counter++;
	}
}

string LoggerEvent::ToString () const {
	stringstream ss;

	ss << "[";
	for (auto it = _tags.begin(); it < _tags.end(); it++) {
		ss << (*it);
		if (it != _tags.end()-1) {
			ss << ", ";
		}
	}
	ss << "]: " << _message;
	return ss.str();
}