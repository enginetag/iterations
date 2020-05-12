//
// Created by admin on 07.05.2020.
//

#ifndef LIST_H
#define LIST_H

#include <iostream>

using namespace std;

template<typename T>
class Element {
public:
    T value;
    Element<T> *next;

    Element() : next(nullptr) {}

    Element(T v) : value(v), next(nullptr) {}

    Element(T v, Element<T> *n) : value(v), next(n) {}
};

class Exception : public runtime_error {
public:
    Exception() : runtime_error("segmentation_fault") {
    }
};

template<typename T>
class ListIterator {
private:
    Element<T> *p;
public:
    using iterator_category = forward_iterator_tag;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using difference_type = ptrdiff_t;

    ListIterator() : p(nullptr) {
    }

    ListIterator(Element<T> *e) : p(e) {}

    T &operator*() const {
        if (p == nullptr)
            throw Exception();
        return p->value;
    }

    ListIterator &operator++() {
        if (p == nullptr) {
            throw Exception();
        }
        p = p->next;
        return *this;
    }

    ListIterator operator++(int) {
        p = p->next;
        return *this;
    }

    bool operator==(const ListIterator &it) const {
        return p == it.p;
    }

    bool operator!=(const ListIterator &it) const {
        return !(*this == it);
    }
};

template<typename T>
class Container {
public:
    // Виртуальный деструктор
    virtual ~Container() = default;

    // Вставка элемента
    virtual void insert(const T &value) = 0;

    // Удаление элемента
    virtual void remove(const T &value) = 0;

    // Проверка наличия элемента
    virtual bool exists(const T &value) const = 0;
};

template<typename T>
class List : public Container<T> {
private:
    Element<T> *root;

    void delete_element(const T &value) {
        Element<T> *cur_elem, *pre_elem;
        pre_elem = root;
        cur_elem = root;
        while (cur_elem->value != value) {
            if ((cur_elem->next == nullptr) & (cur_elem->value != value)) {
                return;
            }
            cur_elem = cur_elem->next;
        }
        while (pre_elem->next != cur_elem) {
            pre_elem = pre_elem->next;
        }
        pre_elem->next = cur_elem->next;
        delete cur_elem;
    }

    void delete_list() {
        for (auto p = root; p != nullptr;) {
            auto t = p;
            p = p->next;
            delete (t);
        }
    }

    void copyOf(const List &src) {
        Element<T> *p = nullptr;
        for (auto t = src.root; t != nullptr; t = t->next) {
            auto n = new Element<T>(t->value);
            if (p != nullptr) {
                p->next = n;
            } else {
                this->root = n;
            }
            p = n;
        }
    }

public:
    List() {
        this->root = nullptr;
    }

    List(const List &src) {
        copyOf(src);
    }

    using iterator = ListIterator<T>;
    using const_iterator = ListIterator<const T>;

    iterator begin() const {
        return ListIterator<T>(root);
    };

    iterator end() const {
        return ListIterator<T>(nullptr);
    };

    const_iterator const_begin() const {
        return ListIterator<T>(root);
    };

    const_iterator const_end() const {
        return ListIterator<const T>(nullptr);
    };

    List &operator=(const List &src) {
        if (this == &src) {
            return *this;
        }
        delete_list();
        copyOf(src);
        return *this;
    }

    ~List() {
        delete_list();
    }

    void insert(const T &value) override {
        if (root == nullptr) {
            root = new Element<T>(value);               // create_list_element(value);
        } else {
            root = new Element<T>(value, root);         // insert_into_list(root, create_list_element(value));
        }
    }

    bool exists(const T &value) const override {
        Element<T> *cur_elem = root;
        if (root == nullptr) {
            return false;
        }
        while (cur_elem->value != value) {
            if (cur_elem->next == nullptr)
                return false;
            cur_elem = cur_elem->next;
        }
        return true;
    }

    void remove(const T &value) override {
        if (root == nullptr) {
            return;
        }
        if (value == root->value) {
            Element<T> *e = root;
            root = root->next;
            delete e;
        } else {
            delete_element(value);
        }
    }
};


#endif //LIST_H
