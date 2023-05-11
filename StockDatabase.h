#ifndef APT_STOCKDATABASE_H
#define APT_STOCKDATABASE_H
#include "LinkedList.h"

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

private:
    LinkedList* stockList;
};
#endif //APT_STOCKDATABASE_H
