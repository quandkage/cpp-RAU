#include <iostream>
#include <stack>
#include <memory>

template <typename T>
struct TreeNode {
    T data;
    std::shared_ptr<TreeNode<T>> left;
    std::shared_ptr<TreeNode<T>> right;
    explicit TreeNode(const T& data) : data(data), left(nullptr), right(nullptr) {}
};

template <typename T>
void postorder(std::shared_ptr<TreeNode<T>> root) {
    if (root == nullptr) {
        return;
    }

    std::stack<std::shared_ptr<TreeNode<T>>> st1;
    std::stack<std::shared_ptr<TreeNode<T>>> st2;
    st1.push(root);

    while (!st1.empty()) {
        std::shared_ptr<TreeNode<T>> temp = st1.top();
        st1.pop();
        st2.push(temp);

        if (temp->left) {
            st1.push(temp->left);
        }

        if (temp->right) {
            st1.push(temp->right);
        }
    }
    while (!st2.empty()) {
        std::cout << st2.top()->data << " ";
        st2.pop();
    }
}

int main() {
    std::shared_ptr<TreeNode<char>> root = std::make_shared<TreeNode<char>>('A');
    root->left = std::make_shared<TreeNode<char>>('B');
    root->right = std::make_shared<TreeNode<char>>('C');
    root->left->left = std::make_shared<TreeNode<char>>('D');
    root->right->left = std::make_shared<TreeNode<char>>('E');
    root->right->right = std::make_shared<TreeNode<char>>('F');
    root->right->left->right = std::make_shared<TreeNode<char>>('G');
    root->right->right->left = std::make_shared<TreeNode<char>>('H');
    root->right->right->right = std::make_shared<TreeNode<char>>('I');
    postorder(root);

    return 0;
}
