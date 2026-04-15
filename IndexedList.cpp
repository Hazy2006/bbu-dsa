#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"

IndexedList::DLLNode* IndexedList::getNode(int pos) const {
    if (pos < 0 || pos >= nrElem)
        return nullptr;
    DLLNode* curr = head;
    for (int i = 0; i < pos; i++)
        curr = curr->next;
    return curr;
}

IndexedList::IndexedList() : head(nullptr), tail(nullptr), nrElem(0)
{}

IndexedList::IndexedList(const IndexedList& other) : head(nullptr), tail(nullptr), nrElem(0)
{
    DLLNode* curr = other.head;
    while (curr != nullptr) {
        addToEnd(curr->info);
        curr = curr->next;
    }
}


IndexedList& IndexedList::operator=(const IndexedList& other)
{
    if (this == &other)
        return *this;
    //destroy current content
    while (head != nullptr)
    {
        DLLNode* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
    nrElem = 0;
    //copy from other
    DLLNode* curr = other.head;
    while (curr != nullptr) {
        addToEnd(curr->info);
        curr = curr->next;
    }
    return *this;
}

int IndexedList::size() const {
    return nrElem;  
}


bool IndexedList::isEmpty() const {
    return nrElem == 0;
}

TElem IndexedList::getElement(int pos) const {
    DLLNode* node = getNode(pos);
    if (node == nullptr)
        throw std::exception();
    return node->info;
}

TElem IndexedList::setElement(int pos, TElem e) {
    DLLNode* node = getNode(pos);
    if (node == nullptr)
        throw std::exception();
    TElem old = node->info;
    node->info = e;
    return old;
}

void IndexedList::addToEnd(TElem e) {
    DLLNode* newNode = new DLLNode(e);
    if (tail == nullptr) {
        //list is empty
        head = newNode;
        tail = newNode;
    }
    else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
    nrElem++;
}

void IndexedList::addToPosition(int pos, TElem e) {
    if (pos < 0 || pos > nrElem)
        throw std::exception();

    if (pos == nrElem) {
        addToEnd(e);
        return;
    }

    DLLNode* newNode = new DLLNode(e);
    if (pos == 0) {
        newNode->next = head;
        if (head != nullptr)
            head->prev = newNode;
        head = newNode;
        if (tail == nullptr)
            tail = newNode;
    }
    else
    {
        DLLNode* curr = getNode(pos);
        DLLNode* prevNode = curr->prev;
        newNode->next = curr;
        newNode->prev = prevNode;
        prevNode->next = newNode;
        curr->prev = newNode;
    }
    nrElem++;
}

TElem IndexedList::remove(int pos) {
    DLLNode* node = getNode(pos);
    if (node == nullptr)
        throw std::exception();
    TElem val = node->info;
    //rewire prev side
    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        head = node->next; //removing head
    if (node->next != nullptr)
        node->next->prev = node->prev;
    else
        tail = node->prev; //removing tail
    delete node;
    nrElem--;
    return val;
}

int IndexedList::search(TElem e) const{
    DLLNode* curr = head;
    int pos = 0;
    while (curr != nullptr) {
        if (curr->info == e)
            return pos;
        curr = curr->next;
        pos++;
    }
	return -1;
}

ListIterator IndexedList::iterator() const {
    return ListIterator(*this);        
}

IndexedList::~IndexedList() {
    while (head != nullptr)
    {
        DLLNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}