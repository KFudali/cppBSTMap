#pragma once

#include <iostream>
#include <map>
#include <chrono>
#include <vector>
#include <cstdlib>
#include "BSTree.hpp"
#include "VecMap.hpp"

using namespace std;
using namespace std::chrono;

template<typename MapType>
void benchmarkInsert(MapType& map, const std::vector<std::pair<typename MapType::key_type, typename MapType::mapped_type>>& data) {
    auto start = high_resolution_clock::now();

    for (const auto& pair : data) {
        map.insert(pair);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Insert time: " << duration << " microseconds" << endl;
}

template<typename MapType>
void benchmarkSearch(MapType& map, const std::vector<typename MapType::key_type>& keys) {
    auto start = high_resolution_clock::now();
    for (const typename MapType::key_type& key : keys) {
        auto val = map.at(key);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Search time: " << duration << " microseconds" << endl;
}