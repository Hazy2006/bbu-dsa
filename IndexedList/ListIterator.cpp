#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>

ListIterator::ListIterator(const IndexedList& list) : list(list){
    currentNode = list.head;
}

void ListIterator::first(){
    currentNode = list.head;
}

void ListIterator::next(){
    if (currentNode == nullptr)
        throw std::exception();
    currentNode = currentNode->next;
}

bool ListIterator::valid() const{
    return currentNode != nullptr;
}

TElem ListIterator::getCurrent() const{
    if (currentNode == nullptr)
        throw std::exception();
    return currentNode->info;
}