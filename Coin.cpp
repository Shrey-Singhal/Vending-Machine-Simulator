#include "Coin.h"
#include "Node.h"
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>


void Coin::displayCoins(const std::map<unsigned, unsigned>& coinMap) {
    std::cout << "Coins Summary\n"
                 "-------------\n"
                 "Denomination    |    Count\n"
                 "---------------------------" << std::endl;

    for (auto denom: coinMap) {
        unsigned denomination = denom.first;
        unsigned amount = denom.second;

        // Create representation string e.g. 1 Dollars or 50 Cents
        std::stringstream centOrDollar;
        if (denomination % 100 == 0) {
            centOrDollar << denomination / 100;
            centOrDollar << " Dollars";
        }
        else {
            centOrDollar << denomination;
            centOrDollar << " Cents";
        }

        // Print row
        std::cout << std::setfill(' ');
        std::cout << std::left << std::setw(16) << centOrDollar.str();
        std::cout << "|";
        std::cout << std::right << std::setw(10) << amount << std::endl;

    }
    std::cout << std::endl;
}

std::map<unsigned, unsigned> Coin::parseCoinFile(const std::string& filename) {
    std::ifstream file(filename);

    std::map<unsigned, unsigned> dataMap;
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        std::getline(ss, token, ',');
        int key = std::stoi(token);

        std::getline(ss, token, ',');
        int value = std::stoi(token);

        dataMap[key] = value;
    }

    file.close();
    return dataMap;
}

void Coin::saveCoins(const std::string& fileName,
                              const std::map<unsigned int, unsigned int>& map) {
    // Open the file in write mode to clear all the content
    std::ofstream outFile(fileName, std::ios::out | std::ios::trunc);
    if (!outFile) {
        std::cerr << "can't open output file" << std::endl;
    }
    outFile.close();

    // Reopen the file in append mode to write new content
    outFile.open(fileName, std::ios::out | std::ios::app);

    // Write new content to the file
    for (auto coinDenom = map.rbegin(); coinDenom != map.rend(); ++coinDenom) {

        outFile << coinDenom->first << DELIM << coinDenom->second << std::endl;
    }

    outFile.close();

}

void Coin::resetCoins(std::map<unsigned, unsigned>& coinMap) {
    for (auto coinDenom: coinMap) {
        coinMap[coinDenom.first] = DEFAULT_COIN_COUNT;
    }
}
