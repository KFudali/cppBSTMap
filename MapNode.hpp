#pragma once

template <typename Key, typename Value>
struct MapNode {

    Key key;
    Value value;

    bool red;

    MapNode* left;
    MapNode* right;
    MapNode* parent;

    MapNode(const std::pair<Key, Value>& pair) : key(pair.first), value(pair.second), red(false), left(nullptr), right(nullptr), parent(nullptr) {}
};