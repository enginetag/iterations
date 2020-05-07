//
// Created by admin on 07.05.2020.
//

#ifndef CLASS_D_LIST_H
#define CLASS_D_LIST_H

#include <iostream>

using namespace std;

template<typename T>
class Element {
public:
    T value;
    Element<T> *next;

    Element() {
        next = NULL;
    };

};


template<typename T>
class Container {
public:
    // Виртуальный деструктор
    virtual ~Container();

    /*
     * Виртуальные методы, должны быть реализованы вашим контейнером
     */

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

    Element<T> *create_list_element(const T &value) {
        Element<T> *elem = new Element<T>();
        elem->value = value;
        elem->next = NULL;
        return elem;
    };

    void insert_into_list(Element<T> *root, Element<T> *new_elem) {
        new_elem->next = root->next;
        root->next = new_elem;
    };

    void printer(struct Element<T> *root) {
        while (root != NULL) {
            cout << root->value << endl;
            root = root->next;
        }
    };

    void delete_element(const T &value, Element<T> *root) {
        Element<T> *cur_elem, *pre_elem;
        pre_elem = root;
        cur_elem = root;
        while (cur_elem->value != value) {
            if ((cur_elem->next == NULL) & (cur_elem->value != value)) {
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

    void delete_list(Element<T> *root) {
        Element<T> *cur_elem, *next_elem;
        cur_elem = root;
        while (cur_elem->next != NULL) {
            next_elem = cur_elem->next;
            delete cur_elem;
            cur_elem = next_elem;
        }
        delete cur_elem;
    }

public:
    List() {
        this->root = NULL;
    }

    ~List() {
        delete_list(root);
    }

    void insert(const T& value) override{
        if (root == NULL) {
            root = create_list_element(value);
        } else {
            insert_into_list(root, create_list_element(value));
        }
    }

    void print(){
        printer(root);
    }

    bool exists(const T &value) const override{
        Element<T> *cur_elem = root;
        while (cur_elem->value != value) {
            if (cur_elem->next == NULL)
                return false;
            cur_elem = cur_elem->next;
        }
        return true;
    }

    void remove(const T &value) override{
        if (value == root->value) {
            Element<T> *e = root;
            root = root->next;
            delete e;
        } else {
            delete_element(value, root);
        }
    }
};


#endif //CLASS_D_LIST_H
