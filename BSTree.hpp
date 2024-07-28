#pragma once

#include <algorithm>
#include "MapNode.hpp"
#include <vector>

// Reference https://en.wikipedia.org/wiki/Binary_search_tree

template <typename Key, typename Value>
class BSTree 
{

    MapNode<Key, Value>* rootNode;
    size_t mapSize;

    void removeNode( MapNode<Key, Value>* node );
    void shiftNodes( MapNode<Key, Value>* u, MapNode<Key, Value>* v);

    MapNode<Key, Value>* searchNode( const Key& key ) const;

    MapNode<Key, Value>* minNode (MapNode<Key, Value>* node) const;
    MapNode<Key, Value>* maxNode (MapNode<Key, Value>* node) const;

    MapNode<Key, Value>* successor (MapNode<Key, Value>* node) const;
    MapNode<Key, Value>* predecessor (MapNode<Key, Value>* node) const;

public:
    typedef Key key_type;
    typedef Value mapped_type;

    BSTree();
    virtual ~BSTree();

    BSTree(const BSTree &) = delete;
    BSTree operator=(const BSTree &) = delete;

    // void insert(std::pair<Key, Value> aPair);
    virtual void erase(const Key& key);
    virtual void insert(const std::pair<Key, Value>& pair);

    Value& at(const Key& key);
    Value& operator[](const Key& key);

    inline size_t size() const {return mapSize;};

};

template <typename Key, typename Value>
BSTree<Key, Value>::BSTree(){
    rootNode = nullptr;
}

template <typename Key, typename Value>
BSTree<Key, Value>::~BSTree(){
    std::vector<MapNode<Key, Value>*> nodes;
    if (rootNode) nodes.push_back(rootNode);

    while (!nodes.empty()) {
        MapNode<Key, Value>* node = nodes.back();
        nodes.pop_back();
        if (node->left) nodes.push_back(node->left);
        if (node->right) nodes.push_back(node->right);
        delete node;
    }
}

template <typename Key, typename Value>
void BSTree<Key, Value>::insert(const std::pair<Key, Value>& pair)
{
    MapNode<Key, Value>* newNode = new MapNode<Key, Value>(pair);
    MapNode<Key, Value>* node = rootNode;
    MapNode<Key, Value>* lastNode = nullptr;
    const Key& key = pair.first;
    while(node){
    lastNode = node;
    if(newNode->key < node->key){
        node = node->left;
    }
    else if(newNode->key > node->key){
        node = node->right;
    }
    else {
        delete newNode;
        return;
    }
    }
    newNode->parent = lastNode;
    if(!lastNode){
        rootNode = newNode;
    }else if(newNode->key < lastNode->key){
        lastNode->left = newNode;
    }else{
        lastNode->right = newNode;
    }
    mapSize++;
}

template <typename Key, typename Value>
MapNode<Key, Value>* BSTree<Key, Value>::searchNode(const Key& key) const
{
    MapNode<Key, Value>* node = rootNode;
    while ( node && (node->key != key)){
        if ( key < node->key ){
            node = node->left;
        }else{
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
        Value val();
        insert(key, val);
        return val;
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
void BSTree<Key, Value>::shiftNodes( MapNode<Key, Value>* u,  MapNode<Key, Value>* v)
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
        return maxNode(node->left)
    } 
    predecessorNode = x->parent;
    while (predecessorNode and (node == successor->left)) {
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