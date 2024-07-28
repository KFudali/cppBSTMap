#pragma once

#include <algorithm>
#include "BSTree.hpp"
#include "MapNode.hpp"
#include <vector>

// Reference https://en.wikipedia.org/wiki/Binary_search_tree

template <typename Key, typename Value>
class RBTree : public BSTree
{
    MapNode<Key, Value>* rootNode;

public:

    RBTree(const RBTree &) = delete;
    RBTree operator=(const RBTree &) = delete;

    // void insert( const std::pair<Key, Value>& newPair ) override;
    // void removeNode( MapNode<Key, Value>* node ) override;

    // void leftRotate(MapNode<Key, Value>* nodeToRotate);
    // void rightRotate(MapNode<Key, Value>* nodeToRotate);
    // void insertFixBalance(MapNode<Key, Value>* node);
    // void removeFixBalance(MapNode<Key, Value>* node);
};