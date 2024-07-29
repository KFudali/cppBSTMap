#pragma once

#include <algorithm>
#include "MapNode.hpp"
#include <vector>

// Reference https://en.wikipedia.org/wiki/Binary_search_tree

template <typename Key, typename Value>
class BSTree 
{
private:
    friend class iterator;
    friend class const_iterator;

    MapNode<Key, Value>* minNode(MapNode<Key, Value>* node) const;
    MapNode<Key, Value>* maxNode(MapNode<Key, Value>* node) const;

    MapNode<Key, Value>* successor(MapNode<Key, Value>* node) const;
    MapNode<Key, Value>* predecessor(MapNode<Key, Value>* node) const;

protected:
    MapNode<Key, Value>* rootNode;
    size_t mapSize;

    MapNode<Key, Value>* searchNode(const Key& key) const;

    bool insertNode(MapNode<Key, Value>* node);
    void removeNode(MapNode<Key, Value>* node);
    void shiftNodes(MapNode<Key, Value>* u, MapNode<Key, Value>* v);

public:
    typedef Key key_type;
    typedef Value mapped_type;

    BSTree() : mapSize(0), rootNode(nullptr) {}
    virtual ~BSTree();
    BSTree(const BSTree &) = delete;
    BSTree& operator=(const BSTree &) = delete;

    virtual void erase(const Key& key);
    virtual void insert(const std::pair<Key, Value>& pair);

    Value& at(const Key& key);
    Value& operator[](const Key& key);

    inline size_t size() const { return mapSize; }


    // reference https://internalpointers.com/post/writing-custom-iterators-modern-cpp
    struct iterator {
        using iterator_category = std::bidirectional_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = std::pair<const Key, Value>;
        using pointer = value_type*;
        using reference = value_type&;

        MapNode<Key, Value>* nodePtr;
        BSTree<Key, Value>* tree;

        iterator(MapNode<Key, Value>* node = nullptr, BSTree<Key, Value>* tree = nullptr)
            : nodePtr(node), tree(tree) {}

        reference operator*() const { 
            std::pair<const Key, Value> data(nodePtr->key, nodePtr->value);
            return data;
        }
        pointer operator->() const { 
            std::pair<const Key, Value> data(nodePtr->key, nodePtr->value);
            return &data;
        }

        bool operator==(const iterator& other) const { return nodePtr == other.nodePtr; }
        bool operator!=(const iterator& other) const { return nodePtr != other.nodePtr; }

        iterator& operator++() {
            nodePtr = tree->successor(nodePtr);
            return *this;
        }
        iterator operator++(int) {
            iterator copy = *this;
            nodePtr = tree->successor(nodePtr);
            return copy;
        }

        iterator& operator--() {
            nodePtr = tree->predecessor(nodePtr);
            return *this;
        }
        iterator operator--(int) {
            iterator copy = *this;
            nodePtr = tree->predecessor(nodePtr);
            return copy;
        }
    };

    // const corectness - https://youtu.be/O65lEiYkkbc?si=n5k0xBKtfo4R-qdl timestamp: 42:10 
    // Back to Basics: Designing Classes (part 2 of 2) - Klaus Iglberger - CppCon 2021

    using const_iterator = const iterator;

    iterator begin() noexcept {return iterator(minNode(rootNode), this);}
    iterator end()   noexcept {return iterator(nullptr, this);}
    iterator rbegin() noexcept {return iterator(maxNode(rootNode), this);}
    iterator rend() noexcept {return iterator(nullptr, this);}

    const_iterator begin() const noexcept {return iterator(minNode(rootNode), this);}
    const_iterator end()   const noexcept {return iterator(nullptr, this);}
    
    const_iterator rbegin() const noexcept {return iterator(maxNode(rootNode), this);}
    const_iterator rend() const noexcept {return iterator(nullptr, this);}

    const_iterator cbegin() const noexcept {return iterator(minNode(rootNode), this);}
    const_iterator cend()   const noexcept {return iterator(nullptr, this);}
};

template <typename Key, typename Value>
BSTree<Key, Value>::~BSTree() {
    for (auto it = rbegin(); it != rend(); ++it) {
        delete it.nodePtr;
    }
    rootNode = nullptr;
    mapSize = 0;
}

