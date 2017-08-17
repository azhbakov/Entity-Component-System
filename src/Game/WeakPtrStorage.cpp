#include "WeakPtrStorage.hpp"

#include <memory>
#include <vector>
#include <iostream>

#ifdef ENABLE_LOG
	#include "Logger.hpp"
#endif

using namespace un;
using namespace std;
//
//template<class T>
//void WeakPtrStorage<T>::AddPointer (std::weak_ptr<T> pointer) {
//	if (pointer.expired()) {
//		cerr << "Error! Adding expired pointer to " + _storageName + " storage!" << endl;
//		LOG ({"WeakPtrStorage", "Error"}, "Adding expired pointer to " + _storageName + " storage!");
//		return;
//	}
//
//	_content.push_back (pointer);
//}
//
//template<class T>
//void WeakPtrStorage<T>::RemoveExpired () {
//	for (auto it = _content.begin(); it != _content.end(); ) {
//		if (it->expired()) {
//			_content.erase(it);
//			LOG({"WeakPtrStorage"}, "Removed expired pointer from storage " + _storageName);
//			continue;
//		}
//		it++;
//	}
//
//}
//
//template<class T>
//void WeakPtrStorage<T>::Clear () {
//	_content.clear();
//	LOG ({"WeakPtrStorage"}, "Storage " + _storageName + " cleared");
//}