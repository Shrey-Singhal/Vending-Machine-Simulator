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
    getline(cin, itemName);
    if (!itemName.empty() && !std::cin.eof()) {
        cout << "Enter the item description: ";
        string itemDescription;
        getline(cin, itemDescription);

        if (!itemDescription.empty() && !std::cin.eof()) {
            bool valid_loop = true;
            while (valid_loop) {

                cout << "Enter the price for the item: ";
                string itemPrice;
                getline(cin, itemPrice);
                long double ld;
                if ((std::istringstream(itemPrice) >> ld >> std::ws).eof() && itemPrice.find('.') != std::string::npos){
                    size_t dotIndex = itemPrice.find('.');
                    std::string centPart = itemPrice.substr(dotIndex + 1);
                    int cents = std::stoi(centPart);
                    if (cents % 5 == 0){
                        cout << "This item \"" << itemName << " - " << itemDescription
                             << "\" has now been added to the menu.\n" << endl;

                        vector<string> content;
                        content.push_back(newItemId);
                        content.push_back(itemName);
                        content.push_back(itemDescription);
                        content.push_back(itemPrice);
                        content.push_back(std::to_string(DEFAULT_STOCK_LEVEL));

                        addBack(content);
                        valid_loop = false;
                    }
                    else {
                        cout << "Error: the cents need to be a multiple of 5." << endl;
                    }
                }
                else{
                    cout << "Error: the price is not valid." << endl;
                }
            }
        }
    }


}

void StockDatabase::displayStock() {
    cout << endl;
    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID   |Name                                   | Available | Price" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    for (int i = 0; i < (int) stockList->size(); ++i) {
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
            "-------------\n";
    

    bool valid_loop = true;
    while (valid_loop){
        cout << "Please enter the id of the item you wish to purchase: ";
        std::string userChoice;
        std::getline(std::cin, userChoice);

        Stock userNode;
        if (stockList->getById(userChoice, userNode)) {
            // Item found
            std::cout << "You have selected \""
            << userNode.name << " - " << userNode.description
            << "\". This will cost you $ "
            << userNode.price.dollars << "."
            << std::setw(2) << std::setfill('0')
            << userNode.price.cents << std::setfill(' ')
            << ".\n";

            std::cout << "Please hand over the money - type in the value of each note/coin in cents.\n";
            std::cout << "Press enter or ctrl-d to cancel this purchase: " << std::endl;
            coinLoop(map, userNode);
            valid_loop = false;
        }
        else {
            if (userChoice.empty() || std::cin.eof()) {
                valid_loop = false;
            }
            else {
                cout << "Error: you did not enter a valid id. Please try again.\n";
            }
        }
    }

}

bool StockDatabase::removeItem() {
    cout << "Enter the item id of the item to remove from the menu: ";
    string itemId;
    getline(cin, itemId);
    bool result;

    if (!itemId.empty() && !std::cin.eof()){
        result = stockList->remove(itemId);

        if (!result) {
            cout << "Error: desired id was not found." << endl;
            cout << "The task Remove Item failed to run successfully.";
        }
        else {
            cout << "Item " << itemId << " has been removed from the system.";
        }

        cout << endl;
    }
    else{
        result = false;
    }


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
    Node* currNode = stockList->head;
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



bool StockDatabase::coinLoop(std::map<unsigned int, unsigned int> &map,
                             Stock &userNode) {
    unsigned costInCents = userNode.price.dollars * 100;
    costInCents += userNode.price.cents;
    bool endLoop = false;
    bool return_val = true;

    while (costInCents > 0 && !endLoop) {
        std::cout << "You still need to give us ";
        Coin::printPrice(costInCents);
        std::cout << ": " << std::setfill(' ') ;

        string input;
        if (std::cin.eof()) {
            endLoop = true;
        }
        std::getline(std::cin, input);

        if (input.find_first_not_of( "0123456789" ) == std::string::npos && !endLoop && !input.empty()){
            unsigned userInput = std::stoul(input);
        // Found denomination
            if (map.count((int) userInput) > 0) {
                // Check if change can be returned
                int valAfterCoin = (int) costInCents - userInput;

                if (valAfterCoin < 0) {
                    cout << "Here is your ";
                    cout << userNode.name;
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
            
            else if (!endLoop){
                std::cout << "Error: ";
                Coin::printPrice(costInCents);
                std::cout << " is not a valid denomination of money. Please try again.\n";
            }
            
        }
        else {
            if (input.empty() || std::cin.eof()) {
                endLoop = true;
            }
            else {
                cout << "Error: you did not enter a valid int. Please try again." << endl;
                return_val = false;
            }
        }

    }

    if (costInCents <= 0) {
        std::cout << "Successful Purchase!" << std::endl;
    }

    return return_val;

}

bool StockDatabase::dispenseCoins(std::map<unsigned, unsigned>& coins, unsigned amount, bool checkOnly) {
    std::cout << " and your change of ";
    Coin::printPrice(amount);
    std::cout << ":";
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
