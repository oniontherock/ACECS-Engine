#include "Duplicatable.hpp"

std::unique_ptr<Duplicatable> Duplicatable::duplicate() {
	std::cerr << "ERROR: duplicate called on base " << "Duplicatable " << "class, downcasting from this duplicate may fail." << std::endl;
	return std::unique_ptr<Duplicatable>(new Duplicatable());
}

Duplicatable* Duplicatable::duplicateAndGetRaw(Duplicatable* objectToDuplicate) {
	std::unique_ptr<Duplicatable> duplicatablePtr = objectToDuplicate->duplicate();

	Duplicatable* rawPointer = duplicatablePtr.get();

	duplicatablePtr.release();

	return rawPointer;
}

Duplicatable* Duplicatable::duplicateAndGetRaw(Duplicatable& objectToDuplicate) {
	std::unique_ptr<Duplicatable> duplicatablePtr = objectToDuplicate.duplicate();

	Duplicatable* rawPointer = duplicatablePtr.get();

	duplicatablePtr.release();

	return rawPointer;
}