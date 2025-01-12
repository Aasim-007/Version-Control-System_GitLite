#pragma once
#include <iostream>
#include "CustomString.h"
using namespace std;


template <typename T>
class CustomList
{
    struct Node
    {
        // Try adding an index too
        T value;
        Node* next = NULL;
        Node* prev = NULL;
    };

    friend class BTree;
    Node* head = NULL;
    int capacity = 0;
public:

    CustomList();

    void insert_object(T val);

    bool find(T val);

    void Remove(T val);

    bool search_it(int k);

    void print();

    int getSize();

    T getElement(int inp);

    void operator=(CustomList& copyFrom);

    ~CustomList();
};
