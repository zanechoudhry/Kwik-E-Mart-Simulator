//Zane Choudhry
//zchoudhry
//pqueue.cpp
#include <iostream>
#include "pqueue.h"
#include "cust.h"

using namespace std;

Pqueue::Pqueue() {
    m_head = NULL;
}
bool Pqueue::empty() {
    return (m_head == NULL);
}

int Pqueue::first_priority() { // if queue is empty then return -1
    if (m_head != NULL) {
        return (m_head->m_priority);
    }
    else {
        return -1;
    }
}

void Pqueue::enqueue(Cust *cust, int priority) { // enqueue customer based on priority
    if (m_head == NULL || m_head->m_priority > priority) {
        m_head = new Node (priority, cust, m_head); // insert cust
    }
    
    else {
        Node *node = m_head;
        while (node->m_next != NULL && node->m_next->m_priority <= priority) {
            node = node->m_next; // traverse the queue
        }
        node->m_next = new Node (priority, cust, node->m_next); // insert cust
    }
    m_size++;
}

Cust* Pqueue::dequeue() { // return cust and decrement the size of the queue
    Cust* result = NULL;
    
    if (!empty()) {
        result = m_head->m_cust;
        Node *deleteNode = m_head;
        m_head = m_head->m_next;
        delete deleteNode;
        m_size--;
    }
    return result;
}
