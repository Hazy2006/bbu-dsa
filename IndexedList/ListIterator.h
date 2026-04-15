#pragma once
#include "IndexedList.h"


class ListIterator{
    //DO NOT CHANGE THIS PART
	friend class IndexedList;
private:
	const IndexedList& list;
    IndexedList::DLLNode* currentNode;

    ListIterator(const IndexedList& list);  // Change 'lista' to 'list'
public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;

};

