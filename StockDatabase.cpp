#include "StockDatabase.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <map>

using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::cin;
using std::ws;
using std::left;

StockDatabase::StockDatabase() {
    stockList = new LinkedList();
}

StockDatabase::~StockDatabase() {
    delete(stockList);
}

void StockDatabase::addBack(const std::vector<std::string>& stockLine) {
    stockList->addBack(stockLine);
    stockList->sortByName();
}

void StockDatabase::addItem() {
    string newItemId = "I";
    int noOfZeroes = 4 -  (int) std::to_string(stockList->size() + 1).length();
    for (int i = 0; i < noOfZeroes; ++i) {
        newItemId += "0";
    }
    newItemId += std::to_string(stockList->size() + 1);

    // Read in new item info
    cout << "The id of the new stock will be: " << newItemId << endl;
    cout << "Enter the item name: ";
    string itemName;
    getline(cin >> ws, itemName);

    cout << "Enter the item description: ";
    string itemDescription;
    getline(cin >> ws, itemDescription);

    cout << "Enter the price for the item: ";
    string itemPrice;
    getline(cin >> ws, itemPrice);

    cout << "This item \"" << itemName << " - " << itemDescription
    << "\" has now been added to the menu.\n" << endl;

    vector<string> content;
    content.push_back(newItemId);
    content.push_back(itemName);
    content.push_back(itemDescription);
    content.push_back(itemPrice);
    content.push_back(std::to_string(DEFAULT_STOCK_LEVEL));

    addBack(content);
}

void StockDatabase::displayStock() {
    cout << endl;
    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID   |Name                                   | Available | Price" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    for (int i = 0; i < stockList->size(); ++i) {
        auto currStock = stockList->get(i);
        cout << std::setfill(' ');
        cout << left << std::setw(5)
        << currStock->data->id << "|";
        cout << left << std::setw(39)
        << currStock->data->name << "|";
        cout << left << std::setw(10)
        << currStock->data->onHand << " |";
        cout << std::fixed << std::setprecision(3)
        << "$ " << currStock->data->price.dollars << ".";
        cout << std::setfill('0') << std::setw(2) <<
        currStock->data->price.cents << endl;
    }

    cout << endl;
}

void StockDatabase::purchaseItem(std::map<unsigned, unsigned>& map) {
    cout << "Purchase Item\n"
            "-------------\n"
            "Please enter the id of the item you wish to purchase:";

    std::string userChoice;
    std::cin >> userChoice;

    Node userNode;
    if (stockList->getById(userChoice, userNode)) {
        // Item found
        std::cout << "You have selected \""
        << userNode.data->name << " - " << userNode.data->description
        << "\". This will cost you $ "
        << userNode.data->price.dollars << "."
        << std::setw(2) << std::setfill('0')
        << userNode.data->price.cents << std::setfill(' ')
        << ".\n";

        std::cout << "Please hand over the money - type in the value of each note/coin in cents.\n";
        std::cout << "Press enter or ctrl-d to cancel this purchase: " << std::endl;
        coinLoop(map, userNode);
    }
    else {
        std::cout << "Please select a valid ID.\n";
    }

}

bool StockDatabase::removeItem() {
    cout << "Enter the item id of the item to remove from the menu: ";
    string itemId;
    getline(cin >> ws, itemId);

    bool result = stockList->remove(itemId);

    if (!result) {
        cout << "Error: desired id was not found." << endl;
        cout << "The task Remove Item failed to run successfully.";
    }
    else {
        cout << "Item " << itemId << " has been removed from the system.";
    }

    cout << endl;
    return result;
}

