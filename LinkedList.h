#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"


class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...
    void addBack(const std::vector<std::string> &stockData);
    int size() const;
    Stock& get(int index);
    void sortByName();
    bool remove(const std::string &id);
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


