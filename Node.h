#ifndef NODE_H
#define NODE_H
#include <string> 
#include "Coin.h"
#include <vector>
#include <iostream>

//The length of the id string not counting the nul terminator
#define IDLEN 5

//The maximum length of a product name not counting the nul terminator
#define NAMELEN 40

//The maximum length of a product description not counting the nul terminator.
#define DESCLEN 255

//The default coin level to reset the coins to on request
#define DEFAULT_COIN_COUNT 20

//The default stock level that all new stock should start at and that we should reset to on restock
#define DEFAULT_STOCK_LEVEL 20

//The number of denominations of currency available in the system 
#define NUM_DENOMS 8

/**
 * a structure to represent a price. One of the problems with the floating
 * point formats in C++ like float and double is that they have minor issues
 * of inaccuracy due to rounding. In the case of currency this really is
 * not acceptable so we introduce our own type to keep track of currency.
 **/
struct Price
{
public:
    // The dollar value, and the cents value for some price
    unsigned dollars, cents;
};

/**
 * data structure to represent a stock item within the system
 **/
class Stock
{
public:
    Stock();

    std::string id;

    std::string name;

    std::string description;

    Price price{};

    unsigned onHand;

    explicit Stock(std::vector<std::string> dataVector);
};

/**
 * the node that holds the data about an item stored in memory
 **/
class Node
{
public:
    Node();

    Node(const std::vector<std::string>& dataVector);

    ~Node();
    // pointer to the data held for the node 
    Stock* data;
    // pointer to the next node in the list 
    Node* next;
};

#endif // NODE_H