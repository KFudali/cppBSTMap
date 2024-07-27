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
void benchmarkInsert(MapType& map, const vector<pair<int, int>>& data) {
    auto start = high_resolution_clock::now();

    for (const auto pair : data) {
        map.insert(pair.first, pair.second);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Insert time: " << duration << " microseconds" << endl;
}

template<typename MapType>
void benchmarkSearch(MapType& map, const vector<int>& keys) {
    std::vector<int> values;
    auto start = high_resolution_clock::now();
    for (const int key : keys) {
        values.push_back(map.search(key));
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Search time: " << duration << " microseconds" << endl;
}

template<>
void benchmarkSearch(std::map<int, int>& map, const vector<int>& keys) {
    std::vector<int> values;
    auto start = high_resolution_clock::now();
    for (const int key : keys) {
        values.push_back(map[key]);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Search time: " << duration << " microseconds" << endl;
}

template<>
void benchmarkInsert(std::map<int, int>& map, const vector<pair<int, int>>& data) {
    auto start = high_resolution_clock::now();

    for (const auto pair : data) {
        map.insert(pair);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Insert time: " << duration << " microseconds" << endl;
}
