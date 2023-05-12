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

    void purchaseItem(std::unordered_map<unsigned, unsigned >& map);

    void purchaseItem(std::map<unsigned int, unsigned int> &map);

    void saveCoins(const std::string &fileName,
                   const std::map<unsigned int, unsigned int>& map);

    void resetCoins(std::map<unsigned int, unsigned int> &coinMap);

private:
    LinkedList* stockList;
    std::map<unsigned, unsigned>* coinList;

    bool dispenseCoins(const std::map<unsigned int, unsigned int> &coins,
                       unsigned int amount, bool checkOnly);

    static bool
    dispenseCoins(std::map<unsigned int, unsigned int> &coins,
                  unsigned int amount,
                  bool checkOnly);

    bool coinLoop(std::map<unsigned int, unsigned int> &map, Node &userNode);

};
#endif //APT_STOCKDATABASE_H
