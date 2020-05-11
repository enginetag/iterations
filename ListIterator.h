//
// Created by admin on 09.05.2020.
//

#ifndef CLASS_D_LISTITERATOR_H
#define CLASS_D_LISTITERATOR_H

#include "List.h"

using namespace std;

/*
template <typename T>
class ListIterator {
private:
    Element *p;
public:
    using iterator_category = forward_iterator_tag;
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = ptrdiff_t;

    ListIterator() : p(nullptr) {
    }

    ListIterator(Element* el) : p(el) {
    }

    reference operator*() const{
        return p->value;
    }

    ListIterator&operator++() {
        p = p->next;
    }
    ListIterator operator++(int) {
        ListIterator resp = *this;
        p = p->next;
        return resp;
    }

    bool operator==(const ListIterator& it) const{
        return p == it.p;
    }
    bool operator!=(const ListIterator& it) const{
        return !(*this == it);
    }
};*/




#endif //CLASS_D_LISTITERATOR_H
