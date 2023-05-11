#include "Node.h"

Node::Node(){
    data = nullptr;
    next = nullptr;
}

Node::~Node(){
    delete(data);
    delete(next);
}

Stock::Stock(std::vector<std::string> data_vector) {
    id = data_vector[0];
    name = data_vector[1];
    description = data_vector[2];
    double priceValue = std::stod(data_vector[3]);
    price.dollars = (int) priceValue;
    price.cents = (int) ((priceValue - price.dollars) * 100);
    on_hand = (unsigned int) std::stoi(data_vector[4]);
}