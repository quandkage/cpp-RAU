#include <iostream>
#include <memory>
#define NIL nullptr

enum Color { Red, Black };

struct RBNode {
    int data;
    std::shared_ptr<RBNode> left;
    std::shared_ptr<RBNode> right;
    std::shared_ptr<RBNode> parent;
    Color color;

    explicit RBNode(int data, std::shared_ptr<RBNode> l = NIL, std::shared_ptr<RBNode> r = NIL,
        std::shared_ptr<RBNode> p = NIL, const Color c = Red)
        : data(data), left(std::move(l)), right(std::move(r)), parent(std::move(p)), color(c) {}

    void print() const {
        std::cout << data << " (" << (color == Black ? "BLACK" : "RED") << ")" << std::endl;
    }

    void ReColor() {
        (color == Black ? color = Red : color = Black);
    }
};

class RedBlackTree {
private:
    std::shared_ptr<RBNode> root = NIL;

public:
    explicit RedBlackTree(std::shared_ptr<RBNode> r = NIL) : root(std::move(r)) {}

    void search(int elem) const {
        std::shared_ptr<RBNode> current = root;
        while (current) {
            if (elem < current->data) {
                current = current->left;
            } else if (elem > current->data) {
                current = current->right;
            } else {
                std::cout << "Found Element: " << current->data << std::endl;
                return;
            }
        }
        std::cout << "Element not found!" << std::endl;
    }

    void bstInsert(int elem) {
        std::shared_ptr<RBNode> parent = NIL;
        std::shared_ptr<RBNode> current = root;

        while (current) {
            parent = current;
            if (elem < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        std::shared_ptr<RBNode> new_node = std::make_shared<RBNode>(elem);
        new_node->parent = parent;

        if (!parent) {
            root = new_node;
        } else if (elem < parent->data) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        new_node->color = Red;
    }

    void insert(int elem) {
        bstInsert(elem);
        std::shared_ptr<RBNode> x = root;
        instertFixup(x);
    }

    void instertFixup(std::shared_ptr<RBNode> p) {
        while (p->parent && p->parent->color == Red) {
            if (p->parent == p->parent->parent->left) {
                std::shared_ptr<RBNode> uncle = p->parent->parent->right;
                if (uncle && uncle->color == Red) {
                    p->parent->ReColor();
                    uncle->ReColor();
                    p->parent->parent->ReColor();
                    p = p->parent->parent;
                } else {
                    if (p == p->parent->right) {
                        p = p->parent;
                        leftRotate(p);
                    }
                    p->parent->ReColor();
                    p->parent->parent->ReColor();
                    rightRotate(p->parent->parent);
                }
            } else {
                std::shared_ptr<RBNode> uncle = p->parent->parent->left;
                if (uncle && uncle->color == Red) {
                    p->parent->ReColor();
                    uncle->ReColor();
                    p->parent->parent->ReColor();
                    p = p->parent->parent;
                } else {
                    if (p == p->parent->left) {
                        p = p->parent;
                        rightRotate(p);
                    }
                    p->parent->ReColor();
                    p->parent->parent->ReColor();
                    leftRotate(p->parent->parent);
                }
            }
        }
        root->ReColor();
    }

    void leftRotate(std::shared_ptr<RBNode> p) {
        std::shared_ptr<RBNode> tmp = p->right;
        p->right = tmp->left;

        if (tmp->left) {
            tmp->left->parent = p;
        }

        tmp->parent = p->parent;

        if (!p->parent) {
            root = tmp;
        } else if (p == p->parent->left) {
            p->parent->left = tmp;
        } else {
            p->parent->right = tmp;
        }

        tmp->left = p;
        p->parent = tmp;
    }

    void rightRotate(std::shared_ptr<RBNode> p) {
        std::shared_ptr<RBNode> tmp = p->left;
        p->left = tmp->right;

        if (tmp->right) {
            tmp->right->parent = p;
        }

        tmp->parent = p->parent;

        if (!p->parent) {
            root = tmp;
        } else if (p == p->parent->left) {
            p->parent->left = tmp;
        } else {
            p->parent->right = tmp;
        }

        tmp->right = p;
        p->parent = tmp;
    }

    void printRB() {
        inorderTVS(root);
    }

private:
    void inorderTVS(std::shared_ptr<RBNode> node) const {
        if (node) {
            inorderTVS(node->left);
            node->print();
            inorderTVS(node->right);
        }
    }
};

int main() {
    RedBlackTree tree(NIL);
    tree.insert(7);
    tree.insert(11);
    tree.insert(4);
    tree.insert(9);
    tree.insert(8);
    tree.insert(10);
    tree.insert(18);
    tree.insert(19);
    tree.insert(22);
    tree.insert(20);
    tree.insert(3);
    tree.insert(6);
    tree.insert(5);
    tree.insert(2);
    tree.printRB();
}
