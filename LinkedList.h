#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...
    void addBack(std::vector<std::string> stock_data);
    int size();
    Stock& get(int i); 
    void sortByName();
    void remove(int index);
    void resetStock();

private:
    // the beginning of the list
    Node* head;

    // pointer to the last node in list
    Node* tail;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


