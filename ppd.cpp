#include <iostream>
#include "LinkedList.h"
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/

void displayMainMenu();
vector<string> tokenize(string s, char delimeter);
void displayStock(LinkedList LL);
int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODO

    // open stock.dat file
    ifstream infile("stock.dat", ios::binary);

    string line;
    vector<string> content;
    LinkedList LL;
    // convert the content in the .dat file to a vector and add that vector to the linked list.
    while (getline(infile, line)) {
        content = tokenize(line, '|');
        LL.addBack(content);
    }

    // Close the file
    infile.close();
    LL.sortByName();

    string user_choice;
    bool valid_loop = true;

    while (valid_loop) {
        displayMainMenu();
        cin>>user_choice;
        if (user_choice == "1") {
            displayStock(LL);
        }
        else if (user_choice == "8") {
            valid_loop = false;
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
    cout << "  6.Reset Stock" << endl;
    cout << "  7.Reset Coins" << endl;
    cout << "  8.Abort Program" << endl;
    cout << "Select your option(1-9): ";
}

vector<string> tokenize(string s, char delimeter) {
    vector<string> tokens;
    // stringstream ss(s);
    string token;

    // while (getline(ss, token, delimeter)) {
    //     tokens.push_back(token);
        
    // }
    // return tokens;
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



void displayStock(LinkedList LL) {
    cout << endl;
    cout << "Items Menu" << endl;
    cout << "----------" << endl;
    cout << "ID   |Name                                   | Available | Price" << endl;
    cout << "-------------------------------------------------------------------" << endl;

    for (int i = 0; i < LL.size(); ++i) {
        cout << LL.get(i).id << "|" << LL.get(i).name << "                 |" << 
        LL.get(i).on_hand << "         |" << "$ " << LL.get(i).price.dollars << "." << LL.get(i).price.cents << endl;
    }

    cout << endl;
}