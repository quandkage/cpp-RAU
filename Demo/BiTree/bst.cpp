#include <iostream>

template<class T>
class Node {
public:
    T data;
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;

    Node(T d, Node<T> *l = nullptr, Node<T> *r = nullptr, Node<T> *p = nullptr) : data(d), left(l), right(r),
                                                                                  parent(p) {}

    T operator*() {
        return data;
    }

    bool operator<(const Node<T> &other) {
        return data < other.data;
    }
};

template<class U>
class AbstractBinaryTree {
public:
    virtual Node<U> *search(U val) = 0;

    virtual void insert(Node<U> *val) = 0;

    virtual void remove(Node<U> *val) = 0;
};

template<class T>
class BinarySearchTree : public AbstractBinaryTree<T> {
private:
    Node<T> *head = nullptr;

    void delete_(Node<T> *val) {
        if (val == nullptr) {
            return;
        }
        delete_(val->left);
        delete_(val->right);

        delete val;
    }
public:
    Node<T> *search(T val) override {
        Node<T> *tmp = head;

        while (tmp) {
            if (tmp->data == val) {
                return tmp;
            }
            if (tmp->data < head->data) {
                tmp = tmp->left;
            } else if (tmp->data > head->data) {
                tmp = tmp->right;
            }
        }
        return nullptr;
    }

    void insert(Node<T> *newNode) override {
        if (!head) {
            head = newNode;
            return;
        }

        Node<T> *tmp = head;
        Node<T> *parent = nullptr;

        while (tmp) {
            parent = tmp;

            if (newNode->data > tmp->data) {
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
            }
        }

        if (parent->data > newNode->data) {

            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    void insert(T newVal) {
        Node<T> *newNode = new Node<T>(newVal);
        insert(newNode);
    }

    void remove(Node<T> *needToDelete) override {
        // case 1 -  տերև է
        if (!needToDelete->left && !needToDelete->right) {
            if (needToDelete->parent->left == needToDelete) {
                needToDelete->parent->left = nullptr;
            } else {
                needToDelete->parent->right = nullptr;
            }
            delete needToDelete;
        }
            // case 2 - ունի մեկ որդի
        else if (!needToDelete->left || !needToDelete->right) {
            Node<T> *child = (needToDelete->left) ? needToDelete->left : needToDelete->right;

            if (!needToDelete->left) {
                if (needToDelete->parent->right == needToDelete) {
                    needToDelete->parent->right = child;
                } else {
                    needToDelete->parent->left = child;
                }
                if (child) {
                    child->parent = needToDelete->parent;
                }
                delete needToDelete;
            }
            else {
                if (needToDelete->parent->left == needToDelete) {
                    needToDelete->parent->left = needToDelete->left;
                } else {
                    needToDelete->parent->right = needToDelete->left;
                }
                delete needToDelete;
            }
        }
            // case 3 - ունի երկու որդի
        else {
            if (needToDelete->parent->left == needToDelete) {
                needToDelete->parent->left = treeMin(needToDelete->right);
            } else {
                needToDelete->parent->right = treeMin(needToDelete->left);
            }
        }
    }

    Node<T> *successor(Node<T> *val) {
        if (!val) {
            return nullptr;
        }
        if (val->right) {
            return treeMin(val->right);
        }

        Node<T> *parent = val->parent;

        while (parent && parent->right == val) {
            val = parent;
            parent = parent->parent;
        }
        return parent;
    }
    T min () const {
        if (!head) {
            throw std::invalid_argument("Empty Tree");
        }
        Node<T> *val = treeMin(head);
        return val->data;
    }
    Node<T> *treeMin(Node<T> *node) const {
        if (!node) {
            return nullptr;
        }
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    void inorderTreeWalk(Node<T> *x) const {
        if (x != nullptr) {
            inorderTreeWalk(x->left);
            std::cout << x->data << " ";
            inorderTreeWalk(x->right);
        }
    }

    void printTree() const {
        inorderTreeWalk(head);
        std::cout << std::endl;
    }

    ~BinarySearchTree() {
        delete_(head);
    }

};

int main() {

    BinarySearchTree<int> bst;

    // Insert nodes
    bst.insert(15);
    bst.insert(6);
    bst.insert(18);
    bst.insert(3);
    bst.insert(7);
    bst.insert(17);
    bst.insert(20);
    bst.insert(2);
    bst.insert(4);
    bst.insert(13);
    bst.insert(9);

    bst.printTree();

}