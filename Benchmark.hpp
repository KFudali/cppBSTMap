#pragma once

#include <iostream>
#include <map>
#include <chrono>
#include <vector>
#include <cstdlib>
#include "BSTree.hpp"
#include "VecMap.hpp"
#include <numeric>


struct benchmarkResults {
    int insertMean;
    int searchMean;
    int insertStdDev;
    int searchStdDev;

    benchmarkResults(int aInsertMean, int aSearchMean, int aInsertStdDev, int aSearchStdDev) :
        insertMean(aInsertMean), searchMean(aSearchMean), insertStdDev(aInsertStdDev), searchStdDev(aSearchStdDev) {};
};

enum class SetType {
    linear,
    linearRev,
    rand,
    count,
};

template<typename MapType>
long long benchmarkInsert(MapType& map, const std::vector<std::pair<typename MapType::key_type, typename MapType::mapped_type>>& data) {
    auto start = std::chrono::high_resolution_clock::now();

    for (const auto& pair : data) {
        map.insert(pair);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return duration;
}

template<typename MapType>
long long benchmarkSearch(MapType& map, const std::vector<typename MapType::key_type>& keys) {
    auto start = std::chrono::high_resolution_clock::now();
    for (const typename MapType::key_type& key : keys) {
        auto val = map.at(key);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    return duration;
}

template<typename MapType>
benchmarkResults benchmarkMap(MapType& map, int setSize, SetType setType)
{
    RandData::init();
    std::vector<int> keysSet(setSize);
    std::vector<std::pair<int, int>> dataSet(setSize);
    for (int i = 0; i < setSize; ++i) {
        int key;
        if(setType == SetType::linear){
            key = i;
        } else if (setType == SetType::linearRev){
            key = setSize - i;
        } else if (setType == SetType::rand){
            key = RandData::randInt(1, setSize);
        }
        int value = RandData::randInt(1, setSize);
        dataSet[i] = {key, value};
        keysSet[i] = key;
    }
    int nSamples = 100;
    std::vector<long long> insertDurations(nSamples);
    std::vector<long long> searchDurations(nSamples);

    MapType bMap;

    for (int i = 0; i < nSamples; i++){
        insertDurations[i] = benchmarkInsert(bMap, dataSet);
        searchDurations[i] = benchmarkSearch(bMap, keysSet);
    }
    double insertMean = mean(insertDurations);
    double searchMean = mean(searchDurations);

    double insertStdDev = stdDev(insertDurations);
    double searchStdDev = stdDev(searchDurations);

    return benchmarkResults(insertMean, searchMean, insertStdDev, searchStdDev);
}

double mean(const std::vector<long long>& data) {
    if (data.empty()) return 0.0;
    double sum = std::accumulate(data.begin(), data.end(), 0LL);
    return sum / data.size();
}

double stdDev(const std::vector<long long>& data) {
    if (data.empty()) return 0.0;
    double m = mean(data);
    double sqSum = std::accumulate(data.begin(), data.end(), 0.0, 
                                    [m](double sum, long long elem) { return sum + (elem - m) * (elem - m); });
    
    double var = sqSum / data.size();
    return std::sqrt(var);
}