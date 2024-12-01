#include <iostream>
#include <memory>

enum Color {Red, Black};

struct RBNode {
    int data;
    std::shared_ptr<RBNode> left;
    std::shared_ptr<RBNode> right;
    std::shared_ptr<RBNode> parent;
    Color color;

    RBNode(int data, std::shared_ptr<RBNode> l = nullptr, std::shared_ptr<RBNode> r = nullptr,
        std::shared_ptr<RBNode> p = nullptr, Color c = Red): left(std::move(l)), right(std::move(r)),
    parent(std::move(p)), color(c) {
    }

    void print() const {
        std::cout << data << std::endl;
        std::cout << (color == Black ? "BLACK" : "RED") << std::endl;
    }

    void ReColor() {
        (color == Black ? color = Red : color = Black);
    }

};

class RBTree {
private:
    std::shared_ptr<RBNode> root;
public:
    explicit RBTree(std::shared_ptr<RBNode> root = nullptr) : root(std::move(root)) {}

    std::shared_ptr<RBNode> search(int elem) {
        // binary search tree searh implemented

    };

    void bstInsert(int elem) {

    }

    void insertFixup(std::shared_ptr<RBNode> node) {
        while (node->parent->color == Red) {
            if (node->parent == node->parent->parent->left) {
                auto temp = node->parent->parent->right;
                if (temp -> color == Red) {
                    node->parent->color = Black;
                    temp->color = Black;
                    node->parent->parent->color = Red;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = Black;
                    node->parent->parent->color = Red;
                    rightRotate(node->parent->parent);
                }
            } else {

            }
        }
        this->root->color = Black;
    }

    void leftRotate(std::shared_ptr<RBNode> node) {
        std::shared_ptr<RBNode> temp = node->right;
        node->right = temp->left;

        if (temp->left != node) {
            temp->left->parent = node;
        }
        temp->parent = node->parent;
        if (node->parent == this->root) {
            this->root = temp;
        } else if (node == node->parent->left) {
            node->parent->left = temp;
        } else {
            node->parent->right = temp;
        }
        temp->left = node;
        node->parent = temp;
    }

    void rightRotate(std::shared_ptr<RBNode> node) {
        // TODO
    }

};