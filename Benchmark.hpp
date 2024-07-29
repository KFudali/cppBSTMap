#pragma once

#include <iostream>
#include <map>
#include <chrono>
#include <vector>
#include <cstdlib>
#include "BSTree.hpp"
#include "VecMap.hpp"

template<typename MapType>
void benchmarkInsert(MapType& map, const std::vector<std::pair<typename MapType::key_type, typename MapType::mapped_type>>& data) {
    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& pair : data) {
        map.insert(pair);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Insert time: " << duration << " microseconds" << std::endl;
}

template<typename MapType>
void benchmarkSearch(MapType& map, const std::vector<typename MapType::key_type>& keys) {
    auto start = std::chrono::high_resolution_clock::now();
    for (const typename MapType::key_type& key : keys) {
        auto val = map.at(key);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Search time: " << duration << " microseconds" << std::endl;
}