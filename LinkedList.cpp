#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   count = 0;
}

LinkedList::~LinkedList() {
    Node* currNode = head;
    Node* prevNode;

    while (currNode != nullptr) {
        prevNode = currNode;
        currNode = currNode->next;
        delete(prevNode);
    }
}

void LinkedList::addBack(std::vector<std::string> stock_data) {
    Node* newNode = new Node();
    auto* data = new Stock(stock_data);

    newNode->data = data;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }

    this->count += 1;
}


Stock& LinkedList::get(int index) {
    Node* current = this->head;
    int x = 0;

    while (x < index && current != nullptr) {
        x += 1;
        current = current->next;
    }
    return *(current->data);
}
int LinkedList::size() const {
    return (int)count;
}

void LinkedList::sortByName() {
    bool sorted = false;
    while (!sorted) {
        sorted = true;
        Node* current = head;
        while (current->next != nullptr) {
            Stock* currentData = current->data;
            Stock* nextData = current->next->data;
            if (currentData->name > nextData->name) {
                // Swap the stocks
                Stock* temp = currentData;
                current->data = nextData;
                current->next->data = temp;
                sorted = false;
            }
            current = current->next;
        }
    }
}

void LinkedList::remove(int index) {
    Node* current = head;
    Node* prev = nullptr;
    int i = 0; 
    while (current != nullptr && i < index) {
        prev = current;
        current = current->next;
        i++;
    }

    if (current != nullptr) {
        if (prev == nullptr) {
            head = current->next;
        } else {
            prev->next = current->next;
        }

        delete current;
        this->count -= 1;
    }
}

void LinkedList::resetStock() {
    Node* current = head;

    while (current != nullptr) {
        Stock* currentData = current->data;
        currentData->on_hand = DEFAULT_STOCK_LEVEL;
    
        current = current->next;
    }
    
}