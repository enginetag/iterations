#include <iostream>

using namespace std;

class Element {
public:
    int value;
    Element *next;

    Element() {
        value = 0;
        next = NULL;
    };

};


class Container {
public:
    virtual void insert(int value) = 0;

    virtual bool exists(int value) = 0;

    virtual void remove(int value) = 0;

    virtual void print() = 0;

    virtual ~Container() {};
};

class List : public Container {
private:
    Element *root;
    
    Element *create_list_element(int value) {
        Element *elem = new Element();
        elem->value = value;
        elem->next = NULL;
        return elem;
    };

    void insert_into_list(Element *root, Element *new_elem) {
        new_elem->next = root->next;
        root->next = new_elem;
    };

    void printer(struct Element *root) {
        while (root != NULL) {
            cout << root->value << endl;
            root = root->next;
        }
    };

    void delete_element(int value, Element *root) {
        Element *cur_elem, *pre_elem;
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

    void delete_list(Element *root) {
        Element *cur_elem, *next_elem;
        cur_elem = root;
        while (cur_elem->next != NULL) {
            next_elem = cur_elem->next;
            delete cur_elem;
            cur_elem = next_elem;
        }
        delete cur_elem;
    }

    Element *delete_root(Element *root) {
        Element *new_root;
        new_root = root->next;
        delete root;
        return new_root;
    }

    Element *change_root(Element *root, int value) {
        Element *new_root, *cur_elem;
        new_root = root;
        cur_elem = root;
        while (cur_elem->value != value) {
            new_root = cur_elem->next;
            delete cur_elem;
            cur_elem = new_root;
        }
        if (cur_elem == NULL) {
            cout << "No new root";
            return NULL;
        }
        return new_root;
    }

    Element *swap(Element *root, Element *new_root) {
        Element *pre_elem = root;
        while (pre_elem->next != new_root) pre_elem = pre_elem->next;
        pre_elem->next = new_root->next;
        new_root->next = root;
        return new_root;
    }


    Element *Delete_root() {
        return delete_root(root);
    }

    Element *Create_list_element(int value) {
        Element *elem = new Element();
        elem->value = value;
        elem->next = NULL;
        return elem;
    }

    Element *Change_root(int value) {
        return change_root(root, value);
    }

public:
    List() {
        this->root = NULL;
    }

    ~List() {
        delete_list(root);
    }

    void insert(int value) {
        if (root == NULL) {
            root = create_list_element(value);
        } else {
            insert_into_list(root, create_list_element(value));
        }
    }

    void print() {
        printer(root);
    }

    bool exists(int value) {
        Element *cur_elem = root;
        while (cur_elem->value != value) {
            if (cur_elem->next == NULL) return false;
            cur_elem = cur_elem->next;
        }
        return true;
    }

    void remove(int value) {
        if (value == root->value) {
            Element *e = root;
            root = root->next;
            delete e;
        } else {
            delete_element(value, root);
        }
    }
};

int main() {
    Container *c = new List();

    for (int i = 1; i < 10; i++)
        c->insert(i * i);

    cout << "Container after creation:" << endl;
    c->print();

    if (c->exists(25))
        cout << "Search for value 25: found" << endl;

    if (!c->exists(111))
        cout << "Search for value 111: not found" << endl;

    c->remove(25);
    cout << "Container after deletion of the element:" << endl;
    c->print();

    delete c;
    return 0;
}