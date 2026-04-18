#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

template <typename T>
class DoublyLinkedList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void pushFront(const T& value);
    void pushBack(const T& value);
    void insert(int index, const T& value);

    T popFront();
    T popBack();
    void remove(int index);

    T getFront() const;
    T getBack() const;
    T get(int index) const;

    int getSize() const;
    bool isEmpty() const;
    void clear();

    void print() const;
    void printReverse() const;
};

#include "DoublyLinkedList.cpp"

#endif // DOUBLY_LINKED_LIST_H