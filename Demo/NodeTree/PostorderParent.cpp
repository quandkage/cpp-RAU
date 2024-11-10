#include <iostream>
#include <memory>

namespace PostorderParent {
    template <typename T>
    struct SaplingNode {
        T val;
        std::shared_ptr<SaplingNode> leftus;
        std::shared_ptr<SaplingNode> rightus;
        std::weak_ptr<SaplingNode> hopar;

        explicit constexpr SaplingNode() : val(std::declval<T>()), leftus(nullptr), rightus(nullptr), hopar() {}
        explicit constexpr SaplingNode(T val) : val(std::move(val)), leftus(nullptr), rightus(nullptr), hopar() {}
    };

    namespace Uzbek {
        template <typename T>
        void postorder(std::shared_ptr<SaplingNode<T>> root) {
            if (!root) return;

            std::shared_ptr<SaplingNode<T>> curr = root;
            std::shared_ptr<SaplingNode<T>> prev = nullptr;

            while (curr) {
                if (curr->leftus && prev != curr->leftus && prev != curr->rightus) {
                    curr = curr->leftus;
                }
                else if (curr->rightus && prev != curr->rightus) {
                    curr = curr->rightus;
                }
                else {
                    std::cout << curr->val << " ";
                    prev = curr;
                    curr = curr->hopar.lock();
                }
            }
        }
    }
}

int main() {
    char a = 'u';
    char b = 'z';
    char c = 'b';
    char d = 'e';
    char e = 'k';

    std::shared_ptr<PostorderParent::SaplingNode<decltype(a)>> root = std::make_shared<PostorderParent::SaplingNode<decltype(b)>>('A');
    root->leftus = std::make_shared<PostorderParent::SaplingNode<decltype(c)>>('B');
    root->rightus = std::make_shared<PostorderParent::SaplingNode<decltype(d)>>('C');
    root->leftus->leftus = std::make_shared<PostorderParent::SaplingNode<decltype(e)>>('D');
    root->rightus->leftus = std::make_shared<PostorderParent::SaplingNode<decltype(a)>>('E');
    root->rightus->rightus = std::make_shared<PostorderParent::SaplingNode<decltype(c)>>('F');
    root->rightus->leftus->rightus = std::make_shared<PostorderParent::SaplingNode<decltype(d)>>('G');
    root->rightus->rightus->leftus = std::make_shared<PostorderParent::SaplingNode<decltype(a)>>('H');
    root->rightus->rightus->rightus = std::make_shared<PostorderParent::SaplingNode<decltype(b)>>('I');

    root->leftus->hopar = root;
    root->rightus->hopar = root;
    root->leftus->leftus->hopar = root->leftus;
    root->rightus->leftus->hopar = root->rightus;
    root->rightus->rightus->hopar = root->rightus;
    root->rightus->leftus->rightus->hopar = root->rightus->leftus;
    root->rightus->rightus->leftus->hopar = root->rightus->rightus;
    root->rightus->rightus->rightus->hopar = root->rightus->rightus;
    PostorderParent::Uzbek::postorder(root);

    return 0;
}
