#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
   tail = nullptr;
   count = 0;

   // TODO
}

LinkedList::~LinkedList() {
    // TODO
}

void LinkedList::addBack(std::vector<std::string> stock_data) {
    Node* newNode = new Node();
    Stock* data = new Stock(stock_data);   
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


Stock& LinkedList::get(int i) {
    Node* current = this->head;
    int x = 0;

    while (x < i && current != nullptr) {

        x += 1;
        current = current->next;
    }
    return *(current->data);
}
int LinkedList::size() {
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
    if (index < 0 || index >= size()) {
        return;
    }

    Node* current = head;
    Node* prev = nullptr;
    for (int i = 0; i < index; ++i) {
        prev = current;
        current = current->next;
    }

    if (prev == nullptr) {
        // remove head node
        head = current->next;
    } else {
        prev->next = current->next;
    }

    delete current;
    this->count -= 1;
}