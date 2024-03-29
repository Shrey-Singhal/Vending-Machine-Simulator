#include "Node.h"

Node::Node(const std::vector<std::string>& dataVector){
    data = new Stock(dataVector);
    next = nullptr;
}

Node::Node() {
    data = nullptr;
    next = nullptr;
}

Node::~Node(){
    delete(data);
}

Stock::Stock(std::vector<std::string> dataVector) {
    id = dataVector[0];
    name = dataVector[1];
    description = dataVector[2];
    double priceValue = std::stod(dataVector[3]);
    price.dollars = (int) priceValue;
    price.cents = (int) (priceValue - price.dollars) * 100;
    onHand = (unsigned int) std::stoi(dataVector[4]);

}

Stock::Stock() = default;

