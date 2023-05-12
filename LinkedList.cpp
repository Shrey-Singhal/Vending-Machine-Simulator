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

void LinkedList::addBack(const std::vector<std::string>& stockData) {
    Node* newNode = new Node(stockData);
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


Node* LinkedList::get(int index) {
    Node* current = this->head;
    int x = 0;

    while (x < index && current != nullptr) {
        x += 1;
        current = current->next;
    }
    return current;
}

size_t LinkedList::size() const {
    return count;
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

bool LinkedList::remove(const std::string& id) {
    Node* current = head;
    Node* prev = nullptr;
    bool found = false;
    while (current != nullptr && !found) {
        if (current->data->id != id){
            prev = current;
            current = current->next;
        }
        else {
            found = true;
            if (prev == nullptr) {
                head = current->next;
            } else {
                prev->next = current->next;
            }


        }
    }

    if (found) {
        delete current;
        this->count -= 1;
    }
    return found;
}

bool LinkedList::getById(const std::string& id, Node& fillNode) {
    Node* current = head;
    bool found = false;
    while (current != nullptr && !found) {
        if (current->data->id != id){
            current = current->next;
        }
        else {
            found = true;
            fillNode = *current;
        }
    }
    return found;
}

void LinkedList::resetStock() {
    Node* current = head;

    while (current != nullptr) {
        Stock* currentData = current->data;
        currentData->onHand = DEFAULT_STOCK_LEVEL;
    
        current = current->next;
    }

    delete(current);
}