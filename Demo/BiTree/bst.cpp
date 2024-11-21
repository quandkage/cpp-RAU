#include <iostream>
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

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
            if (val > tmp->data) {
                tmp = tmp->right;
            } else {
                tmp = tmp->left;
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
        newNode->parent = parent;

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
        if (!needToDelete->left && !needToDelete->right) {
            if (needToDelete->parent) {
                if (needToDelete->parent->left == needToDelete) {
                    needToDelete->parent->left = nullptr;
                } else {
                    needToDelete->parent->right = nullptr;
                }
            } else {
                head = nullptr;
            }
            delete needToDelete;
        }
        else if (!needToDelete->left || !needToDelete->right) {
            Node<T> *child = (needToDelete->left) ? needToDelete->left : needToDelete->right;

            if (needToDelete->parent) {
                if (needToDelete->parent->left == needToDelete) {
                    needToDelete->parent->left = child;
                } else {
                    needToDelete->parent->right = child;
                }
            } else {
                head = child;
            }

            if (child) {
                child->parent = needToDelete->parent;
            }

            delete needToDelete;
        }
        else {
            Node<T> *minNode = needToDelete->right;
            while (minNode->left) {
                minNode = minNode->left;
            }
            needToDelete->data = minNode->data;
            if (minNode->parent->left == minNode) {
                minNode->parent->left = minNode->right;
            } else {
                minNode->parent->right = minNode->right;
            }

            if (minNode->right) {
                minNode->right->parent = minNode->parent;
            }
            delete minNode;

        }
    }



    void remove (const T& elem) {
        if (Node<T> *nodeToDelete = search(elem)) {
            remove(nodeToDelete);
        }
        else {
            throw std::invalid_argument("Element not found");
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

    bst.insert(40);
    bst.insert(20);
    bst.insert(10);
    bst.insert(30);
    bst.insert(50);
    bst.insert(70);
    bst.insert(55);
    try {
        bst.remove(70);
        bst.remove(40);
        bst.remove(60);
    } catch (std::exception &e) {
        std::cout << RED << e.what() << RESET << std::endl;
        bst.printTree();
    }

}