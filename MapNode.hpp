#pragma once

template <typename Key, typename Value>
struct MapNode {

    Key key;
    Value value;

    bool red;

    MapNode* left;
    MapNode* right;
    MapNode* parent;

    MapNode(const Key& key, const Value& value) : key(key), value(value), red(false), left(nullptr), right(nullptr), parent(nullptr) {}
};