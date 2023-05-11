#ifndef APT_STOCKDATABASE_H
#define APT_STOCKDATABASE_H

#include <unordered_map>
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

private:
    LinkedList* stockList;

    bool coinLoop(std::unordered_map<unsigned, unsigned> &map, Node& userNode);
};
#endif //APT_STOCKDATABASE_H
