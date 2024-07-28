#pragma once
#include <vector>
#include <algorithm>
#include <stdexcept>

template<typename Key, typename Value>
class VecMap {

    std::vector<std::pair<Key, Value>> pairs;
    public:
    
    typedef Key key_type;
    typedef Value mapped_type;
    
    VecMap()   = default;
    ~VecMap()  = default;

    VecMap(const VecMap &) = delete;
    VecMap operator=(const VecMap &) = delete;

    void erase(const Key& key);
    void insert(const std::pair<Key, Value>& pair);
    Value& at( const Key& key);
    Value& operator[](const Key& key);

    inline size_t size(){return pairs.size();};
};

template<typename Key, typename Value>
void VecMap<Key, Value>::insert(const std::pair<Key, Value>& pair) {
    auto it = std::find_if(pairs.begin(), pairs.end(), [pair](const auto& mapPair){ return mapPair.first == pair.first; });
    if (it == pairs.end()) {
        pairs.push_back(pair);
    }
}

template<typename Key, typename Value>
Value& VecMap<Key, Value>::at(const Key & key) {
    for (size_t i = 0; i <  pairs.size(); i++) {
        if (pairs[i].first == key) {
            return  pairs[i].second;
        }
    }
    throw std::runtime_error("Key not found");
}

template<typename Key, typename Value>
void VecMap<Key, Value>::erase(const Key & key)
{
    for (size_t i = 0; i < pairs.size(); ++i) {
        if (pairs[i].first == key) {
            pairs.erase(keys.begin() + i);
            return; 
        }
    }
}

template<typename Key, typename Value>
Value& VecMap<Key, Value>::operator[](const Key& key) {
    for (size_t i = 0; i < pairs.size(); ++i) {
        if (pairs[i].first == key) {
            return pairs[i].second;
        }
    }
    insert(std::pair<Key, Value> pair(key, Value()));
    return pairs.back().second;
}