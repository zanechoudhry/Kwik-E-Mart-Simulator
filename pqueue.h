//Zane Choudhry
//zchoudhry
//pqueue.h

#ifndef PQUEUE_H
#define PQUEUE_H
#include <iostream>
#include "cust.h"
using namespace std;

class Pqueue {
public:
    Pqueue();
    bool empty(); // see if the queue is empty
    int length() {return m_size;}; // return the size of the queue
    int first_priority(); // return the first priority in the queue
    void enqueue(Cust* Cust, int priority); // enqueue the cust based on priority
    Cust* dequeue(); // deque the cust that has lowest priority
private:
    class Node {
    public:
        Node (int priority, Cust* cust, Node *next) {
            m_priority = priority;
            m_cust = cust;
            m_next = next;
        }
        
        int m_priority;
        Cust* m_cust;
        Node* m_next;
    };
    
    int m_size = 0;
    Node* m_head;
};

#endif
