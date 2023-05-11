#include "StockDatabase.h"
#include <iomanip>
#include <iostream>
#include <fstream>

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

void StockDatabase::addBack(std::vector<std::string> stockLine) {
    stockList->addBack(stockLine);
    stockList->sortByName();
}

void StockDatabase::addItem() {
    string newItemId = "I";
    int noOfZeroes = 4 -  std::to_string(stockList->size() + 1).length();
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

    cout << "This item \"" << itemName << " - " << itemDescription << "\" has now been added to the menu.\n" << endl;

    vector<string> content;
    content.push_back(newItemId);
    content.push_back(itemName);
    content.push_back(itemDescription);
    content.push_back(itemPrice);
    content.push_back(std::to_string(DEFAULT_STOCK_LEVEL));

    stockList->addBack(content);
}

void StockDatabase::displayStock() {
    cout << endl;
    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID   |Name                                   | Available | Price" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    cout << endl;

    for (int i = 0; i < stockList->size(); ++i) {
        cout << std::setfill(' ');
        cout << left << std::setw(5) << stockList->get(i).id << "|";
        cout << left << std::setw(39) << stockList->get(i).name << "|";
        cout << left << std::setw(10) << stockList->get(i).on_hand << " |";
        cout << std::fixed << std::setprecision(3)
        << "$ " << stockList->get(i).price.dollars << ".";
        cout << std::setfill('0') << std::setw(2) <<
        stockList->get(i).price.cents << endl;
    }

    cout << endl;
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

    cout << endl;
    return result;
}

void StockDatabase::saveData(const std::string& fileName) {
    // Open the file in write mode to clear all the content
    std::ofstream outFile(fileName, std::ios::out | std::ios::trunc);

    outFile.close();

    // Reopen the file in append mode to write new content
    outFile.open("stock.dat", std::ios::out | std::ios::app);

    // Write new content to the file
    for (int i = 0; i < stockList->size(); ++i) {
        outFile << stockList->get(i).id <<"|" << stockList->get(i).name << "|" << stockList->get(i).description << "|" <<
             stockList->get(i).price.dollars << "." << stockList->get(i).price.cents << "|" << stockList->get(i).on_hand;
        if (i < stockList->size() - 1) {
            outFile << endl;
        }
    }

    outFile.close();
}

void StockDatabase::resetStock() {
    stockList->resetStock();
}