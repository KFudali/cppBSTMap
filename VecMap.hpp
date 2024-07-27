#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>

template<typename Key, typename Value>
class VecMap {
    public:
    VecMap() : size(0) {}

    void insert(const Key & key, const Value & value);
    Value search(const Key & key) const;

    private:
    std::vector<Key> keys;
    std::vector<Value> values;
    size_t size;
};

template<typename Key, typename Value>
void VecMap<Key, Value>::insert(const Key & key, const Value & value) {
    const auto it = std::find(keys.begin(), keys.end(), key);
    if (it == keys.end()) {
        keys.push_back(key);
        values.push_back(value);
        size++;
    }
}

template<typename Key, typename Value>
Value VecMap<Key, Value>::search(const Key & key) const {
    for (size_t i = 0; i < size; i++) {
        if (keys[i] == key) {
            return values[i];
        }
    }
    throw std::runtime_error("Key not found");
}