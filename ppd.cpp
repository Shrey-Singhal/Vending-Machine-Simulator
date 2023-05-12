#include <iostream>
#include "LinkedList.h"
#include "StockDatabase.h"
#include <fstream>
#include <vector>
#include <sstream>

using std::cout;
using std::endl;
using std::cin;


void displayMainMenu() {
    std::cout << "Main Menu:\n"
            "  1.Display Items\n"
            "  2.Purchase Items\n"
            "  3.Save and Exit\n"
            "Administrator-Only Menu:\n"
            "  4.Add Item\n"
            "  5.Remove Item\n"
            "  6.Display Coins\n"
            "  7.Reset Stock\n"
            "  8.Reset Coins\n"
            "  9.Abort Program\n"
            "Select your option (1-9):";
}

bool validateFileExistence(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

void parseStockFile(const std::string& filename, StockDatabase& db) {
    std::ifstream file(filename);
    std::string line;

    // Read lines from file and tokenize
    while (std::getline(file, line)) {
        std::vector<std::string> tokens;
        std::istringstream lineStream(line);
        std::string token;

        while (std::getline(lineStream, token, '|')) {
            tokens.push_back(token);
        }

        if (tokens.size() == 5) {
            db.addBack(tokens);
        }
    }

    file.close();
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
//        cout << "DEBUG\n";
//        cout << "Stock: " << argv[1];
//        cout << "Coins: " << argv[2];
        errorCode = EXIT_FAILURE;
    }
    // All args valid
    else {
        // Read stock file
        parseStockFile(argv[1], stockList);

        // Read coin file
        auto coinMap = Coin::parseCoinFile(argv[2]);

        // Main Loop
        std::string user_choice;
        bool valid_loop = true;

        while (valid_loop) {

            displayMainMenu();
            std::cin >> user_choice;

            // All options
            if (user_choice == "1") {
                stockList.displayStock();
            }
            else if (user_choice == "2") {
                stockList.purchaseItem(coinMap);
            }
            else if (user_choice == "3") {
                stockList.saveData(argv[1]);
                Coin::saveCoins(argv[2], coinMap);
                valid_loop = false;
            }
            else if (user_choice == "4") {
                stockList.addItem();
            }
            else if (user_choice == "5") {
                stockList.removeItem();
            }
            else if (user_choice == "6") {
                Coin::displayCoins(coinMap);
            }
            else if (user_choice == "7") {
                stockList.resetStock();
            }
            else if (user_choice == "8") {
                Coin::resetCoins(coinMap);
            }
            else if (user_choice == "9") {
                valid_loop = false;
            }
        }

    }

    exit(errorCode);
}







