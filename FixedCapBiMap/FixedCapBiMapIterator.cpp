#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <exception>
using namespace std;


// Theta(1)
FixedCapBiMapIterator::FixedCapBiMapIterator(const FixedCapBiMap& d) : map(d)
{
	this->currentPos = 0;
}


// Theta(1)
void FixedCapBiMapIterator::first() {
	this->currentPos = 0;
}


// Theta(1)
void FixedCapBiMapIterator::next() {
	if (!this->valid()) {
		throw std::exception();
	}
	this->currentPos++;
}


// Theta(1)
TElem FixedCapBiMapIterator::getCurrent(){
	if (!this->valid()) {
		throw std::exception();
	}
	return this->map.elements[this->currentPos];
}


// Theta(1)
bool FixedCapBiMapIterator::valid() const {
	return this->currentPos >= 0 && this->currentPos < this->map.nrElements;
}



