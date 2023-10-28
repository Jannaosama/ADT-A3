#ifndef BINARYTREE_H
#define BINARYTREE_H
using namespace std;

template <class KeyType, class DataType>
class binaryTree {
public:
    struct Node {
        KeyType key;
        DataType data;
        Node* left;
        Node* right;
    };

    binaryTree();
    ~binaryTree();

    bool empty() const;
    bool insert(const KeyType& key, const DataType& data);
    bool retrieve(const KeyType& key, DataType& data) const;
    void remove(const KeyType& key);
    void traverse() const;

private:
    Node* root;

    void clear(Node* node);
    bool insert(Node*& node, const KeyType& key, const DataType& data);
    bool retrieve(Node* node, const KeyType& key, DataType& data) const;
    void remove(Node*& node, const KeyType& key);
    void traverse(Node* node) const;
};

#endif