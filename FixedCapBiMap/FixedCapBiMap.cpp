#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>

// Theta(capacity)
FixedCapBiMap::FixedCapBiMap(int capacity) {
	if (capacity <= 0) {
		throw std::exception();
	}
	this->cap = capacity;
	this->nrElements = 0;
	this->elements = new TElem[capacity];
}

// Theta(1)
FixedCapBiMap::~FixedCapBiMap() {
	delete[] this->elements;
}

// Best case: Theta(1) - key is not present or has less than 2 values
// Worst case: Theta(n) - need to check all elements
// Overall: O(n)
bool FixedCapBiMap::add(TKey c, TValue v){
	if (this->nrElements == this->cap) {
		throw std::exception();
	}

	int count = 0;
	for (int i = 0; i < this->nrElements; i++) {
		if (this->elements[i].first == c) {
			count++;
			if (count == 2) {
				return false;
			}
		}
	}

	this->elements[this->nrElements] = std::make_pair(c, v);
	this->nrElements++;
	return true;
}

// Best case: Theta(1) - key found at first position
// Worst case: Theta(n) - need to check all elements
// Overall: O(n)
ValuePair FixedCapBiMap::search(TKey c) const{
	TValue first = NULL_TVALUE;
	TValue second = NULL_TVALUE;

	for (int i = 0; i < this->nrElements; i++) {
		if (this->elements[i].first == c) {
			if (first == NULL_TVALUE) {
				first = this->elements[i].second;
			} else {
				second = this->elements[i].second;
				break;
			}
		}
	}

	return std::make_pair(first, second);
}

// Best case: Theta(1) - pair found at first position
// Worst case: Theta(n) - pair not found or at the end
// Overall: O(n)
bool FixedCapBiMap::remove(TKey c, TValue v){
	for (int i = 0; i < this->nrElements; i++) {
		if (this->elements[i].first == c && this->elements[i].second == v) {
			this->elements[i] = this->elements[this->nrElements - 1];
			this->nrElements--;
			return true;
		}
	}
	return false;
}


// Theta(1)
int FixedCapBiMap::size() const {
	return this->nrElements;
}

// Theta(1)
bool FixedCapBiMap::isEmpty() const{
	return this->nrElements == 0;
}

// Theta(1)
bool FixedCapBiMap::isFull() const {
	return this->nrElements == this->cap;
}

FixedCapBiMapIterator FixedCapBiMap::iterator() const {
	return FixedCapBiMapIterator(*this);
}



