#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <ostream>

#define SIMPLE_LOGGER

#define LOG Logger::Instance().Log

namespace un {

	class LoggerEvent {
		private:
			const std::vector<std::string> _tags;
			const std::string _message;
		public:
			LoggerEvent (std::vector<std::string> tags, std::string message) : _tags(tags), _message(message) {}
			~LoggerEvent () {}

			const std::vector<std::string>& GetTags () const {
				return _tags;
			}

			const std::string& GetMessage () const {
				return _message;
			}

			std::string ToString () const;
	};

	class Logger {
		private:
			Logger () {};
			Logger (const Logger&) = delete;
			Logger& operator= (const Logger&) = delete;
			~Logger () {};

			std::vector<LoggerEvent> _events;

		public:
			static Logger& Instance ();

			void Log (std::vector<std::string> tags, std::string message);
			void Print (std::ostream& o);
	};
}

#endif