void StockDatabase::saveData(const std::string& fileName) {
    // Open the file in write mode to clear all the content
    std::ofstream outFile(fileName, std::ios::out | std::ios::trunc);
    if (!outFile) {
        std::cerr << "can't open output file" << endl;
    }
    outFile.close();

    // Reopen the file in append mode to write new content
    outFile.open(fileName, std::ios::out | std::ios::app);

    // Write new content to the file
    Node* currNode = stockList->get(0);
    while (currNode != nullptr) {
        outFile << currNode->data->id << "|";
        outFile << currNode->data->name << "|";
        outFile << currNode->data->description << "|";
        outFile << currNode->data->price.dollars << ".";
        outFile << std::setw(2);
        outFile << std::setfill('0');
        outFile << currNode->data->price.cents << "|";
        outFile << std::setfill(' ');
        outFile << currNode->data->onHand;
        outFile << endl;

        currNode = currNode->next;
    }


    outFile.close();
}

void StockDatabase::resetStock() {
    stockList->resetStock();
    cout << "All stock has been reset to the default level of "
         << DEFAULT_STOCK_LEVEL << endl;
    cout << endl;
}



bool StockDatabase::coinLoop(std::map<unsigned, unsigned> &map, Node& userNode) {
    unsigned costInCents = userNode.data->price.dollars * 100;
    costInCents += userNode.data->price.cents;
    bool endLoop = false;

    while (costInCents > 0 && !endLoop) {
        std::cout << "You still need to give us ";
        Coin::printPrice(costInCents);
        std::cout << ": " << std::endl << std::setfill(' ') ;

        unsigned userInput;
        if (std::cin.eof()) {
            endLoop = true;
        }
        std::cin >> userInput;


        // Found denomination
        if (map.count((int) userInput) > 0) {
            // Check if change can be returned
            int valAfterCoin = (int) costInCents - userInput;

            if (valAfterCoin < 0) {
                endLoop = !dispenseCoins(map, -valAfterCoin, false);
            }


            if (!endLoop){
                // Subtract from map if available
                map[userInput] += 1;

                if (valAfterCoin >= 0){
                    costInCents -= userInput;
                }
                else {
                    costInCents = 0;
                }
            }
        }
        else if (endLoop){
            std::cout << "Error: ";
            Coin::printPrice(costInCents);
            std::cout << " is not a valid denomination of money. Please try again.\n";
        }

    }

    if (costInCents <= 0) {
        std::cout << "Successful Purchase!" << std::endl;
    }

    return true;

}

bool StockDatabase::dispenseCoins(std::map<unsigned, unsigned>& coins, unsigned amount, bool checkOnly) {
    std::cout << "Your change of ";
    Coin::printPrice(amount);
    std::cout << ":" << std::endl;
    bool canBeDispensed;

    std::map<unsigned, unsigned> changeCoins;

    // Iterate over the denominations in descending order
    bool stopLoop = false;
    for (auto it = coins.rbegin(); it != coins.rend() && !stopLoop; ++it) {

        unsigned denomination = it->first;
        unsigned quantity = it->second;

        // Calculate the number of coins required for the current denomination
        unsigned numCoins = std::min(amount / denomination, quantity);

        if (numCoins > 0){
            changeCoins[denomination] = numCoins;
        }

        // Update the remaining amount
        amount -= numCoins * denomination;

        // Break the loop if the amount becomes zero
        if (amount == 0) {
            stopLoop = true;
        }
    }

    // If the amount is still not zero, it cannot be dispensed with the available coins
    if (amount != 0) {
        canBeDispensed = false;
        std::cout << "Change is not available for that amount of money. Please try again.";
    }
    // Print and dispense change
    else {
        canBeDispensed = true;
        for (auto & changeCoin : changeCoins) {
            unsigned denomination = changeCoin.first;
            unsigned& quantity = changeCoin.second;
            Coin::printPrice(denomination);
            std::cout << " x " << quantity << " ";

            if (!checkOnly) {
                coins[denomination] -= quantity;
            }
        }

        std::cout << std::endl;
    }

    return canBeDispensed;
}

void Coin::printPrice(const unsigned& costInCents) {
    std::cout << "$" << costInCents / 100 << "."
              << std::setw(2) << std::setfill('0')
              << costInCents % 100 << std::setfill(' ');
}
