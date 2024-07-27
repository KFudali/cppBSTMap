#pragma once

#include <vector>
#include <string>
#include <cstdlib>   
#include <ctime>
#include <algorithm> 
#include <random>    

namespace RandData {

void init() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

std::string randString(size_t length) {
    const std::string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string result;
    result.resize(length);

    for (size_t i = 0; i < length; ++i) {
        result[i] = characters[std::rand() % characters.size()];
    }
    
    return result;
}

int randInt(int min, int max) {
    return min + std::rand() % (max - min + 1);
}

double randDouble(double min, double max) {
    static std::default_random_engine engine(static_cast<unsigned>(std::time(nullptr)));
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(engine);
}

};