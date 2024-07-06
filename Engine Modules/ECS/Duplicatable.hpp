#ifndef __DUPLICATABLE_H__
#define __DUPLICATABLE_H__

#include <iostream>

struct Duplicatable {
	virtual ~Duplicatable() = default;

	virtual std::unique_ptr<Duplicatable> duplicate() {
		return std::unique_ptr<Duplicatable>(new Duplicatable());
	}

	//// turns a unique_ptr of type Duplicatable to a unique_ptr of type T.
	//// used to assist in duplicating children of Duplicatable, so that manual conversion is not needed
	//template <class T>
	//static std::unique_ptr<T> convertDuplicatePointerToType(std::unique_ptr<Duplicatable> duplicatablePtr) {
	//	// get the raw pointer behind the duplicatablePtr
	//	Duplicatable* rawPointer = duplicatablePtr.get();
	//	// release the duplicatablePtr
	//	duplicatablePtr.release();
	//	// create a new unique_ptr of type T with the rawPointer we just got
	//	return std::unique_ptr<T>(static_cast<T*>(rawPointer));
	//}
};

#endif
