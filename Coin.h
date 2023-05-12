#ifndef COIN_H
#define COIN_H

// Coin.h defines the coin structure for managing currency in the system. 
#include <map>
#include <string>

#define DELIM ","  // delimiter

// enumeration representing the various types of currency available in the system. 
enum Denomination
{
    FIVE_CENTS, TEN_CENTS, TWENTY_CENTS, FIFTY_CENTS, ONE_DOLLAR, 
    TWO_DOLLARS, FIVE_DOLLARS, TEN_DOLLARS
};


// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
class Coin
{
public:
    // the denomination type
    enum Denomination denom;
    
    // the count of how many of these are in the cash register
    unsigned count;

    static void printPrice(const unsigned int &costInCents);

    static void displayCoins(const std::map<unsigned int, unsigned int> &coinMap);

    static void saveCoins(const std::string& fileName,
                         const std::map<unsigned int, unsigned int>& map);

    static void resetCoins(std::map<unsigned int, unsigned int> &coinMap);
};

#endif // COIN_H