template <typename Key, typename Value>
bool BSTree<Key, Value>::insertNode(MapNode<Key, Value>* newNode)
{
    MapNode<Key, Value>* node = rootNode;
    MapNode<Key, Value>* lastNode = nullptr;
    const Key& key = newNode->key;
    while(node){
        lastNode = node;
        if(newNode->key < node->key){
            node = node->left;
        } else if(newNode->key > node->key){
            node = node->right;
        } else {
            delete newNode;
            return false;
        }
    }
    newNode->parent = lastNode;
    if(!lastNode){
        rootNode = newNode;
    } else if(newNode->key < lastNode->key){
        lastNode->left = newNode;
    } else {
        lastNode->right = newNode;
    }
    return true;
}

template <typename Key, typename Value>
void BSTree<Key, Value>::insert(const std::pair<Key, Value>& pair)
{
    MapNode<Key, Value>* newNode = new MapNode<Key, Value>(pair);
    if(insertNode(newNode)){
        mapSize++;
    };
}

template <typename Key, typename Value>
MapNode<Key, Value>* BSTree<Key, Value>::searchNode(const Key& key) const
{
    MapNode<Key, Value>* node = rootNode;
    while ( node && (node->key != key)){
        if ( key < node->key ){
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

template <typename Key, typename Value>
Value& BSTree<Key, Value>::at(const Key& key){
    MapNode<Key, Value>* node = searchNode(key);
    if (node) {
        return node->value;
    }
    throw std::runtime_error("Key not found");
}

template <typename Key, typename Value>
Value& BSTree<Key, Value>::operator[](const Key& key) {
    MapNode<Key, Value>* node = searchNode(key);
    if (node) {
        return node->value;
    } else {
        Value val = Value();
        std::pair<Key, Value> pair{key, val};
        insert(pair);
        return searchNode(key)->value;
    }
}

template <typename Key, typename Value>
void BSTree<Key, Value>::erase(const Key& key){
    MapNode<Key, Value>* nodeToDelete = searchNode(key);
    if(nodeToDelete){
        removeNode(nodeToDelete);
        mapSize--;
    }
}

template <typename Key, typename Value>
void BSTree<Key, Value>::shiftNodes(MapNode<Key, Value>* u, MapNode<Key, Value>* v)
{
    if(!u->parent){
        rootNode = v;
    } else if (u == u->parent->left ){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v) {
        v->parent = u->parent;
    }
}

template <typename Key, typename Value>
MapNode<Key, Value>* BSTree<Key, Value>::maxNode(MapNode<Key, Value>* node) const
{
    while(node->right){
        node = node->right;
    }
    return node;
}

template <typename Key, typename Value>
MapNode<Key, Value>* BSTree<Key, Value>::minNode(MapNode<Key, Value>* node) const
{
    while(node->left){
        node = node->left;
    }
    return node;
}

template <typename Key, typename Value>
MapNode<Key, Value>* BSTree<Key, Value>::successor(MapNode<Key, Value>* node) const
{
    if (node->right) {
        return minNode(node->right);
    }

    MapNode<Key, Value>* successorNode = node->parent;
    while (successorNode && node == successorNode->right) {
        node = successorNode;
        successorNode = successorNode->parent;
    }
    return successorNode;
}

template <typename Key, typename Value>
MapNode<Key, Value>* BSTree<Key, Value>::predecessor(MapNode<Key, Value>* node) const
{
    MapNode<Key, Value>* predecessorNode;
    if (node->left) {
        return maxNode(node->left);
    }
    predecessorNode = node->parent;
    while (predecessorNode && (node == predecessorNode->left)) {
        node = predecessorNode;
        predecessorNode = predecessorNode->parent;
    }
    return predecessorNode;
}

template <typename Key, typename Value>
void BSTree<Key, Value>::removeNode(MapNode<Key, Value>* nodeToDelete) {
    if (!nodeToDelete) {
        throw std::runtime_error("Node to delete is nullptr!");
    }

    if (!nodeToDelete->left) {
        shiftNodes(nodeToDelete, nodeToDelete->right);
    } else if (!nodeToDelete->right) {
        shiftNodes(nodeToDelete, nodeToDelete->left);
    } else {
        MapNode<Key, Value>* successorNode = successor(nodeToDelete);
        if (successorNode->parent != nodeToDelete) {
            shiftNodes(successorNode, successorNode->right);
            successorNode->right = nodeToDelete->right;
            successorNode->right->parent = successorNode;
        }
        shiftNodes(nodeToDelete, successorNode);
        successorNode->left = nodeToDelete->left;
        successorNode->left->parent = successorNode;
    }

    delete nodeToDelete;
}