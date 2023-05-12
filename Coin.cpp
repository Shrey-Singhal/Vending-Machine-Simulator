#include "Coin.h"
#include "Node.h"
#include <map>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <map>


void Coin::displayCoins(const std::map<unsigned, unsigned>& coinMap) {
    std::cout << "Coins Summary\n"
                 "-------------\n"
                 "Denomination    |    Count\n"
                 "---------------------------" << std::endl;

    for (auto denom: coinMap) {
        unsigned denomination = denom.first;
        unsigned amount = denom.second;

        // Create representation string
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

        outFile << coinDenom->first << "," << coinDenom->second << std::endl;
    }

    outFile.close();

}

void Coin::resetCoins(std::map<unsigned, unsigned>& coinMap) {
    for (auto coinDenom: coinMap) {
        coinMap[coinDenom.first] = DEFAULT_COIN_COUNT;
    }
}
