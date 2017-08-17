#pragma once

#include <memory>
#include <vector>
#include <string>
#include <iostream>

#ifdef ENABLE_LOG
	#include "Logger.hpp"
#endif

namespace un {

	template<class T>
	class WeakPtrStorage {
		private:
			std::string _storageName;
			std::vector<std::weak_ptr<T>> _content;
		public:
			WeakPtrStorage (std::string storageName = "")
				: _storageName(storageName) {}
			~WeakPtrStorage () {}

			std::vector<std::weak_ptr<T>>* operator->() { return &_content; }
			std::vector<std::weak_ptr<T>>& operator*() { return _content; }
			
			void AddPointer (std::weak_ptr<T> pointer) {
				if (pointer.expired()) {
					std::cerr << "Error! Adding expired pointer to " + _storageName + " storage!" << std::endl;
					#ifdef SIMPLE_LOGGER
						LOG ({"WeakPtrStorage", "Error"}, "Adding expired pointer to " + _storageName + " storage!");
                    #endif
					return;
				}

				_content.push_back (pointer);
			}

			void RemoveExpired () {
				for (auto it = _content.begin(); it != _content.end(); ) {
					if (it->expired()) {
						_content.erase(it);
						#ifdef SIMPLE_LOGGER
							LOG({"WeakPtrStorage"}, "Removed expired pointer from storage " + _storageName);
                        #endif
						continue;
					}
					it++;
				}

			}
			void Clear () {
				_content.clear();
				#ifdef SIMPLE_LOGGER
					LOG ({"WeakPtrStorage"}, "Storage " + _storageName + " cleared");
                #endif
			}
	};

}