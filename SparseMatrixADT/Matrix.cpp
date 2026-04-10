#include "Matrix.h"
#include <exception>
using namespace std;

///Complexity:
///Best case: Θ(1)
///Average case: Θ(1)
///Worst case: Θ(1)
Matrix::Matrix(int nrLines, int nrCols) {
	this->nrL = nrLines;
	this->nrC = nrCols;
	this->size = 0;
	this->capacity = 2;
	this->elements = new triple[capacity];
}

///Complexity: (size = number of non-zero elements)
///Best case: Θ(size)
///Average case: Θ(size)
///Worst case: Θ(size)
Matrix::Matrix(const Matrix& other) {
	this->nrL = other.nrL;
	this->nrC = other.nrC;
	this->size = other.size;
	this->capacity = other.capacity;
	this->elements = new triple[this->capacity];
	for (int k = 0; k < this->size; k++)
		this->elements[k] = other.elements[k];
}

///Complexity: (size = number of non-zero elements)
///Best case: Θ(1) - self-assignment
///Average case: Θ(size)
///Worst case: Θ(size)
Matrix& Matrix::operator=(const Matrix& other) {
	if (this != &other) {
		this->nrL = other.nrL;
		this->nrC = other.nrC;
		this->size = other.size;
		this->capacity = other.capacity;
		delete[] this->elements;
		this->elements = new triple[this->capacity];
		for (int k = 0; k < this->size; k++)
			this->elements[k] = other.elements[k];
	}
	return *this;
}

///Complexity:
///Best case: Θ(1)
///Average case: Θ(1)
///Worst case: Θ(1)
int Matrix::nrLines() const {
	return this->nrL;
}

///Complexity:
///Best case: Θ(1)
///Average case: Θ(1)
///Worst case: Θ(1)
int Matrix::nrColumns() const {
	return this->nrC;
}

///Complexity: (size = number of non-zero elements)
///Best case: Θ(1) - element found at the beginning or array is empty
///Average case: Θ(size) - element in the middle or not found
///Worst case: Θ(size) - element at the end or not found
TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= this->nrL || j < 0 || j >= this->nrC) ///check if the position is valid(out of bounds or not)
		throw exception();
	for (int k = 0; k < this->size; k++)
		if (this->elements[k].line == i && this->elements[k].col == j)///find element on the position
			return this->elements[k].value;
	return NULL_TELEM;
}

///Complexity: (size = number of non-zero elements)
///Best case: Θ(1) - updating an existing element at the beginning
///Average case: O(size) - searching + potential shifting/resizing
///Worst case: Θ(size) - searching to end + shifting all elements or resizing
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= this->nrL || j < 0 || j >= this->nrC) ///check if the position is valid(out of bounds or not)
		throw exception();
	for (int k = 0; k < this->size; k++) {
		if (this->elements[k].line == i && this->elements[k].col == j) {
			TElem old = this->elements[k].value; // save old first
			if (e == 0) {
				// shift left to delete
				for (int l = k; l < this->size - 1; l++)
					this->elements[l] = this->elements[l + 1];
				this->size--;
			}
			else {
				this->elements[k].value = e; // update value
			}
			return old;
		}
	}
	// triple not found, e != 0 → insert
	if (e != 0) {
		// resize if full
		if (this->size == this->capacity) {
			this->capacity *= 2;
			triple* newArr = new triple[this->capacity];
			for (int k = 0; k < this->size; k++)
				newArr[k] = this->elements[k];
			delete[] this->elements;
			this->elements = newArr;
		}
		// find insertion position (lexicographic order)
		int pos = 0;
		while (pos < this->size &&
			(this->elements[pos].line < i ||
				(this->elements[pos].line == i && this->elements[pos].col < j)))
			pos++;
		// shift right to make room
		for (int k = this->size; k > pos; k--)
			this->elements[k] = this->elements[k - 1];
		// insert
		this->elements[pos] = { i, j, e };
		this->size++;
	}
	return NULL_TELEM;
}

///Complexity:
///Best case: Θ(1)
///Average case: Θ(1)
///Worst case: Θ(1)
Matrix::~Matrix() {
	delete[] elements;
}