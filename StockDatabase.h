#ifndef APT_STOCKDATABASE_H
#define APT_STOCKDATABASE_H

#include <unordered_map>
#include <map>
#include "LinkedList.h"

/*
 * Represents a more robust way to interface with the linked list
 */
class StockDatabase {
public:
    StockDatabase();
    ~StockDatabase();

    void addBack(const std::vector<std::string>& stockLine);
    void addItem();
    void displayStock();
    bool removeItem();
    void saveData(const std::string& fileName);
    void resetStock();

    void purchaseItem(std::map<unsigned int, unsigned int> &map);

private:
    LinkedList* stockList;

    static bool
    dispenseCoins(std::map<unsigned int, unsigned int> &coins,
                  unsigned int amount,
                  bool checkOnly);

    static bool coinLoop(std::map<unsigned int, unsigned int> &map, Stock &userNode);

    bool
    coinLoop(std::map<unsigned int, unsigned int> &map, const Stock &userNode);
};
#endif //APT_STOCKDATABASE_H
