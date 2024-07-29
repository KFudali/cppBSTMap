#include "RBTree.hpp"
#include "BSTree.hpp"
#include "VecMap.hpp"
#include "Benchmark.hpp"
#include "RandData.hpp"

#include <iostream>
#include <map>
#include <string>

int main(int argc, char *argv[]){
    
    RBTree<int, int> RBTreeMap;
    BSTree<int, int> BSTreeMap;
    VecMap<int, int> vecMap;
    std::map<int, int> map;

    size_t setSize = 100000;
    std::vector<int> keysSet(setSize);
    std::vector<std::pair<int, int>> dataSet(setSize);

    RandData::init();

    for (int i = 0; i < setSize; ++i) {
        int key   = i;
        int value = RandData::randInt(1, setSize);
        dataSet[i] = {key, value};
        keysSet[i] = key;
    }

    std::cout << "VecMap - ";
    benchmarkInsert(vecMap, dataSet);
    std::cout << "BSTreeMap - ";
    benchmarkInsert(BSTreeMap, dataSet);
    std::cout << "std::map - ";
    benchmarkInsert(map, dataSet);
    std::cout << "RBTree - ";
    benchmarkInsert(RBTreeMap, dataSet);

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


    std::cout << "RBTreeMap - ";
    try {
        benchmarkSearch(RBTreeMap, keysSet); 
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught a runtime error: " << e.what() << '\n';
    }
    

    return 0;
}
