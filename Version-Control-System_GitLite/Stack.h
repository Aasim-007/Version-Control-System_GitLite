#pragma once
#include <iostream>
using namespace std;


template <class T>
class Stack {
    struct sNode {
        T data;
        sNode* next;
        sNode(T data) : data(data) { next = nullptr; }
    };
    sNode* head = nullptr;
public:
    void push(T element) {
        sNode* _add = new sNode(element);
        if (head) {
            _add->next = head;
            head = _add;
        }
        else head = _add;
    }

    bool isEmpty() { return (head ? 0 : 1); }

    void pop() {
        if (isEmpty()) return;
        else {
            sNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    T top() { return head->data; }

    ~Stack() {
        /*while (head) {
            sNode* temp = head->next;
            delete head;
            head = temp;
        }*/
    }

};