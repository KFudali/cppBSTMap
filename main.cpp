#include "RBTree.hpp"
#include "BSTree.hpp"
#include "VecMap.hpp"
#include "Benchmark.hpp"
#include "RandData.hpp"

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <fstream>

int main(int argc, char *argv[]) {

    VecMap<int, int> vecMap;
    BSTree<int, int> BSTreeMap;
    RBTree<int, int> RBTreeMap;
    std::map<int, int> STDMap;


    std::vector<int> setSizes{1000, 5000, 10000, 20000, 30000, 40000, 50000};

    for (int setType = 0; setType < static_cast<int>(SetType::count); setType++)
    {

        SetType eSetType = static_cast<SetType>(setType);
        std::ofstream resultsFile;
        switch (eSetType) {
            case SetType::linear:
                resultsFile.open("results_linear.txt");
                break;
            case SetType::linearRev:
                resultsFile.open("results_linearRev.txt");
                break;
            case SetType::rand:
                resultsFile.open("results_rand.txt");
                break;
            default:
                std::cerr << "Unknown set type!" << std::endl;
                continue; // Skip the rest of the loop iteration
        }

        resultsFile << "quant\t\tsetSize\tvecMap\tBSTMap\tRBTMap\tstdMap\n";
        for (const int setSize : setSizes) {
        benchmarkResults vecResults = benchmarkMap(vecMap, setSize, eSetType);
        benchmarkResults BSTResults = benchmarkMap(BSTreeMap, setSize, eSetType);
        benchmarkResults RBTResults = benchmarkMap(RBTreeMap, setSize, eSetType);
        benchmarkResults STDResults = benchmarkMap(STDMap, setSize, eSetType);
        resultsFile << "insert-mean\t" << std::to_string(setSize) << "\t" 
                                       << vecResults.insertMean   << "\t"  
                                       << BSTResults.insertMean   << "\t"
                                       << RBTResults.insertMean   << "\t"
                                       << STDResults.insertMean   << std::endl;

        resultsFile << "search-mean\t" << std::to_string(setSize) << "\t" 
                                       << vecResults.searchMean   << "\t"
                                       << BSTResults.searchMean   << "\t"
                                       << RBTResults.searchMean   << "\t"
                                       << STDResults.searchMean   << std::endl;

        resultsFile << "insert-sDev\t" << std::to_string(setSize) << "\t" 
                                         << vecResults.insertStdDev << "\t"
                                         << BSTResults.insertStdDev << "\t"
                                         << RBTResults.insertStdDev << "\t"
                                         << STDResults.insertStdDev << std::endl;

        resultsFile << "search-sDev\t" << std::to_string(setSize) << "\t" 
                                         << vecResults.searchStdDev << "\t"
                                         << BSTResults.searchStdDev << "\t"
                                         << RBTResults.searchStdDev << "\t"
                                         << STDResults.searchStdDev << std::endl;

    }
    resultsFile.close();
    }
    return 0;
}