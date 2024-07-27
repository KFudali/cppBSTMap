#include "BSTree.hpp"
#include "VecMap.hpp"
#include "Benchmark.hpp"
#include "iostream"
#include <map>

int randRange(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main(int argc, char *argv[]){
    
    BSTree<int, int> BSTreeMap;
    VecMap<int, int> vecMap;
    std::map<int,int> map;

    size_t setSize = 100000;
    vector<pair<int, int>> dataSet(setSize);
    vector<int> keysSet(setSize);

    for (int i = 0; i < setSize; ++i) {
        int key = randRange(1, setSize);
        int value = randRange(1, setSize);
        dataSet[i] = {key, value};
        keysSet[i] = key;

    }

    std::cout << "VecMap - ";
    benchmarkInsert(vecMap, dataSet);
    std::cout << "BSTreeMap - ";
    benchmarkInsert(BSTreeMap, dataSet);
    std::cout << "std::map - ";
    benchmarkInsert(map, dataSet);

    std::cout << "VecMap - ";
    try {
        benchmarkSearch(vecMap, keysSet); 
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught a runtime error: " << e.what() << '\n';
    }
    
    std::cout << "BSTreeMap - ";
    try {
        benchmarkSearch(BSTreeMap, keysSet); 
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught a runtime error: " << e.what() << '\n';
    }

    std::cout << "std::map - ";
    try {
        benchmarkSearch(map, keysSet); 
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught a runtime error: " << e.what() << '\n';
    }

    return 0;
}
