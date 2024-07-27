#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>

template<typename Key, typename Value>
class VecMap {

    std::vector<Key> keys;
    std::vector<Value> values;

    public:
    
    typedef Key key_type;
    typedef Value mapped_type;
    
    VecMap()   = default;
    ~VecMap()  = default;

    VecMap(const VecMap &) = delete;
    VecMap operator=(const VecMap &) = delete;

    // void insert(std::pair<Key, Value> aPair);
    void erase(const Key& key);
    void insert(const Key& key, const Value& value);
    void insert(const std::pair<Key, Value>& pair);
    Value& at( const Key& key);
    Value& operator[](const Key& key);

    inline size_t size(){return kesy.size();};
};

template<typename Key, typename Value>
void VecMap<Key, Value>::insert(const Key & key, const Value & value) {
    const auto it = std::find(keys.begin(), keys.end(), key);
    if (it == keys.end()) {
        keys.push_back(key);
        values.push_back(value);
    }
}

template<typename Key, typename Value>
void VecMap<Key, Value>::insert(const std::pair<Key, Value>& pair)
{
    insert(pair.first, pair.second);
}

template<typename Key, typename Value>
Value& VecMap<Key, Value>::at(const Key & key) {
    for (size_t i = 0; i < keys.size(); i++) {
        if (keys[i] == key) {
            return values[i];
        }
    }
    throw std::runtime_error("Key not found");
}

template<typename Key, typename Value>
void VecMap<Key, Value>::erase(const Key & key)
{
    for (size_t i = 0; i < keys.size(); ++i) {
        if (keys[i] == key) {
            keys.erase(keys.begin() + i);
            values.erase(values.begin() + i);
            return; 
        }
    }
}

template<typename Key, typename Value>
Value& VecMap<Key, Value>::operator[](const Key& key) {
    for (size_t i = 0; i < key.size(); ++i) {
        if (keys[i] == key) {
            return values[i];
        }
    }
    keys.push_back(key);
    values.push_back(Value());
    return values.back();
}