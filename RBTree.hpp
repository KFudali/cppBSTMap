#pragma once
#include "BSTree.hpp"
#include "MapNode.hpp"

template <typename Key, typename Value>
class RBTree : public BSTree<Key, Value>
{
public:
    RBTree() : BSTree<Key, Value>() {};

    RBTree(const RBTree &) = delete;
    RBTree& operator=(const RBTree &) = delete;

    void insert(const std::pair<Key, Value>& pair) override;
    void erase(const Key& key) override;


private:
    void leftRotate(MapNode<Key, Value>* node);
    void rightRotate(MapNode<Key, Value>* node);
    void insertFixBalance(MapNode<Key, Value>* node);
    void removeFixBalance(MapNode<Key, Value>* node);
};

template <typename Key, typename Value>
void RBTree<Key, Value>::insert(const std::pair<Key, Value>& pair)
{
    MapNode<Key, Value>* newNode = new MapNode<Key, Value>(pair);
    newNode->red = true;
    if (insertNode(newNode)){
        insertFixBalance(newNode);
        mapSize++;
    }
}

template <typename Key, typename Value>
void RBTree<Key, Value>::erase(const Key& key){
    MapNode<Key, Value>* nodeToDelete = searchNode(key);
    if(nodeToDelete){
        removeNode(nodeToDelete);
        removeFixBalance(nodeToDelete);
        mapSize--;
    }
}


template <typename Key, typename Value>
void RBTree<Key, Value>::leftRotate(MapNode<Key, Value>* node)
{
    MapNode<Key, Value>* rightNode = node->right;
    if (!rightNode) return;

    node->right = rightNode->left;
    if (rightNode->left) {
        rightNode->left->parent = node;
    }

    rightNode->parent = node->parent;
    if (!node->parent) {
        rootNode = rightNode;
    } else if (node == node->parent->left) {
        node->parent->left = rightNode;
    } else {
        node->parent->right = rightNode;
    }

    rightNode->left = node;
    node->parent = rightNode;
}

template <typename Key, typename Value>
void RBTree<Key, Value>::rightRotate(MapNode<Key, Value>* node)
{
    MapNode<Key, Value>* leftNode = node->left;
    if (!leftNode) return;

    node->left = leftNode->right;
    if (leftNode->right) {
        leftNode->right->parent = node;
    }

    leftNode->parent = node->parent;
    if (!node->parent) {
        rootNode = leftNode;
    } else if (node == node->parent->left) {
        node->parent->left = leftNode;
    } else {
        node->parent->right = leftNode;
    }

    leftNode->right = node;
    node->parent = leftNode;
}


template <typename Key, typename Value>
void RBTree<Key, Value>::insertFixBalance(MapNode<Key, Value>* node)
{
    while (node != rootNode && node->parent->red){
        if (node->parent == node->parent->parent->left){
            MapNode<Key, Value>* uncle = node->parent->parent->right;
            if (uncle && uncle->red){
                node->parent->red = false;
                uncle->red = false;
                node->parent->parent->red = true;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right){
                    node = node->parent;
                    leftRotate(node);
                }
                node->parent->red = false;
                node->parent->parent->red = true;
                rightRotate(node->parent->parent);
            }
        } else {
            MapNode<Key, Value>* uncle = node->parent->parent->left;
            if (uncle && uncle->red) {
                node->parent->red = false;
                uncle->red = false;
                node->parent->parent->red = true;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rightRotate(node);
                }
                node->parent->red = false;
                node->parent->parent->red = true;
                leftRotate(node->parent->parent);
            }
        }
    }
    rootNode->red = false;
}


template <typename Key, typename Value>
void RBTree<Key, Value>::removeFixBalance(MapNode<Key, Value>* node)
{
    while (node != rootNode && (!node || !node->red)) {
        if (node == node->parent->left) {
            MapNode<Key, Value>* sibling = node->parent->right;
            if (sibling->red) {
                sibling->red = false;
                node->parent->red = true;
                leftRotate(node->parent);
                sibling = node->parent->right;
            }
            if ((!sibling->left || !sibling->left->red) &&
                (!sibling->right || !sibling->right->red)) {
                sibling->red = true;
                node = node->parent;
            } else {
                if (!sibling->right || !sibling->right->red) {
                    if (sibling->left) sibling->left->red = false;
                    sibling->red = true;
                    rightRotate(sibling);
                    sibling = node->parent->right;
                }
                sibling->red = node->parent->red;
                node->parent->red = false;
                if (sibling->right) sibling->right->red = false;
                leftRotate(node->parent);
                node = rootNode;
            }
        } else {
            MapNode<Key, Value>* sibling = node->parent->left;
            if (sibling->red) {
                sibling->red = false;
                node->parent->red = true;
                rightRotate(node->parent);
                sibling = node->parent->left;
            }
            if ((!sibling->left || !sibling->left->red) &&
                (!sibling->right || !sibling->right->red)) {
                sibling->red = true;
                node = node->parent;
            } else {
                if (!sibling->left || !sibling->left->red) {
                    if (sibling->right) sibling->right->red = false;
                    sibling->red = true;
                    leftRotate(sibling);
                    sibling = node->parent->left;
                }
                sibling->red = node->parent->red;
                node->parent->red = false;
                if (sibling->left) sibling->left->red = false;
                rightRotate(node->parent);
                node = rootNode;
            }
        }
    }
    if (node) node->red = false;
}