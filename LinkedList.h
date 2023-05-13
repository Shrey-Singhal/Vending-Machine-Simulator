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
    size_t size() const;
    Node * get(int index);
    void sortByName();
    bool remove(const std::string &id);
    void resetStock();

    // the beginning of the list
    Node* head;

    bool getById(const std::string &id, Stock &fillNode);


private:

    // pointer to the last node in list
    Node* tail;
  
    // how many nodes are there in the list?
    size_t count;


};

#endif  // LINKEDLIST_H


