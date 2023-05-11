#include <iostream>
#include "LinkedList.h"
#include "StockDatabase.h"
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>

using std::cout;
using std::endl;
using std::string;
using std::cin;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/

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
    cout << "Select your option (1-9): ";
}

bool validateFileExistence(const string& filename) {
    std::ifstream file(filename);
    return file.good();
}

std::vector<std::vector<std::string>> parseInput(std::ifstream& file) {
    std::vector<std::vector<std::string>> result;
    std::string line;

    // Read lines from file and tokenize
    while (std::getline(file, line)) {
        std::vector<std::string> tokens;
        std::istringstream lineStream(line);
        std::string token;

        while (std::getline(lineStream, token, '|')) {
            tokens.push_back(token);
        }

        result.push_back(tokens);
    }

    return result;
}

int main(int argc, char *argv[])
{
    int errorCode = EXIT_SUCCESS;
    StockDatabase stockList;

    if (argc < 3) {
        cout << "Usage: ./ppd <stockfile> <coinsfile>\n" << endl;
        errorCode = EXIT_FAILURE;
    }
    else if (!validateFileExistence(argv[1]) || !validateFileExistence(argv[2])) {
        cout << "One or more of the provided files is invalid. Please provide a valid filename.\n" << endl;
        cout << "DEBUG\n";
        cout << "Stock: " << argv[1];
        cout << "Coins: " << argv[2];
        errorCode = EXIT_FAILURE;
    }
    // All args valid
    else {
        // Read stock file
        std::ifstream infile(argv[1], std::ios::binary);
        auto parsedLines = parseInput(infile);
        infile.close();

        for (const auto& line:parsedLines) {
            if (line.size() == 5) {
                stockList.addBack(line);
            }
        }

        // Read coin file


        // Main Loop
        string user_choice;
        bool valid_loop = true;

        while (valid_loop) {

            displayMainMenu();
            cin>>user_choice;

            if (user_choice == "1") {
                stockList.displayStock();
            }
            else if (user_choice == "3") {
                stockList.saveData(argv[1]);
                valid_loop = false;
            }
            else if (user_choice == "4") {
                stockList.addItem();
            }
            else if (user_choice == "5") {
                cout << endl;
                stockList.removeItem();
            }
            else if (user_choice == "7") {
                cout << endl;
                stockList.resetStock();
                cout << "All stock has been reset to the default level of "
                << DEFAULT_STOCK_LEVEL << endl;
                cout << endl;
            }
            else if (user_choice == "9") {
                valid_loop = false;
            }
        }

    }

    return errorCode;
}







