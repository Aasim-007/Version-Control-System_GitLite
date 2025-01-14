#include <iostream>
#include "CustomList.h"
#include "CustomString.h"
using namespace std;

template <typename T>
CustomList<T>::CustomList() {}

template <typename T>
void CustomList<T>::insert_object(T val)
{

    if (head != NULL)
    {
        Node* temp = head;
        while (temp->next != head)
        {
            temp = temp->next;
        }
        Node* this_one = new Node;
        this_one->value = val;

        temp->next = this_one;
        this_one->prev = temp;
        head->prev = this_one;
        this_one->next = head;
    }
    else
    {
        head = new Node;
        head->value = val;
        head->next = head;
        head->prev = head;
    }
    capacity += 1;

}

template <typename T>
bool CustomList<T>::find(T val) {
    Node* temp = head;
    while (temp) {
        if (temp->value == val) return 1;
        temp = temp->next;
    }
    return 0;
}

template <typename T>
void CustomList<T>::Remove(T val)
{
    Node* ptr = head;

    if (ptr->value == val)
    {
        Node* temp = head;
        head = head->next;
        temp->prev->next = head;
        head->prev = temp->prev;
        delete temp;
        capacity--;
        return;
    }

    while (ptr->next != head)
    {
        if (ptr->value == val)
        {
            Node* sav = ptr->prev;
            ptr->prev->next = ptr->next;
            ptr->next->prev = sav;
            capacity -= 1;
            break;
        }
        ptr = ptr->next;
    }

}

template <typename T>
bool CustomList<T>::search_it(int k)
{
    Node* ptr = head;
    while (ptr->next != head)
    {
        if (ptr->value == k)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

template <typename T>
void CustomList<T>::print()
{
    if (head == NULL)
    {
        cout << "\nEmpty List!!\n";
        return;
    }
    int cap = capacity;
    Node* ptr = head;
    while (cap > 0)
    {
        if (ptr->value != -1)
        {
            if (T == CustomString)
                ptr->value.print();

            else cout << ptr->value;
            cout << '\n';
        }
        ptr = ptr->next;
        cap -= 1;
    }
}

template <typename T>
int CustomList<T>::getSize()
{
    return capacity;
}

template <typename T>
T CustomList<T>::getElement(int inp)
{
    int i = 0;
    Node* temp = head;

    while (i != inp)
    {
        temp = temp->next;
        i += 1;
    }
    return temp->value;
}

template <typename T>
void CustomList<T>::operator=(CustomList& copyFrom) {
    if (head) {
        Node* tempHead = head;
        do {
            Node* tempNext = head->next;
            delete head;
            head = tempNext;
        } while (head != tempHead);
        head = nullptr;
    }
    capacity = 0;

    Node* copyTempHead = copyFrom.head;
    while (capacity < copyFrom.capacity) {
        this->insert_object(copyTempHead->value);
        copyTempHead = copyTempHead->next;
    }
}

template <typename T>
CustomList<T>::~CustomList() {
    if (head) {
        Node* tempHead = head;
        do {
            Node* tempNext = head->next;
            delete head;
            head = tempNext;
        } while (head != tempHead);
    }
}