#include <iostream>
#include "LinkedList.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/

void displayMainMenu();
vector<string> tokenize(string s, char delimeter);
void displayStock(LinkedList* LL);
void addItem(LinkedList* LL);
void removeItem(LinkedList* LL);

int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODO

    // open stock.dat file
    ifstream infile("stock.dat", ios::binary);

    string line;
    vector<string> content;
    LinkedList* LL = new LinkedList;
    // convert the content in the .dat file to a vector and add that vector to the linked list.
    while (getline(infile, line)) {
        content = tokenize(line, '|');
        LL->addBack(content);
    }

    // Close the file
    infile.close();
    LL->sortByName();

    string user_choice;
    bool valid_loop = true;

    while (valid_loop) {
        displayMainMenu();
        cin>>user_choice;
        if (user_choice == "1") {
            displayStock(LL);
        }
        else if (user_choice == "9") {
            valid_loop = false;
        }
        else if (user_choice == "4") {
            cout << endl;
            addItem(LL);
        }
        else if (user_choice == "5") {
            cout << endl;
            removeItem(LL);
        }
    }

 
    return EXIT_SUCCESS;
}

void displayMainMenu() {
    cout << "Main Menu:" << endl;
    cout << "  1.Display Items" << endl;
    cout << "  2.Purchase Items" << endl;
    cout << "  3.Save and Exit" << endl;
    cout << "Administrator-Only Menu:" << endl;
    cout << "  4.Add Item" << endl;
    cout << "  5.Remove Item" << endl;
    cout << "  6.Display Coins" << endl;
    cout << "  7.Reset Stock" << endl;
    cout << "  8.Reset Coins" << endl;
    cout << "  9.Abort Program" << endl;
    cout << "Select your option(1-9): ";
}

vector<string> tokenize(string s, char delimeter) {
    vector<string> tokens;
    // stringstream ss(s);
    string token;

    string::size_type i;
    for (i = 0; i < s.length(); i++) {
        if (s[i] != delimeter) {
            token += s[i];
        }
        else {
            tokens.push_back(token);
            token.clear();
        }
    }
    tokens.push_back(token);
    return tokens;
}



void displayStock(LinkedList* LL) {
    cout << endl;
    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID   |Name                                   | Available | Price" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    cout << endl;
    for (int i = 0; i < LL->size(); ++i) {
        cout << left << setw(5) << LL->get(i).id << "|";
        cout << left << setw(39) << LL->get(i).name << "|";
        cout << left << setw(10) << LL->get(i).on_hand << " |";
        cout << fixed << setprecision(2) << "$ " << LL->get(i).price.dollars << "." << LL->get(i).price.cents << endl;
    }

    cout << endl;
}

void addItem(LinkedList* LL) {
    string newItemId = "I";
    int noOfzeroes = 4 -  to_string(LL->size() + 1).length();
    for (int i = 0; i < noOfzeroes; ++i) {
        newItemId += "0";
    }
    newItemId += to_string(LL->size() + 1);
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

    cout << "This item \"" << itemName << " - " << itemDescription << "\" has now been added to the menu." << endl;
    cout << endl;
    vector<string> content;
    content.push_back(newItemId);
    content.push_back(itemName);
    content.push_back(itemDescription);
    content.push_back(itemPrice);
    content.push_back(to_string(DEFAULT_STOCK_LEVEL));
    LL->addBack(content);
    LL->sortByName();

}

void removeItem(LinkedList* LL) {
    cout << "Enter the item id of the item to remove from the menu: ";
    string itemId;
    getline(cin >> ws, itemId);

    bool itemFound = false;
    int i = 0;
    while (i < LL->size()) {
        if (LL->get(i).id == itemId) {
            cout << "\"" << LL->get(i).id << " - " << LL->get(i).name << " - " << LL->get(i).description << "\" has been removed from the system.";
            LL->remove(i);
            itemFound = true;
        } else {
            ++i;
        }
    }

    if (!itemFound) {
        cout << "Error: desired id was not found." << endl;
        cout << "The task Remove Item failed to run successfully.";
    }

    cout << endl;
}