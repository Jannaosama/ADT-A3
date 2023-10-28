#include "binaryTree.h"
#include <iostream>
using namespace std;

template <class KeyType, class DataType>
binaryTree<KeyType, DataType>::binaryTree() : root(nullptr) {}

template <class KeyType, class DataType>
binaryTree<KeyType, DataType>::~binaryTree() {
    clear(root);
}

template <class KeyType, class DataType>
void binaryTree<KeyType, DataType>::clear(Node* node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <class KeyType, class DataType>
bool binaryTree<KeyType, DataType>::empty() const {
    return (root == nullptr);
}

template <class KeyType, class DataType>
bool binaryTree<KeyType, DataType>::insert(const KeyType& key, const DataType& data) {
    return insert(root, key, data);
}

template <class KeyType, class DataType>
bool binaryTree<KeyType, DataType>::insert(Node*& node, const KeyType& key, const DataType& data) {
    if (!node) {
        node = new Node;
        node->key = key;
        node->data = data;
        node->left = node->right = nullptr;
        return true;
    } else if (key < node->key) {
        return insert(node->left, key, data);
    } else if (key > node->key) {
        return insert(node->right, key, data);
    } else {
        return false; 
    }
}

template <class KeyType, class DataType>
bool binaryTree<KeyType, DataType>::retrieve(const KeyType& key, DataType& data) const {
    return retrieve(root, key, data);
}

template <class KeyType, class DataType>
bool binaryTree<KeyType, DataType>::retrieve(Node* node, const KeyType& key, DataType& data) const {
    if (!node) {
        return false;
    } else if (key == node->key) {
        data = node->data;
        return true;
    } else if (key < node->key) {
        return retrieve(node->left, key, data);
    } else {
        return retrieve(node->right, key, data);
    }
}

template <class KeyType, class DataType>
void binaryTree<KeyType, DataType>::remove(const KeyType& key) {
    remove(root, key);
}

template <class KeyType, class DataType>
void binaryTree<KeyType, DataType>::remove(Node*& node, const KeyType& key) {
    if (!node) {
        return;
    } else if (key < node->key) {
        remove(node->left, key);
    } else if (key > node->key) {
        remove(node->right, key);
    } else {
        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        } else if (!node->left) {
            Node* temp = node;
            node = node->right;
            delete temp;
        } else if (!node->right) {
            Node* temp = node;
            node = node->left;
            delete temp;
        } else {
            Node* temp = node->right;
            while (temp->left) {
                temp = temp->left;
            }
            node->key = temp->key;
            node->data = temp->data;
            remove(node->right, temp->key);
        }
    }
}

template <class KeyType, class DataType>
void binaryTree<KeyType, DataType>::traverse() const {
    traverse(root);
}

template <class KeyType, class DataType>
void binaryTree<KeyType, DataType>::traverse(Node* node) const {
    if (node) {
        traverse(node->left);
        cout << "Key: " << node->key << ", Data: " << node->data << std::endl;
        traverse(node->right);
    }
}